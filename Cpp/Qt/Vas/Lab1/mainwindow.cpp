#include <QInputDialog>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <random>
#include <cassert>
#include <QPoint>
#include <QVector>
#include <QPolygon>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QSize>

bool intercept(QPoint beam_start, QPoint prev, QPoint cur, QPoint next) {
    if (beam_start.y() == cur.y()) {
        if (beam_start.x() < cur.x()) {
            return (beam_start.y() - prev.y()) * (beam_start.y() - next.y()) < 0;
        } else {
            return false;
        }
    }
    if (beam_start.y() <= std::min(cur.y(), next.y()) ||
            beam_start.y() >= std::max(cur.y(), next.y())) {
        return false;
    }
    double x_inter = cur.x() + (double)((beam_start.y() - cur.y()) *
                                        (next.x() - cur.x())) / (next.y() - cur.y());
    if (beam_start.x() < x_inter) {
        return true;
    } else {
        return false;
    }
}

bool in(std::vector<QPoint> polygon, QPoint point) {
    assert(polygon.size() > 2);
    int n = polygon.size();
    int inter_count = 0;
    for (int i = 0; i < polygon.size(); ++i) {
        if (intercept(point, polygon[(i-1 + n) % n], polygon[i], polygon[(i+1) % n])) {
            ++inter_count;
        }
    }
    return inter_count % 2 == 1;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->renew, SIGNAL(clicked(bool)), this, SLOT(renew_button()));
    QMainWindow::setMouseTracking(true);
    ui->text_label->setGeometry(0, 0, 300, 15);
    ui->text_label->setText("Draw polygon, please.");
    ui->renew->setGeometry(0, 20, 50, 40);
    ui->renew->setText("Clear");
    drawn = false;
    points.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPen pen(QBrush(Qt::black), 2);
    painter.setPen(pen);
    for (int i = 0; i < points.size(); ++i) {
        if (i < points.size() -1) {
            painter.drawLine(points[i], points[i+1]);
        }
    }
    if (drawn) {
        painter.drawLine(points[0], points[points.size()-1]);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (!drawn) {
        drawn = true;
        ui->text_label->setText("Polygon was drawn.");
        this->repaint();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (drawn) {
        if (in(this->points, event->pos())) {
            ui->text_label->setText("Yes");
        } else {
            ui->text_label->setText("No");
        }
    } else {
        points.emplace_back(event->pos());
        this->repaint();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (drawn) {
        if (in(this->points, event->pos())) {
            ui->text_label->setText("Yes");
        } else {
            ui->text_label->setText("No");
        }
    } else {
        points.emplace_back(event->pos());
        this->repaint();
    }
}

void MainWindow::renew_button() {
    ui->text_label->setText("Draw polygon, please.");
    points.clear();
    drawn = false;
    this->repaint();
}
