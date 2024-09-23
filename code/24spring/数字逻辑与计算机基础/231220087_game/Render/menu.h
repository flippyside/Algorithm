#ifndef MENU_H
#define MENU_H

#include "Render/inputmanager.h"
#include "Render/render.h"
#include "Render/stageselect.h"
#include "game.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include <QObject>

class StageSelect;

class Menu : public QWidget
{
    Q_OBJECT
    QPushButton* startButton;
    QPushButton* loadSaveButton;
    QPushButton* loadMapButton;
public:
    Menu(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap backgroundImage(":/res/background/menu.png");
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
    }

public slots:
    void selectStage();
    void loadSave();// 用户选择存档文件，并开始游戏
    void loadMap();// 用户选择地图，并在地图上开始新游戏

signals:
    void backToStageSelect_signal();
    void showStageSelect();
    void hideMenu();
    void initializeGame_save(GameSave gamesave);
    void initializeGame_map(std::shared_ptr<Scenemap> map);
};


#endif // MENU_H
