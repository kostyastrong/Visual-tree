#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>

#include "avl_tree.h"
#include "splay_tree.h"
#include "treap.h"
#include "draw_tree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene_avl = new QGraphicsScene;    // 0
    scene_splay = new QGraphicsScene;  // 1
    scene_treap = new QGraphicsScene;  // 2

    ui->showMeWhatYouGot->setScene(scene_avl);

    scene_index = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPen border(Qt::black);
QPen edge(Qt::cyan, 3);
QBrush fillMe(Qt::yellow);

void MainWindow::on_AVLButton_clicked()
{
    ui->showMeWhatYouGot->setScene(scene_avl);
    scene_index = 0;
    initializingTheTree();
}


void MainWindow::on_NewNode_clicked()
{
    int num = ui->number->text().toInt();
    std::cout << num << std::endl;
    InsertSplay(root_splay, num);
    InsertNodeAVL(root_avl, num);

    node_treap * num_treap = new node_treap;
    num_treap->x = num;
    InsertTreap(root_treap, num_treap);

    initializingTheTree();

}

void MainWindow::initializingTheTree() {
    node_avl * avl = nullptr;
    node_splay * splay = nullptr;
    node_treap * treap = nullptr;

    switch(scene_index) {
        case 0:
            avl = root_avl;
            clearScene(scene_avl);
            break;
        case 1:
            splay = root_splay;
            clearScene(scene_splay);
            break;
        case 2:
            treap = root_treap;
            clearScene(scene_treap);
            break;
        default:
            return;
    }

    constructTreeDraw(root_draw, splay, avl, treap);

    switch(scene_index) {
        case 0:
            drawTree(scene_avl, root_draw);
            break;
        case 1:
            drawTree(scene_splay, root_draw);
            break;
        case 2:
            drawTree(scene_treap, root_draw);
            break;
        default:
            return;
    }
}

void MainWindow::drawVertex(QGraphicsScene * scene_now, int num, int x, int y, int width, int hight) {
    QFont fnt = QFont("Times new roman", 14, QFont::Bold);

    QGraphicsEllipseItem * elipse = scene_now->addEllipse(x, y, width, hight, border, fillMe);
    QGraphicsTextItem * pos = scene_now->addText(QString::number(num), fnt);

    QPointF center = elipse->boundingRect().center();
    QPointF text_rect(elipse->mapToScene(center).x() - (elipse->boundingRect().width() / 2),
                      elipse->mapToScene(center).y() - (elipse->boundingRect().height() / 2));
    pos->setDefaultTextColor(Qt::black);
    pos->setPos(x, y);
    pos->setTextWidth(width);
}

void MainWindow::drawLine(QGraphicsScene * scene_now, int x1, int y1, int x2, int y2) {
    QGraphicsLineItem * line = scene_now->addLine(x1, y1, x2, y2, edge);
}

void MainWindow::drawTree(QGraphicsScene * scene_now, node_draw * now, int x, int y) {
    int width = 50, hight = 30;
    drawVertex(scene_now, now->num, x, y, width, hight);
    if (now->left != nullptr) {
        int right_corn_x = x - now->hight * (width + 10), right_corn_y =  y - now->hight * (hight + 10);
        drawLine(scene_now, x, y - hight, right_corn_x, right_corn_y);
        drawTree(scene_now, now->left, right_corn_x - width, right_corn_y);
    }
    if (now->right != nullptr) {
        int left_corn_x = x + now->hight * (width + 10), left_corn_y = y - now->hight * (hight + 10);
        drawLine(scene_now, x + width, y - hight, left_corn_x, left_corn_y);
        drawTree(scene_now, now->right, left_corn_y, left_corn_y);
    }
}

void MainWindow::clearScene(QGraphicsScene * scene_now) {
    clearDraw(root_draw);
    root_draw = new node_draw;
    scene_now->clear();
}

void MainWindow::on_TreapButton_clicked()
{
    ui->showMeWhatYouGot->setScene(scene_treap);
    scene_index = 2;
    initializingTheTree();
    /*
     * drawVertex(scene_treap, 500000, 0, 0);
    drawLine(scene_treap, 0, 0, 50, 50);

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
    scene_index = 1;
    initializingTheTree();
}


void MainWindow::on_DeleteTree_clicked()
{
    int num = ui->numberDelete->text().toInt();
    std::cout << num << std::endl;
}

