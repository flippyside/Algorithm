#ifndef ROLE_H
#define ROLE_H
#include <algorithm>
#include <cstddef>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
#include "scenemap.h"
#include<qtimer.h>
#include "Tool/Special.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsItem>
#include <Qmutex>

class Affix;


class Role  : public QObject{
    Q_OBJECT
std::shared_ptr<Role> owner;
protected:

    int hitted = 0;// 用于绘制受击闪烁

    int totalHP = 500;
    int hp = 500;
    int attackPower = 30;
    int defence = 10;

    int level = 0; // 当前等级
    int attackTime = 0; // 为0时表示可以攻击
    int attackInterval = 200; // 不变量( 能被词缀影响)
    bool canAttack = true; // 根据攻击间隔判定
    bool alive = true;

    std::vector<std::shared_ptr<Affix>> affixSlot; // 词缀槽

    int range = 100;
    Coordinate position; // 绝对坐标

    int teleportTime = 0;
    bool teleport = 0;


public:
    Role(int x, int y, QObject *parent = nullptr):QObject(parent){
        position.pos.setX(x);
        position.pos.setY(y);
    };
    int getTotalHp()const{return totalHP; }
    int getHp()const{return hp; }
    bool getAlive()const{return alive;}
    int getAttackPower()const{return attackPower;}
    int getDefence()const{return defence; }
    int getAttackInterval()const{return attackInterval; }
    int getAttackTime()const{return attackTime; }
    Coordinate getPosition() const {return position; }
    std::vector<std::shared_ptr<Affix>> getAffixSlot() const {return affixSlot;}
    //std::vector<Special>& getSpecialList(){return specialList; }
    bool findSpecial(Special s);
    int getRange()const{return range; }
    bool findAffix(AffixType a);
    virtual QRect getBoundingBox(){int size = 50; QRect boundingBox(this->getPosition().pos.x() - size * 0.5,this->getPosition().pos.y() - size, size,size);return boundingBox;}
    bool getTeleport()const{return teleport; }
    int getTeleportTime()const{return teleportTime; }
    int getLevel()const{return level; }
    int getHitted() const {return hitted; }

    // manage data
    void setDefence(int x){defence = x; }
    void setAttackPower(int x){attackPower = x; }
    void setRange(int x){range = x; }
    void setAttackInterval(int x){attackInterval = x; }
    void decreaseAttackTime(int x){attackTime = std::max(attackTime-x,0);}
    void resetAttackTime(){ attackTime = attackInterval; }
    void resetAttackTime(int newAttackInterval){ attackTime = newAttackInterval; }
    void setAlive(bool t){alive = t;}
    void removeSpecial(Special s);
    void addSpecial(Special s);
    void setPosition(Coordinate c){position = c; }
    void addAffix(std::shared_ptr<Affix> af);
    void deleteAffix(std::shared_ptr<Affix> af);

    void setTeleportTime(int a){teleportTime = std::max(0,a);}
    void setTeleport(bool a){teleport = a; }
    void levelUp(){level++;}
    void setLevel(int x){level = x; }
    void setHitted(int x){hitted = std::max(0,x); }


    // behave
    virtual void hit(int hurt);
    virtual void recover(int recoverHp);
    virtual void attack(int hurt);
    virtual void die();

    //~Role(){}

};


#endif // ROLE_H
