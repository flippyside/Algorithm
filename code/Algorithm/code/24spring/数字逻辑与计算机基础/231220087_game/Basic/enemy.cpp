#include "enemy.h"
#include"scenemap.h"


void Enemy::move() {

    int s = this->speed;

    // 词缀影响
    if(this->findAffix(AffixType::speedUp)) s *= 2;

    switch (this->getPosition().d) {
    case Direction::down:
        position.pos.setY(position.pos.y() + s);
        // qInfo() << "enemy moves down";
        break;
    case Direction::up:
        position.pos.setY(position.pos.y() - s);
        // qInfo() << "enemy moves up";
        break;
    case Direction::left:
        position.pos.setX(position.pos.x() - s);
        // qInfo() << "enemy moves left";
        break;
    case Direction::right:
        position.pos.setX(position.pos.x() + s);
        // qInfo() << "enemy moves right";
        break;
    }
     // qInfo() << "to " << position.pos.x() << "," << position.pos.y();
}


Enemy::Enemy(int x, int y, const Path& pa):Role(x,y), p(pa), path_index(0)
{
    attackPower = 40;
    path_index = 0;
    position =  *(p.getPathInfor()[path_index].get());
    qInfo() << position.pos.x() << "," << position.pos.y();
    next_position = *(p.getPathInfor()[path_index + 1].get());
    end = *(p.getPathInfor().back().get());
}

void EnemyManager::moveManager(std::shared_ptr<Enemy> e) {
    if(!e){qInfo() << "Error: Enemy doesn't exist"; return; }
    if(!e->getAlive() || e->getIcy()) {return; }

    auto tower = cmap->findTowerInGrid(e->next_position);


    // 到达终点
    if(abs(e->position.pos.x() - e->end.pos.x()) <= 2 &&
        abs(e->position.pos.y() - e->end.pos.y()) <= 2){
        e->setAlive(false);
        emit enemyReachEnd();
        qInfo() << "a enemy reach end";
        return;
    }
    // 到达下一位置，更新方向
    else if(abs(e->position.pos.x() - e->next_position.pos.x()) <= 2 &&
             abs(e->position.pos.y() - e->next_position.pos.y()) <= 2){

        e->position.d = e->next_position.d;
        e->path_index++;
        e->next_position = *e->p.getPathInfor()[e->path_index].get();
    }
    // 闪现: 敌人被阻挡，且已经到达传送时间
    else if(e->getBlocked() && e->getTeleport() && e->getTeleportTime() == 0){
        // qInfo() << "enemy teleport! ";

        if(e && e->getAlive()){
            e->setBlocked(false);
        }


        if(tower && tower->getAlive()){
            tower->setBlocking(false);
            tower->removeBlockList(e); // 传送后，塔的阻挡列表也要改变
        }else{
            qInfo() << "moveManager: invalid tower!!!!!";
        }
        e->setTeleportTime(10000); // 重置时间
        e->path_index++;
        Coordinate tmp = *e->p.getPathInfor()[e->path_index];
        if(tmp.pos == e->end.pos){ // 终点附近传送
            e->setAlive(false);
            qInfo() << "a enemy reach end";
            return;
        }
        switch(tmp.d){
            case Direction::up:{
                tmp.pos.ry() += 10;
                break;
            }
            case Direction::down: {
                tmp.pos.ry() -= 10; break;
            }
            case Direction::right:{
                tmp.pos.rx() -= 10;break;
            }
            case Direction::left:
                break;
            }
        e->position = Coordinate(tmp.pos.x(), tmp.pos.y(), tmp.d);
        e->next_position = *e->p.getPathInfor()[e->path_index + 1];
        e->setIcy(true);
        e->setIcyTime(50);
        return;
    }
    // 前方有塔，且塔的阻挡列表为空
    else if(tower && ( tower->getBlockList() == NULL || !tower->getBlockList()->getAlive()) && tower->getAlive()){

        if(std::abs(e->position.pos.x() - e->next_position.pos.x()) <= 20 &&
            std::abs(e->position.pos.y() - e->next_position.pos.y())  <= 20 ){

            if(e && e->getAlive()){
                e->setBlocked(true);
                tower->setBlocking(true);
                tower->setBlockList(e);
                // qInfo() << "enemy blocked! ";
            }

        }else{
            if(e->getBlocked()){return; }
            e->move();
        }
    }
    else{

        if(e->getBlocked()){return; }
        e->move();
    }

}

void EnemyManager::healthSystem(){

    int poison_hurt = 1;
    for (auto e : enemyList){
        if(!e || !e->getAlive()) continue;
        if(e->getBleeding()){
            if(e->getBleedingTime() % 10 == 0){ e->hit(poison_hurt);} //qInfo()<<e->getBleedingTime();}
            e->setBleedingTime(e->getBleedingTime() - 1); // 模拟计时
            if(e->getBleedingTime() <= 0){ // 每秒-10hp
                e->setBleedingTime(0);
                e->setBleeding(false);
            }
        }
        if(e->getIcy()){
            e->setIcyTime(e->getIcyTime() - 1);
            if(e->getIcyTime() == 0){ // 生效一次，持续2秒
                e->setIcy(false);
            }
        }
        if(e->getTeleport()){
            e->setTeleportTime(e->getTeleportTime() - 1);
        }
    }

    if(noMoreNewEnemy){
        int flag = 1;
        for (const auto& e : enemyList){
            if(e && e->getAlive()) flag = 0;
        }
        if(flag == 1){
            emit allEnemyDead();
        }
    }

}


// void EnemyManager::deleteEnemy(std::shared_ptr<Enemy> e){
//     if (!e) {
//         qWarning() << "Invalid enemy pointer.";
//         return;
//     }
//     auto it = std::find(enemyList.begin(), enemyList.end(), e);
//     if (it != enemyList.end()) {
//         enemyList.erase(it);
//         // qInfo() << "delete enemy.";
//     }
//     //else qInfo() << "not found.";

// }
