#include "spawnslot.h"

spawnslot::spawnslot(attr_spawner* parent) : QWidget(parent) {
    /* * * * * * * *
     * ALLOCATION  *
     * * * * * * * */

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

    lbl_sound           = new QLabel(tr("Sound played on spawn"), this);
    le_sound            = new QLineEdit(this);
    btn_select_sound    = new QPushButton("...", this);
    lay_sound           = new QHBoxLayout(this);

    lbl_name    = new QLabel(tr("Name of the slot"), this);
    le_name     = new QLineEdit(this);
    lay_name    = new QHBoxLayout(this);

    m_spawner   = parent;

    /* * * * * * * * * * *
     * WIDGET MANAGEMENT *
     * * * * * * * * * * */

    this->setLayout(lay_main);

    cb_spawn_at_parents_position    = new QCheckBox(tr("Spawn at parent's position"), this);
    cb_autospawn                    = new QCheckBox(tr("Auto-spawn"), this);

    btn_load_entity->setMaximumWidth(32);
    btn_select_sound->setMaximumWidth(32);

    lv_groups->setModel(model_groups);
    lv_groups->setMaximumHeight(MAXHEIGHT);
    lv_groups->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /* * * * * * * *
     *   LAYOUTS   *
     * * * * * * * */

    lay_groups_btn->addWidget(btn_add_group);
    lay_groups_btn->addWidget(btn_del_group);

    lay_cooldown->addWidget(lbl_cooldown_ms);
    lay_cooldown->addWidget(le_cooldown_ms);

    lay_entity_profile->addWidget(lbl_entity_profile);
    lay_entity_profile->addWidget(le_entity_profile);
    lay_entity_profile->addWidget(btn_load_entity);

    lay_sound->addWidget(lbl_sound);
    lay_sound->addWidget(le_sound);
    lay_sound->addWidget(btn_select_sound);

    lay_name->addWidget(lbl_name);
    lay_name->addWidget(le_name);

    lay_main->addLayout(lay_name);
    lay_main->addLayout(lay_entity_profile);
    lay_main->addLayout(lay_cooldown);
    lay_main->addLayout(lay_sound);
    lay_main->addWidget(lbl_groups);
    lay_main->addWidget(lv_groups);
    lay_main->addLayout(lay_groups_btn);
    lay_main->addWidget(cb_spawn_at_parents_position);
    lay_main->addWidget(cb_autospawn);

    setFixedHeight(sizeHint().height());

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(btn_load_entity, SIGNAL(clicked(bool)), this, SLOT(load_profile()));
    connect(btn_add_group, SIGNAL(clicked(bool)), this, SLOT(add_group()));
    connect(btn_del_group, SIGNAL(clicked(bool)), this, SLOT(remove_group()));
    connect(le_name, SIGNAL(textEdited(QString)), m_spawner, SLOT(update_tab_name(QString)));
}

spawnslot::~spawnslot() {

}

QString spawnslot::getCode() {
    QString code = m_spawner->get("spawner") + "->add_slot(\"" + le_name->text() + "\");\n";
    if(!le_sound->text().isEmpty())
        code += m_spawner->get("spawner") + "->set_song_to_play(\"" + le_sound->text() + "\");\n";
    if(!le_entity_profile->text().isEmpty()) {
        code += m_spawner->get("spawner") + QString("->set_profile(\"") + le_name->text() + "\", " + le_entity_profile->text() + QString(");\n");
        if(cb_autospawn->isChecked())
            code += m_spawner->get("spawner") + QString("->set_auto_spawn(\"" + le_name->text() + "\", true);\n");
        if(!cb_spawn_at_parents_position->isChecked())
            code += m_spawner->get("spawner") + QString("->set_spawn_at_parent(\"" + le_name->text() + "\", false);\n");
        if(le_cooldown_ms->text().toInt() != 250)
            code += m_spawner->get("spawner") + QString("->set_cooldown(\"") + le_name->text() + "\", " + le_cooldown_ms->text() + QString(");\n");
        for(int i = 0; i < model_groups->rowCount(); ++i)
            code += m_spawner->get("spawner") + QString("->add_group_to_join(\"") + le_name->text() + "\", " + model_groups->index(i,0).data().toString() + QString(");\n");
    }
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
