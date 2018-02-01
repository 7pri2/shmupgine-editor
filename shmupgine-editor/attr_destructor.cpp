#include "attr_destructor.h"

attr_destructor::attr_destructor(entities_attributes_panel* container) : attribute(container) {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    lv_entities         = new QListView(this);
    lv_groups           = new QListView(this);

    sm_entities         = new QStandardItemModel(this);
    sm_groups           = new QStandardItemModel(this);

    btn_add_entity      = new QPushButton(tr("Add"), this);
    btn_remove_entity   = new QPushButton(tr("Remove"), this);
    btn_add_group       = new QPushButton(tr("Add"), this);
    btn_remove_group    = new QPushButton(tr("Remove"), this);

    lay_entities_btn    = new QHBoxLayout(this);
    lay_groups_btn      = new QHBoxLayout(this);

    lbl_entities        = new QLabel(tr("Entities"), this);
    lbl_groups          = new QLabel(tr("Groups"), this);

    cb_out_of_bounds    = new QCheckBox(tr("Out of bounds"), this);

    /* * * * * * * * * * * * * *
     * CONSTRAINTS AND MODELS  *
     * * * * * * * * * * * * * */

    lv_entities->setEditTriggers(QAbstractItemView::NoEditTriggers);
    lv_groups->setEditTriggers(QAbstractItemView::NoEditTriggers);

    lv_entities->setModel(sm_entities);
    lv_groups->setModel(sm_groups);

    lv_entities->setMaximumHeight(MAXHEIGHT);
    lv_groups->setMaximumHeight(MAXHEIGHT);

    gb_box->setTitle(tr("Destructor"));

    /* * * * * * * *
     *   LAYOUTS   *
     * * * * * * * */

    lay_entities_btn->addWidget(btn_add_entity);
    lay_entities_btn->addWidget(btn_remove_entity);

    lay_groups_btn->addWidget(btn_add_group);
    lay_groups_btn->addWidget(btn_remove_group);

    lay_groupbox->addWidget(lbl_entities);
    lay_groupbox->addWidget(lv_entities);
    lay_groupbox->addLayout(lay_entities_btn);
    lay_groupbox->addWidget(lbl_groups);
    lay_groupbox->addWidget(lv_groups);
    lay_groupbox->addLayout(lay_groups_btn);
    lay_groupbox->addWidget(cb_out_of_bounds);

    setFixedHeight(sizeHint().height());

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(btn_add_entity, SIGNAL(clicked()), this, SLOT(add_entities()));
    connect(btn_remove_entity, SIGNAL(clicked()), this, SLOT(removeEntity()));
    connect(btn_add_group, SIGNAL(clicked(bool)), this, SLOT(add_groups()));
    connect(btn_remove_group, SIGNAL(clicked(bool)), this, SLOT(remove_group()));
}

attr_destructor::~attr_destructor() {

}

QString attr_destructor::getCode() {

}

void attr_destructor::removeEntity() {
    sm_entities->removeRow(lv_entities->currentIndex().row());
}

void attr_destructor::add_entities() {
    QString entity = p_entities_editor::Instance()->select_entity();
    if(entity != "")
        sm_entities->appendRow(new QStandardItem(entity));
}

void attr_destructor::add_groups() {
    QString group = p_groups::Instance()->select_group();
    if(!group.isEmpty())
        sm_groups->appendRow(new QStandardItem(group));
}

void attr_destructor::remove_group() {
    sm_groups->removeRow(lv_groups->currentIndex().row());
}
