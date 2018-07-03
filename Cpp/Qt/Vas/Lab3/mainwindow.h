#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

struct Point3D {
    int x;
    int y;
    int z;
    Point3D(int x_, int y_, int z_): x(x_), y(y_), z(z_) {}
    Point3D() = default;
};

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
    std::vector<Point3D> points;
    std::vector<std::pair<int, int>> edges;
    Point3D center;
    int step;
};

#endif // MAINWINDOW_H
