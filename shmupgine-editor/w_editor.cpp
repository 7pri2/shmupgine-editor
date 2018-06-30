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
    settings.endGroup();
}

void w_editor::closeEvent(QCloseEvent *event) {
    write_settings();
    event->accept();
}
