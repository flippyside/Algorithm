#ifndef ENEMYWAVE_H
#define ENEMYWAVE_H

#include<QTimer>
#include <Basic/enemy.h>
#include <QObject>
#include "qrandom.h"

class EnemyWave : public QObject
{
    Q_OBJECT

    int number = 10; // 敌人总数
    int counter = 0;
    int interval = 5000;
    std::vector<int> intervalList;
    QTimer* timer;
    std::shared_ptr<EnemyManager> enemyManager;
    std::shared_ptr<Scenemap> sceneMap;
public:
    EnemyWave(int number, std::shared_ptr<EnemyManager> enemyManager, std::shared_ptr<Scenemap> sceneMap)
        :number(number),enemyManager(enemyManager), sceneMap(sceneMap){
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &::EnemyWave::createEnemy_0);
        timer->setInterval(interval);
        timer->start();

    }


    // 访问
    int getNumber()const{return number;}
    int getCounter()const{return counter;}
    int getInterval()const {return interval;}

    // 修改
    void setNumer(int x){number=x;}
    void setCounter(int x){counter=x;}
    void setInterval(int x){interval=x;}

    // 行为
    void createEnemy_0(){
        int pathNum = sceneMap->getAllPath().size();
        // qInfo()<< "createEnemy_0 pathNum" << pathNum;
        if(counter < number){
            int t = QRandomGenerator::global()->bounded(0, pathNum); // 随机生成
            auto e = std::make_shared<Enemy>(0, 0, *sceneMap->getPath(t));
            e->setPathType(t);
            enemyManager->addEnemy(e);
            counter++;
        }else{
            timer->stop();
            emit noMoreNewEnemy();
        }
    }
    void startTimer() {
        if (!timer) {
            timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, &EnemyWave::createEnemy_0);
        }
        timer->setInterval(interval);
        timer->start();
    }

    void stopTimer(){
        timer->stop();
    }

    ~EnemyWave() {
        timer->stop();
        delete timer;
    }

signals:
    void noMoreNewEnemy();



};

#endif // ENEMYWAVE_H
