#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stock_diagram.h"
#include <QMainWindow>
#include <QMap>


class QLineEdit;

//class QString;

typedef struct StockData{
    unsigned long final_price;//收市价
    long compare_last_date; //与昨天比较
    unsigned long trading_volume;//交易量
    unsigned long trading_value;//交易资金
    unsigned long open_price; //开盘价
    unsigned long highest_price;//最高价
    unsigned long lowest_price;//最低价
    unsigned long aggregate_value;//市价总额
    unsigned long total_stock_cnt; //市场总股票数
}StockData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init_menuBar();
    void init_main_layout();
    void init_parameters();

public slots:
    void on_open_data_pb();
    void on_load_data(QString dataPath);

private:
    QLineEdit * data_path;
    Stock_Diagram * data_diagram_widget;
    QMap<QDate,StockData> stock_data_map;
};

#endif // MAINWINDOW_H
