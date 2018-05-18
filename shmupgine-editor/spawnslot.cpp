#include "spawnslot.h"

spawnslot::spawnslot(QWidget* parent) : QWidget(parent) {
    lay_main = new QVBoxLayout(this);

    lbl_groups      = new QLabel(tr("Entity spawns in groups"), this);
    lv_groups       = new QListView(this);
    model_groups    = new QStandardItemModel(this);
    btn_add_group   = new QPushButton(tr("Add"), this);
    btn_del_group   = new QPushButton(tr("Delete"), this);
    lay_groups_btn  = new QHBoxLayout(this);

    lbl_cooldown_ms = new QLabel(tr("Time to spawn (ms)"), this);
    le_cooldown_ms  = new QLineEdit(this);
    lay_cooldown        = new QHBoxLayout(this);

    lbl_entity_profile  = new QLabel(tr("Profile to spawn"), this);
    le_entity_profile   = new QLineEdit(this);
    btn_load_entity     = new QPushButton("...", this);
    lay_entity_profile  = new QHBoxLayout(this);

    this->setLayout(lay_main);

    cb_spawn_at_parents_position    = new QCheckBox(tr("Spawn at parent's position"), this);
    cb_autospawn                    = new QCheckBox(tr("Auto-spawn"), this);

    btn_load_entity->setMaximumWidth(32);

    lv_groups->setModel(model_groups);
    lv_groups->setMaximumHeight(MAXHEIGHT);
    lv_groups->setEditTriggers(QAbstractItemView::NoEditTriggers);

    lay_groups_btn->addWidget(btn_add_group);
    lay_groups_btn->addWidget(btn_del_group);

    lay_cooldown->addWidget(lbl_cooldown_ms);
    lay_cooldown->addWidget(le_cooldown_ms);

    lay_entity_profile->addWidget(lbl_entity_profile);
    lay_entity_profile->addWidget(le_entity_profile);
    lay_entity_profile->addWidget(btn_load_entity);

    lay_main->addLayout(lay_entity_profile);
    lay_main->addLayout(lay_cooldown);
    lay_main->addWidget(lbl_groups);
    lay_main->addWidget(lv_groups);
    lay_main->addLayout(lay_groups_btn);
    lay_main->addWidget(cb_spawn_at_parents_position);
    lay_main->addWidget(cb_autospawn);

    setFixedHeight(sizeHint().height());

    connect(btn_load_entity, SIGNAL(clicked(bool)), this, SLOT(load_profile()));
    connect(btn_add_group, SIGNAL(clicked(bool)), this, SLOT(add_group()));
    connect(btn_del_group, SIGNAL(clicked(bool)), this, SLOT(remove_group()));
}

spawnslot::~spawnslot() {

}

QString spawnslot::getCode() {
    QString code = " ";
    return code;
}

void spawnslot::load_profile() {
    le_entity_profile->setText(p_entities_collection::Instance()->select_entity());
}

void spawnslot::add_group() {
    QString group = p_groups::Instance()->select_group();
    if(!group.isEmpty())
        model_groups->appendRow(new QStandardItem(group));
}

void spawnslot::remove_group() {
    model_groups->removeRow(lv_groups->currentIndex().row());
}
