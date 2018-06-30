#ifndef W_EDITOR_H
#define W_EDITOR_H

#include <QSplitter>
#include <QWidgetAction>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSplitter>
#include <QDockWidget>
#include <QSettings>
#include <QCloseEvent>

#include <QHBoxLayout>
#include "singleton.h"

#define WIDTH   720
#define HEIGHT  480

class w_editor : public QMainWindow, public Singleton<w_editor> {
    Q_OBJECT

    friend class Singleton<w_editor>;

public:
    void write_settings();
    void read_settings();
    void closeEvent(QCloseEvent *event);

public slots:
    void handle_file_choice(QAction*);
    void handle_build_choice(QAction*);
    void handle_config_choice(QAction*);
    void handle_ressources_choice(QAction*);
    void export_code();

private:
    w_editor(const w_editor&);
    w_editor(QWidget *parent = 0);
    virtual ~w_editor();

    /// Menu Bar
    QMenuBar*   mb_menuBar;
    // File
    QMenu*      m_file;
    QAction*    a_new;
    QAction*    a_open;
    QAction*    a_save;
    QAction*    a_close;
    QAction*    a_exit;
    // Config
    QMenu*      m_config_window;
    QAction*    a_project;
    QAction*    a_makefile;
    // Ressources
    QMenu*      m_ressources;
    QAction*    a_graphics;
    QAction*    a_entities_collection;
    QAction*    a_groups;
    QAction*    a_sounds;
    // Build
    QMenu*      m_build;
    QAction*    a_run;
    QAction*    a_build;
    QAction*    a_build_and_run;

    // GraphicScene
    QGraphicsScene* gs_scene;
    QGraphicsView*  gv_graphicsview;
    QWidget*        gv_widget;
    QHBoxLayout*    gv_layout;

    QDockWidget*    dock_entities;
    QDockWidget*    dock_attributes;
};

#endif // W_EDITOR_H
