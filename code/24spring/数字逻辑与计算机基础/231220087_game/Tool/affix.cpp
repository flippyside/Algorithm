#include "Tool/affix.h"
#include "qrandom.h"
#include "Basic/enemy.h"

std::shared_ptr<Affix>AffixManager::searchFreeAffix(AffixType type){
    for(const auto & it : affixList_tower){
        if(it->type == type  && !it->getOccupied()) return it;
    }
    return nullptr;
}

std::shared_ptr<Affix> AffixManager:: searchOccupiedAffix(AffixType type){
    for(const auto & it : affixList_tower){
        if(it->type == type  && it->getOccupied()) return it;
    }
    return nullptr;
}

void AffixManager::randomBind(){
    if(affixList_enemy.empty() || enemyManager == NULL || enemyManager->getEnemyList().empty()){return; }

    std::vector<std::shared_ptr<Enemy>> list = enemyManager->getEnemyList();
    for(auto& e : list){
        if(e && e->getAlive()){
            for(const auto& af : affixList_enemy){
                if(af && !af->getOccupied()){
                    e->addAffix(af);
                    af->changeOwner(e);
                    af->setOccupied(true);
                    af->effect();
                    // qInfo() << "bind affix " << af->getType() << " to" << "enemy in " << e->getPosition().pos;
                    return;
                }
            }
        }
    }
}
/*
enum AffixType{awake, icy, poison, aoe, teleport, speedUp };
 */
void AffixManager::randomCreateForTower(){
    int x = 1;//QRandomGenerator::global()->bounded(0, 4);// 1/4概率
    if(x == 1){
        int t = QRandomGenerator::global()->bounded(0, 4); // 随机生成一种词缀
        std::shared_ptr<Affix> a = std::make_shared<Affix>(static_cast<AffixType>(t));
        addAffix_tower(a);

        switch(t){
        case 0:{
            free_affixNum_tower["Awake"]++;
            break;
        }
        case 1:{
            free_affixNum_tower["Icy"]++;
            break;
        }
        case 2:{
            free_affixNum_tower["Poison"]++;
            break;
        }
        case 3:{
            free_affixNum_tower["AOE"]++;
            break;
        }
        }
    }
}


void AffixManager::randomCreateForEnemy(){
    int x = 1; //QRandomGenerator::global()->bounded(0,3);// 1/3概率
    if(x == 1){
        int t = QRandomGenerator::global()->bounded(4, 6); // 随机生成一种词缀
        std::shared_ptr<Affix> a = std::make_shared<Affix>(static_cast<AffixType>(t));
        addAffix_enemy(a);
    }
}




void Affix::effect(){
    switch(type){
    case teleport:{
        owner->setTeleport(true);
        owner->setTeleportTime(0);
        break;
    }
    case awake:
    case icy:
    case aoe:
    case poison:
    case speedUp:
        break;
    }
}
void Affix::remove(){

}
