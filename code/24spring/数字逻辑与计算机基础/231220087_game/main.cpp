#include "Render/menu.h"
#include "Render/tdgame.h"
#include <Render/Settlement.h>
#include <game.h>
#include <Basic/scenemap.h>
#include <Render/inputmanager.h>
#include <QMediaPlayer>
#include <QJsonDocument>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtMultimedia>
#include <qfile.h>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TDgame tdgame;
    tdgame.show();

    return a.exec();
}



// QMediaPlayer *player = new QMediaPlayer;
// QAudioOutput* audioOutput = new QAudioOutput;
// player->setAudioOutput(audioOutput);
// player->setSource(QUrl::fromLocalFile(":/res/background/mountain.mp3"));
// audioOutput->setVolume(100);
// player->play();


//     GameSave gamesave;
// QString filename = "debug/Json/savegame0.json";
// std::shared_ptr<Game> game = gamesave.loadGame(filename);


// // 新游戏
// auto p1 = createDefaultPath1(); p1->setType(0);
// auto p2 = createDefaultPath2(); p2->setType(1);
// std::shared_ptr<Scenemap> sceneMap = createDefaultMap1(*p1);
// sceneMap->addPath(*p2);

// std::shared_ptr<ConditionMap> conditionMap = std::make_shared<ConditionMap>();
// std::shared_ptr<EnemyManager> enemyManager = std::make_shared<EnemyManager>(*sceneMap.get(), conditionMap); // 使用场景地图和状态地图初始化 EnemyManager
// std::shared_ptr<TowerManager> towerManager = std::make_shared<TowerManager>(*sceneMap.get(), conditionMap);
// std::shared_ptr<FightSystem> fightSystem = std::make_shared<FightSystem>(enemyManager,towerManager,conditionMap);
// std::shared_ptr<AffixManager> affixManager = std::make_shared<AffixManager>(enemyManager, towerManager);
// std::shared_ptr<EnemyWave> enemyWave = std::make_shared<EnemyWave>(30,enemyManager,sceneMap);

// std::shared_ptr<Game> game = std::make_shared<Game>();
// std::shared_ptr<Render> render = std::make_shared<Render>(game);
// std::shared_ptr<InputManager> inputManager = std::make_shared<InputManager>(render, game);
// QObject::connect(render.get(), &Render::mousePressEvent, inputManager.get(), &InputManager::mousePressEvent);
// render->show();
// game->startGame();
// auto p = createDefaultPath0();
// std::shared_ptr<Scenemap> sceneMap = createDefaultMap(*p.get()); // 创建地图


// // map_0
// auto p = createDefaultPath0();
// std::shared_ptr<Scenemap> sceneMap = createDefaultMap(*p);


// 保存存档测试------
// // map_1
// auto p1 = createDefaultPath1(); p1->setType(0);
// auto p2 = createDefaultPath2(); p2->setType(1);
// std::shared_ptr<Scenemap> sceneMap = createDefaultMap1(*p1);
// sceneMap->addPath(*p2);


// std::shared_ptr<ConditionMap> conditionMap = std::make_shared<ConditionMap>();
// std::shared_ptr<EnemyManager> enemyManager = std::make_shared<EnemyManager>(*sceneMap, conditionMap); // 使用场景地图和状态地图初始化 EnemyManager
// std::shared_ptr<TowerManager> towerManager = std::make_shared<TowerManager>(*sceneMap, conditionMap);
// std::shared_ptr<FightSystem> fightSystem = std::make_shared<FightSystem>(enemyManager,towerManager,conditionMap);
// std::shared_ptr<AffixManager> affixManager = std::make_shared<AffixManager>(enemyManager, towerManager);
// std::shared_ptr<EnemyWave> enemyWave = std::make_shared<EnemyWave>(30,enemyManager,sceneMap);

// // 一些操作
// auto t1 = std::make_shared<Tower>(0, 0, MeleeTower);
// auto t2 = std::make_shared<Tower>(0, 0, MeleeTower);
// std::shared_ptr<Affix> af1 = std::make_shared<Affix>(aoe);
// std::shared_ptr<Affix> af2 = std::make_shared<Affix>(teleport);
// affixManager->addAffix_tower(af1);
// affixManager->addAffix_enemy(af2);
// t1->addAffix(af1);
// af1->setOccupied(true);
// af1->changeOwner(t1);

// auto e1 = std::make_shared<Enemy>(0, 0, *p);
// auto e2 = std::make_shared<Enemy>(0, 20, *p);
// auto e3 = std::make_shared<Enemy>(0, 0, *p);
// e1->addAffix(af2);
// af2->setOccupied(true);
// af2->changeOwner(e1);

// enemyManager->addEnemy(e1); // 将敌人添加到 EnemyManager 中
// enemyManager->addEnemy(e2);
// enemyManager->addEnemy(e3);

// Coordinate coo1(275,225);
// Coordinate coo2(475,225);
// towerManager->TowerArrange(t1,coo1);
// towerManager->TowerArrange(t2,coo2);

// // for(auto it : sceneMap->getPath(0)->getPathInfor()){
// //     qInfo()<<it->pos;
// // }

// GameSave gamesave(0);
// qInfo() << gamesave.saveGame(*sceneMap,*conditionMap,*towerManager,*enemyManager,*affixManager,*enemyWave);

// -------

// QObject::connect(render.get(), &Render::mousePressEvent, inputManager.get(), &InputManager::mousePressEvent);

// // 塔攻击敌人后，会调用随机生成词缀函数
// QObject::connect(fightSystem.get(), &FightSystem::towerAttackEnemy_signal,
//                  affixManager.get(), &AffixManager::randomCreateForTower);


// // 塔的hp低于50，随机掉落词缀
// QObject::connect(fightSystem.get(), &FightSystem::towerLowHp,
//                  affixManager.get(), &AffixManager::randomCreateForEnemy);


// QTimer* timer_affix = new QTimer();
// QObject::connect(timer_affix, &QTimer::timeout, affixManager.get(), &AffixManager::randomBind);
// timer_affix->start(1000); // 每秒检查一次


// QTimer* timer1 = new QTimer();
// QTimer* timer2 = new QTimer();


// QObject::connect(timer1, &QTimer::timeout, [=]() {
//     QtConcurrent::run([=]() {
//         enemyManager->allEnemyMove();
//     });
// });

// QObject::connect(timer2, &QTimer::timeout, [=]() {
//     QtConcurrent::run([=]() {
//         fightSystem->AttackGenerator();
//     });
// });


// QObject::connect(timer2, &QTimer::timeout, [=]() {
//     QtConcurrent::run([=]() {
//         enemyManager->healthSystem();
//     });
// });

// timer1->start(10);
// timer2->start(1);

// auto t1 = std::make_shared<Tower>(0, 0, MeleeTower);
// auto t2 = std::make_shared<Tower>(0, 0, MeleeTower);

// auto e1 = std::make_shared<Enemy>(0, 0, *p.get());
// auto e2 = std::make_shared<Enemy>(0, 20, *p.get());
// auto e3 = std::make_shared<Enemy>(0, 0, *p.get());

// enemyManager->addEnemy(e1); // 将敌人添加到 EnemyManager 中
// enemyManager->addEnemy(e2);
// enemyManager->addEnemy(e3);

// Coordinate coo1;
// Coordinate coo2;
// coo1.relToAbs(4,5);
// coo2.relToAbs(4,9);
// towerManager->TowerArrange(t1,coo1);
// towerManager->TowerArrange(t2,coo2);

// 词缀

// auto affix_awake = std::make_shared<Affix>(AffixType::awake);
// auto affix_icy = std::make_shared<Affix>(AffixType::icy);
// auto affix_poison = std::make_shared<Affix>(AffixType::poison);
// auto affix_aoe = std::make_shared<Affix>(AffixType::aoe);
// auto affix_teleport = std::make_shared<Affix>(AffixType::teleport);
// auto affix_speedUp = std::make_shared<Affix>(AffixType::speedUp);

// affixManager->addAffix(affix_awake);
// affixManager->addAffix(affix_icy);
// affixManager->addAffix(affix_poison);
// affixManager->addAffix(affix_aoe);
// affixManager->addAffix(affix_teleport);
// affixManager->addAffix(affix_speedUp);


// affixManager->bind(e1, affix_teleport);

// affixManager->bind(e2, affix_speedUp);

// e1->setDefence(0);
