#include "menu.h"


Menu::Menu(QWidget *parent) : QWidget(parent) {
    // 按钮
    // startButton = new QPushButton("Start New Game", this);

    QFont ft;
    ft.setPointSize(14);

    startButton = new QPushButton("选择关卡", this); startButton->setFont(ft);
    loadSaveButton = new QPushButton("导入存档", this); loadSaveButton->setFont(ft);
    loadMapButton = new QPushButton("导入地图", this); loadMapButton->setFont(ft);

    startButton->setFixedSize(400, 300);
    loadSaveButton->setFixedSize(400, 300);
    loadMapButton->setFixedSize(400, 300);

    startButton->setStyleSheet(
        "QPushButton {"
        "border: none;"  // 去除按钮的边框
        "background-image: url(:/res/background/button.png);"  // 设置背景图片路径
        "background-repeat: no-repeat;"  // 禁止背景图片重复
        "background-position: center;"  // 背景图片居中
        "}"
        "QPushButton:hover {"
        "background-image: url(:/res/background/button.png);"  // 设置鼠标悬停时的背景图片
        "}"
        "QPushButton:pressed {"
        "background-image: url(:/res/background/button.png);"  // 设置按钮按下时的背景图片
        "}"
        );
    loadSaveButton->setStyleSheet(
        "QPushButton {"
        "border: none;"  // 去除按钮的边框
        "background-image: url(:/res/background/button.png);"  // 设置背景图片路径
        "background-repeat: no-repeat;"  // 禁止背景图片重复
        "background-position: center;"  // 背景图片居中
        "}"
        "QPushButton:hover {"
        "background-image: url(:/res/background/button.png);"  // 设置鼠标悬停时的背景图片
        "}"
        "QPushButton:pressed {"
        "background-image: url(:/res/background/button.png);"  // 设置按钮按下时的背景图片
        "}"
        );
    loadMapButton->setStyleSheet(
        "QPushButton {"
        "border: none;"  // 去除按钮的边框
        "background-image: url(:/res/background/button.png);"  // 设置背景图片路径
        "background-repeat: no-repeat;"  // 禁止背景图片重复
        "background-position: center;"  // 背景图片居中
        "}"
        "QPushButton:hover {"
        "background-image: url(:/res/background/button.png);"  // 设置鼠标悬停时的背景图片
        "}"
        "QPushButton:pressed {"
        "background-image: url(:/res/background/button.png);"  // 设置按钮按下时的背景图片
        "}"
        );

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(startButton);
    layout->addWidget(loadSaveButton);
    layout->addWidget(loadMapButton);
    setLayout(layout);

    connect(startButton, &QPushButton::clicked, this, &Menu::selectStage);
    connect(loadSaveButton, &QPushButton::clicked, this, &Menu::loadSave);
    connect(loadMapButton, &QPushButton::clicked, this, &Menu::loadMap);
}

void Menu::selectStage(){
    emit hideMenu();
    emit showStageSelect();
}

void Menu::loadSave(){// 用户选择存档文件，并开始游戏

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);// 设置文件对话框的模式为选择文件
    QString selectedFile;
    if (dialog.exec()){// 获取用户选择的文件路径
        selectedFile = dialog.selectedFiles().at(0);
    }
    else{qDebug() << "select file cancel";}

    QString appDirPath = QCoreApplication::applicationDirPath();
    QDir currentDir(appDirPath);
    QString relativePath = currentDir.relativeFilePath(selectedFile);
    qDebug() << "user select: " << relativePath; // "Json/savegame0.json"

    GameSave gamesave;
    gamesave.setRelativePath(relativePath);
    emit initializeGame_save(gamesave);

}

void Menu::loadMap(){ // 用户选择地图，并在地图上开始新游戏

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);// 设置文件对话框的模式为选择文件
    QString selectedFile;
    if (dialog.exec()){// 获取用户选择的文件路径
        selectedFile = dialog.selectedFiles().at(0);
    }
    else{qDebug() << "select file cancel";}

    QString appDirPath = QCoreApplication::applicationDirPath();
    QDir currentDir(appDirPath);
    QString relativePath = currentDir.relativeFilePath(selectedFile);
    qDebug() << "user select: " << relativePath; // "Json/savegame0.json"

    GameSave gamesave;
    std::shared_ptr<Scenemap> map = gamesave.loadMap(relativePath);
    qInfo() << map->getLength();

    // 注册类型
    qRegisterMetaType<std::shared_ptr<Scenemap>>("std::shared_ptr<Scenemap>");

    emit initializeGame_map(map);
}
