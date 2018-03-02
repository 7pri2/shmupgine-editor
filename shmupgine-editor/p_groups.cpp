#include "p_groups.h"

p_groups::p_groups(QWidget* parent) : QWidget(parent) {
    lv_groups       = new QListView(this);
    lv_entities     = new QListView(this);
    model_groups    = new QStandardItemModel(this);

    btn_new_group       = new QPushButton(tr("Add group"), this);
    btn_delete_group    = new QPushButton(tr("Delete group"), this);

    btn_add_entity      = new QPushButton(tr("Add entity"), this);
    btn_remove_entity   = new QPushButton(tr("Remove entity"), this);

    lay_mainlayout  = new QHBoxLayout(this);
    lay_entities    = new QVBoxLayout(this);
    lay_groups      = new QVBoxLayout(this);
    lay_btn_group   = new QHBoxLayout(this);
    lay_btn_entity  = new QHBoxLayout(this);

    lbl_entities    = new QLabel(tr("Entities"), this);
    lbl_groups      = new QLabel(tr("Groups"), this);

    lv_groups->setModel(model_groups);
    groups_max_id = 0;

    lay_btn_group->addWidget(btn_new_group);
    lay_btn_group->addWidget(btn_delete_group);

    lay_btn_entity->addWidget(btn_add_entity);
    lay_btn_entity->addWidget(btn_remove_entity);

    lay_groups->addWidget(lbl_groups);
    lay_groups->addWidget(lv_groups);
    lay_groups->addLayout(lay_btn_group);
    lay_entities->addWidget(lbl_entities);
    lay_entities->addWidget(lv_entities);
    lay_entities->addLayout(lay_btn_entity);
    lay_mainlayout->addLayout(lay_groups);
    lay_mainlayout->addLayout(lay_entities);

    connect(btn_new_group, SIGNAL(clicked(bool)), this, SLOT(new_group()));
    connect(btn_delete_group, SIGNAL(clicked(bool)), this, SLOT(delete_group()));
    connect(btn_remove_entity, SIGNAL(clicked(bool)), this, SLOT(remove_entity()));
    connect(btn_add_entity, SIGNAL(clicked(bool)), this, SLOT(add_entity()));
    connect(lv_groups, SIGNAL(clicked(QModelIndex)), this, SLOT(update_entitites_visible()));

    update_entitites_visible();
}

p_groups::~p_groups() {

}

void p_groups::new_group() {
    groups_max_id += 1;
    model_entities[groups_max_id] = new QStandardItemModel;
    QStandardItem* item = new QStandardItem(QString(QObject::tr("group"))+QString::number(groups_max_id));
    item->appendRow(new QStandardItem(QString::number(groups_max_id)));
    model_groups->appendRow(item);
    update_entitites_visible();
}

void p_groups::delete_group() {
    model_groups->removeRow(lv_groups->currentIndex().row());
}


QString p_groups::select_group() {
    select_window *select  = new select_window(tr("Select a group"), model_groups);
    if(select->exec())  return select->get_selected_item(-1); // name
    else                return "";
}

void p_groups::update_entitites_visible() {
    lv_entities->setModel(model_entities[lv_groups->currentIndex().child(0,0).data().toInt()]);
    btn_add_entity->setEnabled(lv_groups->currentIndex().child(0,0).data().toInt());
    btn_remove_entity->setEnabled(lv_groups->currentIndex().child(0,0).data().toInt());
}

void p_groups::add_entity() {
    QString entity = p_entities_editor::Instance()->select_entity();
    if(!entity.isEmpty() && !already_exists(entity)) {
        QStandardItem* item = new QStandardItem(entity);
        model_entities[lv_groups->currentIndex().child(0,0).data().toInt()]->appendRow(item);
    }
    update_entitites_visible();
}

void p_groups::remove_entity() {
    model_entities[lv_groups->currentIndex().child(0,0).data().toInt()]->removeRow(lv_entities->currentIndex().row());
}

bool p_groups::already_exists(QString entity) {
    return model_entities[lv_groups->currentIndex().child(0,0).data().toInt()]->findItems(entity).size();
    //return false;
}

QString p_groups::get_code() {

}
