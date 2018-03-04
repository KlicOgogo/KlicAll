#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->renew_n, SIGNAL(clicked(bool)), this, SLOT(renew_button()));
    points.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    points.emplace_back(event->pos());
    this->repaint();
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPen pen(QBrush(Qt::black), 4);
    painter.setPen(pen);
    for (int i = 0; i < points.size(); ++i) {
        painter.drawPoint(points[i]);
    }
    pen.setWidth(2);
    painter.setPen(pen);
    for (int i = 1; i < points.size(); ++i) {
        painter.drawLine(points[i-1], points[i]);
    }
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    int n = points.size();
    std::vector<QPoint> line(10001);
    double t = 0;
    if (n > 1) {
        for (int i = 0; i < 10001; ++i) {
            double x = std::pow(1-t, n-1) * points[0].x();
            double temp_x = x;
            double y = std::pow(1-t, n-1) * points[0].y();
            double temp_y = y;
            for (int j = 1; j < n; ++j) {
                temp_x *= points[j].x() * t * (n-j) / j / (1-t) / points[j-1].x();
                x += temp_x;
                temp_y *= points[j].y() * t * (n-j) / j / (1-t) / points[j-1].y();
                y += temp_y;
            }
            line[i] = QPoint(x, y);
            t += 0.0001;
        }
        for (int i = 0; i < line.size(); ++i) {
            painter.drawPoint(line[i]);
        }
    }
}

void MainWindow::renew_button() {
    points.clear();
    this->repaint();
}
