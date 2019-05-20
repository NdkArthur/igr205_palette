#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSlider>
#include <QMainWindow>
#include <QGroupBox>
#include <QBoxLayout>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGroupBox * buttonZone;
};

#endif // MAINWINDOW_H
