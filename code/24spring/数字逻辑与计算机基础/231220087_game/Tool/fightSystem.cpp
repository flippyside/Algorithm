#include <Tool/fightSystem.h>
#include <algorithm>


// 敌人攻击塔
void FightSystem::enemyAttackTower(std::shared_ptr<Enemy> e, std::shared_ptr<Tower> t){

    if (t == NULL || e == NULL) {
        qWarning() << "Invalid Tower or Enemy pointer.";
        return;
    }
    // 普通攻击
    e->resetAttackTime(); // 重置攻击间隔
    int damage = std::max(1, e->getAttackPower() - t->getDefence());
    t->hit(damage);
    e->attack(damage);

    int hp = t->getHp();
    if(hp > 0 && hp <= 450 && !t->getHasDropped()){ // 只掉落一次
        emit towerLowHp();
        t->setHasDropped(true);
    }

    if(hp <= 0){ // 死亡
        t->die();
        // towerManager->deleteTower(t);// 更改塔列表
        cmap->deleteTower(t);// 更改状态地图
    }
    emit enemyAttackTower_signal();
}

// 塔攻击敌人
bool FightSystem::towerAttackEnemy(std::shared_ptr<Tower> t, std::shared_ptr<Enemy> e){

    if (!t || !e) {qWarning() << "Invalid Tower or Enemy pointer.";return false;}

    // 绘制攻击效果
    std::shared_ptr<Bullet> bullet;
    if(t->getType() == TowerType::MeleeTower){
        bullet = std::make_shared<Bullet>(e->getPosition().pos, bulletType::melee_stab, 20);
    }
    else if (t->getName() == TowerName::_Splendid) {bullet = std::make_shared<Bullet>(t->getPosition().pos, e->getPosition().pos,bulletType::laser, 20, 0);}
    else if (t->getType() == TowerType::RemoteTower) {bullet = std::make_shared<Bullet>(e->getPosition().pos, bulletType::remote_boom, 20);}

    bulletList.push_back(bullet);



    t->resetAttackTime(); // 重置攻击间隔
    int attackPower = t->getAttackPower();
    // affix影响
    if(!t->getAffixSlot().empty()){
        for(const auto& it : t->getAffixSlot()) {
            if(it->getType() == AffixType::icy){
                e->setIcy(true);
                e->setIcyTime(100);
            }
            if(it->getType() ==  AffixType::poison){
                e->setBleeding(true);
                e->setBleedingTime(1000);
            }
            if(it->getType() == AffixType::awake){ // 可叠加
                attackPower *= 2;
                int tmp = t->getAttackInterval();
                tmp /= 2; // 缩短攻击间隔
                t->resetAttackTime(tmp);
            }
        }
    }

    int damage = 0;

    if(t->getSkillTime()){
        t->setSkillTime(false);
        switch(t->getName()){

        case _Giggles:{
            emit cure(attackPower, t->getPosition().pos, t->getRange());
            //qInfo() << "Giggles skill time!";
            t->setAttack_counter(0);
            break;
        }
        case _Flippy:{
            damage += 100;// 造成额外的100真实伤害
            //qInfo() << "Flippy skill time!";
            std::shared_ptr<Bullet> f_stab = std::make_shared<Bullet>(e->getPosition().pos, bulletType::flippy_stab, 20);
            t->setAttack_counter(0);
            bulletList.push_back(f_stab);
            break;
        }
        case _Splendid:{
            damage += e->getHp();
            std::shared_ptr<Bullet> l = std::make_shared<Bullet>(t->getPosition().pos, e->getPosition().pos, bulletType::laser, 1, 0);
            bulletList.push_back(l);
            t->skill_released();
            break;
        }
        case Flaky:
            break;
        }
    }

    // 普通攻击, 最低为1
    damage += std::max(1, attackPower - e->getDefence());

    t->attack(damage);
    e->hit(damage);

    if(e->getHp() <= 0) {
        e->setAlive(false);
        emit aEnemyDead(e->getEnemyCoin());
    }
    emit towerAttackEnemy_signal();

    return true;
}



void FightSystem::AttackGenerator(){

    std::vector<std::shared_ptr<Enemy>> enemyList = enemyManager->getEnemyList();
    std::vector<std::shared_ptr<Tower>> towerList = towerManager->getTowerList();
    if(towerList.empty() || enemyList.empty()) return;

    // 每一毫秒调用一次: 将所有塔的attacktime - 1

    for(auto it : enemyList){
        // 检查状态
        if(!it->getAlive()) continue;

        // 处理攻击间隔
        it->decreaseAttackTime(1);
        if(it->getAttackTime() != 0 || it->getIcy()) continue;

        // 寻找目标
        int range = it->getRange();
        std::shared_ptr<Tower> target = findClosestTower(it->getPosition().pos, range, towerList);
        if(target) enemyAttackTower(it, target);
    }


    for(auto it : towerList){
        // 检查塔的阻挡列表
        if(it->getBlockList() && !it->getBlockList()->getAlive()){
            it->setBlocking(false);
            it->setBlockList(NULL);
        }else if(!it->getBlockList()) it->setBlocking(false);

        // 检查状态
        if(!it->getAlive()) continue;

        // 处理攻击间隔
        it->decreaseAttackTime(1);
        if(it->getAttackTime() != 0) continue;

        // 寻找目标
        // 词缀影响
        int range = it->getRange();
        if(!it->getAffixSlot().empty()){
            if(it->findAffix(AffixType::aoe)){
                std::vector<std::shared_ptr<Enemy>>* list = findAllEnemyInRange(it->getPosition(),range,enemyList);
                int flag = 0;
                for(const auto& enemy : *list){
                    if(enemy && enemy->getAlive()) {
                        if(towerAttackEnemy(it, enemy)) flag = 1;
                    }
                }
                if(flag){
                    // 群攻算一次攻击次数
                    it->setAttack_counter(it->getAttack_counter() + 1);
                }
                return;
            }
        }

        // 普通攻击
        std::shared_ptr<Enemy> target = findClosestEnemy(it->getPosition().pos,range,enemyList);
        if(target) {
            if(towerAttackEnemy(it, target)){
                it->setAttack_counter(it->getAttack_counter() + 1);// 攻击成功，攻击次数+1
            }
        }
    }
}


std::vector<std::shared_ptr<Enemy>>* findAllEnemyInRange(const Coordinate& a, int range, const std::vector<std::shared_ptr<Enemy>>& enemyList) {
    auto list = new std::vector<std::shared_ptr<Enemy>>;

    for (const auto& enemy : enemyList) {
        if (enemy && enemy->getAlive() && isInRange(enemy->getPosition().pos, range, a.pos)) {
            list->push_back(enemy);
        }
    }

    return list;
}


