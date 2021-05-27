#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>

#include "avl_tree.h"
#include "splay_tree.h"
#include "treap.h"

node_avl * root_avl = new node_avl;
node_splay * root_splay = new node_splay;
node_treap * root_treap = new node_treap;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene_avl = new QGraphicsScene;
    scene_splay = new QGraphicsScene;
    scene_treap = new QGraphicsScene;

    ui->showMeWhatYouGot->setScene(scene_avl);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPen border(Qt::black);
QBrush fillMe(Qt::darkMagenta);

void MainWindow::on_AVLButton_clicked()
{
    ui->showMeWhatYouGot->setScene(scene_avl);
}


void MainWindow::on_NewNode_clicked()
{
    int num = ui->number->text().toInt();
    std::cout << num << std::endl;
}


void MainWindow::drawVertex(int num, int x, int y, int width = 50) {
    int high = 30;
    QFont fnt = QFont("Times new roman", 14, QFont::Bold);

    QGraphicsEllipseItem * elipse = scene_treap->addEllipse(x, y, width, high, border, fillMe);
    QGraphicsTextItem * pos = scene_treap->addText("", fnt);
    pos->setPos(x, y);
    pos->setTextWidth(width);
}

void MainWindow::on_TreapButton_clicked()
{
    ui->showMeWhatYouGot->setScene(scene_treap);
    /*

    QGraphicsEllipseItem * el = scene_treap->addEllipse(5, 6, 100, 100, border, fillMe);

    el->setZValue(-1);
    QPainter *painter = new QPainter;
    QFont fnt;
    fnt.setPixelSize(18);
    painter->setPen(Qt::black);
    painter->setFont(fnt);
    painter->drawText(5, 6, 100, 100, Qt::AlignHCenter, QString::number(5));
    QGraphicsTextItem * pos = scene_treap->addText("AAAAA");
    pos->setPos(5, 6);*/
}


void MainWindow::on_SplayButton_clicked()
{
    ui->showMeWhatYouGot->setScene(scene_splay);
}


void MainWindow::on_DeleteTree_clicked()
{
    int num = ui->numberDelete->text().toInt();
    std::cout << num << std::endl;
}

