#include "attr_spawner.h"

attr_spawner::attr_spawner(entities_attributes_panel* container) : attribute(container) {
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

    cb_spawn_at_parents_position    = new QCheckBox(tr("Spawn at parent's position"), this);
    cb_autospawn                    = new QCheckBox(tr("Auto-spawn"), this);

    gb_box->setTitle(tr("Spawner"));
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

    lay_groupbox->addLayout(lay_entity_profile);
    lay_groupbox->addLayout(lay_cooldown);
    lay_groupbox->addWidget(lbl_groups);
    lay_groupbox->addWidget(lv_groups);
    lay_groupbox->addLayout(lay_groups_btn);
    lay_groupbox->addWidget(cb_spawn_at_parents_position);
    lay_groupbox->addWidget(cb_autospawn);

    setFixedHeight(sizeHint().height());

    connect(btn_load_entity, SIGNAL(clicked(bool)), this, SLOT(load_profile()));
    connect(btn_add_group, SIGNAL(clicked(bool)), this, SLOT(add_group()));
    connect(btn_del_group, SIGNAL(clicked(bool)), this, SLOT(remove_group()));
}

attr_spawner::~attr_spawner() {

}

QString attr_spawner::getCode() {
    QString code = attribute::allocation("spawner");
    if(!le_entity_profile->text().isEmpty()) {
        code += attribute::get("spawner") + QString("->set_profile(") + le_entity_profile->text() + QString(");\n");
        if(cb_autospawn->isChecked())
            code += attribute::get("spawner") + QString("->f_auto_spawn = true;\n");
        if(!cb_spawn_at_parents_position->isChecked())
            code += attribute::get("spawner") + QString("->f_spawn_at_parent = false;\n");
        if(le_cooldown_ms->text().toInt() != 250)
            code += attribute::get("spawner") + QString("->ms_cooldown = ") + le_cooldown_ms->text()+ QString(";\n");
        for(int i = 0; i < model_groups->rowCount(); ++i)
            code += attribute::get("spawner") + QString("->add_group_to_join(") + model_groups->index(i,0).data().toString() + QString(");\n");
    }
    return code;
}

void attr_spawner::load_profile() {
    le_entity_profile->setText(p_entities_collection::Instance()->select_entity());
}

void attr_spawner::add_group() {
    QString group = p_groups::Instance()->select_group();
    if(!group.isEmpty())
        model_groups->appendRow(new QStandardItem(group));
}

void attr_spawner::remove_group() {
    model_groups->removeRow(lv_groups->currentIndex().row());
}
