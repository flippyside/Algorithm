#include "enemy.h"


void Enemy::move(){
    int x = position.x;
    int y = position.y;
    Direction d = position.d;
    int next_x, next_y;

    switch(d){
        case Direction::down:{
            next_y += speed;
            break;
        }
        case Direction::up:{
            next_y -= speed;
            break;
        }
        case Direction::left:{
            next_x -= speed;
            break;
        }
        case Direction::right:{
            next_x += speed;
            break;
        }
    }
    x = next_x; y = next_y;
}



void EnemyManager::moveManager(Scenemap map, Enemy* e) {
    // 获取当前坐标、移动方向
    if(!e->movable){return;}

    Coordinate* absNext = absoluteCoo(map, e->next_position);
    Coordinate* absEnd = absoluteCoo(map, e->end);
    if(e->position.x == absNext->x && e->position.y == absNext->y){ // 到达下一位置
        e->path_index++;
        e->next_position = e->p.path[e->path_index];
    }
    else if(e->next_position.MT){ // 阻挡
        if(e->findSpecial(Special::teleport)){ // 闪现的
            e->path_index += 2;
            Coordinate* tmp = absoluteCoo(map,e->p.path[e->path_index]); 
            e->position.x = tmp->x;        
            e->position.y = tmp->y;   
            delete absNext;     
        }
        if(e->position.x - absNext->x <= Scenemap::a || e->position.y - absNext->y <= Scenemap::a){
            e->movable = false;
            delete absNext;
            return;
        }
    }
    else if(e->position.x == absEnd->x || e->position.y == absEnd->y){ // 到达终点
        delete absNext;
        // 计数器+1
        e->alive = false;
        deleteEnemy(e);
    }
    else{
        delete absNext;
        e->move();
    }
    
}


void EnemyManager::deleteEnemy(Enemy* e){
    auto it = std::find(enemyList.begin(), enemyList.end(), e);
    if (it != enemyList.end()) {
        delete *it;
        enemyList.erase(it);
    }
}