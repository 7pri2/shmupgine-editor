#include "p_graphics_manager.h"

p_graphics_manager::p_graphics_manager(QWidget *parent) : QWidget(parent) {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */


    lv_pictures_view    = new QListView(this);

    gs_scene    = new QGraphicsScene(this);
    gv_view     = new QGraphicsView(gs_scene, this);

    lbl_name    = new QLabel(tr("Name"), this);
    lbl_path    = new QLabel(tr("Path"), this);
    lbl_width   = new QLabel(tr("Width"), this);
    lbl_height  = new QLabel(tr("Height"), this);

    le_name     = new QLineEdit(this);
    le_path     = new QLineEdit(this);
    le_width    = new QLineEdit(this);
    le_height   = new QLineEdit(this);

    lay_mainlayout      = new QHBoxLayout(this);
    lay_details         = new QVBoxLayout(this);
    lay_pictures_list   = new QVBoxLayout(this);
    lay_buttons         = new QHBoxLayout(this);
    lay_width           = new QHBoxLayout(this);
    lay_height          = new QHBoxLayout(this);
    lay_path            = new QHBoxLayout(this);
    lay_name            = new QHBoxLayout(this);

    pictures_model      = new QStandardItemModel(this);

    btn_open    = new QPushButton(tr("Open"), this);
    btn_remove  = new QPushButton(tr("Remove"), this);

    /* * * * * * * * * * * * * *
     * CONSTRAINTS AND MODELS  *
     * * * * * * * * * * * * * */

    le_width->setValidator(new QIntValidator(0, 0xFFFFFFFF, this));
    le_height->setValidator(new QIntValidator(0, 0xFFFFFFFF, this));

    lv_pictures_view->setModel(pictures_model);

    /* * * * * * * * * * *
     * WINDOW MANAGEMENT *
     * * * * * * * * * * */

    lay_name->addWidget(lbl_name);
    lay_name->addWidget(le_name);
    lay_path->addWidget(lbl_path);
    lay_path->addWidget(le_path);
    lay_width->addWidget(lbl_width);
    lay_width->addWidget(le_width);
    lay_height->addWidget(lbl_height);
    lay_height->addWidget(le_height);
    lay_details->addWidget(gv_view);
    lay_details->addLayout(lay_name);
    lay_details->addLayout(lay_path);
    lay_details->addLayout(lay_width);
    lay_details->addLayout(lay_height);
    lay_pictures_list->addWidget(lv_pictures_view);
    lay_buttons->addWidget(btn_open);
    lay_buttons->addWidget(btn_remove);
    lay_pictures_list->addLayout(lay_buttons);
    lay_mainlayout->addLayout(lay_pictures_list);
    lay_mainlayout->addLayout(lay_details);

    dis_or_enable_details();

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(btn_open, SIGNAL(clicked()), this, SLOT(add_picture()));
    connect(lv_pictures_view, SIGNAL(clicked(QModelIndex)), this, SLOT(fill_infos(QModelIndex)));
    connect(lv_pictures_view, SIGNAL(clicked(QModelIndex)), this, SLOT(dis_or_enable_details()));
    connect(pictures_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(update_infos(QStandardItem*)));
    connect(le_name, SIGNAL(textEdited(QString)), this, SLOT(update_model()));
    connect(le_path, SIGNAL(textEdited(QString)), this, SLOT(update_model()));
    connect(le_width, SIGNAL(textEdited(QString)), this, SLOT(update_model()));
    connect(le_height, SIGNAL(textEdited(QString)), this, SLOT(update_model()));
    connect(btn_remove, SIGNAL(clicked()), this, SLOT(delete_picture()));
}

p_graphics_manager::~p_graphics_manager() {
}

void p_graphics_manager::add_picture() {
    add_image_window* aiw = new add_image_window();
    if(aiw->exec()) {
        pictures_model->appendRow(aiw->get_image());
    }
    delete aiw;
}

void p_graphics_manager::fill_infos(QModelIndex index) {
    current_selection = index;
    QPixmap file = QPixmap(index.child(PIC_PATH, 0).data().toString());
    gs_scene->clear();
    gs_scene->setSceneRect(0, 0, index.child(PIC_WIDTH,0).data().toInt(), index.child(PIC_HEIGHT,0).data().toInt());
    gs_scene->addItem(new QGraphicsPixmapItem(file));
    le_name->setText(index.data().toString());
    le_path->setText(index.child(PIC_PATH, 0).data().toString());
    le_height->setText(index.child(PIC_HEIGHT, 0).data().toString());
    le_width->setText(index.child(PIC_WIDTH, 0).data().toString());
}

void p_graphics_manager::update_infos(QStandardItem *item) {
    le_name->setText(item->index().data().toString());
}

void p_graphics_manager::update_model() {
    for(int i = 0; i < pictures_model->rowCount(); ++i)
        if(pictures_model->index(i,0) == current_selection) {
            pictures_model->item(i)->child(PIC_PATH)->setText(le_path->text());
            pictures_model->item(i)->child(PIC_HEIGHT)->setText(le_height->text());
            pictures_model->item(i)->child(PIC_WIDTH)->setText(le_width->text());
            pictures_model->item(i)->setText(le_name->text());
            return;
        }
}

void p_graphics_manager::delete_picture() {
    QMessageBox confirm;
    QCheckBox remove_from_disk(tr("Remove from disk"), this);
    confirm.setIcon(QMessageBox::Icon::Critical);
    confirm.addButton(QMessageBox::Yes);
    confirm.addButton(QMessageBox::No);
    confirm.setDefaultButton(QMessageBox::No);
    confirm.setText(tr("Are you sure you want to delete the selected picture ?"));
    confirm.setCheckBox(&remove_from_disk);
    if(confirm.exec() == QMessageBox::Yes) {
        if(remove_from_disk.isChecked()) {
            QFile f(lv_pictures_view->currentIndex().child(0, 0).data().toString());
            f.remove();
        }
        pictures_model->removeRow(lv_pictures_view->currentIndex().row());
    }
    fill_infos(lv_pictures_view->currentIndex());
    dis_or_enable_details();
}

void p_graphics_manager::dis_or_enable_details() {
    bool id_state = current_selection.row() != -1;
    gv_view->setEnabled(id_state);
    lbl_height->setEnabled(id_state);
    lbl_name->setEnabled(id_state);
    lbl_path->setEnabled(id_state);
    lbl_width->setEnabled(id_state);
    le_height->setEnabled(id_state);
    le_name->setEnabled(id_state);
    le_path->setEnabled(id_state);
    le_width->setEnabled(id_state);
    btn_remove->setEnabled(id_state);
}

QString p_graphics_manager::select_picture() {
    select_window *select  = new select_window(tr("Select a picture"), pictures_model);
    if(select->exec()) {
        return select->get_selected_item(-1);
    } else {
        return "";
    }
    delete select;
}

QString p_graphics_manager::getCode() {
    QString code;
    for(int i = 0; i < pictures_model->rowCount(); ++i)
        code += QString("\tgmanager::instance().new_texture(\"")
                + pictures_model->index(i, 0).data().toString() + QString("\", \"")
                + pictures_model->index(i, 0).child(PIC_PATH, 0).data().toString() + QString("\", ")
                + pictures_model->index(i, 0).child(PIC_WIDTH, 0).data().toString() + QString(", ")
                + pictures_model->index(i, 0).child(PIC_HEIGHT, 0).data().toString() + QString(");\n");
    return code;
}

QString p_graphics_manager::get_picture_path(QString pic_name) {
    for(int i = 0; i < pictures_model->rowCount(); ++i)
        if(pictures_model->index(i, 0).data().toString() == pic_name)
            return pictures_model->index(i,0).child(PIC_PATH,0).data().toString();
    return "";
}

bool p_graphics_manager::load(const QJsonArray &json) {
    for(int i = 0; i < json.size(); ++i) {
        if(json[i].isObject()) {
            QJsonObject picture = json[i].toObject();
            if(picture.contains("name") && picture["title"].isString()
                && picture.contains("path") && picture["path"].isString()) {
                pictures_model->appendRow(add_image_window::get_image(picture["name"].toString(), picture["path"].toString()));
            }
        }
    }
    return true;
}

void p_graphics_manager::save() {
    QFile out_pictures(QDir(project_data::Instance()->prj_config[WORKING_DIR]).filePath(project_data::Instance()->graphics_config_file));
    if(out_pictures.open(QIODevice::WriteOnly)) {
        QJsonArray json_pictures;
        for(int i = 0; i < pictures_model->rowCount(); ++i) {
            QJsonObject picture;
            picture["name"] = pictures_model->index(i, 0).data().toString();
            picture["path"] = pictures_model->index(i, 0).child(0, 0).data().toString();
            json_pictures.append(picture);
        }
        out_pictures.write(QJsonDocument(json_pictures).toJson());
        out_pictures.close();
    }
}
