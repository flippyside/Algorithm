#include "role.h"
#include "Special.h"

void Role::setAttackPower(int mul, bool increase){
    if(increase)
        attackPower *= mul; // increase power
    else attackPower /= mul;
}
void Role::setAttackInterval(float mul, bool decrease){
    if(decrease)
        attackInterval *= mul; // decrease time
    else attackInterval /= mul;
}

void Role::addSpecial(Special s){
    specialList.push_back(s);
}
bool Role::findSpecial(Special s){
    auto it = std::find(specialList.begin(), specialList.end(), s);
    if (it != specialList.end()) {
        return true;
    } else {
        return false;
    }
}
void Role::removeSpecial(Special s){
    auto it = std::find(specialList.begin(), specialList.end(), s);
    if (it != specialList.end()) {
        specialList.erase(it);
    } else {
        return;
    }    
}