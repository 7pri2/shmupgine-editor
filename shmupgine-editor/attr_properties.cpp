#include "attr_properties.h"
#include "entities_attributes_panel.h"

attr_properties::attr_properties(entities_attributes_panel* container) : attribute(container) {
    /* * * * * * * *
     * ALLOCATION  *
     * * * * * * * */

    lay_coord       = new QHBoxLayout(this);
    lbl_position    = new QLabel(tr("Position"), this);
    lbl_x           = new QLabel(tr("x"), this);
    lbl_y           = new QLabel(tr("y"), this);
    le_x            = new QLineEdit("0", this);
    le_y            = new QLineEdit("0", this);

    /* * * * * * * * * * * * * *
     * CONSTRAINTS AND MODELS  *
     * * * * * * * * * * * * * */

    le_x->setValidator(new QIntValidator(-99999, 99999, this));
    le_y->setValidator(new QIntValidator(-99999, 99999, this));

    /* * * * * * * * * * *
     * WINDOW MANAGEMENT *
     * * * * * * * * * * */

    gb_box->setTitle(tr("Properties"));

    btn_delete->hide();
    cb_enabled->hide();

    /* * * * * * * *
     *   LAYOUTS   *
     * * * * * * * */

    lay_groupbox->addWidget(lbl_position);
    lay_coord->addWidget(lbl_x);
    lay_coord->addWidget(le_x);
    lay_coord->addWidget(lbl_y);
    lay_coord->addWidget(le_y);
    lay_groupbox->addLayout(lay_coord);

    setFixedHeight(sizeHint().height());

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */
}

attr_properties::~attr_properties() {

}

QString attr_properties::getCode() {
    QString code;
    code += QString("\tentity* ") + container->get_entity_name(id_parent) + QString(" = new entity");
    if(le_x->text().toInt() != 0 || le_y->text().toInt() != 0)
        code += QString("(sf::Vector2f(") + le_x->text() + QString(", ") + le_y->text() + QString("))");
    code += QString(";\n");
    return code;
}

int attr_properties::getPosX() {
    return le_x->text().toInt();
}

int attr_properties::getPosY() {
    return le_y->text().toInt();
}

bool attr_properties::verify_validity() {
    return !le_x->text().isEmpty() && !le_y->text().isEmpty();
}

bool attr_properties::load(const QJsonObject &json) {
    if(json.contains("x"))
        le_x->setText(QString::number(json.value("x").toInt()));
    else
        return false;
    if(json.contains("y"))
        le_y->setText(QString::number(json.value("y").toInt()));
    else
        return false;
    return true;
}

QJsonObject attr_properties::save() {
    QJsonObject o;
    o["x"] = le_x->text().toInt();
    o["y"] = le_y->text().toInt();
    return o;
}
