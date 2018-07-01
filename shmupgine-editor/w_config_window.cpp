#include "w_config_window.h"

w_config_window::w_config_window(QWidget* parent) : QWidget(parent)  {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    tab_widget  = new QTabWidget(this);

    mainlayout  = new QVBoxLayout(this);
    btn_layout  = new QHBoxLayout(this);

    btn_save    = new QPushButton(tr("Save"), this);
    btn_close   = new QPushButton(tr("Close"), this);

    /* * * * * *
     * LAYOUTS *
     * * * * * */

    btn_layout->addWidget(btn_save);
    btn_layout->addWidget(btn_close);

    mainlayout->addWidget(tab_widget);
    mainlayout->addLayout(btn_layout);

    /* * * * * * * * * * *
     * WINDOW MANAGEMENT *
     * * * * * * * * * * */

    this->setWindowTitle(tr("Configuration"));
    this->setProperty("class", "background");

    tab_widget->addTab(p_config_panel::Instance(), tr("&Project"));
    tab_widget->addTab(p_makefile::Instance(), tr("&Makefile"));

    btn_save->setEnabled(false);

    connect(btn_close, SIGNAL(clicked(bool)), this, SLOT(revert_changes()));
    connect(btn_save, SIGNAL(clicked(bool)), this, SLOT(save_changes()));
    connect(p_config_panel::Instance(), SIGNAL(changes_made(QWidget*, bool)), this, SLOT(update_buttons(QWidget*, bool)));
    connect(p_makefile::Instance(), SIGNAL(changes_made(QWidget*, bool)), this, SLOT(update_buttons(QWidget*, bool)));
}

w_config_window::~w_config_window() {

}

void w_config_window::show_tab(int tab) {
    tab_widget->setCurrentIndex(tab);
    this->show();
}

void w_config_window::revert_changes() {
    p_config_panel::Instance()->revert_changes();
    p_makefile::Instance()->revert_changes();
    close();
}

void w_config_window::save_changes() {
    p_config_panel::Instance()->save_changes();
    p_makefile::Instance()->save_changes();
}

void w_config_window::update_buttons(QWidget* sender, bool state) {
    modifs[sender] = state;
    btn_save->setEnabled(modifs[p_config_panel::Instance()] || modifs[p_makefile::Instance()]);
}
