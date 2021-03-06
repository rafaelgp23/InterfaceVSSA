#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>

using namespace cv;

QImage IplImage2QImage(const IplImage *iplImage);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = (new Ui::MainWindow);
    ui->setupUi(this);

    this->showMaximized();
    capturar();
}

void MainWindow::capturar(){
    CvCapture *cap;     //cria um objeto do tipo CvCapture para captar as imagens a cam
    cap = cvCaptureFromCAM(0);   //seta que a captura ocorrera no dispositivo video0(por default é a webcam do note)
    IplImage *frame, *hsv, *img, *bin;   //cria um objeto de imagem, para guardar a imagem capturada;
    frame = cvQueryFrame(cap);  //faz a requisição de um frame e o guarda no objeto préviamente instanciado

    while(frame){    //enquanto frame nao for null, ou seja, houver alguma imagem
        cvWaitKey(10);   //aguarda 10 microseg.
        img = cvCloneImage(frame);  //clona a imagem capturada (sem isso não funciona)
        hsv = cvCloneImage(frame);  //clona

        cvCvtColor(img, hsv, CV_BGR2HSV);  //converte a img original em hsv e guarda em imagem.hsv

        // isso nao é importante agora, somente um método pra colocar imagem em uma label, já que o opencv nao dispoe de outro recurso pra colocar video na UI
        QImage qimg;
        qimg = IplImage2QImage(img);
        ui->label_2->setPixmap(QPixmap::fromImage(qimg));
        qimg = IplImage2QImage(hsv);
        ui->label_3->setPixmap(QPixmap::fromImage(qimg));


        cvReleaseImage(&hsv);
        cvReleaseImage(&img); //desaloca a memória
        frame = cvQueryFrame(cap);  // frame recebe uma nova imagem da captura.
    }

    cvReleaseCapture(&cap); //desaloca o espaço alocado pra captura.
}



MainWindow::~MainWindow()
{
    delete ui;
}

QImage IplImage2QImage(const IplImage *iplImage)
{
    int height = iplImage->height;
    int width = iplImage->width;

    if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
    {
      const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
      QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
      return img.rgbSwapped();
    } else if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1){
    const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
    QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);

    QVector<QRgb> colorTable;
    for (int i = 0; i < 256; i++){
        colorTable.push_back(qRgb(i, i, i));
    }
    img.setColorTable(colorTable);
    return img;
    }else{
      return QImage();
    }
}

void MainWindow::on_radioButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_radioButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
