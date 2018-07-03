#ifndef W_RESSOURCES_H
#define W_RESSOURCES_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "singleton.h"

enum {
    graphics_manager    = 0,
    entities_collection = 1,
    groups              = 2,
    sounds              = 3
};

class w_ressources : public QWidget, public Singleton<w_ressources> {
    Q_OBJECT

    friend class Singleton<w_ressources>;

public slots:
    void show_tab(int tab);

private:
    w_ressources(const w_ressources&);
    w_ressources(QWidget* parent = 0);
    ~w_ressources();

    QTabWidget*     tabs;
    QPushButton*    btn_close;
    QVBoxLayout*    lay_mainlayout;

    QAction*        a_graphics_manager;
    QAction*        a_entities_collection;
    QAction*        a_groups;
    QAction*        a_sounds_manager;
};

#endif // W_RESSOURCES_H
