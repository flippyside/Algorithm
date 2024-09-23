#include "archive.h"
#include "qdir.h"

 // 加载游戏存档文件，初始化game对象并返回
std::shared_ptr<Game> GameSave::loadGame(QString relativePath){

    // 文件: 构建路径
    QString basePath = QCoreApplication::applicationDirPath();// "D:/TowerDefence/build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/debug"
    QString absPath = basePath + "/" + relativePath;// "Json/savegame0.json"
    // qInfo() << absPath;

    QFile loadFile(absPath);
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Truncate)) {
        qWarning("Couldn't open save file.");
        return nullptr;
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    // 恢复游戏对象
    std::shared_ptr<Scenemap> sceneMap = std::make_shared<Scenemap>();
    std::shared_ptr<ConditionMap> conditionMap = std::make_shared<ConditionMap>();

    scenemapFromJson(json["map"].toObject(), *sceneMap);// 读取地图

    std::shared_ptr<EnemyManager> enemyManager = std::make_shared<EnemyManager>(*sceneMap, conditionMap); // 使用场景地图和状态地图初始化 EnemyManager
    std::shared_ptr<TowerManager> towerManager = std::make_shared<TowerManager>(*sceneMap, conditionMap);

    towerManagerFromJson(json["towerManager"].toObject(), *towerManager);
    enemyManagerFromJson(json["enemyManager"].toObject(), *enemyManager);
    // std::map<Coordinate, std::shared_ptr<Tower>> sharedTowers;
    // for (const auto& tower : towerManager->getTowerList()) {
    //     sharedTowers.emplace(tower->getPosition(), tower);
    // }
    cmapFromJson(json["conditionMap"].toObject(), *conditionMap, towerManager); // 确保tower都一致（用指针保存）

    // 绑定敌人与路线（路线type被保存）
    for(auto it : enemyManager->getEnemyList()){
        if(it)
            it->setPath(*(sceneMap->getPath(it->getPathType())));
    }

    std::shared_ptr<FightSystem> fightSystem = std::make_shared<FightSystem>(enemyManager,towerManager,conditionMap);
    std::shared_ptr<AffixManager> affixManager = std::make_shared<AffixManager>(enemyManager, towerManager);
    std::shared_ptr<EnemyWave> enemyWave = std::make_shared<EnemyWave>(30,enemyManager,sceneMap);
    affixManagerFromJson(json["affixManager"].toObject(), *affixManager);
    enemyWaveFromJson(json["enemyWave"].toObject(), *enemyWave);
    std::shared_ptr<HealthSystem> healthSystem = std::make_shared<HealthSystem>(enemyManager, towerManager);
    std::shared_ptr<Game> game = std::make_shared<Game>(sceneMap, conditionMap, enemyManager, towerManager,
                                                        fightSystem,affixManager,enemyWave, healthSystem);
    game->setCoin(json["coin"].toInt());
    qInfo() << "load and initialize success!";
    return game;
}

 // 生成游戏存档文件
bool GameSave::saveGame(int coin, const Scenemap& map, const ConditionMap& cmap,
              const TowerManager& towerManager, const EnemyManager& enemyManager,
              const AffixManager& affixManager, const EnemyWave& enemyWave){
    QJsonObject saveData;

    saveData["index"] = index;
    saveData["coin"] = coin;
    saveData["map"] = scenemapToJson(map);
    saveData["conditionMap"] = cmapToJson(cmap);
    saveData["towerManager"] = towerManagerToJson(towerManager);
    saveData["enemyManager"] = enemyManagerToJson(enemyManager);
    saveData["affixManager"] = affixManagerToJson(affixManager);
    saveData["enemyWave"] = enemyWaveToJson(enemyWave);


    QJsonDocument doc(saveData);// 将object设置为本文档的主要对象

    // 保存到文件save
    QString folderPath = QCoreApplication::applicationDirPath() + "/Json";
    QString filePath = folderPath + "/save1.json";

    QFile f(filePath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Couldn't open file for writing.";
        return false;
    }

    QTextStream stream(&f);
    stream.setEncoding(QStringConverter::Utf8);		// 设置写入编码是UTF8

    stream << doc.toJson();// 写入文件
    f.close();

    return true;
}

// 生成地图文件
bool GameSave::saveMap(const Scenemap& map){
    QJsonObject json;
    json["index"] = index;
    json["map"] = scenemapToJson(map);

    QJsonDocument doc(json);// 将object设置为本文档的主要对象
    // 保存到文件game_save
    QString folderPath = QCoreApplication::applicationDirPath() + "/Json";
    QString filePath = folderPath + "/map_save.json";

    QFile f(filePath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Couldn't open file for writing.";
        return false;
    }

    QTextStream stream(&f);
    stream.setEncoding(QStringConverter::Utf8);		// 设置写入编码是UTF8

    stream << doc.toJson();// 写入文件
    f.close();

    return true;
}



// 加载地图文件
std::shared_ptr<Scenemap> GameSave::loadMap(QString relativePath){
    // 文件: 构建路径
    QString basePath = QCoreApplication::applicationDirPath();// "D:/TowerDefence/build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/debug"
    QString absPath = basePath + "/" + relativePath;// "Json/savegame0.json"

    QFile loadFile(absPath);
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Truncate)) {
        qWarning("Couldn't open save file.");
        return nullptr;
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    // 恢复地图
    std::shared_ptr<Scenemap> sceneMap = std::make_shared<Scenemap>();
    scenemapFromJson(json["map"].toObject(), *sceneMap);

    qInfo() << "load and initialize map success!";

    return sceneMap;
}





// 序列化、反序列化


// coordinate
QJsonObject coordinateToJson(const Coordinate& c) {
    QJsonObject coo;
    coo["x"] = c.pos.x();
    coo["y"] = c.pos.y();
    coo["direction"] = static_cast<int>(c.d);
    return coo;
}


void coordinateFromJson(const QJsonObject& json, Coordinate& c) {
    c.pos.setX(json["x"].toInt());
    c.pos.setY(json["y"].toInt());
    c.d = static_cast<Direction>(json["direction"].toInt());
}


// path
QJsonObject pathToJson(const Path& p) {
    QJsonObject path;
    path["type"] = p.getType();

    QJsonArray pathArray;
    for (const auto& coord : p.getPathInfor()) {
        pathArray.append(coordinateToJson(*coord));
    }
    path["path"] = pathArray;
    return path;
}


void pathFromJson(const QJsonObject& json, Path& p) {
    p.changeType(json["type"].toInt());
    QJsonArray pathArray = json["path"].toArray();
    for (const auto& value : pathArray) {
        Coordinate coord;
        coordinateFromJson(value.toObject(), coord);
        p.addInCoordinate(coord.pos.x(), coord.pos.y(), coord.d);
    }
}


// Scenemap
QJsonObject scenemapToJson(const Scenemap& s) {
    QJsonObject scenemap;
    scenemap["length"] = s.getLength();
    scenemap["width"] = s.getWidth();
    scenemap["gridSize"] = s.getGridSize();

    QJsonArray allPathArray;
    for (const auto& path : s.getAllPath()) {
        allPathArray.append(pathToJson(*path));
    }
    scenemap["allPath"] = allPathArray;

    QJsonArray startPointsArray;
    for (const auto& startPoint : s.getStartPoints()) {
        startPointsArray.append(coordinateToJson(*startPoint));
    }
    scenemap["startPoints"] = startPointsArray;

    QJsonArray endPointsArray;
    for (const auto& endPoint : s.getEndPoints()) {
        endPointsArray.append(coordinateToJson(*endPoint));
    }
    scenemap["endPoints"] = endPointsArray;

    QJsonArray RTableArray;
    for (const auto& rt : s.getRTable()) {
        RTableArray.append(coordinateToJson(*rt));
    }
    scenemap["RTable"] = RTableArray;

    return scenemap;
}


void scenemapFromJson(const QJsonObject& json, Scenemap& s) {
    s = Scenemap(json["length"].toInt(), json["width"].toInt(), json["gridSize"].toInt());

    QJsonArray allPathArray = json["allPath"].toArray();
    for (const auto& value : allPathArray) {
        Path path;
        pathFromJson(value.toObject(), path);
        s.addPath(path);
    }

    QJsonArray startPointsArray = json["startPoints"].toArray();
    for (const auto& value : startPointsArray) {
        Coordinate coord;
        coordinateFromJson(value.toObject(), coord);
        s.getStartPoints().push_back(std::make_shared<Coordinate>(coord));
    }

    QJsonArray endPointsArray = json["endPoints"].toArray();
    for (const auto& value : endPointsArray) {
        Coordinate coord;
        coordinateFromJson(value.toObject(), coord);
        s.getEndPoints().push_back(std::make_shared<Coordinate>(coord));
    }

    QJsonArray RTableArray = json["RTable"].toArray();
    for (const auto& value : RTableArray) {
        Coordinate coord;
        coordinateFromJson(value.toObject(), coord);
        s.getRTable().push_back(std::make_shared<Coordinate>(coord));
    }
}

// ConditionMap
QJsonObject cmapToJson(const ConditionMap& m) {
    QJsonObject json;
    QJsonArray g;

    for (const auto& pair : m.getGridAndTower()) {
        QJsonObject p;
        p["coordinate"] = coordinateToJson(pair.first);

        if (auto giggles = std::dynamic_pointer_cast<Giggles>(pair.second)) {
            p["tower"] = GigglesToJson(*giggles);
        } else if (auto flippy = std::dynamic_pointer_cast<Flippy>(pair.second)) {
            p["tower"] = FlippyToJson(*flippy);
        }
        g.append(p);
    }

    json["gridAndTower"] = g;

    return json;
}


void cmapFromJson(const QJsonObject& json, ConditionMap& m,  std::shared_ptr<TowerManager> towerManager) {
    QJsonArray gridAndTowerArray = json["gridAndTower"].toArray();
    for (const auto& item : gridAndTowerArray) {
        QJsonObject entry = item.toObject();
        Coordinate coo;
        coordinateFromJson(entry["coordinate"].toObject(), coo);
        for(auto& it : towerManager->getTowerList()){
            if(it->getPosition() == coo) m.getGridAndTower()[coo] = it;
        }
    }
}


// Affix


QJsonObject affixToJson(const Affix& affix) {
    QJsonObject json;
    json["type"] = static_cast<int>(affix.getType());
    json["isOccupied"] = affix.getOccupied();
    if (affix.getOwner() != nullptr) {
        if (std::dynamic_pointer_cast<Tower>(affix.getOwner())) {
            json["ownerType"] = "Tower";
            //json["owner"] = towerToJson(*std::dynamic_pointer_cast<Tower>(affix.getOwner())); // 会造成递归调用！
        } else if (std::dynamic_pointer_cast<Enemy>(affix.getOwner())) {
            json["ownerType"] = "Enemy";
            //json["owner"] = enemyToJson(*std::dynamic_pointer_cast<Enemy>(affix.getOwner()));
        }
    } else {
        json["ownerType"] = "None";
    }
    return json;
}

void affixFromJson(const QJsonObject& json, Affix& affix) {
    affix.setOccupied(json["isOccupied"].toBool());
    affix.setType(static_cast<AffixType>(json["type"].toInt()));

    QString ownerType = json["ownerType"].toString();
    if (ownerType == "Tower") {
        std::shared_ptr<Tower> owner = std::make_shared<Tower>(0,0);
        towerFromJson(json["owner"].toObject(), *owner);
        affix.changeOwner(owner);
    } else if (ownerType == "Enemy") {
        std::shared_ptr<Enemy> owner = std::make_shared<Enemy>();
        enemyFromJson(json["owner"].toObject(), *owner);
        affix.changeOwner(owner);
    } else {
        affix.changeOwner(nullptr);
    }
}


// affix manager

QJsonObject affixManagerToJson(const AffixManager& affixManager) {
    QJsonObject j;

    try {
        QJsonArray affixArray_t;
        for (const auto& affix : affixManager.getAffixList_tower()) {
            affixArray_t.append(affixToJson(*affix));
        }

        QJsonArray affixArray_e;
        for (const auto& affix : affixManager.getAffixList_enemy()) {
            affixArray_e.append(affixToJson(*affix));
        }

        j["affixList_tower"] = affixArray_t;
        j["affixList_enemy"] = affixArray_e;

    } catch (const std::bad_alloc& e) {
        qCritical() << "Memory allocation failed in affixManagerToJson: " << e.what();
        throw;  // 重新抛出异常
    } catch (const std::exception& e) {
        qCritical() << "An error occurred in affixManagerToJson: " << e.what();
        throw;  // 重新抛出异常
    } catch (...) {
        qCritical() << "An unknown error occurred in affixManagerToJson.";
        throw;  // 重新抛出异常
    }

    return j;
}


void affixManagerFromJson(const QJsonObject& json, AffixManager& manager) {
    QJsonArray towerAffixesArray = json["affixList_tower"].toArray();
    for (const auto& value : towerAffixesArray) {
        std::shared_ptr<Affix> affix = std::make_shared<Affix>();
        affixFromJson(value.toObject(), *affix);
        manager.addAffix_tower(affix);
    }

    QJsonArray enemyAffixesArray = json["affixList_enemy"].toArray();
    for (const auto& value : enemyAffixesArray) {
        std::shared_ptr<Affix> affix = std::make_shared<Affix>();
        affixFromJson(value.toObject(), *affix);
        manager.addAffix_enemy(affix);
    }
}

// Role

QJsonObject roleToJson(const Role& role) {
    QJsonObject json;

    json["level"] = role.getLevel();
    json["totalHP"] = role.getTotalHp();
    json["hp"] = role.getHp();
    json["alive"] = role.getAlive();
    json["attackPower"] = role.getAttackPower();
    json["defence"] = role.getDefence();
    json["attackInterval"] = role.getAttackInterval();
    json["attackTime"] = role.getAttackTime();
    json["range"] = role.getRange();
    json["position"] = coordinateToJson(role.getPosition());
    json["teleport"] = role.getTeleport();
    json["teleportTime"] = role.getTeleportTime();

    QJsonArray affixArray;
    for (const auto& affix : role.getAffixSlot()) {
        affixArray.append(affixToJson(*affix));
    }
    json["affixSlot"] = affixArray;

    return json;
}

void roleFromJson(const QJsonObject& json, Role& role) {

    role.setLevel(json["level"].toInt());
    role.setDefence(json["defence"].toInt());
    role.setAttackPower(json["attackPower"].toInt());
    role.setRange(json["range"].toInt());
    role.setAttackInterval(json["attackInterval"].toInt());
    role.decreaseAttackTime(json["attackTime"].toInt() - role.getAttackTime());
    role.setAlive(json["alive"].toBool());
    role.setTeleport(json["teleport"].toBool());
    role.setTeleportTime(json["teleportTime"].toInt());

    Coordinate coord;
    coordinateFromJson(json["position"].toObject(), coord);
    Coordinate position = coord;
    role.setPosition(coord);

    QJsonArray affixArray = json["affixSlot"].toArray();
    for (const QJsonValue& val : affixArray) {
        std::shared_ptr<Affix> affix = std::make_shared<Affix>();
        affixFromJson(val.toObject(), *affix);
        role.addAffix(affix);
    }
}





// enemy

QJsonObject enemyToJson(const Enemy& enemy) {
    QJsonObject json = roleToJson(enemy);
    json["speed"] = enemy.getSpeed();
    json["blocked"] = enemy.getBlocked();
    json["icy"] = enemy.getIcy();
    json["icyTime"] = enemy.getIcyTime();
    json["attackable"] = enemy.getAttackable();
    json["bleeding"] = enemy.getBleeding();
    json["bleedingTime"] = enemy.getBleedingTime();
    json["speedUp"] = enemy.getSpeedUp();
    json["end"] = coordinateToJson(enemy.getEnd());
    json["pathType"] = enemy.getPathType();
    json["next_position"] = coordinateToJson(enemy.getNext_position());
    json["path_index"] = enemy.getPath_index();
    return json;
}

void enemyFromJson(const QJsonObject& json, Enemy& enemy) {
    roleFromJson(json, enemy);
    enemy.setSpeed(json["speed"].toInt());
    enemy.setBlocked(json["blocked"].toBool());
    enemy.setIcy(json["icy"].toBool());
    enemy.setIcyTime(json["icyTime"].toInt());
    enemy.setAttackable(json["attackable"].toBool());
    enemy.setBleeding(json["bleeding"].toBool());
    enemy.setBleedingTime(json["bleedingTime"].toInt());
    enemy.setSpeedUp(json["speedUp"].toBool());
    Coordinate end, next;
    coordinateFromJson(json["end"].toObject(), end);
    enemy.setEnd(end);
    enemy.setPathType(json["pathType"].toInt());
    coordinateFromJson(json["next_position"].toObject(), next);
    enemy.setNext_position(next);
    enemy.setPath_index(json["path_index"].toInt());

}

// tower

QJsonObject towerToJson(const Tower& tower) {
    QJsonObject json = roleToJson(tower);


    json["name"] = static_cast<int>(tower.getName());
    json["cost"] = tower.getCost();
    json["levelUP_material"] = tower.getLevelUP_material();
    json["hit_counter"] = tower.getHit_counter();
    json["attack_counter"] = tower.getHit_counter();

    json["type"] = static_cast<int>(tower.getType());
    json["blocking"] = tower.getBlocking();
    json["hasDropped"] = tower.getHasDropped();
    if (tower.getBlockList() != nullptr) {
        json["blockList"] = enemyToJson(*tower.getBlockList());
    } else {
        json["blockList"] = QJsonValue();
    }
    return json;
}

void towerFromJson(const QJsonObject& json, Tower& tower) {
    roleFromJson(json, tower);


    tower.setName(static_cast<TowerName>(json["name"].toInt()));
    tower.setCost(json["cost"].toInt());
    tower.setLevelUP_material(json["levelUP_material"].toInt());
    tower.setHit_counter(json["hit_counter"].toInt());
    tower.setAttack_counter(json["attack_counter"].toInt());


    tower.setType(static_cast<TowerType>(json["type"].toInt()));
    tower.setBlocking(json["blocking"].toBool());
    tower.setHasDropped(json["hasDropped"].toBool());
    if (!json["blockList"].isNull()) {
        std::shared_ptr<Enemy> blockListEnemy = std::make_shared<Enemy>();
        enemyFromJson(json["blockList"].toObject(), *blockListEnemy);
        tower.setBlockList(blockListEnemy);
    }
}

QJsonObject GigglesToJson(const Giggles& p){
    QJsonObject json = towerToJson(p);
    return json;
}


void GigglesFromJson(const QJsonObject& json, Giggles& p){
    towerFromJson(json, p);
}

QJsonObject FlippyToJson(const Flippy& p){
    QJsonObject json = towerToJson(p);
    return json;
}


void FlippyFromJson(const QJsonObject& json, Flippy& p){
    towerFromJson(json, p);
}


// enemy manager
QJsonObject enemyManagerToJson(const EnemyManager& manager) {
    QJsonObject json;
    QJsonArray enemyListJson;

    for (const auto& enemy : manager.getEnemyList()) {
        enemyListJson.append(enemyToJson(*enemy));
    }

    json["enemyList"] = enemyListJson;
    return json;
}

void enemyManagerFromJson(const QJsonObject& json, EnemyManager& manager) {
    QJsonArray enemyListJson = json["enemyList"].toArray();
    std::vector<std::shared_ptr<Enemy>> enemyList;

    for (const auto& e : enemyListJson) {
        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
        enemyFromJson(e.toObject(), *enemy);
        enemyList.push_back(enemy);
    }
    manager.setEnemyList(enemyList);
}

// tower manager
QJsonObject towerManagerToJson(const TowerManager& manager) {
    QJsonObject json;
    QJsonArray towerListJson;

    for (const auto& tower : manager.getTowerList()) {
        if (auto giggles = std::dynamic_pointer_cast<Giggles>(tower)) {
            towerListJson.append(GigglesToJson(*giggles));
        } else if (auto flippy = std::dynamic_pointer_cast<Flippy>(tower)) {
            towerListJson.append(FlippyToJson(*flippy));
        }
    }
    json["towerList"] = towerListJson;
    return json;
}

void towerManagerFromJson(const QJsonObject& json, TowerManager& manager) {
    QJsonArray towerListJson = json["towerList"].toArray();
    std::vector<std::shared_ptr<Tower>> towerList;

    for (const auto& towerJsonValue : towerListJson) {
        QJsonObject towerJson = towerJsonValue.toObject();
        TowerName name = static_cast<TowerName>(towerJson["name"].toInt());

        if (name == TowerName::_Giggles) {
            std::shared_ptr<Giggles> giggles = std::make_shared<Giggles>();
            GigglesFromJson(towerJson, *giggles);
            towerList.push_back(giggles);
        } else if (name == TowerName::_Flippy) {
            std::shared_ptr<Flippy> flippy = std::make_shared<Flippy>();
            FlippyFromJson(towerJson, *flippy);
            towerList.push_back(flippy);
        }
    }
    manager.setTowerList(towerList);
}

// enemywave
QJsonObject enemyWaveToJson(const EnemyWave& enemyWave) {
    QJsonObject json;
    json["number"] = enemyWave.getNumber();
    json["counter"] = enemyWave.getCounter();
    json["interval"] = enemyWave.getInterval();
    // 你可以在此处添加其他需要保存的状态

    return json;
}
void enemyWaveFromJson(const QJsonObject& json, EnemyWave& enemyWave) {
    enemyWave.setNumer(json["number"].toInt());
    enemyWave.setCounter(json["counter"].toInt());
    enemyWave.setInterval(json["interval"].toInt());
}
