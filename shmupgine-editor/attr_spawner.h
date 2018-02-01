#ifndef ATTR_SPAWNER_H
#define ATTR_SPAWNER_H

#include <QLineEdit>
#include <QLabel>
#include <QListView>
#include <QStandardItemModel>
#include <QCheckBox>
#include <QHBoxLayout>
#include "attribute.h"
#include "windows_panels.h"

class attr_spawner : public attribute {
    Q_OBJECT
public:
    attr_spawner(entities_attributes_panel* container);
    virtual ~attr_spawner();

    virtual QString getCode();

private slots:

private:
    QLabel*             lbl_groups;
    QListView*          lv_groups;
    QStandardItemModel* model_groups;
    QPushButton*        btn_add_group;
    QPushButton*        btn_del_group;

    QCheckBox*  cb_spawn_at_parents_position;
    QCheckBox*  cb_autospawn;

    QLabel*     lbl_cooldown_ms;
    QLineEdit*  le_cooldown_ms;

    QLabel*      lbl_entity_profile;
    QLineEdit*      le_entity_profile;
    QPushButton*    btn_load_entity;

    QHBoxLayout*    lay_entity_profile;
    QHBoxLayout*    lay_cooldown;
    QHBoxLayout*    lay_groups_btn;
};

#endif // ATTR_SPAWNER_H
