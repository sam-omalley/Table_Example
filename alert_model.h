#ifndef ALERT_MODEL_H
#define ALERT_MODEL_H

#include <QAbstractTableModel>
#include <QTimer>
#include <vector>
#include <deque>
#include <boost/date_time.hpp>

class Alert_Model : public QAbstractTableModel
{
    Q_OBJECT

public:

    struct Alert
    {
        boost::posix_time::ptime timestamp;
        std::string source;
        std::string message;
    };

    Alert_Model();

    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    int columnCount(const QModelIndex &parent=QModelIndex()) const;

    QVariant headerData(
            int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole) const;

    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

    void add_alert();

    void clear_all();

    int get_age(const Alert &alert) const;

private slots:
    void timer_callback();

private:
    std::deque<Alert> alert_data;
    std::vector<std::string> header_titles;
    QTimer timer;

    int count;
    int fade_out;
};

#endif // ALERT_MODEL_H
