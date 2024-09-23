#include "inputmanager.h"
#include <Tool/Special.h>

void InputManager::mousePressEvent(QMouseEvent *event)
{

    // // 鼠标左键按下
    // if(event->button() == Qt::LeftButton)
    // {

    // }
    // // 鼠标右键按下
    // else if(event->button() == Qt::RightButton)
    // {

    // }

    // 给tower升级
    std::shared_ptr<Tower> target = game->findTower(event->pos());
    if (waitingForMTDeployment)
    {
        waitingForMTDeployment = false;
        game->arrangeMTtower(event->pos());  
    }
    else if(waitingForRTDeployment){
        waitingForRTDeployment = false;
        game->arrangeRTtower(event->pos());
    }else if(wfBind){
        wfBind = false;
        game->bindAffixToTower(event->pos(), affix);
    }else if(wfUnbind){
        wfUnbind = false;
        game->unbindAffixOfTower(event->pos(), affix);
    }else if(waitingForGiggles){
        waitingForGiggles = false;
        game->arrangeRTtower(event->pos(), TowerName::_Giggles);
    }else if(waitingForFlippy){
        waitingForFlippy = false;
        game->arrangeMTtower(event->pos(), TowerName::_Flippy);
    }else if(waitingForSplendid){
        waitingForSplendid = false;
        game->arrangeRTtower(event->pos(), TowerName::_Splendid);
    }
    else if(target && target->getAlive()){

        qInfo() << "emit showTowerStatus";
        emit showTowerStatus(target);
    }
}


void InputManager::trigerMenu(QAction* act)
{
    QString actionText = act->text();
    if (actionText == "equip awake") {
        qDebug() << "装备词缀: 狂暴";
        wfBind = true;
        affix = awake;
    } else if (actionText == "equip icy") {
        qDebug() << "装备词缀: 冰系";
        wfBind = true;
        affix = icy;
    } else if (actionText == "equip aoe") {
        qDebug() << "装备词缀: 群伤";
        wfBind = true;
        affix = aoe;
    } else if (actionText == "equip poison") {
        qDebug() << "装备词缀: 放血";
        wfBind = true;
        affix = poison;
    } else if (actionText == "demount awake") {
        qDebug() << "卸下词缀: 狂暴";
        wfUnbind = true;
        affix = awake;
    } else if (actionText == "demount icy") {
        qDebug() << "卸下词缀: 冰系";
        wfUnbind = true;
        affix = icy;
    } else if (actionText == "demount aoe") {
        qDebug() << "卸下词缀: 群伤";
        wfUnbind = true;
        affix = aoe;
    } else if (actionText == "demount poison") {
        qDebug() << "卸下词缀: 放血";
        wfUnbind = true;
        affix = poison;
    }
    // emit deployAffix();
}
