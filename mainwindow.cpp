#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(MainWidget);
    MainWidget->setLayout(MainLayout);
    MainLayout->addWidget(ShoppingList);
    MainWindow::setup();
    MainLayout->addWidget(ListOfSameCategory);
    MainLayout->addWidget(ShoppingLabel);
    MainLayout->addWidget(FilterBox);
    MainLayout->addWidget(FilterButton);
    MainLayout->addWidget(DeleteButton);
    connect(ShoppingList,&QListWidget::itemClicked,this,[&](){
        qInfo()<<ShoppingList->currentItem()->text();
        auto nameOfCategory = ShoppingList->currentItem()->text();
        vector <shoppinglist*> items;
        ListOfSameCategory->clear();
        for (auto  it:ShoppingOfList)
        {
            if (it->_category == nameOfCategory.toStdString())
                items.push_back(it);
        }
        for(auto it:items)
        {
            QString qString = QString::fromStdString(it->_name);
            ListOfSameCategory->insertItem(ListOfSameCategory->count(),qString);
        }
        ShoppingLabel->clear();
    });
    connect(ListOfSameCategory,&QListWidget::itemClicked,this,[&](){
        auto nameOfItem = ListOfSameCategory->currentItem()->text();
        shoppinglist* item;
        for (auto it:ShoppingOfList)
        {
            if(it->_name == nameOfItem.toStdString())
            {
                ShoppingLabel->setText(QString::fromStdString("Quantity : " + it->_quantity));
            }
        }
    });
    connect(FilterButton,&QPushButton::clicked,this,[&](){
        auto toBeSearched = FilterBox->text();
        for (auto it:ShoppingOfList)
        {
            if (it->_name == toBeSearched.toStdString())
            {
                int i = 0;
                while(i < ShoppingList->count())
                {
                    if(ShoppingList->item(i)->text() == QString::fromStdString(it->_category))
                        break;
                    i++;
                }
                ShoppingList->setCurrentRow(i);
                qInfo()<<i;
                auto nameOfItem = it->_name;
                shoppinglist* item;
                for (auto it2:ShoppingOfList)
                {
                    if (it2->_name == nameOfItem)
                    {
                        ShoppingLabel->setText(QString::fromStdString(it->_quantity));
                    }
                }
            }
        }
    });
    connect(DeleteButton, &QPushButton::clicked, this, [&](){
        QListWidgetItem *currentItem = ListOfSameCategory->currentItem();
        if (currentItem) {
            delete ListOfSameCategory->takeItem(ListOfSameCategory->row(currentItem));
        }
        ListOfSameCategory->clear();
    });

}

void MainWindow::setup()
{
    string f;
    string category;
    string name;
    string quantity;
    int i = 0;
    ifstream fin("C:/Test1proa/info.txt");
    while(getline(fin,f,'|'))
    {
        if (f == "\n")
            break;
        i++;
        if (i == 1)
        {
            category = f;
        }
        if (i == 2)
        {
            name = f;
        }
        if (i == 3)
        {
            i = 0;
            ShoppingOfList.push_back(new shoppinglist(category,name,f));
        }
    }
    sort(ShoppingOfList.begin(),ShoppingOfList.end(),[](const auto& obj1, const auto& obj2){return obj1->_category<obj2->_category;});
    string previous_el = "asd";
    for (auto el:ShoppingOfList)
    {
        if (previous_el != el->_category)
        {
            QString qString = QString::fromStdString(el->_category);
            ShoppingList->insertItem(ShoppingList->count(),qString);
        }
        previous_el = el->_category;
    }
    fin.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
