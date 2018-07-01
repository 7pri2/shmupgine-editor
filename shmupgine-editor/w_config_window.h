#ifndef W_CONFIG_WINDOW_H
#define W_CONFIG_WINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <map>
#include "p_config_panel.h"
#include "p_makefile.h"
#include "singleton.h"

enum {
    project     = 0,
    makefile    = 1
};

class w_config_window : public QDialog, public Singleton<w_config_window> {
    friend class Singleton<w_config_window>;
    Q_OBJECT

public slots:
    void show_tab(int tab);

private slots:
    void revert_changes();
    void save_changes();
    void update_buttons(QWidget* sender, bool state);

private:
    w_config_window(QWidget* parent = 0);
    w_config_window(const w_config_window&);
    virtual ~w_config_window();

    QTabWidget*     tab_widget;

    QHBoxLayout*    btn_layout;
    QVBoxLayout*    mainlayout;

    QPushButton*    btn_save;
    QPushButton*    btn_close;

    std::map<QWidget*, bool> modifs;
};

#endif // W_CONFIG_WINDOW_H
