#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class Ui_MainWindow;
class QTreeWidgetItem;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionButton_clicked();
    void on_actionExit_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    void setupTreeWidget();
    void addTreeItem(const QString &text, const QString &data = QString());
    
private:
    Ui_MainWindow *ui;
};