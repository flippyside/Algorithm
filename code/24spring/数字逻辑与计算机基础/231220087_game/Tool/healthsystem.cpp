#include "healthsystem.h"
#include "Basic/tower.h"
#include "Tool/bullet.h"

void HealthSystem::cureLowestHPTower(int hp, QPoint pos, int range){
    std::shared_ptr<Tower> target = findLowestHpTower(pos, range, towerManager->getTowerList());
    if(target) {
        target->recover(hp);
        std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(target->getPosition().pos, bulletType::cure, 100);
        cureList.push_back(bullet);
        // qInfo() << target->getName() << "recover "<< hp << "HP!";
    }
}
