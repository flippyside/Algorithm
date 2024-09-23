#ifndef GLOBALATTRIBUTE_H
#define GLOBALATTRIBUTE_H

class GlobalAttributes {
public:
    GlobalAttributes(){

    }
    static int defaultAttackPower;
    static int defaultHP;
    static int defaultDefence;

    static void setDefaultAttackPower(int attackPower) {
        defaultAttackPower = attackPower;
    }

    static void setdefaultHP(int healthPoints) {
        defaultHP = healthPoints;
    }
    static void setdefaultDefence(int x) {
        defaultDefence = x;
    }

    static void addDefaultAttackPower(int attackPower) {
        defaultAttackPower += attackPower;
    }

    static void adddefaultHP(int healthPoints) {
        defaultHP += healthPoints;
    }
    static void adddefaultDefence(int x) {
        defaultDefence += x;
    }
};


#endif // GLOBALATTRIBUTE_H
