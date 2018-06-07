#ifndef ATTR_DESTRUCTOR_H
#define ATTR_DESTRUCTOR_H

#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include "windows_panels.h"
#include "attribute.h"

class attr_destructor : public attribute {
    Q_OBJECT
public:
    attr_destructor(entities_attributes_panel*);
    ~attr_destructor();

    virtual QString getCode();
    virtual bool verify_validity();

public slots:

private slots:
    void removeEntity();
    void add_entities();
    void remove_group();
    void add_groups();

private:
    QListView*  lv_entities;
    QListView*  lv_groups;

    QStandardItemModel* sm_entities;
    QStandardItemModel* sm_groups;

    QPushButton*    btn_add_entity;
    QPushButton*    btn_remove_entity;
    QPushButton*    btn_add_group;
    QPushButton*    btn_remove_group;

    QHBoxLayout*    lay_entities_btn;
    QHBoxLayout*    lay_groups_btn;

    QLabel*         lbl_entities;
    QLabel*         lbl_groups;

    QCheckBox*      cb_out_of_bounds;
};

#endif // ATTR_DESTRUCTOR_H
