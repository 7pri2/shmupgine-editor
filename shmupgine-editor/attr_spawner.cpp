#include "attr_spawner.h"
#include "spawnslot.h"

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
    for(int i = 0; i < tw_spawnslots->count()-1; ++i)
        code += ((attr_spawner*)(tw_spawnslots->widget(i)))->getCode();
    return code;
}

void attr_spawner::new_tab(int tab) {
    if(tw_spawnslots->indexOf(newtab) == tab) {
        tw_spawnslots->addTab(new spawnslot(this), QString::number(tw_spawnslots->count()));
        tw_spawnslots->removeTab(tab);
        tw_spawnslots->addTab(newtab, "+");
    }
}

void attr_spawner::update_tab_name(QString name) {
    tw_spawnslots->setTabText(tw_spawnslots->currentIndex(), name);
}

bool attr_spawner::verify_validity() {
    return true;
}
