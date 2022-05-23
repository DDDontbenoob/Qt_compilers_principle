#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsItem>
#include <QMessageBox>
#include <QColorDialog>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <QDir>

#include "sdt.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myView = new Graphics_view_zoom(ui->graphicsView);
    myView->set_modifiers(Qt::NoModifier);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);//抗锯齿设置

    scene=new QGraphicsScene;
    scene->setSceneRect(-LINE_INFO_WIDTH,0,SCENE_WIDTH,SCENE_HEIGHT);//设置场景边界
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    tabWigetsVector.push_back(ui->tree);
    tabWigetsVector.push_back(ui->thraddrcode);
    tabWigetsVector.push_back(ui->other);

    tabTextVector.push_back("语法分析树");
    tabTextVector.push_back("三地址码");
    tabTextVector.push_back("其他");
    ui->tabWidget->clear();
    ui->tabWidget->addTab(tabWigetsVector[0],tabTextVector[0]);
    ui->tabWidget->addTab(tabWigetsVector[1],tabTextVector[1]);
    ui->tabWidget->addTab(tabWigetsVector[2],tabTextVector[2]);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actioncompile_triggered()
{
    QString text=ui->textEdit->toPlainText();//获取文本输入框代码
    istringstream in(text.toStdString());
    auto lexres=getLexRes(in);
    print_lexres(lexres);
    ifstream gra_text("../compilers_principle/input/grammer.txt",ios::in);
    //cout<<QDir::currentPath().toStdString()<<endl;
    if(!gra_text.is_open()){cout<<"grammer.txt failed!"<<endl;return;}
    Grammer G(gra_text);
    ofstream ofs1("../compilers_principle/output/action_table.txt",ios::out);
    G.print_actiontable(ofs1);
    SLR slr(G);
    slr.make_input(lexres);
    slr.start();
    slr.print();
    ostringstream ofs;
    SDT sdt(slr,ofs);
    sdt.start();
    ui->textBrowser->setText(QString::fromStdString(ofs.str()));
}
