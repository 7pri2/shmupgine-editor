#include "p_groups.h"

p_groups::p_groups(QWidget* parent) : QWidget(parent) {
    lv_groups       = new QListView(this);
    model_groups    = new QStandardItemModel(this);

    btn_new_group       = new QPushButton(tr("Add"), this);
    btn_delete_group    = new QPushButton(tr("Delete"), this);

    lay_mainlayout  = new QVBoxLayout(this);
    lay_btn_group   = new QHBoxLayout(this);

    lv_groups->setModel(model_groups);
    groups_max_id = 0;

    lay_btn_group->addWidget(btn_new_group);
    lay_btn_group->addWidget(btn_delete_group);

    lay_mainlayout->addWidget(lv_groups);
    lay_mainlayout->addLayout(lay_btn_group);

    connect(btn_new_group, SIGNAL(clicked(bool)), this, SLOT(new_group()));
    connect(btn_delete_group, SIGNAL(clicked(bool)), this, SLOT(delete_group()));
}

p_groups::~p_groups() {

}

void p_groups::new_group() {
    groups_max_id += 1;
    QStandardItem* item = new QStandardItem(QString(QObject::tr("group"))+QString::number(groups_max_id));
    item->appendRow(new QStandardItem(QString::number(groups_max_id)));
    model_groups->appendRow(item);
}

void p_groups::delete_group() {
    model_groups->removeRow(lv_groups->currentIndex().row());
}


QString p_groups::select_group() {
    select_window *select  = new select_window(tr("Select a group"), model_groups);
    if(select->exec()) {
        return select->get_selected_item(-1); // name
    } else {
        return "";
    }
}
