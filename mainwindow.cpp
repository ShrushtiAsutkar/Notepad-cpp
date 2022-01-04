#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)    /*calling the parent constructor*/
    , ui(new Ui::MainWindow) /*creating UI class*/
{
    ui->setupUi(this);  /*set up UI for us */
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear(); /*delelting the Qstring file we created in mai.cpp(originally created)*/
    ui->textEdit->setText(QString()); /*creates new file */
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open the file"); /* this is reference ,""title for  dialog box */
    QFile file (fileName);                                                 /* obj for reading n writing file     */
    currentFile=fileName;                                                  /*  storing filename in currentfile   */
    if(!file.open(QIODevice::ReadOnly | QFile::Text))                      /* read only or else error  */
    {
        QMessageBox::warning(this,"Warning","Cannot open file : "+ file.errorString());
        return ;
    }

    setWindowTitle(fileName);             /*giving filename to window */
    QTextStream in(&file);                /*creating interface for reading text*/
    QString text =in.readAll();            /*COPY THE TEST IN STRING */
    ui->textEdit->setText(text);           /* text in text edit widget */
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as");       /* opening a dialog */
    QFile file (fileName);                                                 /* obj for reading n writing file     */
    if(!file.open(QFile::WriteOnly | QFile::Text))                         /* read only or else error  */
    {
        QMessageBox::warning(this,"Warning","Cannot save file : " + file.errorString());
        return;
    }
    currentFile=fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();                             /* getting data from ui n text edit is widget*/
    out<<text;
    file.close();

}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;           /*allows intereaction with printer*/
    printer.setPrinterName("Printer name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec()==QDialog::Rejected){
        QMessageBox::warning(this,"warning","cannot acces printer");
        return ;
    }
    ui->textEdit->print(&printer); /*acees to printer*/
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

