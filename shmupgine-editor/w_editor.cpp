#include "w_editor.h"
#include "windows_panels.h"

w_editor::w_editor(QWidget *parent) : QMainWindow(parent){
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    /// Menu Bar
    mb_menuBar      = new QMenuBar(this);
    // File
    m_file  = new QMenu(tr("File"), this);
    a_new   = new QAction(tr("&New project"), this);
    a_open  = new QAction(tr("&Open project"), this);
    a_save  = new QAction(tr("&Save project"), this);
    a_close = new QAction(tr("&Close project"), this);
    a_exit  = new QAction(tr("&Exit"), this);
    // Config
    m_config_window = new QMenu(tr("Config"), this);
    a_project       = new QAction(tr("&Project"), this);
    a_makefile      = new QAction(tr("&Makefile"), this);
    // Ressources
    m_ressources            = new QMenu(tr("Ressources"), this);
    a_graphics              = new QAction(tr("&Graphics manager"), this);
    a_entities_collection   = new QAction(tr("&Entities collection"), this);
    a_groups                = new QAction(tr("&Groups"), this);
    a_sounds                = new QAction(tr("&Sounds"), this);
    // Build
    m_build         = new QMenu(tr("Build"), this);
    a_run           = new QAction(tr("&Run"), this);
    a_build         = new QAction(tr("&Build"), this);
    a_build_and_run = new QAction(tr("Build a&nd run"), this);

    // Graphics Scene
    gs_scene        = new QGraphicsScene(this);
    gv_graphicsview = new QGraphicsView(gs_scene, this);
    gv_layout       = new QHBoxLayout(this);
    gv_widget       = new QWidget(this);

    // Dock
    dock_entities   = new QDockWidget(tr("Entities"), this);
    dock_attributes = new QDockWidget(tr("Attributes"), this);

    /* * * * * * * * *
     * SETUP MENUBAR *
     * * * * * * * * */

    setMenuBar(mb_menuBar);

    // File
    mb_menuBar->addMenu(m_file);
    m_file->addAction(a_new);
    m_file->addAction(a_open);
    m_file->addSeparator();
    m_file->addAction(a_save);
    m_file->addSeparator();
    m_file->addAction(a_close);
    m_file->addSeparator();
    m_file->addAction(a_exit);
    // Config
    mb_menuBar->addMenu(m_config_window);
    m_config_window->addAction(a_project);
    m_config_window->addAction(a_makefile);
    // Ressources
    mb_menuBar->addMenu(m_ressources);
    m_ressources->addAction(a_graphics);
    m_ressources->addAction(a_entities_collection);
    m_ressources->addAction(a_groups);
    m_ressources->addAction(a_sounds);
    // Build
    mb_menuBar->addMenu(m_build);
    m_build->addAction(a_run);
    m_build->addAction(a_build);
    m_build->addAction(a_build_and_run);

    /// Shortcuts
    a_new->setShortcut(Qt::CTRL + Qt::Key_N);
    a_open->setShortcut(Qt::CTRL + Qt::Key_O);
    a_save->setShortcut(Qt::CTRL + Qt::Key_S);

    a_graphics->setShortcut(Qt::Key_F1);
    a_entities_collection->setShortcut(Qt::Key_F2);
    a_groups->setShortcut(Qt::Key_F3);
    a_sounds->setShortcut(Qt::Key_F4);

    /* * * * * * * * * * *
     * WINDOW MANGEMENT  *
     * * * * * * * * * * */

    gv_layout->addWidget(gv_graphicsview);
    gv_widget->setLayout(gv_layout);

    dock_entities->setWidget(p_entities_editor::Instance()->get_entities_panel());
    dock_attributes->setWidget(p_entities_editor::Instance()->get_attributes_panel());

    dock_entities->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock_attributes->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    this->addDockWidget(Qt::RightDockWidgetArea, dock_entities);
    this->addDockWidget(Qt::RightDockWidgetArea, dock_attributes);

    setDockNestingEnabled(false);

    this->setCentralWidget(gv_widget);

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(a_exit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(m_ressources, SIGNAL(triggered(QAction*)), this, SLOT(handle_ressources_choice(QAction*)));
    connect(m_file, SIGNAL(triggered(QAction*)), this, SLOT(handle_file_choice(QAction*)));
    connect(m_config_window, SIGNAL(triggered(QAction*)), this, SLOT(handle_config_choice(QAction*)));
    connect(m_build, SIGNAL(triggered(QAction*)), this, SLOT(handle_build_choice(QAction*)));
    connect(dock_attributes, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), p_entities_editor::Instance(), SLOT(change_scroll_perspective(Qt::DockWidgetArea)));

    read_settings();
    enable_editor(false);
}

w_editor::~w_editor() {

}

void w_editor::handle_config_choice(QAction *a) {
    if(a == a_project)
        w_config_window::Instance()->show_tab(project);
    else if(a == a_makefile)
        w_config_window::Instance()->show_tab(makefile);
}

void w_editor::handle_file_choice(QAction *a) {
    if(a == a_new)
        w_new_project::Instance()->show();
    else if(a == a_open)
        open_project();
    else if(a == a_save)
        save_project();
}

void w_editor::handle_ressources_choice(QAction *a) {
    if(a == a_graphics)
        w_ressources::Instance()->show_tab(graphics_manager);
    else if(a == a_entities_collection)
        w_ressources::Instance()->show_tab(entities_collection);
    else if(a == a_groups)
        w_ressources::Instance()->show_tab(groups);
    else if(a == a_sounds)
        w_ressources::Instance()->show_tab(sounds);

}

void w_editor::handle_build_choice(QAction *a) {
    if(a == a_run) {
        export_code();
    }
}

void w_editor::export_code() {
    QString maincode = "#include \"shmupgine.h\"\n\n";
    maincode += "using namespace std;\n\n";
    maincode += "int main() {\n";
    maincode += "\tshmupgine::init();\n\n";

    maincode += p_graphics_manager::Instance()->getCode();

    maincode += "\n\tscene sc1;\n";

    maincode += p_entities_collection::Instance()->getCode();
    maincode += p_entities_editor::Instance()->getCode();

    QStringList entites = p_entities_editor::Instance()->get_entities_names();
    for(int i = 0; i < entites.size(); ++i)
        maincode += QString("\tsc1.add_entity(") + entites.at(i) + QString(");\n");

    maincode += "\tsc1.run();\n\n\treturn 0;\n}";
}

void w_editor::write_settings() {
    QSettings settings;
    settings.beginGroup("editor");
    settings.setValue("size", size());
    settings.setValue("position", pos());
    settings.setValue("attr_dock_floating", dock_attributes->isFloating());
    settings.setValue("attr_dock_position", dock_attributes->pos());
    settings.setValue("attr_dock_size", dock_attributes->size());
    settings.setValue("ent_dock_floating", dock_entities->isFloating());
    settings.setValue("ent_dock_position", dock_entities->pos());
    settings.setValue("ent_dock_size", dock_entities->size());
    settings.setValue("ent_dock_size", dock_entities->size());
    settings.setValue("default_path_dialog", w_new_project::Instance()->default_path_dialog);
    settings.endGroup();
}

void w_editor::read_settings() {
    QSettings settings;

    settings.beginGroup("editor");
    resize(settings.value("size", QSize(WIDTH, HEIGHT)).toSize());
    move(settings.value("position", QPoint(200, 200)).toPoint());
    dock_attributes->move(settings.value("attr_dock_position").toPoint());
    dock_attributes->resize(settings.value("attr_dock_size").toSize());
    dock_attributes->setFloating(settings.value("attr_dock_floating", false).toBool());
    dock_attributes->move(settings.value("ent_dock_position").toPoint());
    dock_attributes->resize(settings.value("ent_dock_size").toSize());
    dock_attributes->setFloating(settings.value("ent_dock_floating", false).toBool());
    w_new_project::Instance()->default_path_dialog = settings.value("default_path_dialog", QDir::home().path()).toString();
    settings.endGroup();
}

void w_editor::closeEvent(QCloseEvent *event) {
    write_settings();
    w_ressources::Instance()->close();
    event->accept();
}

void w_editor::open_project() {
    QFile project_file(QFileDialog::getOpenFileName(this, tr("Open project file"), "", tr("JSON files (*.json)")));
    project_data::Instance()->prj_config_file = project_file.fileName();
    if(project_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonObject json_project = QJsonDocument::fromJson(project_file.readAll()).object();
        if(json_project.contains("config") && json_project["config"].isObject()) {
            p_config_panel::Instance()->load(json_project["config"].toObject());
            p_makefile::Instance()->load(json_project["config"].toObject());
            if(json_project.contains("project") && json_project["project"].isObject()) {
                QJsonObject project = json_project["project"].toObject();
                // Audio
                if(project.contains("audio") && project["audio"].isString()) {
                    QFile audio_file(QDir(project_data::Instance()->prj_config[WORKING_DIR]).filePath(project["audio"].toString()));
                    project_data::Instance()->audio_config_file = audio_file.fileName();
                    if(audio_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        QJsonObject json_audio = QJsonDocument::fromJson(audio_file.readAll()).object();
                        p_sounds::Instance()->load(json_audio);
                    }
                    audio_file.close();
                }
                // Graphics
                if(project.contains("graphics") && project["graphics"].isString()) {
                    QFile graphics_file(QDir(project_data::Instance()->prj_config[WORKING_DIR]).filePath(project["graphics"].toString()));
                    project_data::Instance()->graphics_config_file = graphics_file.fileName();
                    if(graphics_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        QJsonArray json_graphics = QJsonDocument::fromJson(graphics_file.readAll()).array();
                        p_graphics_manager::Instance()->load(json_graphics);
                    }
                    graphics_file.close();
                }
                // Entities
                if(project.contains("entities") && project["entities"].isString()) {
                    QFile entities_file(QDir(project_data::Instance()->prj_config[WORKING_DIR]).filePath(project["entities"].toString()));
                    project_data::Instance()->entities_config_file = entities_file.fileName();
                    if(entities_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        QJsonArray json_entities = QJsonDocument::fromJson(entities_file.readAll()).array();
                        p_entities_editor::Instance()->load(json_entities);
                    }
                    entities_file.close();
                }
            }
        }
        w_editor::Instance()->enable_editor(true);
        project_file.close();
    }
}

void w_editor::save_project() {
    QFile out_project_file(QDir(project_data::Instance()->prj_config[WORKING_DIR]).filePath(project_data::Instance()->prj_config_file));
    if(out_project_file.open(QIODevice::WriteOnly)) {
        QJsonObject json_config;
        json_config["project_name"] = project_data::Instance()->prj_config[NAME];
        json_config["working_dir"] = project_data::Instance()->prj_config[WORKING_DIR];
        json_config["compiler"] = project_data::Instance()->prj_config[COMPILER_PATH];
        json_config["compiler_flags"] = project_data::Instance()->prj_config[COMPILER_FLAGS];
        json_config["shmupgine"] = project_data::Instance()->prj_config[ENGINE_PATH];
        json_config["make"] = project_data::Instance()->prj_config[MAKE_PATH];
        json_config["makefile"] = p_makefile::Instance()->get_filename();
        QJsonObject json_project;
        json_project["config"] = json_config;
        QJsonObject json_project_files;
        json_project_files["audio"] = project_data::Instance()->audio_config_file;
        json_project_files["graphics"] = project_data::Instance()->graphics_config_file;
        json_project_files["entities"] = project_data::Instance()->entities_config_file;
        json_project["project"] = json_project_files;
        out_project_file.write(QJsonDocument(json_project).toJson());
        out_project_file.close();
    }
    p_sounds::Instance()->save();
    p_graphics_manager::Instance()->save();
    p_entities_editor::Instance()->save();
}

void w_editor::enable_editor(bool enable) {
    dock_attributes->setEnabled(enable);
    dock_entities->setEnabled(enable);
    m_config_window->setEnabled(enable);
    m_ressources->setEnabled(enable);
    m_build->setEnabled(enable);
    a_save->setEnabled(enable);
    a_close->setEnabled(enable);
    a_graphics->setEnabled(enable);
    a_entities_collection->setEnabled(enable);
    a_sounds->setEnabled(enable);
    a_groups->setEnabled(enable);
}
