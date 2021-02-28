#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));       //Create Graphics Scene object
    ui->graphicsView->scene()->addItem(&pixItem);
}

MainWindow::~MainWindow()                                   //Destructor
{
    delete ui;
}






void MainWindow::on_DeviceButton_pressed()                  // Device number button
{
    using namespace cv;


    if(video.isOpened())
    {
        ui->DeviceButton->setText("Play");              // If pressed twice, starts again
        video.release();
        return;
    }

    bool ok;
    QString text = ui->ButtonEdit->text();              // push button
    int devNum = text.toInt(&ok);                       // Converts to Integer (video.open(...))
    qInfo() << devNum;

    if (!ok)                                                        // non-Integer input
      {

        QMessageBox msgBox;
        msgBox.setText("Please enter an Integer!!");
        msgBox.exec();
        return;
      }

    if(!video.open(devNum))                                         // if device number is not found
       {
         QMessageBox msgBox;
         msgBox.setText("Device Number is not correct!!");
         msgBox.exec();
         return;
        }

    ui->DeviceButton->setText("Stop");                              // If there is video, button will be stop

    Mat frames;
    while(video.isOpened())
    {
        video >> frames;                                            // takes frames in a while loop
        if(!frames.empty())
        {

            QImage qimg(frames.data,frames.cols,frames.rows,frames.step,QImage::Format_RGB888); // colorful QImage
            pixItem.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView->fitInView(&pixItem, Qt::KeepAspectRatio);     // fit image to View
        }
        qApp->processEvents();
    }

    ui->DeviceButton->setText("Continue");
}






void MainWindow::on_RTSPButton_pressed()                            //RTSP link button
{
    using namespace cv;

    if(video.isOpened())
    {
        ui->RTSPButton->setText("Play");
        video.release();
        return;
    }

    QString text = ui->RTSPEdit->text();                                //When push button is pressed takes QString .
    String link = text.trimmed().toStdString();                         // Convert Qstring to String.
    qInfo() << text;

    if(!video.open(link))                                               // If the given link is wrong

    {
        QMessageBox msgBox;
        msgBox.setText("RTSP link/path is not correct!!");
        msgBox.exec();
        return;
    }
    else
    {

    ui->RTSPButton->setText("Stop");

    Mat frames;
    while(video.isOpened())
    {
        video >> frames;                                                // takes frames in a while loop
        if(!frames.empty())
        {

            QImage qimg(frames.data,frames.cols,frames.rows,frames.step,QImage::Format_RGB888); // colorful QImage
            pixItem.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView->fitInView(&pixItem, Qt::KeepAspectRatio);
        }
        qApp->processEvents();                                          // process the events
    }

    }
        ui->RTSPButton->setText("Continue");
}





void MainWindow::on_exitButton_pressed()                                    // Exit button
{
    this->close();
}
