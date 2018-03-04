#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QPainter>
#include <QPen>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::ifstream fig("figure.txt");
    int n;
    fig >> n;
    points.resize(n);
    for (int i = 0; i < n; ++i) {
        fig >> points[i].x >> points[i].y >> points[i].z;
    }
    int m;
    fig >> m;
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        fig >> edges[i].first >> edges[i].second;
    }
    fig >> center.x >> center.y >> center.z;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(300);
    step = 10;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {

    center.z -= -step;
    QPainter painter(this);
    QPen pen(QBrush(Qt::blue), 2);
    painter.setPen(pen);
    std::vector<QPoint> drawPoints(points.size());
    for (int i = 0; i < points.size(); ++i) {
        drawPoints[i].setX(center.x + (points[i].x - center.x) * (-center.z) / (points[i].z - center.z));
        drawPoints[i].setY(center.y + (points[i].y - center.y) * (-center.z) / (points[i].z - center.z));
    }
    for (int i = 0; i < edges.size(); ++i) {
        painter.drawLine(drawPoints[edges[i].first - 1], drawPoints[edges[i].second - 1]);
    }
    if (center.z >= 0 || center.z < -2000) {
        step *= -1;
    }
}

