#ifndef W_BUILD_H
#define W_BUILD_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVariant>
#include "singleton.h"

class w_build : public QWidget, public Singleton<w_build> {
    Q_OBJECT

    friend class Singleton<w_build>;

public slots:
    void build();

private:
    w_build(const w_build&);
    w_build(QWidget *parent = 0);
    ~w_build();

    QProgressBar*   pb_compilation_progress;
    QPushButton*    btn_close;
    QVBoxLayout*    lay_main;
};

#endif // W_BUILD_H
