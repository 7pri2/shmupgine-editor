#include "p_config_panel.h"

p_config_panel::p_config_panel(QWidget *parent) : QWidget(parent) {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    lbl_name            = new QLabel(tr("Project name"), this);
    lbl_working_dir     = new QLabel(tr("Working directory"), this);
    lbl_compiler        = new QLabel(tr("Compiler"), this);
    lbl_compiler_flags  = new QLabel(tr("Compiler flags"), this);
    lbl_engine          = new QLabel(tr("Path to shmupgine"), this);
    lbl_make            = new QLabel(tr("Make"), this);

    le_name             = new QLineEdit(project_data::Instance()->prj_config[NAME], this);
    le_working_dir      = new QLineEdit(project_data::Instance()->prj_config[WORKING_DIR], this);
    le_compiler         = new QLineEdit(project_data::Instance()->prj_config[COMPILER_PATH], this);
    le_compiler_flags   = new QLineEdit(project_data::Instance()->prj_config[COMPILER_FLAGS], this);
    le_engine           = new QLineEdit(project_data::Instance()->prj_config[ENGINE_PATH], this);
    le_make             = new QLineEdit(project_data::Instance()->prj_config[MAKE_PATH], this);

    lay_mainlayout      = new QVBoxLayout(this);
    lay_working_dir     = new QHBoxLayout(this);
    lay_compiler        = new QHBoxLayout(this);
    lay_compiler_flags  = new QHBoxLayout(this);
    lay_engine          = new QHBoxLayout(this);
    lay_make            = new QHBoxLayout(this);
    lay_buttons         = new QHBoxLayout(this);

    btn_working_dir = new QPushButton("...", this);
    btn_compiler    = new QPushButton("...", this);
    btn_engine      = new QPushButton("...", this);
    btn_make        = new QPushButton("...", this);

    /* * * * * * * * * * *
     * WINDOW MANAGEMENT *
     * * * * * * * * * * */

    // Working dir
    lay_working_dir->addWidget(le_working_dir);
    lay_working_dir->addWidget(btn_working_dir);

    // Compiler
    lay_compiler->addWidget(lbl_compiler);
    lay_compiler->addWidget(le_compiler);
    lay_compiler->addWidget(btn_compiler);

    // Compiler flags
    lay_compiler_flags->addWidget(lbl_compiler_flags);
    lay_compiler_flags->addWidget(le_compiler_flags);

    // Engine path
    lay_engine->addWidget(lbl_engine);
    lay_engine->addWidget(le_engine);
    lay_engine->addWidget(btn_engine);

    // Make
    lay_make->addWidget(lbl_make);
    lay_make->addWidget(le_make);
    lay_make->addWidget(btn_make);

    // Main Layout
    this->setLayout(lay_mainlayout);
    lay_mainlayout->addWidget(lbl_name);
    lay_mainlayout->addWidget(le_name);
    lay_mainlayout->addWidget(lbl_working_dir);
    lay_mainlayout->addLayout(lay_working_dir);
    lay_mainlayout->addLayout(lay_compiler);
    lay_mainlayout->addLayout(lay_compiler_flags);
    lay_mainlayout->addLayout(lay_engine);
    lay_mainlayout->addLayout(lay_make);

    // Resize buttons
    btn_working_dir->setMaximumWidth(BTN_WIDTH);
    btn_compiler->setMaximumWidth(BTN_WIDTH);
    btn_engine->setMaximumWidth(BTN_WIDTH);
    btn_make->setMaximumWidth(BTN_WIDTH);

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */
    connect(le_name, SIGNAL(textChanged(QString)), this, SLOT(emit_changes()));
    connect(le_compiler, SIGNAL(textChanged(QString)), this, SLOT(emit_changes()));
    connect(le_compiler_flags, SIGNAL(textChanged(QString)), this, SLOT(emit_changes()));
    connect(le_working_dir, SIGNAL(textChanged(QString)), this, SLOT(emit_changes()));
    connect(le_engine, SIGNAL(textChanged(QString)), this, SLOT(emit_changes()));
    connect(le_make, SIGNAL(textChanged(QString)), this, SLOT(emit_changes()));

    revert_changes();
}

p_config_panel::~p_config_panel() {

}

void p_config_panel::emit_changes() {
    emit changes_made(this, project_data::Instance()->prj_config[NAME] != le_name->text()
        || project_data::Instance()->prj_config[COMPILER_FLAGS] != le_compiler_flags->text()
        || project_data::Instance()->prj_config[COMPILER_PATH] != le_compiler->text()
        || project_data::Instance()->prj_config[MAKE_PATH] != le_make->text()
        || project_data::Instance()->prj_config[WORKING_DIR] != le_working_dir->text());
}

void p_config_panel::revert_changes() {
    le_name->setText(project_data::Instance()->prj_config[NAME]);
    le_working_dir->setText(project_data::Instance()->prj_config[WORKING_DIR]);
    le_compiler->setText(project_data::Instance()->prj_config[COMPILER_PATH]);
    le_compiler_flags->setText(project_data::Instance()->prj_config[COMPILER_FLAGS]);
    le_engine->setText(project_data::Instance()->prj_config[ENGINE_PATH]);
    le_make->setText(project_data::Instance()->prj_config[MAKE_PATH]);
    emit_changes();
}

void p_config_panel::save_changes() {
    project_data::Instance()->prj_config[NAME] = le_name->text();
    project_data::Instance()->prj_config[COMPILER_FLAGS] = le_compiler_flags->text();
    project_data::Instance()->prj_config[COMPILER_PATH] = le_compiler->text();
    project_data::Instance()->prj_config[MAKE_PATH] = le_make->text();
    project_data::Instance()->prj_config[WORKING_DIR] = le_working_dir->text();
    emit_changes();
}
