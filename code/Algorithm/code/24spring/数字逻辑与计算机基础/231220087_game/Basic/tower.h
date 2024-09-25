#ifndef TOWER_H
#define TOWER_H
#include "Tool/healthsystem.h"
#include "qmovie.h"
#include "role.h"
#include <Qmutex>
#include <QMutexLocker>
#include <Basic/globalattribute.h>

class HealthSystem;
class Enemy;
enum TowerType{RemoteTower, MeleeTower};


class Tower:public Role{
    friend class TowerManager;

    int current_coin = 0;// 持有费用，撤退时返还30%
    int levelUP_material = 5; // 升级费用
    int cost = 5;// 部署费用
    bool levelUP_able = false; // 是否可以升级

    bool skillTime = false;// 是否在技能释放期间
    bool release_skill_able = false;
    int attack_counter = 0;// 攻击次数
    int hit_counter = 0;// 受击次数
    int skill_release_counter = 0;
    int skill_interval_time = -1;

    TowerType type;
    TowerName name;
    bool blocking = false; // 是否正在阻挡
    std::shared_ptr<Enemy> blockList = NULL; // 阻挡的敌人列表
    bool hasDropped = false;

protected:
    QTimer* timer;



public:
    Tower(int x, int y, TowerType t = MeleeTower):Role(x,y), type(t){
        // timer = new QTimer();
        // connect(timer,&QTimer::timeout,this,&Tower::setRelease_skill_able_slot);
        // timer->setInterval(2000);
        // timer->start();
    }

    // 访问
    TowerType getType()const{return type; }
    TowerName getName() const {return name; }
    bool getBlocking()const{return blocking; }
    bool getHasDropped()const{return hasDropped; }
    std::shared_ptr<Enemy> getBlockList()const{return blockList; }
    QRect getBoundingBox() override{int size = 80; QRect boundingBox(this->getPosition().pos.x() - size * 0.5,this->getPosition().pos.y() - size, size,size);return boundingBox;}
    int getAttack_counter()const{return attack_counter; }
    int getHit_counter() const{return hit_counter; }
    bool getSkillTime()const{return skillTime;}

    int getCurrent_coin() const {return current_coin;}
    int getLevelUP_material() const {return levelUP_material;}
    int getCost()const {return cost;}
    bool getLevelUP_able()const{return levelUP_able;}
    bool getRelease_skill_able()const{return release_skill_able;}
    int getSkill_release_counter() const {return skill_release_counter; }
    int getSkill_interval_time() const {return skill_interval_time; }

    // 获得增益后的攻击力、攻击间隔
    int getTrueAttackPower();
    int getTrueAttackInterval();

    // 修改
    void setName(TowerName a){name = a; }
    void setSkillTime(bool a){skillTime = a;}
    void setBlocking(bool a){ blocking = a; }
    void setHasDropped(bool a){hasDropped = a; }
    void setBlockList(std::shared_ptr<Enemy> e); // enemy的blocked被设置为t
    void removeBlockList(std::shared_ptr<Enemy> e){ blockList = NULL; }
    void setAttack_counter(int x){attack_counter = x; }
    void setHit_counter(int x){hit_counter = x;}
    void setType(TowerType t) {type = t; }
    void setLevelUP_material(int x) {levelUP_material = x;}
    void changeCurrent_coin(int x){current_coin += x; }
    void setLevelUP_able(bool a){levelUP_able = a; }
    void setCost(int x){cost = x; }
    void setRelease_skill_able(bool a){release_skill_able = a; }
    void setSkill_release_counter(int x) {skill_release_counter = x; }
    void increaseSkill_release_counter(){skill_release_counter++;}
    void setSkill_interval_time(int x) {skill_interval_time = x; }

    // 行为
    void die() override; // enemy的blocked被设置为false

    void hit(int hurt)override{
        hp -= hurt;
        hp = std::max(0, hp);
        hitted = 50;
        setHit_counter(getHit_counter() + 1);
    }
    void levelUP();// 最高3级

    void releaseSkill(){ // 玩家点击释放技能
        qInfo() << "player: release skill now";
        qInfo() << "Release_skill_able:" << getRelease_skill_able();
        if(getRelease_skill_able()) {
            setSkillTime(true);
            qInfo() << "setSkillTime(true)";
            setRelease_skill_able(false);
        }
    }

    void skill_released(){
        // timer->start();
        // qInfo() << "timer restart";
        setSkill_release_counter(0);
    }

};

class Giggles : public Tower{
    int offset_attackpower = 0;
    int offset_hp = 0;
    int offset_defence = 0;

public:
    Giggles() : Tower(0, 0, RemoteTower) {
        setName(TowerName::_Giggles);
        attackPower = GlobalAttributes::defaultAttackPower + offset_attackpower;
        defence = GlobalAttributes::defaultDefence + offset_defence;
        totalHP = GlobalAttributes::defaultHP + offset_defence;
        hp = GlobalAttributes::defaultHP + offset_hp;
        range = 150;
    }
    Giggles(int x, int y, TowerType t = RemoteTower):Tower(x,y,t){
        setName(TowerName::_Giggles);
        attackPower = GlobalAttributes::defaultAttackPower + offset_attackpower;
        defence = GlobalAttributes::defaultDefence + offset_defence;
        totalHP = GlobalAttributes::defaultHP + offset_defence;
        hp = GlobalAttributes::defaultHP + offset_hp;
        range = 150;
    }
    void attack(int hurt)override{ // 每7次攻击，伴随攻击进行一次治疗
        if(getAttack_counter() >= 3){
            setSkillTime(true);
            return;
        }
        setAttack_counter(getAttack_counter() + 1);
    }
};

class Flippy:public Tower{
    int offset_attackpower = 30;
    int offset_hp = 0;
    int offset_defence = 10;
public:
    Flippy() : Tower(0, 0, MeleeTower) {
        setName(TowerName::_Flippy);
        attackPower = GlobalAttributes::defaultAttackPower + offset_attackpower;
        defence = GlobalAttributes::defaultDefence + offset_defence;
        totalHP = GlobalAttributes::defaultHP + offset_defence;
        hp = GlobalAttributes::defaultHP + offset_hp;
        range = 50;
    }
    void attack(int hurt)override{ // 每7次攻击，下一次攻击额外造成伤害
        if(getAttack_counter() >= 3){
            setSkillTime(true);
            return;
        }
        setAttack_counter(getAttack_counter() + 1);
    }
};

class Splendid : public Tower{
    int offset_attackpower = 20;
    int offset_hp = 0;
    int offset_defence = 0;
public:
    Splendid() : Tower(0, 0, RemoteTower) {
        setName(TowerName::_Splendid);
        attackPower = GlobalAttributes::defaultAttackPower + offset_attackpower;
        defence = GlobalAttributes::defaultDefence + offset_defence;
        totalHP = GlobalAttributes::defaultHP + offset_defence;
        hp = GlobalAttributes::defaultHP + offset_hp;
        setAttackInterval(100);
        range = 150;
        setSkill_interval_time(1000);
    }
    void attack(int hurt)override{
    }

public slots:

};

class TowerManager : public QObject{
    Q_OBJECT
    friend class FightSystem;
protected:
    QMap<QPoint, QMovie*> towerImage;
    std::vector<std::shared_ptr<Tower>> towerList;
    Scenemap map;
    std::shared_ptr<ConditionMap> cmap;
public:

    TowerManager(const Scenemap& m, std::shared_ptr<ConditionMap> cm) : map(m), cmap(cm) {}

    // 访问
    std::vector<std::shared_ptr<Tower>> getTowerList()const{return towerList;}
    std::vector<std::shared_ptr<Tower>>& getTowerList(){return towerList;}

    // 修改
    void addTower(std::shared_ptr<Tower> t){
        towerList.push_back(t);
        // QMovie *movie = new QMovie(gifPath, QByteArray(), this);
        // towerImage[t->position.pos] = movie;
        // movie->start(); // 启动 GIF 动画
    }// 不要用它部署塔
    void setTowerList(std::vector<std::shared_ptr<Tower>> t){towerList=t;}

    // 行为
    void TowerArrange(std::shared_ptr<Tower> t,const Coordinate& pos);// 部署塔

    ~TowerManager(){ }

public slots:
    void updataTower_skill_release_counter(){
        for(const auto& it : towerList){
            if(it->getSkill_interval_time() == -1) continue;
            if(it->getSkillTime() == false && it->getSkill_release_counter() >= it->getSkill_interval_time()){
                it->setRelease_skill_able(true);
            }
            else if(it->getRelease_skill_able()) continue;
            else it->increaseSkill_release_counter();
        }
    }

};


#endif // TOWER_H

