#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "capturethread.h"
#include <QStandardItem>
#include <QTableWidget>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QStandardItemModel *mainModel;

    mainModel = new QStandardItemModel();
    mainModel->setColumnCount(6);
    mainModel->setHeaderData(0, Qt::Horizontal, tr("序号"));
    mainModel->setHeaderData(1, Qt::Horizontal, tr("时间"));
    mainModel->setHeaderData(2, Qt::Horizontal, tr("源IP地址"));
    mainModel->setHeaderData(3, Qt::Horizontal, tr("目标IP地址"));
    mainModel->setHeaderData(4, Qt::Horizontal, tr("协议"));
    mainModel->setHeaderData(5, Qt::Horizontal, tr("发送长度"));

    ui->treeView->setModel(mainModel);
    ui->treeView->setColumnWidth(0,50);
    ui->treeView->setColumnWidth(1,200);
    ui->treeView->setColumnWidth(2,200);
    ui->treeView->setColumnWidth(3,200);
    ui->treeView->setColumnWidth(4,200);
    ui->treeView->setColumnWidth(5,200);

    iPosition = 0;



//    Sniffer *snif = new Sniffer;

//    connect(this,SIGNAL(sendData()),this,SLOT(receiveData()));
//    QStandardItem *item;
//    item = new QStandardItem("5");
//    mainModel->setItem(0, 0, item);

//    item = new QStandardItem("hah");
//    mainModel->setItem(0, 1, item);
//     item = new QStandardItem("127.0.1.1");
//        mainModel->setItem(0, 2, item);
//        item = new QStandardItem("197.235.5.2");
//        mainModel->setItem(0, 3, item);
//        item = new QStandardItem("ip");
//        mainModel->setItem(0, 4, item);
//        item = new QStandardItem("20");
//        mainModel->setItem(0, 5, item);
//    for (int row = 0; row < 4; ++row) {
//        for (int column = 0; column < 2; ++column) {
//            QModelIndex index = model->index(row, column, QModelIndex());
//            model->setItem(1,2, QVariant("dsasa"));
//        }
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startCapture_clicked()
{
    CaptureThread *capturethread = new CaptureThread();
    capturethread->sniffer = &sniffer;
    // 启动线程
    capturethread->start();
    connect(capturethread,SIGNAL(sendData(QString,QString,QString,QString)),this,SLOT(receiveData(QString,QString,QString,QString)),Qt::QueuedConnection);

}

void MainWindow::receiveData(QString data1,QString data2,QString data3,QString data4){
        QStandardItem *item;
        item = new QStandardItem(data1);
        mainModel->setItem(iPosition, 2, item);

        item = new QStandardItem(data2);
        mainModel->setItem(iPosition, 3, item);
         item = new QStandardItem(data3);
            mainModel->setItem(iPosition, 4, item);
            item = new QStandardItem(data4);
            mainModel->setItem(iPosition, 5, item);
//            item = new QStandardItem("ip");
//            mainModel->setItem(0, 5, item);;
         iPosition = iPosition + 1;
}
