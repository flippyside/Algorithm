#include "scenemap.h"


// Scenemap

void Scenemap::addPath(Path p){
    allPath.push_back(std::make_shared<Path>(p));
    startPoints.push_back(p.getPathInfor()[0]);
    endPoints.push_back(p.getPathInfor().back());
}

void Scenemap::addRTable(int x, int y, Direction d){
    int _x =( (y * 2) + 1 )* 50 * 0.5;
    int _y =( (x * 2) + 1 )* 50 * 0.5;
    RTable.push_back(std::make_shared<Coordinate>(_x, _y, d));
}

std::shared_ptr<Path> Scenemap::getPath(int type) const {
    for (auto& p : allPath) {
        if (p->getType() == type) {
            return p;
        }
    }
    return nullptr;
}

// 判断 Coordinate 是否在 startPoints 中
bool Scenemap::isInStartPoints(const Coordinate& coo) {
    return std::any_of(startPoints.begin(), startPoints.end(), [&coo](const std::shared_ptr<Coordinate>& p) {
        return *p == coo;
    });
}

// 判断 Coordinate 是否在 endPoints 中
bool Scenemap::isInEndPoints(const Coordinate& coo) {
    return std::any_of(endPoints.begin(), endPoints.end(), [&coo](const std::shared_ptr<Coordinate>& p) {
        return *p == coo;
    });
}

// 判断 Coordinate 是否在 RTable 中
bool Scenemap::isInRTable(const Coordinate& coo) {
    return std::any_of(RTable.begin(), RTable.end(), [&coo](const std::shared_ptr<Coordinate>& p) {
        return *p == coo;
    });
}

// 判断 Coordinate 是否在所有路径中
bool Scenemap::isInPath(const Coordinate& coo) {
    return std::any_of(allPath.begin(), allPath.end(), [&coo](const std::shared_ptr<Path>& path) {
        return path->isCoordinateInPath(coo);
    });
}

// Path

void Path::addInCoordinate(int x, int y, Direction d){
    path.push_back(std::make_shared<Coordinate>(x, y, d));
}

void Path::addInCoordinate_rel(int x, int y, Direction d){
    int _x =( (y * 2) + 1 )* 50 * 0.5;
    int _y =( (x * 2) + 1 )* 50 * 0.5;
    path.push_back(std::make_shared<Coordinate>(_x, _y, d));
}

bool Path::isCoordinateInPath(Coordinate coo){
    for(auto it : path){
        if(*it == coo) return true;
    }
    return false;
}


Coordinate absoluteCoo(const Coordinate c){
    int x = ((c.pos.y() * 2) + 1) * 50 * 0.5;
    int y = ((c.pos.x() * 2) + 1) * 50 * 0.5;
    return Coordinate(x,y,c.d);
}

void Path::printPath(){
    for(auto it : path){
        qInfo() << it->pos.x() <<", "<< it->pos.y();
    }
}


// ConditionMap

void ConditionMap::deleteTowerInGrid(int x, int y) {
    Coordinate coo(x, y);
    gridAndTower.erase(coo);
}

void ConditionMap::deleteTower(const std::shared_ptr<Tower> tower) {
    for (auto it = gridAndTower.begin(); it != gridAndTower.end(); ) {
        if (it->second == tower) {
            it = gridAndTower.erase(it);
        } else {
            ++it;
        }
    }
}

void ConditionMap::addTowerInGrid(const std::shared_ptr<Tower> tower, const Coordinate& coo) {
    gridAndTower.emplace(coo,tower);
}

std::shared_ptr<Tower> ConditionMap::findTowerInGrid(const Coordinate& coo) const {
    auto it = gridAndTower.find(coo);
    // qInfo() << "findtowerin "<< it->first.pos;
    if (it != gridAndTower.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

