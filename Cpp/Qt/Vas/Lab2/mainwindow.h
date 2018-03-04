#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct Cut {
    QPoint start;
    QPoint finish;
    Cut() = default;
    Cut(const QPoint &start_, const QPoint &finish_): start(start_),
                                                    finish(finish_) {}
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
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
private:
    Ui::MainWindow *ui;
    std::vector<Cut> cuts;
    int n;
    QPoint ld;
    QPoint ur;
    QPoint p;
private slots:
    void renew_button();
};

#endif // MAINWINDOW_H
