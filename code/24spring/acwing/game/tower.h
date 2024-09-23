#ifndef TOWER_H
#define TOWER_H
#include "role.h"
enum TowerType{RemoteTower, MeleeTower};
enum Speacial;

class Tower:public Role{
TowerType type;
public:
    TowerType getType(){return type; }
    // bool getIcy(){return icy; }
    // bool getAoe(){return aoe; }
    // bool getPoison(){return poison; }
    // void setPoison(bool a){ poison = a;}
    // void setIcy(bool a){icy = a;}
    // void setAoe(bool a){aoe = a;}
};

/*
近战单位：
* 狂暴的：装备后伤害和攻击间隔都⼤幅增加（⽐如简单设定为都乘以2）
* 冰系的：装备后攻击能使得敌⽅单位停⽌攻击、移动⼀段时间
* 群伤的：附加范围伤害，装备后能同时攻击多个敌⼈

远程单位
* 放⾎的：装备后对敌⼈的攻击附加流⾎效果，使得敌⼈在⼀定时间内持续扣⾎
*/
// class RemoteTower : public Role{

// public:
//     void attack(Enemy& enemy){
//         int totalHurt = attackPower - enemy.showDefence();
//         enemy.hit(totalHurt);
//     }
//     void setPoison(bool a){
//         poison = a;
//     }

// private:
//     bool poison = false; // 放血能力
// };

// class MeleeTower : public Role{
// public:
//     void attack(Enemy& enemy){
//         int totalHurt = attackPower - enemy.defence;
//         enemy.hit(totalHurt);

//         if(icy){
//             enemy.setMovable(false);
//         }
//         if(aoe){

//         }
//     }
//     void setIcy(bool a){
//         icy = a;
//     }
//     void setAoe(bool a){
//         aoe = a;
//     }

// private:
//     int blocking = 1; // 阻挡数
//     bool icy = false; // 冰系能力
//     bool aoe = false; // 群伤能力

// };
#endif // TOWER_H
