#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent*) override;
private:
    Ui::MainWindow *ui;
    int n;
    QVector<QPoint> points;
    QVector<QPoint> conv_hull;
};

#endif // MAINWINDOW_H
