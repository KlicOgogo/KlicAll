#include <QInputDialog>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>
#include <QPoint>
#include <QVector>
#include <QPolygon>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QSize>
#include <climits>

QVector<QPoint> polygon(int n) {
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_real_distribution<double> x_distr(20., 1200.0);
    std::uniform_real_distribution<double> y_distr(20., 700.0);
    QVector<QPoint> QPoints(n);
    for (int i = 0; i < n; ++i) {
        QPoints[i] = QPoint(x_distr(generator), y_distr(generator));
    }
    return QPoints;
}

bool has_right_rotate(QPoint v, QPoint top, QPoint w) {
    return (top.x() - v.x()) * (w.y() - top.y()) - (top.y() - v.y()) * (w.x() - top.x()) <= 0;
}

bool point_pred(QPoint a, QPoint b) {
    if (a.x() != b.x()) {
        return a.x() < b.x();
    } else {
        return a.y() < b.y();
    }
}

bool pair_pred(std::pair<double, QPoint> a, std::pair<double, QPoint> b) {
    if (a.first != b.first) {
        return a.first < b.first;
    } else {
        return point_pred(a.second, b.second);
    }
}

QVector<QPoint> convex_hull(const QVector<QPoint> &pol) {
    QPoint min_point = *std::min_element(pol.begin(), pol.end(), point_pred);
    std::vector<double> tans(pol.size());
    for (int i = 0; i < pol.size(); ++i) {
        if (pol[i].x() == min_point.x()) {
            if (pol[i].y() != min_point.y()) {
                tans[i] = std::numeric_limits<double>::max();
            } else {
                tans[i] = -std::numeric_limits<double>::max();
            }
        } else {
            tans[i] = (double)(pol[i].y() - min_point.y()) / (pol[i].x() - min_point.x());
        }
    }
    std::vector<std::pair<double, QPoint> > for_sort(pol.size());
    for (int i = 0; i < pol.size(); ++i) {
        for_sort[i].first = tans[i];
        for_sort[i].second = pol[i];
    }
    std::sort(for_sort.begin(), for_sort.end(), pair_pred);
    QVector<QPoint> conv_hull;
    conv_hull.push_back(for_sort[0].second);
    conv_hull.push_back(for_sort[1].second);
    for (int i = 2; i < for_sort.size(); ++i) {
        while (has_right_rotate(conv_hull[conv_hull.size() - 2],
                                conv_hull.back(),
                                for_sort[i].second) && conv_hull.size() > 1) {
            conv_hull.pop_back();
        }
        conv_hull.push_back(for_sort[i].second);
    }
    return conv_hull;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool ok = false;
    while (!ok) {
    n = QInputDialog::getInt(this, tr("Input vertex number"),
                         tr("Number of vertices:"),
                         1000, 10, 10000000, 1, &ok);
    }
    points = polygon(n);
    conv_hull = convex_hull(points);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPen pen(QBrush(Qt::blue), 3);
    painter.setPen(pen);
    QPolygon poi = QPolygon(points);
    if (!conv_hull.empty()) {
         QPolygon pol = QPolygon(conv_hull);
         painter.drawPolygon(pol);
    }
    painter.drawPoints(poi);
}
