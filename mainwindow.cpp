#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QDebug>
#include <vector>

class MyTableModel: public QAbstractTableModel{
public:

    struct Row{
        int a;
        double c;
        QString b;
    };

    Row sr{1, 3, "drfg"};

    Qt::ItemFlags flags ( const QModelIndex & index ) const override {

            return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;

    }
    void MyAddRow(const Row& a){
        beginInsertRows(QModelIndex(), MyData.size(), MyData.size());
        MyData.push_back(a);
        endInsertRows();
    }

    MyTableModel(QObject *parent, const Row& a){
        //MyData.push_back({15, 5.23, "abc"});
        //MyData.push_back({12, 5.56, "yujhrfd"});
        MyData.push_back(a);
    }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return MyData.size();
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 3;
    }

    bool setData (const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override{
        switch (role) {
        case Qt::EditRole:
            switch (index.column()) {
                case 0:
                    MyData[index.row()].a = value.toInt();
                    break;
                case 1:
                    MyData[index.row()].c = value.toDouble();
                    break;
                case 2:
                    MyData[index.row()].b = value.toString();
                    break;
                default: return true;
            }
        }
        return true;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{

            switch(role)
            {
            case Qt::DisplayRole:
                switch (index.column()){
                case 0:
                    return MyData[index.row()].a;
                case 1:
                    return MyData[index.row()].c;
                case 2:
                    return MyData[index.row()].b;
                default: return {};
            }
            }
            return {};
    }
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                       int role = Qt::EditRole) override{
        return true;
    }

private:

    std::vector<Row> MyData;
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyTableModel *tab = new MyTableModel(this, {1, 5.46667878, "refge"});
    tab->setData(tab->index(tab->rowCount()-1, tab->columnCount()-1), 2);
    qDebug() << tab->rowCount();
    ui->tableView->setModel(tab);
    tab->MyAddRow({1, 8.46667878, "reewfrge"});
    tab->setHeaderData(0, Qt::Vertical, "dsfs", Qt::EditRole);
    ui->tableView->setModel(tab);

}

MainWindow::~MainWindow()
{
    delete ui;
}

