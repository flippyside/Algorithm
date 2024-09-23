#include "tdgame.h"
#include "game.h"
#include "Render/menu.h"


TDgame::TDgame(){
    stageStatus.emplace(0,false);// 第一关默认开放
    stageStatus.emplace(1,false);
    stageStatus.emplace(2,false);

    setFixedSize(1200,900);

    menu = std::make_shared<Menu>(this);
    menu->setGeometry(0,0,1200,900);
    menu->show();// 初始状态，显示menu

    game = std::make_shared<Game>();

    globalAttributes = GlobalAttributes();

    // 关卡选择
    stageSelect = std::make_shared<StageSelect>(this);
    stageSelect->setGeometry(0,0,1200,900);
    stageSelect->hide();

    // 游戏渲染
    render = std::make_shared<Render>(game, this);
    render->setGeometry(0,0,1200,900);
    render->hide();

    // 塔属性界面
    towerStatus = std::make_shared<TowerStatus>(this);
    towerStatus->setGeometry(900,0,300,600);
    towerStatus->hide();



    // 升级界面
    upgradePage = std::make_shared<UpgradePage>(this);
    upgradePage->setGeometry(200,200,800,600);
    upgradePage->hide();

    // 结算界面
    settlement = std::make_shared<Settlement>(this);
    settlement->setGeometry(200,200,800,600);
    settlement->hide();

    // 注册类型
    qRegisterMetaType<std::shared_ptr<Scenemap>>("std::shared_ptr<Scenemap>");



    inputManager = std::make_shared<InputManager>(render, game);// 输入
    QObject::connect(stageSelect.get(),&StageSelect::initializeGame,this,&TDgame::initializeGame);
    QObject::connect(stageSelect.get(),&StageSelect::showUpgradePage,this,&TDgame::showUpgradePage_slot);

    QObject::connect(menu.get(), &Menu::showStageSelect, this, &TDgame::showStageSelect_slot);
    QObject::connect(menu.get(), &Menu::hideMenu, this, &TDgame::hideMenu_slot);
    QObject::connect(menu.get(), &Menu::initializeGame_save, this, &TDgame::initializeGame_save);
    QObject::connect(menu.get(), &Menu::initializeGame_map, this, &TDgame::initializeGame_map);



    QObject::connect(settlement.get(), &Settlement::backToStageSelect, this, &TDgame::backToStageSelect_slot);

    QObject::connect(towerStatus.get(), &TowerStatus::closeTowerStatus, this, &TDgame::closeTowerStatus);

    QObject::connect(upgradePage.get(), &UpgradePage::upgradeAttackPower, this, &TDgame::upgradeAttackPower);
    QObject::connect(upgradePage.get(), &UpgradePage::upgradeDefence, this, &TDgame::upgradeDefence);
    QObject::connect(upgradePage.get(), &UpgradePage::upgradeHP, this, &TDgame::upgradeHP);
    QObject::connect(upgradePage.get(), &UpgradePage::upgrade_ToStageSelect, this, &TDgame::hideUpgradePage);



// 记得与下面的connecting函数同步更新
    QObject::connect(render.get(), &Render::mousePressEvent, inputManager.get(), &InputManager::mousePressEvent);
    QObject::connect(game.get(), &Game::game_backToStageSelect, this, &TDgame::backToStageSelect_slot);// 返回选择关卡界面
    QObject::connect(game.get(), &Game::showSettlement, this, &TDgame::showSettlement);
    QObject::connect(game.get(), &Game::stageStatusChange, this, &TDgame::stageStatusChange);
    QObject::connect(inputManager.get(), &InputManager::showTowerStatus, this, &TDgame::showTowerStatus);

    QObject::connect(towerStatus.get(), &TowerStatus::towerLevelUp, game.get(), &Game::towerLevelUp);
    QObject::connect(towerStatus.get(), &TowerStatus::disarrangeTower, game.get(), &Game::disarrangeTower);
    QObject::connect(towerStatus.get(), &TowerStatus::tower_release_skill, game.get(), &Game::tower_release_skill);


}

void TDgame::connecting(){
    QObject::connect(render.get(), &Render::mousePressEvent, inputManager.get(), &InputManager::mousePressEvent);
    QObject::connect(game.get(), &Game::game_backToStageSelect, this, &TDgame::backToStageSelect_slot);// 返回选择关卡界面
    QObject::connect(game.get(), &Game::showSettlement, this, &TDgame::showSettlement);
    QObject::connect(game.get(), &Game::stageStatusChange, this, &TDgame::stageStatusChange);
    QObject::connect(inputManager.get(), &InputManager::showTowerStatus, this, &TDgame::showTowerStatus);

    QObject::connect(towerStatus.get(), &TowerStatus::towerLevelUp, game.get(), &Game::towerLevelUp);
    QObject::connect(towerStatus.get(), &TowerStatus::disarrangeTower, game.get(), &Game::disarrangeTower);
    QObject::connect(towerStatus.get(), &TowerStatus::tower_release_skill, game.get(), &Game::tower_release_skill);


}

void TDgame::initializeGame(int stage){
    game->startGame(stage);
    game->connecting();
    render->initialize();
    inputManager->connecting();
    render->show();
}

void TDgame::initializeGame_save(GameSave gamesave){
    game = gamesave.loadGame(gamesave.getRelativePath());
    game->connecting();
    render = std::make_shared<Render>(game, this);
    render->initialize();
    inputManager = std::make_shared<InputManager>(render, game);
    inputManager->connecting();
    QObject::connect(render.get(), &Render::mousePressEvent, inputManager.get(), &InputManager::mousePressEvent);
    QObject::connect(inputManager.get(), &InputManager::showTowerStatus, this, &TDgame::showTowerStatus);
    menu->hide();
    render->show();
}

void TDgame::initializeGame_map(std::shared_ptr<Scenemap> map){
    game = std::make_shared<Game>(map);
    qInfo() << game->getMap()->getLength();
    game->connecting();
    render = std::make_shared<Render>(game, this);
    render->initialize();
    inputManager = std::make_shared<InputManager>(render, game);
    inputManager->connecting();
    QObject::connect(render.get(), &Render::mousePressEvent, inputManager.get(), &InputManager::mousePressEvent);
    QObject::connect(inputManager.get(), &InputManager::showTowerStatus, this, &TDgame::showTowerStatus);

    menu->hide();
    render->show();
}

void TDgame::showTowerStatus(std::shared_ptr<Tower> tower){
    qInfo() << "showTowerStatus";
    towerStatus->raise();
    towerStatus->show();
    towerStatus->setTower(tower);
}

void TDgame::closeTowerStatus(){
    qInfo() << "closeTowerStatus";
    towerStatus->hide();
}


void TDgame::stageStatusChange(int stage){
    stageStatus[stage] = true;
    qInfo() << "you passed stage " << stage;
    if(stageStatus[0] == true){
        connect(stageSelect->stage1, &QPushButton::clicked, stageSelect.get(), &StageSelect::startGame1);
    }
    if(stageStatus[1] == true){
        connect(stageSelect->stage2, &QPushButton::clicked, stageSelect.get(), &StageSelect::startGame2);
    }
}

void TDgame::showSettlement(int coin){

    if(coin == -1){
        settlement->setLose(true);
        settlement->raise();
        settlement->show();
        return;
    }else if(coin == -2){
        settlement->setQuit(true);
        settlement->raise();
        settlement->show();
        return;
    }

    changeCOIN(coin);
    settlement->raise();
    settlement->setCoin(coin);
    settlement->show();
}

void TDgame::hideRender(){
    render->hide();
}

void TDgame::backToStageSelect_slot(){

    settlement->setLose(false);
    settlement->setQuit(false);
    settlement->hide();

    render->hide();
    stageSelect->raise();
    stageSelect->show();

    game.reset();
    render.reset();
    inputManager.reset();

    game = std::make_shared<Game>();
    render = std::make_shared<Render>(game, this);
    inputManager = std::make_shared<InputManager>(render, game);
    connecting();
}

void TDgame::showStageSelect_slot(){
    render->hide();
    stageSelect->show();
}

void TDgame::hideMenu_slot(){
    menu->hide();
}

void TDgame::upgradeAttackPower(){
    int add = 50;
    int cost = 10;
    if(COIN < cost){
        qInfo() << "no enough coin.";
        return;
    }
    GlobalAttributes::addDefaultAttackPower(add);
    qInfo() << "all towers attack power increase 50!";
    changeCOIN(cost * -1);

}

void TDgame::upgradeDefence(){
    int add = 10;
    int cost = 10;
    if(COIN < cost){
        qInfo() << "no enough coin.";
        return;
    }
    GlobalAttributes::adddefaultDefence(add);
    qInfo() << "all towers defence increase 10!";
    changeCOIN(cost * -1);

}

void TDgame::upgradeHP(){
    int add = 100;
    int cost = 10;
    if(COIN < cost){
        qInfo() << "no enough coin.";
        return;
    }
    GlobalAttributes::adddefaultHP(add);
    qInfo() << "all towers hp increase 100!";
    changeCOIN(cost * -1);

}

void TDgame::showUpgradePage_slot(){
    stageSelect->hide();
    // qInfo() << "showUpgradePage";
    upgradePage->show();
}

void TDgame::hideUpgradePage(){
    stageSelect->show();
    upgradePage->hide();
}
