#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QTreeWidgetItem>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui_MainWindow)
{
    ui->setupUi(this);
    
    setupTreeWidget();
    
    ui->statusbar->showMessage("Ready", 2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTreeWidget()
{
    ui->treeWidget->setHeaderLabel("Project Explorer");
    
    addTreeItem("Project Files");
    
    QTreeWidgetItem *sourceItem = new QTreeWidgetItem(ui->treeWidget);
    sourceItem->setText(0, "Source Files");
    sourceItem->setExpanded(true);
    
    QTreeWidgetItem *headerItem = new QTreeWidgetItem(sourceItem);
    headerItem->setText(0, "mainwindow.h");
    headerItem->setData(0, Qt::UserRole, "header");
    
    QTreeWidgetItem *sourceFileItem = new QTreeWidgetItem(sourceItem);
    sourceFileItem->setText(0, "mainwindow.cpp");
    sourceFileItem->setData(0, Qt::UserRole, "source");
    
    QTreeWidgetItem *mainItem = new QTreeWidgetItem(sourceItem);
    mainItem->setText(0, "main.cpp");
    mainItem->setData(0, Qt::UserRole, "source");
    
    QTreeWidgetItem *uiItem = new QTreeWidgetItem(ui->treeWidget);
    uiItem->setText(0, "UI Files");
    uiItem->setExpanded(true);
    
    QTreeWidgetItem *uiFileItem = new QTreeWidgetItem(uiItem);
    uiFileItem->setText(0, "mainwindow.ui");
    uiFileItem->setData(0, Qt::UserRole, "ui");
}

void MainWindow::addTreeItem(const QString &text, const QString &data)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, text);
    if (!data.isEmpty()) {
        item->setData(0, Qt::UserRole, data);
    }
}

void MainWindow::on_actionButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    
    if (text.isEmpty()) {
        QMessageBox::information(this, "Information", "Please enter some text first!");
        return;
    }
    
    QMessageBox::information(this, "Button Clicked", 
                           QString("You entered: %1").arg(text));
    
    ui->statusbar->showMessage("Button was clicked!", 3000);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->clear();
    ui->statusbar->showMessage("New document created", 2000);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    
    if (!fileName.isEmpty()) {
        ui->statusbar->showMessage(QString("Opening: %1").arg(fileName), 3000);
    }
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    
    if (!item) return;
    
    QString itemText = item->text(0);
    QString itemData = item->data(0, Qt::UserRole).toString();
    
    ui->statusbar->showMessage(QString("Selected: %1").arg(itemText), 2000);
    
    if (itemData == "source" || itemData == "header") {
        ui->titleLabel->setText(QString("Editing: %1").arg(itemText));
    } else if (itemData == "ui") {
        ui->titleLabel->setText(QString("UI File: %1").arg(itemText));
    }
}