#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(0));

    ui->setupUi(this);
    this->resize(1400,900);
    this->setFixedSize(1400,900);

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(-670,-420,1340,840);

    QPen borderPen(Qt::red);

    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(TopLine, borderPen);
    scene->addLine(LeftLine, borderPen);
    scene->addLine(RightLine, borderPen);
    scene->addLine(BottomLine, borderPen);

    border_bottom = new Border(BorderSide::BOTTOM_BORDER);
    border_top = new Border(BorderSide::TOP_BORDER);
    border_left = new Border(BorderSide::LEFT_BORDER);
    border_right = new Border(BorderSide::RIGHT_BORDER);
    scene->addItem(border_bottom);
    scene->addItem(border_top);
    scene->addItem(border_left);
    scene->addItem(border_right);

    foodStorage = new FoodStorage();
    oreStorage = new OreStorage();
    scene->addItem(foodStorage);
    scene->addItem(oreStorage);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    int tempRand;

    if (e->key() == Qt::Key_Space)
    {
        createHuman();
    };

    if (e->key() == Qt::Key_5)
    {
        foreach(Human* humanToUnload, humans)
        {
            humanToUnload->UnloadEverything();
        }
    };

    if (e->key() == Qt::Key_4)
    {
        foreach(Food* foodObjectToDelete, foodObjects)
        {
            DeleteDepletedFoodObject(foodObjectToDelete);
        }
        foreach(Ore* oreObjectToDelete, oreObjects)
        {
            DeleteDepletedOreObject(oreObjectToDelete);
        }
        foreach(Obstacle* obstacleObjectToDelete, obstacleObjects)
        {
            DeleteObstacleObject(obstacleObjectToDelete);
        }
        foreach(Human* humanToDelete, humans)
        {
            DeleteHuman(humanToDelete);
        }
        foodStorage->MakeEmpty();
        oreStorage->MakeEmpty();
    };

    if (e->key() == Qt::Key_3)
    {
        tempRand = rand() % (2);
        switch (tempRand)
        {
        case 1:
            createObstacleObject(ObstacleColor::ROCK, rand() % (100) + 40, rand() % (100) + 40);
            break;
        case 2:
            createObstacleObject(ObstacleColor::WOOD, rand() % (100) + 40, rand() % (100) + 40);
            break;
        }
    };

    if (e->key() == Qt::Key_2)
    {
        tempRand = rand() % (3);
        switch (tempRand)
        {
        case 1:
            createFoodObject(FoodColor::GREEN, rand() % (200) + 100);
            break;
        case 2:
            createFoodObject(FoodColor::RED, rand() % (200) + 100);
            break;
        case 3:
            createFoodObject(FoodColor::YELLOW, rand() % (200) + 100);
            break;
        }

    };

    if (e->key() == Qt::Key_1)
    {
        tempRand = rand() % (3);
        switch (tempRand)
        {
        case 1:
            createOreObject(OreColor::GOLDEN, rand() % (300));
            break;
        case 2:
            createOreObject(OreColor::IRON, rand() % (300));
            break;
        case 3:
            createOreObject(OreColor::COPPER, rand() % (300));
            break;
        }
    };
}

void MainWindow::createHuman()
{
    human = new Human(foodStorage, oreStorage);
    scene->addItem(human);
    humans.append(human);
    human->checkForCollision();
    connect(human, &Human::signalCheckItem, this, &MainWindow::slotCheckFacedObject);
    connect(human, &Human::signalDebug, this, &MainWindow::slotDebug);
}

void MainWindow::createFoodObject(FoodColor foodColor, int pointsToCollectFoodObject = 180)
{
    Food *foodObject = new Food(foodColor, pointsToCollectFoodObject);
    scene->addItem(foodObject);
    foodObjects.append(foodObject);
    foodObject->checkForCollision();
}

void MainWindow::createOreObject(OreColor oreColor, int pointsToCollectFoodObject = 180)
{
    Ore *oreObject = new Ore(oreColor, pointsToCollectFoodObject);
    scene->addItem(oreObject);
    oreObjects.append(oreObject);
    oreObject->checkForCollision();
}

void MainWindow::createObstacleObject(ObstacleColor obstacleColor, int width, int hight)
{
    Obstacle *obstacleObject = new Obstacle(obstacleColor, width, hight);
    scene->addItem(obstacleObject);
    obstacleObjects.append(obstacleObject);
    obstacleObject->checkForCollision();
}

void MainWindow::slotCheckFacedObject(QGraphicsItem *facedObject, Human* humanSender, int foodRequest, int oreRequest, bool isMovingToStorage)
{
    if(!isMovingToStorage)
    {
        foreach(Food* possibleFoodObject, foodObjects)
        {
            if (possibleFoodObject == facedObject)
            {
                if (possibleFoodObject->getCollected(foodRequest)) // true if depleted
                {
                    DeleteDepletedFoodObject(possibleFoodObject);
                }
                humanSender->collectFood(foodRequest);
            }
        }
        foreach(Ore* possibleOreObject, oreObjects)
            {
                if (possibleOreObject == facedObject)
                {
                    if (possibleOreObject->getCollected(oreRequest)) // true if depleted
                    {
                        DeleteDepletedOreObject(possibleOreObject);
                    }
                    humanSender->collectOre(oreRequest);
                }
            }
        foreach(Obstacle* possibleObstacleObject, obstacleObjects)
            {
                if (possibleObstacleObject == facedObject)
                {
                    humanSender->DoCollision(possibleObstacleObject->getSideOfCollision(humanSender->getLocation()));
                }
            }
        if (facedObject == foodStorage || facedObject == oreStorage)
            humanSender->DoCollision();
    }
    else
    {
        if (facedObject == foodStorage)
        {
            foodStorage->GetResources(humanSender->GetPackageOfFood());
            humanSender->unloadPackageOfFood();
        }
        if (facedObject == oreStorage)
        {
            oreStorage->GetResources(humanSender->GetPackageOfOre());
            humanSender->unloadPackageOfOre();
        } 
    }

    if (facedObject == border_bottom)
        humanSender->DoCollision(WhatSideCollisionIsFrom::TOP);
    if (facedObject == border_top)
        humanSender->DoCollision(WhatSideCollisionIsFrom::BOTTOM);
    if (facedObject == border_left)
        humanSender->DoCollision(WhatSideCollisionIsFrom::RIGHT);
    if (facedObject == border_right)
        humanSender->DoCollision(WhatSideCollisionIsFrom::LEFT);
}

void MainWindow::slotDebug(int a, int b, int c)
{
    ui->label->setText(QString::number(a));
    ui->label_2->setText(QString::number(b));
    ui->label_3->setText(QString::number(c));
}

void MainWindow::DeleteDepletedFoodObject(Food *depletedFoodObject)
{   
    scene->removeItem(depletedFoodObject);
    foodObjects.removeOne(depletedFoodObject);
}

void MainWindow::DeleteDepletedOreObject(Ore *depletedOreObject)
{
    scene->removeItem(depletedOreObject);
    oreObjects.removeOne(depletedOreObject);
}

void MainWindow::DeleteObstacleObject(Obstacle *obstacleObject)
{
    scene->removeItem(obstacleObject);
    obstacleObjects.removeOne(obstacleObject);
}

void MainWindow::DeleteHuman(Human *humanToDelete)
{
    scene->removeItem(humanToDelete);
    humans.removeOne(humanToDelete);
}
