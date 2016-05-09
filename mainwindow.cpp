#include "mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMap>
#include <QDate>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    init_menuBar();
    init_main_layout();
    init_parameters();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init_menuBar()
{
    //menu Bard
    QMenu * Setting_Menu = menuBar()->addMenu("Setting");
    QMenu * About_Menu = menuBar()->addMenu("About");

}

void MainWindow::init_main_layout()
{
    QWidget* Main_central_widget = new QWidget;
    this->setCentralWidget(Main_central_widget);
    QVBoxLayout* Main_Vlayout = new QVBoxLayout(Main_central_widget);

    Main_central_widget->setLayout(Main_Vlayout);

    //file load layout
    QHBoxLayout * fileLoad_Hlayout = new QHBoxLayout(Main_central_widget);
    data_path = new QLineEdit(Main_central_widget);
    QPushButton *open_data_pb = new QPushButton(Main_central_widget);
    open_data_pb->setText("&Open");
    connect(open_data_pb,SIGNAL(clicked(bool)),this,SLOT(on_open_data_pb()));

    //data diagram widget
    data_diagram_widget = new Stock_Diagram(Main_central_widget);

    fileLoad_Hlayout->addWidget(data_path);
    fileLoad_Hlayout->addWidget(open_data_pb);


    Main_Vlayout->addItem(fileLoad_Hlayout);
    Main_Vlayout->addWidget(data_diagram_widget);
    this->resize(800,600);

}

void MainWindow::init_parameters()
{

}

void MainWindow::on_open_data_pb()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        data_path->setText(fileName);
        on_load_data(fileName);
    }
}

void MainWindow::on_load_data(QString dataPath)
{
    QFile file(dataPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QStringList line_str_list;
    StockData stock_data;
    QString temp_item;
    QLocale my_local(QLocale::AnyLanguage,QLocale::SouthKorea);//use korean currency format
    QDate stock_time;
    in.readLine();
    while(!in.atEnd())
    {
        line_str_list = in.readLine().split(",\"");
        for(int i =1;i<line_str_list.count();i++)
        {
            temp_item =line_str_list.at(i);
            temp_item = temp_item.section("\"",0,0);
            line_str_list[i]=temp_item;
        }
        stock_time = my_local.toDate(line_str_list.at(0),"yyyy/MM/dd");
        stock_data.final_price = my_local.toLongLong(line_str_list.at(1));
        stock_data.compare_last_date = my_local.toLongLong(line_str_list.at(2));
        stock_data.trading_volume = my_local.toLongLong(line_str_list.at(3));
        stock_data.trading_value = my_local.toLongLong(line_str_list.at(4));
        stock_data.open_price = my_local.toLongLong(line_str_list.at(5));
        stock_data.highest_price = my_local.toLongLong(line_str_list.at(6));
        stock_data.lowest_price = my_local.toLongLong(line_str_list.at(7));
        stock_data.aggregate_value = my_local.toLongLong(line_str_list.at(8));
        stock_data.total_stock_cnt = my_local.toLongLong(line_str_list.at(9));
        stock_data_map.insert(stock_time,stock_data);
    }
    qDebug()<<"QHash create completed!";
}
