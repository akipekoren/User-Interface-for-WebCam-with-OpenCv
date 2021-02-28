#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>

#include "opencv2/opencv.hpp"
#include <QImage>
#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QGraphicsLayout>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>


#include <QMessageBox>
#include <QDebug>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_DeviceButton_pressed();

    void on_exitButton_pressed();

    void on_RTSPButton_pressed();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture video;
    QGraphicsPixmapItem pixItem;


};

#endif // MAINWINDOW_H
