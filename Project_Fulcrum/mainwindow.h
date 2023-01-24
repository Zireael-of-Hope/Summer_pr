#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QLabel>>
#include <QKeyEvent>
#include "human.h"
#include "obstacle.h"
#include "ore.h"
#include "food.h"
#include "border.h"
#include "foodstorage.h"
#include "orestorage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene  *scene;
    QTimer* timer;
    Human* human;
    QList<Human*> humans;
    QList<Food*> foodObjects;
    QList<Ore*> oreObjects;
    QList<Obstacle*> obstacleObjects;
    Border* border_bottom;
    Border* border_top;
    Border* border_left;
    Border* border_right;
    FoodStorage* foodStorage;
    OreStorage* oreStorage;

    void keyPressEvent(QKeyEvent *e) override;

    void createHuman();
    void createFoodObject(FoodColor foodColor, int pointsToCollectFoodObject);
    void createOreObject(OreColor oreColor, int pointsToCollectOreObject);
    void createObstacleObject(ObstacleColor obstacleColor, int width, int hight);

    void DeleteHuman(Human* humanToDelete);
    void DeleteDepletedFoodObject(Food* depletedFoodObject);
    void DeleteDepletedOreObject(Ore* depletedFoodObject);
    void DeleteObstacleObject(Obstacle *obstacleObject);

public slots:
    void slotCheckFacedObject(QGraphicsItem *facedObject, Human *humanSender, int foodRequest, int oreRequest, bool isMovingToStorage);
    void slotDebug(int a, int b, int c);
};

#endif // MAINWINDOW_H
