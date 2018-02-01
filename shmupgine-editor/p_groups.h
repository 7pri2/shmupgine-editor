#ifndef P_GROUPS_H
#define P_GROUPS_H

#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QPushButton>
#include "singleton.h"
#include "select_window.h"

class p_groups : public QWidget, public Singleton<p_groups> {
    Q_OBJECT

    friend class Singleton<p_groups>;

public:
    QString select_group();

public slots:
    void new_group();
    void delete_group();

private:
    p_groups(const p_groups&);
    p_groups(QWidget* parent = 0);
    virtual ~p_groups();

    QListView*          lv_groups;
    QStandardItemModel* model_groups;

    QPushButton*        btn_new_group;
    QPushButton*        btn_delete_group;

    QHBoxLayout*        lay_btn_group;
    QVBoxLayout*        lay_mainlayout;

    int groups_max_id;
};

#endif // P_GROUPS_H
