#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupWindow();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupWindow()
{
    // 设置窗口大小
    this->resize(750, 500);

    // 可选：设置窗口标题
    this->setWindowTitle("My Game Window");

    // 可选：设置窗口的最小和最大尺寸（以防用户调整窗口大小）
    this->setMinimumSize(1000, 750);
    this->setMaximumSize(1000, 750);

    // 设置背景图片
    QFile file(":/myresourses/background/map1.jpeg"); // 假设图片在资源文件中，路径为":/images/background.jpg"
    if (!file.exists()) {
        qWarning() << "Background image not found!";
    } else {
        this->setStyleSheet("MainWindow {"
                            "border-image: url(:/images/background.jpg) 0 0 0 0 stretch stretch;"
                            "}");
    }
}
