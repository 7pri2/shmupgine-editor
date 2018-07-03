#include "w_ressources.h"
#include "windows_panels.h"

w_ressources::w_ressources(QWidget *parent) : QWidget(parent) {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    tabs            = new QTabWidget(this);
    btn_close       = new QPushButton(tr("Close"), this);
    lay_mainlayout  = new QVBoxLayout(this);

    a_graphics_manager      = new QAction(this);
    a_entities_collection   = new QAction(this);
    a_groups                = new QAction(this);
    a_sounds_manager        = new QAction(this);

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
    tabs->addTab(p_sounds::Instance(), tr("&Sounds"));

    this->setProperty("class", "background");

    a_graphics_manager->setShortcut(Qt::Key_F1);
    a_entities_collection->setShortcut(Qt::Key_F2);
    a_groups->setShortcut(Qt::Key_F3);
    a_sounds_manager->setShortcut(Qt::Key_F4);

    tabs->addAction(a_graphics_manager);
    tabs->addAction(a_entities_collection);
    tabs->addAction(a_groups);
    tabs->addAction(a_sounds_manager);

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    QSignalMapper* actions_mapper = new QSignalMapper(this);
    actions_mapper->setMapping(a_graphics_manager, graphics_manager);
    actions_mapper->setMapping(a_entities_collection, entities_collection);
    actions_mapper->setMapping(a_groups, groups);
    actions_mapper->setMapping(a_sounds_manager, sounds);

    connect(btn_close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(a_graphics_manager, SIGNAL(triggered(bool)), actions_mapper, SLOT(map()));
    connect(a_entities_collection, SIGNAL(triggered(bool)), actions_mapper, SLOT(map()));
    connect(a_groups, SIGNAL(triggered(bool)), actions_mapper, SLOT(map()));
    connect(a_sounds_manager, SIGNAL(triggered(bool)), actions_mapper, SLOT(map()));
    connect(actions_mapper, SIGNAL(mapped(int)), this, SLOT(show_tab(int)));
}

w_ressources::~w_ressources() {

}

void w_ressources::show_tab(int tab) {
    tabs->setCurrentIndex(tab);
    this->show();
}
