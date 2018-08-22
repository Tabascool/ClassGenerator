#ifndef MAINWINDOWV2_H
#define MAINWINDOWV2_H

#include <QMainWindow>

namespace Ui {
class MainWindowV2;
}

class MainWindowV2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowV2(QWidget *parent = 0);
    ~MainWindowV2();

private slots:
    void on_actionNew_XML_File_triggered();

    void on_actionOpen_XML_File_triggered();

    void on_actionSave_XML_File_triggered();

    void enabledWidgets();

    void on_actionExit_triggered();

    void on_pushButton_CreateClass_clicked();

    void on_pushButton_CreateVariable_clicked();

    void on_pushButton_CreateFunction_clicked();

    void on_pushButton_checkXMLFile_clicked();

    void on_pushButton_generate_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindowV2 *ui;
};

#endif // MAINWINDOWV2_H
