#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtGui>

#include "avl_tree.h"
#include "splay_tree.h"
#include "treap.h"

extern node_avl * root_avl;
extern node_splay * root_splay;
extern node_treap * root_treap;

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

    void drawVertex(int num, int x, int y, int width);



private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene_avl;
    QGraphicsScene * scene_splay;
    QGraphicsScene * scene_treap;
};

#endif // MAINWINDOW_H
