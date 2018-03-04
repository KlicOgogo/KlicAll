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
    void mousePressEvent(QMouseEvent *) override;

private:
    Ui::MainWindow *ui;
    std::vector<QPoint> points;
private slots:
    void renew_button();
};

#endif // MAINWINDOW_H
