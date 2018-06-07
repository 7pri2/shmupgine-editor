#ifndef SPAWNSLOT_H
#define SPAWNSLOT_H

#include <QLineEdit>
#include <QLabel>
#include <QListView>
#include <QStandardItemModel>
#include <QCheckBox>
#include <QHBoxLayout>
#include "attribute.h"
#include "attr_spawner.h"
#include "windows_panels.h"

class spawnslot : public QWidget {
    Q_OBJECT
public:
    spawnslot(attr_spawner* parent = 0);
    virtual ~spawnslot();

    virtual QString getCode();

private slots:

private slots:
    void    load_profile();
    void    add_group();
    void    remove_group();

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

    QLabel*         lbl_entity_profile;
    QLineEdit*      le_entity_profile;
    QPushButton*    btn_load_entity;

    QLabel*         lbl_sound;
    QLineEdit*      le_sound;
    QPushButton*    btn_select_sound;

    QLabel*         lbl_name;
    QLineEdit*      le_name;

    QHBoxLayout*    lay_entity_profile;
    QHBoxLayout*    lay_cooldown;
    QHBoxLayout*    lay_name;
    QHBoxLayout*    lay_groups_btn;
    QHBoxLayout*    lay_sound;
    QVBoxLayout*    lay_main;

    attr_spawner*   m_spawner;
};


#endif // SPAWNSLOT_H
