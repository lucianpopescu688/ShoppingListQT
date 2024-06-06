#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QLayout>
#include <fstream>
#include "shoppinglist.h"
#include <QPushButton>
#include <vector>
#include <sstream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setup();


private:
    Ui::MainWindow *ui;
    QWidget* MainWidget = new QWidget;
    QVBoxLayout* MainLayout = new QVBoxLayout;
    QListWidget* ShoppingList =  new QListWidget;
    vector <shoppinglist*> ShoppingOfList;
    QListWidget* ListOfSameCategory = new QListWidget;
    QLabel* ShoppingLabel = new QLabel;
    QPushButton* FilterButton = new QPushButton("Filter");
    QLineEdit* FilterBox = new QLineEdit;
    QPushButton* DeleteButton = new QPushButton("Delete");
};
#endif // MAINWINDOW_H
