#include "buff.h"


void Buff::effect(Role* role){
    switch(type){
        case BuffType::aoe : {
            role->addSpecial(Special::aoe);
            break;
        }
        case BuffType::awake : { 
            // int multiple1 = 2;
            // float multiple2 = 0.5;   
            // role->setAttackPower(multiple1, 1);
            // role->setAttackInterval(multiple2, 1);
            role->addSpecial(Special::awake);
            break;
        }
        case BuffType::icy : {
            role->addSpecial(Special::icy);
            break;
        }
        case BuffType::poison : {
            role->addSpecial(Special::poison);
            break;
        }
    }

}
void Buff::remove(Role* role){
    switch(type){
        case BuffType::aoe : {

            break;
        }
        case BuffType::awake : {
            int multiple1 = 2;
            float multiple2 = 0.5; 
            role->setAttackPower(multiple1, 0);
            role->setAttackInterval(multiple2, 0);
            break;
        }
        case BuffType::icy : {

            break;
        }
        case BuffType::poison : {

            break;
        }
    }    
}