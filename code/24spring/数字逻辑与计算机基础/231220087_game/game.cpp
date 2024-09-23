#include "Render/inputmanager.h"
#include "Tool/archive.h"
#include "qapplication.h"
#include<game.h>
#include <QTimer>
#include <Render/render.h>
#include <memory>

// 塔升级
void Game::towerLevelUp(std::shared_ptr<Tower> target){
    if(target && target->getAlive() && target->getLevelUP_able()){
        target->levelUP();
        target->changeCurrent_coin(target->getLevelUP_material());
        target->setLevelUP_able(false);
        changeCoin(target->getLevelUP_material() * -1);
        qInfo() << target->getName() << " level up";
    }
}

// 删除塔 （待修改
void Game::disarrangeTower(std::shared_ptr<Tower> target){
    if(target && target->getAlive()){
        target->die();
    }
}

// 点击释放技能
void Game::tower_release_skill(std::shared_ptr<Tower> target){
    if(target && target->getAlive()){
        target->releaseSkill();
    }
}


Game::Game(std::shared_ptr<Scenemap> m, std::shared_ptr<ConditionMap> cm,std::shared_ptr<EnemyManager> enemyManager,
     std::shared_ptr<TowerManager> towerManager,std::shared_ptr<FightSystem> fightSystem,
     std::shared_ptr<AffixManager> affixManager,std::shared_ptr<EnemyWave> enemyWave
           , std::shared_ptr<HealthSystem> healthSystem) :
    enemyManager(enemyManager), towerManager(towerManager), map(m),conditionMap(cm), fightSystem(fightSystem)
    ,affixManager(affixManager),enemyWave(enemyWave), healthSystem(healthSystem){
    timer_affix = new QTimer();
    timer1 = new QTimer();
    timer2 = new QTimer();
}

Game::Game()
{
    timer_affix = new QTimer();
    timer1 = new QTimer();
    timer2 = new QTimer();
}
Game::Game(std::shared_ptr<Scenemap> map):map(map){

    conditionMap = std::make_shared<ConditionMap>();
    enemyManager = std::make_shared<EnemyManager>(*map.get(), conditionMap);
    towerManager = std::make_shared<TowerManager>(*map.get(), conditionMap);
    fightSystem = std::make_shared<FightSystem>(enemyManager,towerManager,conditionMap);
    affixManager = std::make_shared<AffixManager>(enemyManager, towerManager);
    enemyWave = std::make_shared<EnemyWave>(15,enemyManager,map);
    healthSystem = std::make_shared<HealthSystem>(enemyManager, towerManager);

    timer_affix = new QTimer();
    timer1 = new QTimer();
    timer2 = new QTimer();
}


// 根据不同关卡创造不同的游戏对象
void Game::startGame(int stage){

    this->stage = stage;
    int enemyNumber = 1;
    switch(stage){
    case 0:{
        auto p = createDefaultPath0();
        map = createDefaultMap0();
        enemyNumber = 2;
        break;
    }
    case 1:{
        map = createDefaultMap1();
        enemyNumber = 5;
        break;
    }
    case 2:{
        map = createDefaultMap2();
        enemyNumber = 10;
        break;
    }
    }

    conditionMap = std::make_shared<ConditionMap>();
    enemyManager = std::make_shared<EnemyManager>(*map, conditionMap);
    towerManager = std::make_shared<TowerManager>(*map, conditionMap);
    fightSystem = std::make_shared<FightSystem>(enemyManager,towerManager,conditionMap);
    affixManager = std::make_shared<AffixManager>(enemyManager, towerManager);
    enemyWave = std::make_shared<EnemyWave>(enemyNumber, enemyManager,map);
    healthSystem = std::make_shared<HealthSystem>(enemyManager, towerManager);

    this->setPaused(false);

}


// 搭建信号与槽
void Game::connecting(){

    // 游戏总状态
    QObject::connect(enemyManager.get(), &EnemyManager::enemyReachEnd,this, &Game::gameOver_lose);
    QObject::connect(enemyWave.get(), &EnemyWave::noMoreNewEnemy, enemyManager.get(), &EnemyManager::noMoreNewEnemy_slot);
    QObject::connect(enemyManager.get(), &EnemyManager::allEnemyDead,this, &Game::gameOver_win);

    // 敌人死亡增加coin
    QObject::connect(fightSystem.get(), &FightSystem::aEnemyDead,this, &Game::changeCoin);


    // 治疗信号
    QObject::connect(fightSystem.get(), &FightSystem::cure, healthSystem.get(), &HealthSystem::cureLowestHPTower);

    QObject::connect(fightSystem.get(), &FightSystem::towerAttackEnemy_signal,
                     affixManager.get(), &AffixManager::randomCreateForTower);
    QObject::connect(fightSystem.get(), &FightSystem::towerLowHp,
                     affixManager.get(), &AffixManager::randomCreateForEnemy);

    QObject::connect(timer_affix, &QTimer::timeout, affixManager.get(), &AffixManager::randomBind);

    // 检查tower状态
    QObject::connect(timer_affix, &QTimer::timeout, this,  &Game::updateTowerCondition);

    QObject::connect(timer1, &QTimer::timeout, [=](){
        QtConcurrent::run([=]() {
            enemyManager->allEnemyMove();
        });
    });

    QObject::connect(timer2, &QTimer::timeout, [=]() {
        QtConcurrent::run([=]() {
            fightSystem->AttackGenerator();
        });
    });

    QObject::connect(timer2, &QTimer::timeout, [=]() {
        QtConcurrent::run([=]() {
            enemyManager->healthSystem();
        });
    });

    QObject::connect(timer2, &QTimer::timeout,
                     towerManager.get(), &TowerManager::updataTower_skill_release_counter);


    timer_affix->setInterval(30);
    timer1->setInterval(30); // allEnemyMove
    timer2->setInterval(10); // AttackGenerator

    timer_affix->start();
    timer1->start();
    timer2->start();
}


void Game::quit(){
    this->pause();
    qInfo() << "game over";
    emit showSettlement(-2);
}


/*
什么也不获得
*/
void Game::gameOver_lose(){
    this->pause();
    qInfo() << "You Lose!!!";

    emit showSettlement(-1);
}

/*
获得剩余的金币，供下一局开始前使用
*/
void Game::gameOver_win(){
    this->pause();
    if(coin <= 0) coin = 0;
    qInfo() << "You Win!!! You get " << coin <<" coins!!";

    emit stageStatusChange(stage);
    emit showSettlement(coin);
}


void Game::pause(){ // 暂停游戏
    enemyWave->stopTimer();
    timer_affix->stop();
    timer1->stop();
    timer2->stop();
    setPaused(true);
}
void Game::resume(){ // 继续游戏
    enemyWave->startTimer();
    timer_affix->start();
    timer1->start();
    timer2->start();
    setPaused(false);
}

void Game::updateTowerCondition(){ // 检查tower是否可以升级
    for(const auto& it : towerManager->getTowerList()){
        if(it->getLevel() <= 2 && !it->getLevelUP_able()){
            if(coin >= it->getLevelUP_material()){
                it->setLevelUP_able(true);
            }
        }else if(it->getLevel() > 2 || coin < it->getLevelUP_material()){
            it->setLevelUP_able(false);
        }
    }
}

void Game::arrangeMTtower(QPoint pos, TowerName name){
    // 部署近战塔
    int gridsize = map->getGridSize();
    auto new_tower = std::make_shared<Flippy>();
    if(coin < new_tower->getCost()){
        qInfo() << "no enough coin to arrange!";
        return;
    }

    for(const auto& it : map->getAllPath()){
        for(const auto& p : it->getPathInfor()){
            if(abs(p->pos.x() - pos.x()) <= gridsize*0.5 &&
                abs(p->pos.y() - pos.y()) <= gridsize*0.5 ){
                if(name == TowerName::_Flippy){
                    towerManager->TowerArrange(new_tower,*p);
                    coin -= new_tower->getCost();
                }
                return;
            }
        }
    }

    qInfo() << "wrong grid!";
}

void Game::arrangeRTtower(QPoint pos, TowerName name){

    int gridsize = map->getGridSize();

    for(const auto& it : map->getRTable()){
        if(abs(it->pos.x() - pos.x()) <= gridsize*0.5 &&
            abs(it->pos.y() - pos.y()) <= gridsize*0.5 ){
            if(name == TowerName::_Giggles){
                auto new_tower = std::make_shared<Giggles>(0,0,RemoteTower);
                if(coin < new_tower->getCost()){
                    qInfo() << "no enough coin to arrange!";
                    return;
                }
                towerManager->TowerArrange(new_tower,*it);
                coin -= new_tower->getCost();
            }
            else if(name == TowerName::_Splendid){
                auto new_tower = std::make_shared<Splendid>();
                if(coin < new_tower->getCost()){
                    qInfo() << "no enough coin to arrange!";
                    return;
                }
                towerManager->TowerArrange(new_tower,*it);
                coin -= new_tower->getCost();
            }
            return;
        }
    }

    qInfo() << "wrong grid!";
}


std::shared_ptr<Tower> Game::findTower(QPoint pos){
    int gridsize = map->getGridSize();
    for(const auto& p : conditionMap->getGridAndTower()){
        if(abs(p.first.pos.x() - pos.x()) <= gridsize*0.5 &&
            abs(p.first.pos.y() - pos.y()) <= gridsize*0.5 && p.second != nullptr){
            return p.second;
        }
    }
    // qInfo() << "bind canceled";
    return NULL;
}


// 用户操作：将词缀绑定到鼠标点击位置
void Game::bindAffixToTower(const QPoint &pos, AffixType affix){
    auto af = affixManager->searchFreeAffix(affix);
    if(!af){
        qInfo() << "No free affix.";
        return;
    }
    auto tower = findTower(pos);

    if(!tower){ qInfo() << "No such tower."; return;}
    if(tower->getAffixSlot().size() >= 2){
        qInfo() << "Affix Slot is full";
        return;
    }

    switch(affix){
    case 0:{
        affixManager->free_affixNum_tower["Awake"]--;
        break;
    }
    case 1:{
        affixManager->free_affixNum_tower["Icy"]--;
        break;
    }
    case 2:{
        affixManager->free_affixNum_tower["Poison"]--;
        break;
    }
    case 3:{
        affixManager->free_affixNum_tower["AOE"]--;
        break;
    }
    }
    tower->addAffix(af);
    af->setOccupied(true);
    af->changeOwner(tower);

    qInfo() << "bind affix success!";
}

void Game::unbindAffixOfTower(const QPoint &pos, AffixType affix){
    auto tower = findTower(pos);
    if(tower == NULL){return;}
    if(tower->getAffixSlot().empty()){
        qInfo() << "Affix Slot is empty";
        return;
    }

    if(tower->findAffix(affix)){
        auto af = affixManager->searchOccupiedAffix(affix);
        if(!af){
            qInfo() << "Unknown affix and tower ope";
            return;
        }

        switch(affix){
        case 0:{
            affixManager->free_affixNum_tower["Awake"]++;
            break;
        }
        case 1:{
            affixManager->free_affixNum_tower["Icy"]++;
            break;
        }
        case 2:{
            affixManager->free_affixNum_tower["Poison"]++;
            break;
        }
        case 3:{
            affixManager->free_affixNum_tower["AOE"]++;
            break;
        }
        }

        tower->deleteAffix(af);
        af->changeOwner(NULL);
        af->setOccupied(false);

        qInfo() << "unbind affix success!"; return;
    }

    qInfo() << "tower do not have this affix!";
}












