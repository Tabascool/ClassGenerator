#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    string path = ui->lineEdit->text().toStdString();
    ClassParser parser(path, path);
    CGUtils::ResultCode result = parser.run();
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(result.second));
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open XML file"), "XML file", tr("XML Files (*.xml)"));
    ui->lineEdit->setText(path);
}
