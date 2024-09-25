#include "Basic/role.h"
#include "Tool/Special.h"
#include "Tool/affix.h"

void Role::hit(int hurt){
    hp -= hurt;
    hp = std::max(0, hp);
    // qInfo() << this->getPosition().pos << " lose " << hurt << " HP!";
}

void Role::recover(int recoverHp){
    hp += recoverHp;
    hp = std::min(hp, totalHP);
    // qInfo() << "hp: "<<hp<<"totalhp: "<<totalHP;
}


void Role::attack(int hurt){

}

void Role::die(){

}

void Role::deleteAffix(std::shared_ptr<Affix> af){
    auto it = std::find(affixSlot.begin(), affixSlot.end(), af);
    if (it != affixSlot.end()) {
        affixSlot.erase(it);
        qInfo() << "delete Affix successfully! ";
        return;
    }
    qInfo() << "no such Affix! ";
}

bool Role::findAffix(AffixType a){
    for(const auto& it : affixSlot){
        if (it->getType() == a) return true;
    }
    return false;
}

void Role::addAffix(std::shared_ptr<Affix> af){
    if(affixSlot.size() >= 2){
        qInfo() << "affixslot is full"; return;
    }
    affixSlot.push_back(af);
}
