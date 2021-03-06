#include "select_window.h"

select_window::select_window(QString title, QStandardItemModel* model) : QDialog() {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    listview        = new QListView(this);
    btn_ok          = new QPushButton(tr("Select"), this);
    btn_cancel      = new QPushButton(tr("Cancel"), this);
    lay_mainlayout  = new QVBoxLayout(this);
    lay_btn         = new QHBoxLayout(this);

    /* * * * * * * * * * * * * *
     * CONSTRAINTS AND MODELS  *
     * * * * * * * * * * * * * */

    listview->setModel(model);
    listview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    btn_ok->setEnabled(false);

    setWindowTitle(title);

    /* * * * * * * *
     *   LAYOUTS   *
     * * * * * * * */

    lay_btn->addWidget(btn_ok);
    lay_btn->addWidget(btn_cancel);
    lay_mainlayout->addWidget(listview);
    lay_mainlayout->addLayout(lay_btn);

    this->setProperty("class", "background");

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    btn_ok->setDefault(true);

    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(listview, SIGNAL(clicked(QModelIndex)), this, SLOT(item_selected()));
    connect(btn_ok, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(listview, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accept()));
}

select_window::~select_window () {}

void select_window::item_selected() {
    btn_ok->setEnabled(true);
}

QString select_window::get_selected_item(int row) {
    if(row == -1)
        return listview->currentIndex().data().toString();
    else
        return listview->currentIndex().data().toString();
}
