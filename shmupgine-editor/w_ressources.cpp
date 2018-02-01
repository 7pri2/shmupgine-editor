#include "w_ressources.h"
#include "windows_panels.h"

w_ressources::w_ressources(QWidget *parent) : QWidget(parent) {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    tabs            = new QTabWidget(this);
    btn_close       = new QPushButton(tr("Close"), this);
    lay_mainlayout  = new QVBoxLayout(this);

    /* * * * * *
     * LAYOUTS *
     * * * * * */

    lay_mainlayout->addWidget(tabs);
    lay_mainlayout->addWidget(btn_close);

    /* * * * * * * * * * *
     * WINDOW MANAGEMENT *
     * * * * * * * * * * */

    this->setWindowTitle(tr("Ressources"));

    tabs->addTab(p_graphics_manager::Instance(), tr("&Graphics manager"));
    tabs->addTab(p_entities_collection::Instance(), tr("&Entities collection"));
    tabs->addTab(p_groups::Instance(), tr("&Groups"));

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(btn_close, SIGNAL(clicked(bool)), this, SLOT(close()));
}

w_ressources::~w_ressources() {

}

void w_ressources::show_tab(int tab) {
    tabs->setCurrentIndex(tab);
    this->show();
}
