#include "entities_attributes_panel.h"
#include "attributes.h"

entities_attributes_panel::entities_attributes_panel(QWidget *parent) : QWidget(parent) {
    /* * * * * * * *
     * ALLOCATION  *
     * * * * * * * */

    // Entities
    entities_widget     = new QWidget(this);
    btn_new_entity      = new QPushButton(tr("New entity"), entities_widget);
    btn_delete_entity   = new QPushButton(tr("Delete entity"), entities_widget);

    lay_entities_layout = new QVBoxLayout(entities_widget);
    lay_btn             = new QVBoxLayout(entities_widget);

    lv_list             = new QListView(entities_widget);
    entities_model      = new QStandardItemModel(entities_widget);

    // Attributes
    scroll_area         = new QScrollArea(this);
    attributes_widget   = new QWidget(this);
    btn_new_attribute   = new QPushButton(tr("+"), attributes_widget);
    lay_attr_layout    = new QGridLayout(attributes_widget);

    // Attr Menu
    m_choose_attribute  = new QMenu(attributes_widget);
    a_physics           = new QAction(tr("&physics"), attributes_widget);
    a_graphic_renderer  = new QAction(tr("&graphic renderer"), attributes_widget);
    a_destructor        = new QAction(tr("&destructor"), attributes_widget);
    a_controls          = new QAction(tr("&controls"), attributes_widget);
    a_spawner           = new QAction(tr("&Spawner"), attributes_widget);

    /* * * * * * * * * * *
     *  MENU MANAGEMENT  *
     * * * * * * * * * * */

    m_choose_attribute->addAction(a_physics);
    m_choose_attribute->addAction(a_graphic_renderer);
    m_choose_attribute->addAction(a_destructor);
    m_choose_attribute->addAction(a_controls);
    m_choose_attribute->addAction(a_spawner);

    // Entities
    lay_btn->addWidget(btn_new_entity);
    lay_btn->addWidget(btn_delete_entity);
    lay_entities_layout->addWidget(lv_list);
    lay_entities_layout->addLayout(lay_btn);
    entities_widget->setLayout(lay_entities_layout);
    lv_list->setModel(entities_model);

    // Attributes
    lay_attr_layout->addWidget(btn_new_attribute);
    lay_attr_layout->setAlignment(Qt::AlignTop);
    attributes_widget->setLayout(lay_attr_layout);

    scroll_area->setWidget(attributes_widget);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setWidgetResizable(true);
    scroll_area->setMinimumWidth(300);
    scroll_area->setMinimumHeight(300);

    attributes_widget->setProperty("class", "background");

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(btn_new_attribute, SIGNAL(clicked()), this, SLOT(showMenu()));
    connect(lv_list, SIGNAL(clicked(QModelIndex)), this, SLOT(update_current_index(QModelIndex)));
    connect(btn_delete_entity, SIGNAL(clicked()), this, SLOT(remove_entity()));
    connect(btn_new_entity, SIGNAL(clicked()), this, SLOT(new_entity()));
    connect(m_choose_attribute, SIGNAL(triggered(QAction*)), this, SLOT(handle_actions(QAction*)));

    update_what_is_visible();
}

entities_attributes_panel::~entities_attributes_panel() {

}

void entities_attributes_panel::update_current_index(QModelIndex index) {
    current_entity = index;
    update_what_is_visible();
}

void entities_attributes_panel::remove_entity() {
    remove_all_attributes(entities_model->index(lv_list->currentIndex().row(), 0).child(0,0).data().toInt());
    entities_model->removeRow(lv_list->currentIndex().row());
    update_current_index(lv_list->currentIndex());
    update_what_is_visible();
}

void entities_attributes_panel::remove_all_attributes(int entity_id) {
    for(std::list<attribute*>::iterator it = attr_list.begin(); it != attr_list.end();)
        if((*it)->getId_parent() == entity_id) {
            (*it)->delete_attribute();
            it = attr_list.erase(it);
        } else
            ++it;
}

void entities_attributes_panel::new_entity() {
    project_data::Instance()->entity_max_id += 1;
    QStandardItem* item = new QStandardItem(QString(tr("entity"))+QString::number(project_data::Instance()->entity_max_id));
    item->appendRow(new QStandardItem(QString::number(project_data::Instance()->entity_max_id)));
    entities_model->appendRow(item);
    add_attribute(project_data::Instance()->entity_max_id, new attr_properties(this));
}

int entities_attributes_panel::new_clear_entity(QString name) {
    project_data::Instance()->entity_max_id += 1;
    QStandardItem* item = new QStandardItem(name);
    item->appendRow(new QStandardItem(QString::number(project_data::Instance()->entity_max_id)));
    entities_model->appendRow(item);
    return project_data::Instance()->entity_max_id;
}

void entities_attributes_panel::update_what_is_visible() {
    int id = current_entity.child(0,0).data().toInt();
    for(std::list<attribute*>::iterator it = attr_list.begin(); it != attr_list.end(); ++it) {
        (*it)->setVisible((*it)->getId_parent() == id);
    }
    btn_new_attribute->setEnabled(lv_list->currentIndex().row() != -1);
}

void entities_attributes_panel::add_attribute(attribute *attr) {
    attr->setId_parent(current_entity.child(0,0).data().toInt());
    attr->setParent(attributes_widget);
    attributes_widget->layout()->addWidget(attr);
    attr_list.push_back(attr);
    update_what_is_visible();
}

void entities_attributes_panel::add_attribute(int id, attribute *attr) {
    attr->setId_parent(id);
    attr->setParent(attributes_widget);
    attributes_widget->layout()->addWidget(attr);
    attr_list.push_back(attr);
    update_what_is_visible();
}

void entities_attributes_panel::handle_actions(QAction *a) {
    if(a == a_destructor)
        add_attribute(new attr_destructor(this));
    else if(a == a_controls)
        add_attribute(new attr_controls(this));
    else if(a == a_graphic_renderer)
        add_attribute(new attr_graphic_renderer(this));
    else if(a == a_physics)
        add_attribute(new attr_physics(this));
    else if(a == a_spawner)
        add_attribute(new attr_spawner(this));
}

void entities_attributes_panel::showMenu() {
    if(current_entity.child(0,0).data().toInt()) // id
        m_choose_attribute->popup(QCursor::pos());
}

void entities_attributes_panel::remove_attribute(attribute *attr) {
    attr_list.remove(attr);
}

QString entities_attributes_panel::select_entity() {
    select_window *select  = new select_window(tr("Select an entity"), entities_model);
    if(select->exec()) {
        return select->get_selected_item(-1); // We want the name
    } else {
        return "";
    }
}

QWidget* entities_attributes_panel::get_entities_panel() {
    return entities_widget;
}

QWidget* entities_attributes_panel::get_attributes_panel() {
    return scroll_area;
}

bool entities_attributes_panel::check_entity(QString entity) {
    return !entities_model->findItems(entity).isEmpty();
}

QString entities_attributes_panel::get_entity_name(int id) {
    for(int i = 0; i < entities_model->rowCount(); ++i)
        if(entities_model->item(i)->index().child(0,0).data().toInt() == id) {
            return entities_model->item(i)->index().data().toString();
        }
    return "";
}

QString entities_attributes_panel::getCode() {
    QString code;
    // First step: we only want to declare the entities to avoid bugs
    for(std::list<attribute*>::iterator it = attr_list.begin(); it != attr_list.end(); ++it)
        if(dynamic_cast<attr_properties*>(*it) != NULL)
            code += (*it)->getCode();
    // Then we can deal with the other attributes
    for(std::list<attribute*>::iterator it = attr_list.begin(); it != attr_list.end(); ++it)
        if(dynamic_cast<attr_properties*>(*it) == NULL)
            code += (*it)->getCode();
    return code;
}

QStringList entities_attributes_panel::get_entities_names() {
    QStringList sl;
    for(int i = 0; i < entities_model->rowCount(); ++i)
        sl.append(entities_model->item(i)->index().data().toString());
    return sl;
}

void entities_attributes_panel::change_scroll_perspective(Qt::DockWidgetArea np) {
    /*
    int id = current_entity.child(0,0).data().toInt();
    switch (np) {
    case Qt::DockWidgetArea::TopDockWidgetArea:
    case Qt::DockWidgetArea::BottomDockWidgetArea:
    default: {
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        // Change from vertical to horizontal layout
        QHBoxLayout* new_lyt = new QHBoxLayout(this);
        delete attributes_widget->layout();
        new_lyt->addWidget(btn_new_attribute);
        for(std::list<attribute*>::iterator it = attr_list.begin(); it != attr_list.end(); ++it) {
            new_lyt->addWidget(*it);
        }
        attributes_widget->setLayout(new_lyt);
        break;
    }
    case Qt::DockWidgetArea::LeftDockWidgetArea:
    case Qt::DockWidgetArea::RightDockWidgetArea: {
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        // Change from horizontal to vertical layout
        QVBoxLayout* new_lyt = new QVBoxLayout(this);
        delete attributes_widget->layout();
        new_lyt->addWidget(btn_new_attribute);
        for(std::list<attribute*>::iterator it = attr_list.begin(); it != attr_list.end(); ++it) {
            new_lyt->addWidget(*it);
        }
        attributes_widget->setLayout(new_lyt);
        break;
    }
    }
    */
}

bool entities_attributes_panel::load(const QJsonArray &entites) {
    for(int i = 0; i < entites.size(); ++i) {
        QJsonObject en = entites[i].toObject();
        if(en.contains("name")) {
            int id = new_clear_entity(en.value("name").toString());
            // Load its properties
            if(en.contains("position")) {
                attr_properties* p = new attr_properties(this);
                if(!p->load(en.value("position").toObject()))
                    return false;

                add_attribute(id, p);

                // Then load its attributes
                if(en.contains("attributes")) {
                    QJsonArray attrs = en.value("attributes").toArray();
                    for(int j = 0; j < attrs.size(); ++j) {
                        QJsonObject attr_current = attrs[j].toObject();
                        if(attr_current.contains("type")) {
                            attribute* a;
                            if(attr_current.value("type").toString() == "destructor") {
                                a = new attr_destructor(this);
                            } else if(attr_current.value("type").toString() == "graphicsrenderer") {
                                a = new attr_graphic_renderer(this);
                            } else if(attr_current.value("type").toString() == "controls") {
                                a = new attr_controls(this);
                            } else if(attr_current.value("type").toString() == "physics") {
                                a = new attr_physics(this);
                            } else if(attr_current.value("type").toString() == "spawner") {
                                a = new attr_spawner(this);
                            } else {
                                return false;
                            }
                            if(!a->load(attr_current))
                                return false;
                            add_attribute(id, a);
                        }
                    }
                }
            }
        }
    }
}

void entities_attributes_panel::save() {
    QFile out_entities(QDir(project_data::Instance()->prj_config[WORKING_DIR]).filePath(project_data::Instance()->entities_config_file));
    if(out_entities.open(QIODevice::WriteOnly)) {
        QJsonArray array;
        for(int i = 0; i < entities_model->rowCount(); ++i) {
            QJsonObject o;
            QJsonArray attrjson;
            o["name"] = entities_model->index(i,0).data().toString();
            int id = entities_model->index(i,0).child(0,0).data().toInt();
            std::list<attribute*> attrs = list_all_attributes(id);
            for(std::list<attribute*>::iterator it = attrs.begin(); it != attrs.end(); ++it) {
                if(dynamic_cast<attr_properties*>(*it) != NULL)
                    o["position"] = (*it)->save();
                else
                    attrjson.append((*it)->save());
            }
            o["attributes"] = attrjson;
            array.append(o);
        }
        out_entities.write(QJsonDocument(array).toJson());
        out_entities.close();
    }
}

std::list<attribute*> entities_attributes_panel::list_all_attributes(int id) {
    std::list<attribute*> attrs;
    for(std::list<attribute*>::iterator it = attr_list.begin(); it != attr_list.end(); ++it)
        if((*it)->getId_parent() == id) {
            attrs.push_back(*it);
        }
    return attrs;
}
