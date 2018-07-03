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

Cut random_cut() {
    std::random_device device;
    std::default_random_engine g(device());
    std::uniform_real_distribution<double> distr_y(0, 600.0);
    std::uniform_real_distribution<double> distr_x(0, 1200.0);
    return Cut(QPoint(distr_x(g), distr_y(g)), QPoint(distr_x(g), distr_y(g)));
}

Cut cutting(Cut cut, QPoint ld, QPoint ur) {
    double m1 = -cut.start.x() + cut.finish.x();
    double m2 = -cut.start.y() + cut.finish.y();
    double t_min = 0.;
    double t_max = 1.;
    if (m1 > 0) {
        t_min = std::min(t_max, std::max(t_min, (ld.x() - cut.start.x()) / m1));
        t_max = std::max(t_min, std::min(t_max, (ur.x() - cut.start.x()) / m1));
    } else if (m1 < 0){
        t_max = std::max(t_min, std::min(t_max, (ld.x() - cut.start.x()) / m1));
        t_min = std::min(t_max, std::max(t_min, (ur.x() - cut.start.x()) / m1));
    } else {
        if (cut.start.x() < ld.x() || cut.start.x() > ur.x()) {
            t_min = 1.;
        }
    }
    if (m2 > 0) {
        t_min = std::min(t_max, std::max(t_min, (ld.y() - cut.start.y()) / m2));
        t_max = std::max(t_min, std::min(t_max, (ur.y() - cut.start.y()) / m2));
    } else if (m2 < 0){
        t_max = std::max(t_min, std::min(t_max, (ld.y() - cut.start.y()) / m2));
        t_min = std::min(t_max, std::max(t_min, (ur.y() - cut.start.y()) / m2));
    } else {
        if (cut.start.y() < ld.y() || cut.start.y() > ur.y()) {
            t_min = 1.;
        }
    }
    if (t_min < t_max) {
        return {QPoint(m1 * t_min + cut.start.x(), m2 * t_min + cut.start.y()),
                    QPoint(m1 * t_max + cut.start.x(), m2 * t_max + cut.start.y())};
    } else {
        return {QPoint(0, 0), QPoint(0, 0)};
    }
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
                             10, 10, 1000, 1, &ok);
        }
    QObject::connect(ui->renew_lines, SIGNAL(clicked(bool)), this, SLOT(renew_button()));
    cuts.resize(n);
    for (int i = 0; i < n; ++i) {
        cuts[i] = random_cut();
    }
    ld = QPoint(0, 0);
    ur = QPoint(0, 0);
    p = QPoint(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPen pen(QBrush(Qt::blue), 1);
    painter.setPen(pen);
    for (int i = 0; i < cuts.size(); ++i) {
        if (cuts[i].start != cuts[i].finish) {
            painter.drawLine(cuts[i].start, cuts[i].finish);
        }
    }
    if (ld != p) {
        painter.setPen(QPen(QBrush(Qt::black), 1));
        painter.drawRect(ld.x(), ld.y(), p.x() - ld.x(), p.y() - ld.y());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    ur = event->pos();
    p = ur;
    if (ld != ur) {
        for (int i = 0; i < n; ++i) {
            cuts[i] = cutting(cuts[i], ld, ur);
        }
    }
    this->repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    ld = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    p = event->pos();
    this->repaint();
}

void MainWindow::renew_button() {
    bool ok = false;
        while (!ok) {
        n = QInputDialog::getInt(this, tr("Input vertex number"),
                             tr("Number of vertices:"),
                             100, 100, 1000, 1, &ok);
        }
    cuts.resize(n);
    for (int i = 0; i < n; ++i) {
        cuts[i] = random_cut();
    }
    ld = QPoint(0, 0);
    ur = QPoint(0, 0);
    p = QPoint(0, 0);
    this->repaint();
}
