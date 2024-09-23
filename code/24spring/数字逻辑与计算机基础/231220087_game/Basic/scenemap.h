#ifndef SCENEMAP_H
#define SCENEMAP_H
#include <QtConcurrent/qtconcurrentrun.h>
#include <map>          // 映射容器
#include <vector>
#include <QPoint>
#include <Tool/Special.h>
#include <memory>
#include<QDebug>
#include <QReadWriteLock>
#include <QReadLocker>
#include <QWriteLocker>


class Tower;
class Scenemap;

enum class Direction : unsigned char{
    up,down,left,right
};

struct Coordinate {
    QPoint pos; // 绝对坐标
    Direction d = Direction::down; // 目标方向

    Coordinate(int x = 0, int y = 0, Direction dir = Direction::down)
        : pos(x, y), d(dir) {}
    bool operator==(const Coordinate& other) const {
        return pos.x() == other.pos.x() && pos.y() == other.pos.y();
    }
    bool operator<(const Coordinate& other) const {
        if (pos.x() != other.pos.x()) {
            return pos.x() < other.pos.x();
        } else {
            return pos.y() < other.pos.y();
        }
    }
};


bool isCoordinateEqual(const Coordinate& a, const Coordinate& b);

class Path{
    std::vector<std::shared_ptr<Coordinate>> path; // 一条路径
    int type;
public:
    Path(int t = 0):type(t){}

    // 访问
    std::vector<std::shared_ptr<Coordinate>> getPathInfor() const {return path;}
    int getType() const {return type;}
    void printPath();

    // 修改
    void addInCoordinate_rel(int x, int y, Direction d);// 创建新路径时使用
    void changeType(int t){type = t; }
    void addInCoordinate(int x, int y, Direction d);
    void setType(int x) {type = x;}

    // 行为
    bool isCoordinateInPath(Coordinate coo);

    Path& operator=(const Path& other) {
        if (this == &other) {
            return *this; // 处理自赋值
        }
        type = other.type;
        // 深拷贝
        path.clear();
        for (const auto& coordPtr : other.path) {
            if (coordPtr) {
                path.push_back(std::make_shared<Coordinate>(*coordPtr));
            }
        }
        return *this;
    }

    ~Path() = default;
};

class Scenemap{
    // 格子数
    int length = 15;
    int width = 10;
    int gridSize = 50;
    std::vector<std::shared_ptr<Path>> allPath;  // 地图的全部路径
    std::vector<std::shared_ptr<Coordinate>> startPoints; // 敌人生成格
    std::vector<std::shared_ptr<Coordinate>> endPoints;  // 终点格
    std::vector<std::shared_ptr<Coordinate>> RTable;  // 地图的远程塔可部署点

public:
    Scenemap(){}
    Scenemap(int len, int wid, int size): length(len), width(wid), gridSize(size){}

    // 访问
    void printRTable();
    std::vector<std::shared_ptr<Path>> getAllPath() const{return allPath;}
    std::shared_ptr<Path> getPath (int type) const;
    int getGridSize() const {return gridSize; }
    int getLength() const {return length; }
    int getWidth()const{return width; }


    std::vector<std::shared_ptr<Coordinate>>& getRTable() {return RTable; }
    const std::vector<std::shared_ptr<Coordinate>>& getRTable() const { return RTable; }
    std::vector<std::shared_ptr<Coordinate>>& getStartPoints() {return startPoints; }
    const std::vector<std::shared_ptr<Coordinate>> getStartPoints() const {return startPoints; }
    std::vector<std::shared_ptr<Coordinate>>& getEndPoints() {return endPoints; }
    const std::vector<std::shared_ptr<Coordinate>> getEndPoints() const {return endPoints; }

    // 修改
    void addPath(Path p);// 添加路径
    void addRTable(int x, int y, Direction d = Direction::down);// 添加可部署点


    // 行为
    bool isInStartPoints(const Coordinate& coo);
    bool isInEndPoints(const Coordinate& coo);
    bool isInRTable(const Coordinate& coo);
    bool isInPath(const Coordinate& coo);


    ~Scenemap() = default;
};


// 注册std::shared_ptr<Scenemap>类型
Q_DECLARE_METATYPE(std::shared_ptr<Scenemap>)

Coordinate absoluteCoo(const Coordinate c);


class ConditionMap{

    std::map<Coordinate, std::shared_ptr<Tower>> gridAndTower;
public:
    // 访问
    ConditionMap(){
        gridAndTower.clear();
    }
    std::map<Coordinate,std::shared_ptr<Tower>> getGridAndTower()const{return gridAndTower; }
    std::map<Coordinate,std::shared_ptr<Tower>>& getGridAndTower() {return gridAndTower; }


    // 修改
    void deleteTowerInGrid(int x, int y);
    void deleteTower(const std::shared_ptr<Tower>);
    void addTowerInGrid(const std::shared_ptr<Tower>, const Coordinate& coo);
    void setGridAndTower(std::map<Coordinate, std::shared_ptr<Tower>> g){gridAndTower=g;}


    // 行为
    std::shared_ptr<Tower> findTowerInGrid(const Coordinate& coo) const;

    ~ConditionMap(){ }
};




#endif // SCENEMAP_H
//     friend class TowerManager;
//     // 状态地图: 记录所有格子的状态: 被远程塔占用、被近站塔占用...
//     // 通过它查看、修改这些状态
// protected:
// std::vector<Coordinate> RTable;
// std::vector<Coordinate> gridOfPath;

// public:
// // 将scenemap中的路径、部署点信息拷贝过来
//     ConditionMap();
//     ConditionMap(std::vector<Path*> Paths,std::vector<Coordinate*> rtable){
//         for(auto it : Paths){
//             for(auto itt : it->getPathInfor()){
//                 int x = itt->x; int y = itt->y;
//                 Coordinate coo(x,y);
//                 gridOfPath.push_back(coo);
//             }
//             // 删去交叉点
//             auto last = std::unique(gridOfPath.begin(), gridOfPath.end(), isCoordinateEqual);
//             gridOfPath.erase(last, gridOfPath.end());
//         }
//         for(auto it : rtable){
//             Coordinate coo(it->x, it->y);
//             RTable.push_back(coo);
//         }
//     }
//     std::vector<Coordinate>& getRTable(){return RTable; }
//     std::vector<Coordinate>& getgridOfPath(){return gridOfPath;}
//     bool checkRTable(int x, int y){ // 检查是不是rtable点
//         for(auto it : RTable){
//             if(x == it.x && x == it.y){
//                 return true;
//             }
//         }
//     }
//     bool checkRTableOccupied(int x, int y){ // 检查rtable点是不是被占用
//         for(auto it : RTable){
//             if(x == it.x && x == it.y){
//                 if(it.RT == true) return true;
//             }
//         }
//         return false;
//     }
//     bool checkGridOfPath(int x, int y){ // 检查是不是路径点
//         for(auto it : gridOfPath){
//             if(x == it.x && x == it.y){
//                 return true;
//             }
//         }
//     }
//     bool checkGridOfPathOccupied(int x, int y){ // 检查路径点是不是被占用
//         for(auto it : gridOfPath){
//             if(x == it.x && x == it.y){
//                 if(it.MT == true) return true;
//             }
//         }
//         return false;
//     }
