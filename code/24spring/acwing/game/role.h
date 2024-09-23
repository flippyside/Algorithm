#ifndef ROLE_H
#define ROLE_H
#include <algorithm>
#include <cstddef>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <stack>
#include "scenemap.h"
#include "Special.h"


class Buff;

class Role{
public:
    Role();
    virtual void attack() = 0;
    virtual void hit(int hurt) = 0;

    // get data
    int getTotalHp(){return totalHP; }
    int getHp(){return hp; }
    bool isAlive(){return alive;}
    int getAttackPower(){return attackPower;}
    int getDefence(){return defence; }
    float getAttackInterval(){return attackInterval; }
    Coordinate getPosition(){return position; }
    std::vector<Buff*>& getBuff(){return buff;}
    std::vector<Special>& getSpecialList(){return specialList; }
    void addSpecial(Special s);
    bool findSpecial(Special s);
    void removeSpecial(Special s);
    int getRange(){return range; }

    // manage data

    void hit(int hurt);
    void recover(int recoverHp);
    void attack();


    // base buff effect
    void setAttackPower(int mul, bool increase);
    void setAttackInterval(float mul, bool decrease);

protected:
    std::string name;
    int totalHP;
    int hp;
    bool alive;
    int attackPower;
    int defence;
    float attackInterval;
    std::vector<Buff*> buff;
    std::vector<Special> specialList; // 攻击效果
    int range;
    Coordinate position; // 绝对坐标
};


#endif // ROLE_H
