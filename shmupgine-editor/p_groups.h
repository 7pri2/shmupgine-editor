#ifndef P_GROUPS_H
#define P_GROUPS_H

#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <map>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "singleton.h"
#include "select_window.h"
#include "windows_panels.h"

class p_groups : public QWidget, public Singleton<p_groups> {
    Q_OBJECT

    friend class Singleton<p_groups>;

public:
    QString select_group();
    QString get_code();

public slots:
    void new_group();
    void delete_group();
    void add_entity();
    void remove_entity();
    void update_entitites_visible();

private:
    p_groups(const p_groups&);
    p_groups(QWidget* parent = 0);
    virtual ~p_groups();

    bool    already_exists(QString entity);

    QLabel*             lbl_groups;
    QLabel*             lbl_entities;
    QListView*          lv_groups;
    QListView*          lv_entities;
    QStandardItemModel* model_groups;
    std::map<int, QStandardItemModel*> model_entities;

    QPushButton*        btn_new_group;
    QPushButton*        btn_delete_group;

    QPushButton*        btn_add_entity;
    QPushButton*        btn_remove_entity;

    QHBoxLayout*        lay_btn_group;
    QHBoxLayout*        lay_btn_entity;
    QVBoxLayout*        lay_groups;
    QVBoxLayout*        lay_entities;
    QHBoxLayout*        lay_mainlayout;

    int groups_max_id;
};

#endif // P_GROUPS_H
