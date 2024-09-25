#include "role.h"
#include "buff.h"
#include "scenemap.h"

class Enemy : public Role
{
friend class EnemyManager;
public:
    Enemy(Path pa){
        p = pa;
        path_index = 0;
        next_position = p.path[path_index + 1];
        end = p.path.back();
    };

    void check(){};
    void attack(){};
    void hit(){};
    void move(){};


private:
    Path p;
    Coordinate next_position; // e的前进目标（e的下一个坐标, 且是相对的）
    Coordinate end; // 终点
    int path_index; // 当前路径坐标
    int speed;
    bool movable = true;
    bool attackable = true;
    bool bleeding = false;
};

class EnemyManager{

std::vector<Enemy*> enemyList;
public:
    void addEnemy(Enemy* e){enemyList.push_back(e);};
    void deleteEnemy(Enemy* e);
    void moveManager(Scenemap map, Enemy* e);
    void allEnemyMove(Scenemap map){
        for (Enemy* enemy : enemyList) moveManager(map, enemy);
    }


};



