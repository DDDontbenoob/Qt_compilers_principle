#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graphics_view_zoom.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    Ui::MainWindow *ui;
    Graphics_view_zoom *myView;     //自定义视图，用于鼠标缩放
    QVector<QWidget*> tabWigetsVector;  //保存tab部件指针
    QVector<QIcon> tabIconVector;       //保存tab部件Icon
    QVector<QString> tabTextVector;     //保存tab部件标题
    QGraphicsScene *scene;          //场景
private slots:
    void on_actioncompile_triggered();
};
#define LINE_INFO_WIDTH 0   //预留边框用于信息展示
#define MARGIN 30          //视图左边距
#define NET_WIDTH 6000      //网络图最大宽度
#define NET_HEIGHT 6000     //网络图最大高度
#define SCENE_WIDTH (LINE_INFO_WIDTH+MARGIN*2+NET_WIDTH)    //视图宽度
#define SCENE_HEIGHT (MARGIN*2+NET_HEIGHT)                  //视图高度

#define EDGE_PEN_WIDTH 2    //线路边宽
#define NODE_HALF_WIDTH 3   //节点大小
#endif // MAINWINDOW_H
