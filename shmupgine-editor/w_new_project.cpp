#include "w_new_project.h"
#include "w_editor.h"

w_new_project::w_new_project(QWidget *parent) : QDialog(parent) {
    /* * * * * * * * *
     * WINDOW TITLE  *
     * * * * * * * * */

    setWindowTitle(tr("Create new project"));
    this->setModal(true);

    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    lbl_name            = new QLabel(tr("Project name"), this);
    lbl_working_dir     = new QLabel(tr("Create in"), this);
    lbl_compiler        = new QLabel(tr("Compiler"), this);
    lbl_compiler_flags  = new QLabel(tr("Compiler flags"), this);
    lbl_engine          = new QLabel(tr("Path to shmupgine"), this);
    lbl_make            = new QLabel(tr("Make"), this);
    lbl_error           = new QLabel(this);

    le_name             = new QLineEdit(project_data::Instance()->prj_config[NAME], this);
    le_working_dir      = new QLineEdit(project_data::Instance()->prj_config[WORKING_DIR], this);
    le_compiler         = new QLineEdit(project_data::Instance()->prj_config[COMPILER_PATH], this);
    le_compiler_flags   = new QLineEdit(project_data::Instance()->prj_config[COMPILER_FLAGS], this);
    le_engine           = new QLineEdit(project_data::Instance()->prj_config[ENGINE_PATH], this);
    le_make             = new QLineEdit(project_data::Instance()->prj_config[MAKE_PATH], this);

    lay_mainlayout      = new QVBoxLayout(this);
    lay_advanced_config = new QVBoxLayout(this);
    lay_working_dir     = new QHBoxLayout(this);
    lay_compiler        = new QHBoxLayout(this);
    lay_compiler_flags  = new QHBoxLayout(this);
    lay_engine          = new QHBoxLayout(this);
    lay_make            = new QHBoxLayout(this);
    lay_buttons         = new QHBoxLayout(this);
    lay_show_more       = new QHBoxLayout(this);

    btn_create  = new QPushButton(tr("&Create"), this);
    btn_cancel  = new QPushButton(tr("&Cancel"), this);

    btn_working_dir = new QPushButton("...", this);
    btn_compiler    = new QPushButton("...", this);
    btn_engine      = new QPushButton("...", this);
    btn_make        = new QPushButton("...", this);

    chkbx_show_more = new QCheckBox(tr("Show advanced configuration"), this);

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

    // Exit buttons
    lay_buttons->addWidget(btn_create);
    lay_buttons->addWidget(btn_cancel);

    // Advanced configuration checkbox
    lay_show_more->addWidget(chkbx_show_more, 0, Qt::AlignRight);

    // Advanced configuration layout
    lay_advanced_config->addLayout(lay_compiler);
    lay_advanced_config->addLayout(lay_compiler_flags);
    lay_advanced_config->addLayout(lay_engine);
    lay_advanced_config->addLayout(lay_make);

    // Main layout
    this->setLayout(lay_mainlayout);
    lay_mainlayout->addWidget(lbl_name);
    lay_mainlayout->addWidget(le_name);
    lay_mainlayout->addWidget(lbl_working_dir);
    lay_mainlayout->addLayout(lay_working_dir);
    lay_mainlayout->addLayout(lay_show_more);
    lay_mainlayout->addLayout(lay_advanced_config);
    lay_mainlayout->addLayout(lay_buttons);
    lay_mainlayout->addWidget(lbl_error);

    // Resize buttons
    btn_working_dir->setMaximumWidth(BTN_WIDTH);
    btn_compiler->setMaximumWidth(BTN_WIDTH);
    btn_engine->setMaximumWidth(BTN_WIDTH);
    btn_make->setMaximumWidth(BTN_WIDTH);

    this->setProperty("class", "background");
    this->setMinimumWidth(280);
    lbl_error->hide();
    lbl_error->setProperty("class", "error");
    default_path_dialog = QDir::home().path();

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(le_name, SIGNAL(textChanged(QString)), this, SLOT(switch_create_btn_state()));
    connect(le_compiler, SIGNAL(textChanged(QString)), this, SLOT(switch_create_btn_state()));
    connect(le_compiler_flags, SIGNAL(textChanged(QString)), this, SLOT(switch_create_btn_state()));
    connect(le_engine, SIGNAL(textChanged(QString)), this, SLOT(switch_create_btn_state()));
    connect(le_make, SIGNAL(textChanged(QString)), this, SLOT(switch_create_btn_state()));
    connect(le_working_dir, SIGNAL(textChanged(QString)), this, SLOT(switch_create_btn_state()));
    connect(btn_cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(btn_create, SIGNAL(clicked(bool)), this, SLOT(create_new_project()));
    connect(chkbx_show_more, SIGNAL(toggled(bool)), this, SLOT(show_details(bool)));

    connect(btn_compiler, SIGNAL(clicked(bool)), this, SLOT(choose_compiler_path()));
    connect(btn_engine, SIGNAL(clicked(bool)), this, SLOT(choose_engine_path()));
    connect(btn_make, SIGNAL(clicked(bool)), this, SLOT(choose_make_path()));
    connect(btn_working_dir, SIGNAL(clicked(bool)), this, SLOT(choose_working_dir()));

    switch_create_btn_state();
    refill_fields();
    show_details(false);
}

w_new_project::~w_new_project() {

}

/* * * * *
 * SLOTS *
 * * * * */

void w_new_project::switch_create_btn_state() {
    bool can_be_activated =
        !le_compiler->text().isEmpty()          &&
        !le_compiler_flags->text().isEmpty()    &&
        !le_engine->text().isEmpty()            &&
        !le_make->text().isEmpty()              &&
        !le_name->text().isEmpty()              &&
        !le_working_dir->text().isEmpty();
    btn_create->setEnabled(can_be_activated);
}

void w_new_project::create_new_project() {
    QDir root = QDir::root();
    project_data::Instance()->prj_config[NAME] = le_name->text();
    project_data::Instance()->prj_config[COMPILER_PATH] = le_compiler->text();
    project_data::Instance()->prj_config[COMPILER_FLAGS] = le_compiler_flags->text();
    project_data::Instance()->prj_config[WORKING_DIR] = le_working_dir->text();
    project_data::Instance()->prj_config[ENGINE_PATH] = le_engine->text();
    project_data::Instance()->prj_config[MAKE_PATH] = le_make->text();
    QDir wd = QDir(project_data::Instance()->prj_config[WORKING_DIR]);

    // We need to know if the user already created a new directory for the project or not
    if(wd.exists()) {
        if(wd.dirName() == project_data::Instance()->prj_config[NAME]) { // Already created by user
            project_data::Instance()->prj_config[WORKING_DIR] = wd.path();
        } else { // We create the directory
            root.mkpath(QDir(project_data::Instance()->prj_config[WORKING_DIR]).filePath(project_data::Instance()->prj_config[NAME]));
        }
    } else {
        lbl_error->show();
        lbl_error->setText(tr("Can't set up project at this directory"));
        return;
    }

    lbl_error->hide();
    w_editor::Instance()->enable_editor(true);
    close();
}

void w_new_project::refill_fields() {
    le_name->setText(project_data::Instance()->prj_config[NAME]);
    le_compiler->setText(project_data::Instance()->prj_config[COMPILER_PATH]);
    le_compiler_flags->setText(project_data::Instance()->prj_config[COMPILER_FLAGS]);
    le_engine->setText(project_data::Instance()->prj_config[ENGINE_PATH]);
    le_make->setText(project_data::Instance()->prj_config[MAKE_PATH]);
    le_working_dir->setText(project_data::Instance()->prj_config[WORKING_DIR]);
}

void w_new_project::show_details(bool show) {
    if(show) {
        lay_mainlayout->addLayout(lay_advanced_config);
        lay_mainlayout->removeItem(lay_buttons);
        lay_mainlayout->addLayout(lay_buttons);
        lay_mainlayout->removeWidget(lbl_error);
        lay_mainlayout->addWidget(lbl_error);
    } else {
        lay_mainlayout->removeItem(lay_advanced_config);
    }

    le_compiler->setVisible(show);
    le_compiler_flags->setVisible(show);
    le_engine->setVisible(show);
    le_make->setVisible(show);

    btn_compiler->setVisible(show);
    btn_engine->setVisible(show);
    btn_make->setVisible(show);

    lbl_compiler->setVisible(show);
    lbl_compiler_flags->setVisible(show);
    lbl_engine->setVisible(show);
    lbl_make->setVisible(show);

    adjustSize();
}

void w_new_project::choose_compiler_path() {
    le_compiler->setText(QFileDialog::getOpenFileName(this, tr("Choose compiler")));
}

void w_new_project::choose_engine_path() {
    le_engine->setText(QFileDialog::getExistingDirectory(this,
                                           tr("Locate shmupgine directory"),
                                           QDir::homePath(),
                                           QFileDialog::ShowDirsOnly));
}

void w_new_project::choose_make_path() {
    le_make->setText(QFileDialog::getOpenFileName(this, tr("Locate make")));
}

void w_new_project::choose_working_dir() {
    le_working_dir->setText(QFileDialog::getExistingDirectory(this,
                                          tr("Choose project directory"),
                                          default_path_dialog,
                                          QFileDialog::ShowDirsOnly));
    default_path_dialog = le_working_dir->text();
}
