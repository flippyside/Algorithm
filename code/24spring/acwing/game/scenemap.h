#ifndef SCENEMAP_H
#define SCENEMAP_H
#include <iostream>     // 输入输出流
#include <iomanip>      // 输入输出格式控制
#include <fstream>      // 文件输入输出流
#include <vector>       // 向量容器
#include <list>         // 链表容器
#include <map>          // 映射容器
#include <vector>
#include <unordered_map>

enum class Direction : unsigned char{
    up,down,left,right
};

struct Coordinate {
    int x, y; // (0,0),(0,1)...
    Direction d;
    bool MT = false;
};

class Path{
friend class Enemy;
friend class EnemyManager;
    std::vector<Coordinate> path;
    int type;

public:
    Path(int t = 0):type(t){}

    void addInCoordinate(int x, int y, Direction d);


    std::vector<Coordinate> getPathInfor() const {return path;}
    void changeType(int t){type = t; }
    int getType(){return type;}
    void print();

    ~Path() = default;
};

class Scenemap{

    const int L = 20;
    const int W = 20;
    int length;
    int width;
    std::vector<Path> allPath;
    std::vector<std::pair<int, int>> RTable;
public:
    static int a; // 格子边长*0.5 
    Scenemap(){ a = 5;};
    Scenemap(int len, int wid, Path p): length(len), width(wid){allPath.push_back(p); a = 5;}

    // 添加路径、可部署点
    void addPath(Path p){allPath.push_back(p);}
    void addRTable(int x, int y){RTable.push_back(std::make_pair(x, y));}

    void printRTable();
    Path getPath(int type);

    ~Scenemap() = default;
};

Coordinate* absoluteCoo(Scenemap map, Coordinate c){
    int x = ((c.y*2) + 1) * map.a;
    int y = ((c.x*2) + 1) * map.a;
    Coordinate* tmp = new Coordinate;
    tmp->d = c.d;
    tmp->x = x;
    tmp->y = y;
    return tmp;
}


#endif // SCENEMAP_H