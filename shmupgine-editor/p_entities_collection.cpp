#include "p_entities_collection.h"

p_entities_collection::p_entities_collection(QWidget* parent) : entities_attributes_panel(parent) {
    splitter    = new QSplitter(this);
    mainlayout  = new QHBoxLayout(this);

    splitter->addWidget(entities_widget);
    splitter->addWidget(scroll_area);

    mainlayout->addWidget(splitter);
}

p_entities_collection::~p_entities_collection() {

}
