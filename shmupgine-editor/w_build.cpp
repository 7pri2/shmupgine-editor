#include "w_build.h"

w_build::w_build(QWidget *parent) : QWidget(parent) {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    lay_main = new QVBoxLayout(this);
    btn_close = new QPushButton(tr("Close"), this);
    pb_compilation_progress = new QProgressBar(this);

    /* * * * * *
     * LAYOUTS *
     * * * * * */

    lay_main->addWidget(pb_compilation_progress);
    lay_main->addWidget(btn_close);

    /* * * * * * * * * * *
     * WINDOW MANAGEMENT *
     * * * * * * * * * * */

    pb_compilation_progress->setMaximum(10);
    pb_compilation_progress->setValue(4);
    this->setProperty("class", "background");

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(btn_close, SIGNAL(clicked(bool)), this, SLOT(close()));
}

w_build::~w_build() {

}

void w_build::build() {
}
