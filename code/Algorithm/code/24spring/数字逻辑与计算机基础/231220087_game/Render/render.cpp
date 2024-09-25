#include "render.h"
#include <game.h>


void Render::initialize(){// 确定game对象后，再初始化

    int len = game->getMap()->getLength(), wid = game->getMap()->getWidth();
    gridsize = game->getMap()->getGridSize();
    length = len*gridsize; width = wid*gridsize;

    qInfo() << length << " " << width;

    int buttonSize = 100;
    int interval = buttonSize*1.5;


    timer = new QTimer(this);
    setFixedSize(windowLength, windowWidth);

    // 按钮
    Flippy = new QPushButton("Flippy", this);
    Giggles = new QPushButton("Giggles", this);
    Splendid = new QPushButton("Splendid", this);

    saveButton = new QPushButton("保存游戏", this);
    saveMapButton = new QPushButton("保存地图", this);

    Flippy->setGeometry(gridsize + interval, width + gridsize,  buttonSize, buttonSize/2);
    saveButton->setGeometry(gridsize + interval*4, width + gridsize,  buttonSize, buttonSize/2);
    saveMapButton->setGeometry(gridsize + interval*5, width + gridsize,  buttonSize, buttonSize/2);
    Giggles->setGeometry(gridsize + interval*2, width + gridsize, buttonSize, buttonSize/2);
    Splendid->setGeometry(gridsize + interval*3, width + gridsize, buttonSize, buttonSize/2);

    // 词缀数量
    QLabel *label = new QLabel(this);
    label->resize(150,30);
    label->move(length + gridsize ,gridsize);
    label->setText("词缀库");
    QFont font = label->font();
    font.setPointSize(16);  // 设置字体大小
    label->setFont(font);
    label->setTextFormat(Qt::MarkdownText);
    int affix_num_interval = 40;

    font.setPointSize(14);  // 设置字体大小
    awake_num = new QLabel("Awake: 0", this);
    awake_num->setGeometry(length + gridsize, gridsize+affix_num_interval, 100, 20); awake_num->setFont(font);
    icy_num = new QLabel("Icy: 0", this);
    icy_num->setGeometry(length + gridsize, gridsize+affix_num_interval*2, 100, 20); icy_num->setFont(font);
    poison_num = new QLabel("Poison: 0", this);
    poison_num->setGeometry(length + gridsize, gridsize+affix_num_interval*3, 100, 20); poison_num->setFont(font);
    aoe_num = new QLabel("AOE: 0", this);
    aoe_num->setGeometry(length + gridsize, gridsize+affix_num_interval*4, 100, 20); aoe_num->setFont(font);

    Flippy->setFont(font);
    Giggles->setFont(font);
        Splendid->setFont(font);
saveButton->setFont(font);
        saveMapButton->setFont(font);
    // coin数量
    font.setPointSize(19);
    coinLabel = new QLabel("Coin: 0", this);
    coinLabel->resize(150,30);
    coinLabel->move(length + gridsize ,gridsize / 2);
    coinLabel->setFont(font);
    coinLabel->setTextFormat(Qt::MarkdownText);


    int interval_time = 10;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(interval_time); // 启动定时器

    menu[0] = new QMenu("equip affix",this);
    menu[0]->addAction("equip awake");
    menu[0]->addAction("equip icy");
    menu[0]->addAction("equip aoe");
    menu[0]->addAction("equip poison");

    menu[1] = new QMenu("demount affix",this);
    menu[1]->addAction("demount awake");
    menu[1]->addAction("demount icy");
    menu[1]->addAction("demount aoe");
    menu[1]->addAction("demount poison");
    menuBar = new QMenuBar(this);
    menuBar->addMenu(menu[0]);
    menuBar->addMenu(menu[1]);

    QVBoxLayout *Layout = new QVBoxLayout(this);
    Layout->setMenuBar(menuBar);
    setLayout(Layout);

    melee_stab_image = QPixmap(":/res/enemy/hit_2.png");
    remote_boom_image = QPixmap(":/res/enemy/remote_boom.png");
    flippy_stab_image = QPixmap(":/res/tower/flippy_stab.png");
    enemyImage = QPixmap(":/res/enemy/bunny.png");
    affix_tel = QPixmap(":/res/enemy/affix_teleport.png");
    affix_spe = QPixmap(":/res/enemy/affix_speedUp.png");

    switch(game->getStage()){
    case 0: {
        backgroundImage = QPixmap(":/res/background/dream.png"); // 背景图像的文件路径
        rtableImage = QPixmap(":/res/path/path_pink.png");
        pathImage = QPixmap(":/res/path/DW_VastForest.png");
        break;
    }
    case 1: {
        backgroundImage = QPixmap(":/res/background/forest.png"); // 背景图像的文件路径
        rtableImage = QPixmap(":/res/path/path_yellow.png");
        pathImage = QPixmap(":/res/path/rtable_green.png");
        break;
    }
    case 2: {
        backgroundImage = QPixmap(":/res/background/dream.png"); // 背景图像的文件路径
        rtableImage = QPixmap(":/res/path/path_pink.png");
        pathImage = QPixmap(":/res/path/DW_VastForest.png");
        break;
    }
    }

}

void Render::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int gridsize = game->getMap()->getGridSize();



    //绘制背景图像
    // QPixmap backgroundImage(":/res/background/dream.png"); // 背景图像的文件路径
    painter.drawPixmap(0, 0, windowLength, windowWidth, backgroundImage);

    QPixmap levelUp(":/res/tower/levelUp.png");// tower可以升级的标识
    QPixmap level1(":/res/tower/level1.png");
    QPixmap level2(":/res/tower/level2.png");
    QPixmap level3(":/res/tower/level3.png");
    // QPixmap pathImage(":/res/tower/omori.png");
    QPixmap affix_aoe(":/res/tower/affix_aoe.png");
    QPixmap affix_poi(":/res/tower/affix_poison.png");
    QPixmap affix_awa(":/res/tower/affix_awake.png");
    QPixmap affix_icy(":/res/tower/affix_icy.png");
    QPixmap flippy(":/res/tower/flippy.png");
    QPixmap giggles(":/res/tower/giggles.png");
    QPixmap flippy_hit(":/res/tower/flippy_hit.png");
    QPixmap giggles_hit(":/res/tower/giggles_hit.png");
    QPixmap omori(":/res/tower/omori.png");

    QPixmap skill_able_image(":/res/tower/skill.png");

    QBrush station( QColor("#6A5ACD") );
    QBrush frame( QColor("#191970") );
    painter.setBrush(station);
    painter.drawRect(0,width+3, windowLength , windowWidth - width - 3); // 下操作台

    painter.setBrush(station);
    painter.drawRect(length, 0, windowLength - length , windowWidth); // 右操作台

    painter.setBrush(frame);
    painter.drawRect(0, width, length + 5, 5); // 地图下边框
    painter.drawRect(length, 0, 5, width); // 地图右边框


    int awakenum = game->getAffixManager()->getFree_affixNum_tower().at("Awake");
    int icynum = game->getAffixManager()->getFree_affixNum_tower().at("Icy");
    int poisonnum = game->getAffixManager()->getFree_affixNum_tower().at("Poison");
    int aoenum = game->getAffixManager()->getFree_affixNum_tower().at("AOE");
    int coin = game->getCoin();

    awake_num->setText("Awake: " + QString::number(awakenum));
    icy_num->setText("Icy: " + QString::number(icynum));
    poison_num->setText("Poison: " + QString::number(poisonnum));
    aoe_num->setText("AOE: " + QString::number(aoenum));
    coinLabel->setText("Coin: " + QString::number(coin));


    // 绘制部署点
    for(const auto& it : game->getMap()->getRTable()){
        int x = it->pos.x() - gridsize / 2;
        int y = it->pos.y() - gridsize / 2;
        painter.drawPixmap(x, y, gridsize , gridsize, rtableImage);
    }

    // 绘制路径
    for(const auto& path : game->getMap()->getAllPath()){
        for(const auto& it : path->getPathInfor()){
            int x = it->pos.x() - gridsize / 2;
            int y = it->pos.y() - gridsize / 2;
            painter.drawPixmap(x, y, gridsize , gridsize, pathImage);
        }
    }



    // 绘制敌人
    for (const auto &enemy : game->getEnemyManager()->getEnemyList()) {
        if(!enemy || !enemy->getAlive()) continue;

        int x = enemy->getPosition().pos.x(), y = enemy->getPosition().pos.y();
        int size = 50;
        int HPbar_width = 6, internal = 3, affix_size = 15;

        QRect boundingBox = enemy->getBoundingBox();
        QRect affix1 = QRect(x - size*0.5, y - size - HPbar_width - internal*2 ,affix_size,affix_size);
        QRect affix2 = QRect(x + size*0.2, y - size - HPbar_width - internal*2 ,affix_size,affix_size);

        painter.drawPixmap(boundingBox, enemyImage);

        // 血条
        QBrush red_brush( QColor("#F20900") );
        painter.setBrush(red_brush);
        float rate = 1.0*enemy->getHp() / enemy->getTotalHp();//计算比例
        painter.drawRect(x - size*0.5, y - size - HPbar_width - internal , rate * size, HPbar_width);//绘制矩形


        // 词缀
        if(!enemy->getAffixSlot().empty()){
            int counter = 0;
            if(enemy->findAffix(teleport)){
                painter.drawPixmap(affix1,affix_tel);
                counter++;
            }
            if(enemy->findAffix(speedUp)){
                counter++;
                if(counter == 1) painter.drawPixmap(affix2,affix_spe);
                else painter.drawPixmap(affix1,affix_spe);
            }
        }
    }



    // 绘制塔
    for(const auto &tower:game->getTowerManager()->getTowerList()){
        if(!tower || !tower->getAlive()) continue;

        QPoint pos = tower->getPosition().pos;
        QRect boundingBox = tower->getBoundingBox();
        int range = tower->getRange();

        int x = pos.x(), y = pos.y();
        int size = 50;
        int HPbar_width = 6, internal = 3, affix_size = 15;

        QRect affix1 = QRect(x - size, y - size  ,affix_size*2,affix_size*2);
        QRect affix2 = QRect(x + size*0.3, y - size  ,affix_size*2,affix_size*2);
        QRect levelUp_r = QRect(x + size * 0.3, y  - size , affix_size *2,affix_size*2);
        QRect level_r = QRect(x - size * 0.8, y - size - 40 - HPbar_width - internal - affix_size*2 ,affix_size*5,affix_size*5);
        QRect skill_able = QRect(x + size * 0.3, y - size - 40 - HPbar_width - internal - affix_size ,affix_size*3,affix_size*3);


        switch(tower->getName()){
        case _Flippy:{
            if(tower->getHitted() > 0) {painter.drawPixmap(boundingBox, flippy_hit);tower->setHitted(tower->getHitted() - 1);}
            else painter.drawPixmap(boundingBox, flippy);

            break;
        }
        case _Giggles:{
            if(tower->getHitted() > 0) {painter.drawPixmap(boundingBox, giggles_hit); tower->setHitted(tower->getHitted() - 1);}
            else painter.drawPixmap(boundingBox, giggles);
            break;
        }
        case _Splendid:{
            painter.drawPixmap(boundingBox, omori);
            break;
        }
        }
        // // 绘制攻击范围
        // QPen pen(Qt::gray, 1);   // 黑色画笔，宽度为2
        // painter.setPen(pen);
        // painter.setBrush(Qt::NoBrush);
        // painter.drawEllipse(pos, range, range);

        // 绘制等级
        if(tower->getLevelUP_able()){
            painter.drawPixmap(levelUp_r, levelUp);
        }
        int level = tower->getLevel();
        switch(level){
        case 0:{
            break;
        }
        case 1:{
            painter.drawPixmap(level_r, level1);
            break;
        }
        case 2:{
            painter.drawPixmap(level_r, level2);
            break;
        }
        case 3:{
            painter.drawPixmap(level_r, level3);
            break;
        }
        }


        if(tower->getRelease_skill_able()){
            painter.drawPixmap(skill_able, skill_able_image);
        }

        // 血条
        QBrush red_brush( QColor("#F20900") );
        painter.setBrush(red_brush);
        float rate = 1.0*tower->getHp() / tower->getTotalHp();//计算比例
        painter.drawRect(x - size*0.5, y - size - HPbar_width - internal*6 , rate * size, HPbar_width);//绘制矩形



        // 词缀
        if(!tower->getAffixSlot().empty()){
            int counter = 0;
            if(tower->findAffix(aoe)){
                painter.drawPixmap(affix1,affix_aoe);
                counter++;
            }
            if(tower->findAffix(awake)){             
                if(counter == 1) painter.drawPixmap(affix2,affix_awa);
                else painter.drawPixmap(affix1,affix_awa);
                counter++;
            }
            if(tower->findAffix(poison)){               
                if(counter == 1) painter.drawPixmap(affix2,affix_poi);
                else painter.drawPixmap(affix1,affix_poi);
                counter++;
            }
            if(tower->findAffix(icy)){            
                if(counter == 1) painter.drawPixmap(affix2,affix_icy);
                else painter.drawPixmap(affix1,affix_icy);
                counter++;
            }
        }
    }


    // 受到攻击的效果

    QPen red_pen( QColor("#F20900") );

    for(auto it : game->getFightSystem()->getBulletList()){
        if(!it || it->getTime() <= 0){
            continue;
        }
        QRect damageRect = QRect(it->getPosition().x()-25, it->getPosition().y()-25, 40,40);

        switch(it->getType()){
        case melee_stab:
            painter.drawPixmap(damageRect, melee_stab_image);
            break;
        case remote_boom:
            painter.drawPixmap(damageRect, remote_boom_image);
            break;
        // case cure:
        case flippy_stab:
            painter.drawPixmap(damageRect, flippy_stab_image);
            break;
        case laser:
            QPoint begin = it->getBegin();
            begin.rx() -= 20;
            begin.ry() -= 40;
            QPoint end = it->getEnd();
            bullet->show();
            QPropertyAnimation *animation = new QPropertyAnimation(bullet, "pos");
            animation->setDuration(50);  // 动画持续时间
            animation->setStartValue(begin);
            animation->setEndValue(end);
            connect(animation, &QPropertyAnimation::finished, this, &Render::hideBullet);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
            break;
        }
        it->decreaseTime();
    }
    // 受到治疗
    QPixmap tea_cure(":/res/tower/h_tea_time.png");

    for(auto& it : game->getHealthSystem()->getCureImagePos()){
        if(!it || it->getTime() <= 0){
            continue;
        }
        QRect Rect = QRect(it->getPosition().x()-40, it->getPosition().y()-40, 40,40);
        painter.drawPixmap(Rect, tea_cure);
        it->decreaseTime();
    }

}

void TowerStatus::paintEvent(QPaintEvent *event) {

    if(!tower->getAlive()){
        this->hide();
        return;
    }

    QPainter painter(this);

    //绘制背景图像
    QPixmap backgroundImage(":/res/background/window.png"); // 背景图像的文件路径
    painter.drawPixmap(0, 0, width(), height(), backgroundImage);


    QString tname;
    switch(tower->getName()){

    case _Giggles:tname="Giggles";
        break;
    case _Flippy:tname="Flippy";
        break;
    case _Splendid:tname="Splendid"; break;
    case Flaky:
        break;
    }

    name->setText("  "+tname);
    hp->setText("HP："+QString::number(tower->getHp()));
    attackPower->setText("攻击力："+QString::number(tower->getTrueAttackPower()));
    defence->setText("防御力："+QString::number(tower->getDefence()));
    // attackInterval->setText("攻击间隔："+QString::number(tower->getTrueAttackInterval()));


}

