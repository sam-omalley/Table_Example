#include <sstream>
#include <QBrush>
#include <QColor>
#include "alert_model.h"

Alert_Model::Alert_Model() : count(0), fade_out(5000000)
{
    header_titles.push_back(" ");
    header_titles.push_back("           Timestamp           ");
    header_titles.push_back("Source");
    header_titles.push_back("Message");

    timer.setInterval(100);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(timer_callback()));
}


int Alert_Model::rowCount(const QModelIndex &parent) const
{
    return alert_data.size();
}

int Alert_Model::columnCount(const QModelIndex &parent) const
{
    return header_titles.size();
}

QVariant Alert_Model::headerData(
        int section,
        Qt::Orientation orientation,
        int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            return QString(header_titles.at(section).c_str());
        }
    }
    return QVariant();
}

QVariant Alert_Model::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case 1:
            return QString(
                        boost::posix_time::to_simple_string(
                            alert_data.at(index.row()).timestamp).c_str());
        case 2:
            return QString(alert_data.at(index.row()).source.c_str());
        case 3:
            return QString(alert_data.at(index.row()).message.c_str());
        }
    case Qt::BackgroundRole:
    {
        if (index.column() == 0)
        {
            int age = get_age(alert_data.at(index.row()));
            if (age <= fade_out)
            {
                int x = static_cast<int>((255.0/fade_out) * age);
                QColor c(255, x, x);
                return QBrush(c);
            }
        }
    }
    }

    return QVariant();
}

void Alert_Model::add_alert()
{
    Alert a;
    a.timestamp = boost::posix_time::second_clock::local_time();
    a.source = "Button";
    std::stringstream s;
    s << "Button was clicked at ";
    s << boost::posix_time::to_simple_string(a.timestamp);
    a.message = s.str();

    beginInsertRows(QModelIndex(), 0, 0);
    alert_data.push_front(a);
    endInsertRows();

    timer.start();
}

void Alert_Model::clear_all()
{
    beginRemoveRows(QModelIndex(), 0, alert_data.size() - 1);
    alert_data.clear();
    endRemoveRows();
}

void Alert_Model::timer_callback()
{
    if (alert_data.size() == 0)
    {
        timer.stop();
        return;
    }

//    std::cout << "Timer triggered: " << count++ << std::endl;
    int start_row = 0;
    int end_row = 0;

    for (int i = 0; i < alert_data.size(); ++i)
    {
        if (get_age(alert_data[i]) > fade_out+1000000)
        {
            if (i == 0)
            {
                timer.stop();
                return;
            }

            break;
        }
        else
        {
            end_row = i;
        }
    }

    QModelIndex index;
    emit dataChanged(
                index.child(start_row, 0),
                index.child(end_row, header_titles.size() - 1));
}

int Alert_Model::get_age(const Alert & alert) const
{
    boost::posix_time::ptime now =
            boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration diff;
    diff = now - alert.timestamp;
    return static_cast<int>(diff.total_microseconds());
}
