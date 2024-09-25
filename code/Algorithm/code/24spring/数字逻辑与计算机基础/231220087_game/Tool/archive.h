#ifndef ARCHIVE_H
#define ARCHIVE_H
#include "Basic/scenemap.h"
#include "Basic/role.h"
#include "Basic/enemy.h"
#include "Basic/tower.h"
#include "Tool/affix.h"
#include "Tool/fightSystem.h"
#include "Tool/enemywave.h"
#include <map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <Basic/scenemap.h>
#include <game.h>

// coordinate
QJsonObject coordinateToJson(const Coordinate& c);
void coordinateFromJson(const QJsonObject& json, Coordinate& c);
// path
QJsonObject pathToJson(const Path& p);
void pathFromJson(const QJsonObject& json, Path& p);
// map
QJsonObject scenemapToJson(const Scenemap& s);
void scenemapFromJson(const QJsonObject& json, Scenemap& s);
QJsonObject cmapToJson(const ConditionMap& m);
void cmapFromJson(const QJsonObject& json, ConditionMap& m,  std::shared_ptr<TowerManager> towerManager);
// Affix
QJsonObject affixToJson(const Affix& affix);
std::shared_ptr<Affix> jsonToAffix(const QJsonObject& json);
QJsonObject affixManagerToJson(const AffixManager& affixManager);
void affixManagerFromJson(const QJsonObject& json, AffixManager& manager);
// Role
QJsonObject roleToJson(const Role& role);
void roleFromJson(const QJsonObject& json, Role& role);
QJsonObject enemyToJson(const Enemy& enemy);
void enemyFromJson(const QJsonObject& json, Enemy& enemy);
QJsonObject towerToJson(const Tower& tower);
void towerFromJson(const QJsonObject& json, Tower& tower);
QJsonObject GigglesToJson(const Giggles& p);
void GigglesFromJson(const QJsonObject& json, Giggles& p);
QJsonObject FlippyToJson(const Flippy& p);
void FlippyFromJson(const QJsonObject& json, Flippy& p);


// enemy manager
QJsonObject enemyManagerToJson(const EnemyManager& manager);
void enemyManagerFromJson(const QJsonObject& json, EnemyManager& manager);
// tower manager
QJsonObject towerManagerToJson(const TowerManager& manager);
void towerManagerFromJson(const QJsonObject& json, TowerManager& manager);
QJsonObject enemyWaveToJson(const EnemyWave& enemyWave);
void enemyWaveFromJson(const QJsonObject& json, EnemyWave& enemyWave);


class GameSave{
    int index;
    QString relativePath;

public:
    GameSave(int index = 0):index(index){}
    bool saveGame(int coin, const Scenemap& map, const ConditionMap& cmap,
                  const TowerManager& towerManager, const EnemyManager& enemyManager,
                  const AffixManager& affixManager, const EnemyWave& enemyWave);
    bool saveMap(const Scenemap& map);

    QString getRelativePath(){return relativePath; }
    void setRelativePath(QString s){relativePath = s; }

    std::shared_ptr<Game> loadGame(QString relativePath);// 通过json对象创建game的数据成员，返回game
    std::shared_ptr<Scenemap> loadMap(QString relativePath);// 通过json对象创建scenemap，返回scenemap
};




#endif // ARCHIVE_H
