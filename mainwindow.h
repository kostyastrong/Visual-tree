#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtGui>

#include "avl_tree.h"
#include "splay_tree.h"
#include "treap.h"
#include "draw_tree.h"

extern node_avl * root_avl;
extern node_splay * root_splay;
extern node_treap * root_treap;
extern node_draw * root_draw;
extern int scene_index;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AVLButton_clicked();

    void on_NewNode_clicked();

    void on_TreapButton_clicked();

    void on_SplayButton_clicked();

    void on_DeleteTree_clicked();

    void drawVertex(QGraphicsScene * scene_now, int num, int x, int y, int width = 50, int hight = 30);

    void drawTree(QGraphicsScene * scene_now, node_draw * now, int x = 0, int y = 0);

    void clearScene(QGraphicsScene * scene_now);

    void drawLine(QGraphicsScene * scene_now, int x1, int y1, int x2, int y2);

    void initializingTheTree();


private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene_avl;
    QGraphicsScene * scene_splay;
    QGraphicsScene * scene_treap;
};

#endif // MAINWINDOW_H
