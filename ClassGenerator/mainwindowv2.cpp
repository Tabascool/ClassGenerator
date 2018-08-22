#include "mainwindowv2.h"
#include "ui_mainwindowv2.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStandardPaths>
#include <iostream>
#include <fstream>
#include "CGUtils.h"
#include "ClassParser.h"

/* Fonction qui affiche la fenêtre graphique et initialise les paramètres */
MainWindowV2::MainWindowV2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowV2)
{
    ui->setupUi(this);
    // Initialisation des options dans les menus déroulant.
    ui->comboBox_variablePermission->addItems(QStringList()<<"Private"<<"Public"<<"Protected");
    ui->comboBox_functionPermission->addItems(QStringList()<<"Private"<<"Public"<<"Protected");
    ui->comboBox_variableType->addItems(QStringList()<<"bool"<<"char"<<"int"<<"float"<<"double"<<"void");
    ui->comboBox_functionType->addItems(QStringList()<<"bool"<<"char"<<"int"<<"float"<<"double"<<"void");
}

/* Fonction qui détruit la fenêtre */
MainWindowV2::~MainWindowV2()
{
    delete ui;
}

/* Fonction qui créer un nouveau fichier XML dans l'éditeur de texte */
void MainWindowV2::on_actionNew_XML_File_triggered()
{
    enabledWidgets();

    ui->comboBox_variable->clear();
    ui->textEdit->setText("<classes>\r\n"
                          "</classes>");
}

/* Fonction qui ouvre un fichier existant choisi par l'utilisateur
 * et affiche son contenu dans l'éditeur de texte */
void MainWindowV2::on_actionOpen_XML_File_triggered()
{
    // Ouverture d'une fenêtre de selection de fichier exclusivement en XML
    QString path = QFileDialog::getOpenFileName(this, tr("Open XML file"), "XML file", tr("XML Files (*.xml)"));

    enabledWidgets();

    // Récupération du contenu du fichier qui a été sélectionné et affichage dans l'éditeur.
    QFile inputFile(path);
    int i = 0;
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        QString XMLText = in.readAll();
        ui->textEdit->setText(XMLText);

        while (i < XMLText.length())
        {
            // Parcour de toutes les classes du contenu.
            if (i == XMLText.indexOf("<classe name=\"", i))
            {
                // Récupération de la position du début du nom de la classe.
                int firstPosition = i+14;
                // Récupération de la position de fin du nom de la classe.
                int endPosition = XMLText.indexOf("\"", firstPosition);
                // Récupération du nom de la classe
                QString className = XMLText.mid(firstPosition, endPosition - firstPosition);


                ui->comboBox_variable->clear();
                ui->comboBox_variable->addItem(className);
                ui->comboBox_function->addItem(className);
            }
            i++;
        }
    }
    inputFile.close();
}

/* Fonction qui sauvegarde le contenu de l'éditeur actuel nomé par l'utilisateur */
void MainWindowV2::on_actionSave_XML_File_triggered()
{
    // Ouvre une fenêtre de dialogue de sauvegarde de nouveau fichier.
    QString path = QFileDialog::getSaveFileName(this, "Save XML file", "XML file", ".xml");

    // Vérification du format du fichier.
    if (path.right(4) != ".xml")
        path = path+".xml";
    QFile outputFile(path);
    outputFile.open(QIODevice::WriteOnly);

    if(outputFile.isOpen())
    {
        QTextStream out(&outputFile);
        out << ui->textEdit->toPlainText();
    }

    outputFile.close();
}

/* Fonction qui débloque les composants graphiques */
void MainWindowV2::enabledWidgets()
{
    ui->textEdit->clear();
    ui->groupBox_XML_file->setEnabled(true);
    ui->groupBox_form->setEnabled(true);
    ui->textEdit->setEnabled(true);
    ui->actionSave_XML_File->setEnabled(true);
    ui->pushButton_checkXMLFile->setEnabled(false);
}

/* Fonction qui ferme l'application */
void MainWindowV2::on_actionExit_triggered()
{
    this->close();
}

/* Fonction qui créer une nouvelle classe dans le fichier ouvert dans l'éditeur */
void MainWindowV2::on_pushButton_CreateClass_clicked()
{
    if(ui->comboBox_variable->findText(ui->lineEdit_Class->text())>=0) {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("This class already exist"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
    } else {
        // Vérification que les champs obligatoires ne soient pas vide.
        if (ui->lineEdit_Class->text().length() > 0)
        {
            // Ligne contenant la nouvelle classe.
            QString newClass = "\t<classe name=\"" + ui->lineEdit_Class->text() + "\" extends=\"" + ui->lineEdit_extend->text() + "\">\r\n" "\t</classe>\r";
            // Récupération du contenu actuel de l'éditeur.
            QString currentXML = ui->textEdit->toPlainText();
            QString newXML;

            // Réécriture du contenu de l'éditeur en y insérant la ligne entre les bonnes balises.
            // Positionnement de la nouvelle classe juste avant la balise de fin et tout le contenu déjà existant.
            newXML = currentXML.left(currentXML.length() - 10) + newClass + currentXML.right(10);

            ui->textEdit->setText(newXML);

            // Attribution du nom de la nouvelle classe dans les menu déroulant de création de variables et fonctions.
            ui->comboBox_variable->addItem(ui->lineEdit_Class->text());
            ui->comboBox_function->addItem(ui->lineEdit_Class->text());
        }
    }
}

/* Fonction qui créer une nouvelle variable dans la classe qui a été selectionné */
void MainWindowV2::on_pushButton_CreateVariable_clicked()
{
    // Vérification que les champs obligatoires ne sont pas vide.
    if (ui->comboBox_variable->currentText().length() > 0 && ui->lineEdit_VariableName->text().length() > 0)
    {
        // Ligne contenant la nouvelle variable.
        QString newVariable = "\t\t<attribute name=\"" + ui->lineEdit_VariableName->text() + "\" type=\"" + ui->comboBox_variableType->currentText() + "\" visibility=\"" + ui->comboBox_variablePermission->currentText() + "\"/>\r\n";
        // Récupération du contenu actuel de l'éditeur.
        QString currentXML = ui->textEdit->toPlainText();
        QString newXML;

        int i = 0;
        // Parcour de tout le contenu caractère par caractère.
        while (i < currentXML.length())
        {
            // Parcour de toutes les classes du contenu.
            if (i == currentXML.indexOf("<classe name=\"", i))
            {
                // Récupération de la position du début du nom de la classe.
                int firstPosition = i+14;
                // Récupération de la position de fin du nom de la classe.
                int endPosition = currentXML.indexOf("\"", firstPosition);
                // Récupération du nom de la classe
                QString tempClassName = currentXML.mid(firstPosition, endPosition - firstPosition);

                // Si le nom de la classe correspond au nom sélectionné dans les paramètre
                // alors on se position dans ses balises.
                if (tempClassName == ui->comboBox_variable->currentText())
                {
                    // Récupération de la position juste avant la balise de fin.
                    int endPositionClass = currentXML.indexOf("</classe>", i) - 1;
                    // Ajout de la variable dans le contenu de la même manière que l'insertion de nouvelles classes.
                    newXML = currentXML.left(endPositionClass) + newVariable + currentXML.right(currentXML.length() - endPositionClass);
                    ui->textEdit->setText(newXML);
                }
            }
            i++;
        }
    }
}

/* Fonction qui créer une nouvelle fonction dans la classe qui a été selectionné */
void MainWindowV2::on_pushButton_CreateFunction_clicked()
{
    // Vérification que les champs obligatoires ne sont pas vide.
    if (ui->comboBox_function->currentText().length() > 0 && ui->lineEdit_FunctionName->text().length() > 0)
    {
        // Ligne contenant la nouvelle fonction.
        QString newVariable = "\t\t<function name=\"" + ui->lineEdit_FunctionName->text() + "\" type=\"" + ui->comboBox_functionType->currentText() + "\" visibility=\"" + ui->comboBox_functionPermission->currentText() + "\"/>\r\n";
        // Récupération du contenu actuel de l'éditeur.
        QString currentXML = ui->textEdit->toPlainText();
        QString newXML;
        int i = 0;
        // Parcour de tout le contenu caractère par caractère.
        while (i < currentXML.length())
        {
            // Parcour de toutes les classes du contenu.
            if (i == currentXML.indexOf("<classe name=\"", i))
            {
                // Récupération de la position du début du nom de la classe.
                int firstPosition = i+14;
                // Récupération de la position de fin du nom de la classe.
                int endPosition = currentXML.indexOf("\"", firstPosition);
                // Récupération du nom de la classe
                QString tempClassName = currentXML.mid(firstPosition, endPosition - firstPosition);

                // Si le nom de la classe correspond au nom sélectionné dans les paramètre
                // alors on se position dans ses balises.
                if (tempClassName == ui->comboBox_function->currentText())
                {
                    // Récupération de la position juste avant la balise de fin.
                    int endPositionClass = currentXML.indexOf("</classe>", i) - 1;
                    // Ajout de la fonction dans le contenu de la même manière que l'insertion de nouvelles classes.
                    newXML = currentXML.left(endPositionClass) + newVariable + currentXML.right(currentXML.length() - endPositionClass);
                    ui->textEdit->setText(newXML);
                }
            }
            i++;
        }
    }
}


/* Fonction qui vérifie si le fichier XML dans l'éditeur est apte a générer du code */
void MainWindowV2::on_pushButton_checkXMLFile_clicked()
{
    // TODO : vérifier le fichier XML
}

/* Fonction qui permet de générer du code via le fichier en XML */
void MainWindowV2::on_pushButton_generate_clicked()
{
    std::string filePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation).toStdString()+"/tmpxml.xml";
        std::ofstream tmpFile(filePath.c_str());
        tmpFile << ui->textEdit->toPlainText().toStdString();
        tmpFile.close();

        string folderPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString()+"/";
        ClassParser parser(filePath.c_str(), folderPath.c_str());
        CGUtils::ResultCode result = parser.run();
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(result.second));
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        remove(filePath.c_str());
}

void MainWindowV2::on_actionAbout_triggered()
{
    QMessageBox::information(NULL, "About Class Generator", "Class Generator\nVersion : 1.0\nCompagny : ESGI\nDevelopers :\nJulien CASSONE\nArnaud LE BOURBLANC\nAntoine ZAZZERA\n\t\t\t\t\t\t\t\t\t");
}
