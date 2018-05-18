#include "attr_spawner.h"

attr_spawner::attr_spawner(entities_attributes_panel* container) : attribute(container) {
    tw_spawnslots = new QTabWidget(this);
    newtab = new QWidget(this);

    tw_spawnslots->addTab(new spawnslot(this), "1");
    tw_spawnslots->addTab(newtab, "+");

    gb_box->setTitle(tr("Spawner"));

    lay_groupbox->addWidget(tw_spawnslots);

    setFixedHeight(sizeHint().height());

    connect(tw_spawnslots, SIGNAL(tabBarClicked(int)), this, SLOT(new_tab(int)));
}

attr_spawner::~attr_spawner() {

}

QString attr_spawner::getCode() {
    QString code = attribute::allocation("spawner");
    /*if(!le_entity_profile->text().isEmpty()) {
        code += attribute::get("spawner") + QString("->set_profile(") + le_entity_profile->text() + QString(");\n");
        if(cb_autospawn->isChecked())
            code += attribute::get("spawner") + QString("->f_auto_spawn = true;\n");
        if(!cb_spawn_at_parents_position->isChecked())
            code += attribute::get("spawner") + QString("->f_spawn_at_parent = false;\n");
        if(le_cooldown_ms->text().toInt() != 250)
            code += attribute::get("spawner") + QString("->ms_cooldown = ") + le_cooldown_ms->text()+ QString(";\n");
        for(int i = 0; i < model_groups->rowCount(); ++i)
            code += attribute::get("spawner") + QString("->add_group_to_join(") + model_groups->index(i,0).data().toString() + QString(");\n");
    }*/
    return code;
}

void attr_spawner::new_tab(int tab) {
    if(tw_spawnslots->indexOf(newtab) == tab) {
        tw_spawnslots->addTab(new spawnslot(this), QString::number(tw_spawnslots->count()));
        tw_spawnslots->removeTab(tab);
        tw_spawnslots->addTab(newtab, "+");
    }
}
