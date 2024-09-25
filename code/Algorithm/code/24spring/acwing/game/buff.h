#ifndef BUFF_H
#define BUFF_H
#include "role.h"
#include "tower.h"
#include "Special.h"

enum BuffType{awake, icy, aoe, poison };
class Buff{
    friend class BuffManager;
public:
    Buff();

    void effect(Role* role);    // 添加效果
    void remove(Role* role); // 移除效果
    BuffType getType() const { return type;}
    bool checkCondition(){return isOccupied; }

protected:
    BuffType type;
    Role* owner = nullptr;
    bool isOccupied = false;
    bool infinite = false;
    float time;

private:
         // timer

};

class BuffManager{
    // 存有所有buff, 管理buff与tower之间的关系
public:
    void getNewBuff(Buff* newbuff){ // 捡到新buff
        buffs.push_back(newbuff);
    }
    Buff* searchType(BuffType type){
        for(const auto & it : buffs){
            if(it->type == type) return it;
        }
    }

    void bind(Role* role, Buff* buff){
        std::vector<Buff*> buffvec = role->getBuff();
        if(buff->isOccupied == true || buffvec.size() >= 2){return;}
        // 将buff属性修改
        buff->owner = role;
        buff->isOccupied = true;
        // 将buff指针放入塔的buff槽中
        buffvec.push_back(buff);

        buff->effect(role);
    }

    void unbind(Role* role, Buff* buff){
        if(buff->isOccupied == false){return;}
        buff->owner = nullptr;
        buff->isOccupied = false;
        // 从塔的buff槽中删除buff
        auto& buffvec = role->getBuff();
        auto it = std::find(buffvec.begin(), buffvec.end(), buff);
        if (it != buffvec.end()) {
            buffvec.erase(it);
        }

        buff->remove(role);
    }

private:
    std::vector<Buff*> buffs;
};

#endif // BUFF_H
