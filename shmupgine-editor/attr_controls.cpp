#include "entities_attributes_panel.h"
#include "attr_controls.h"

attr_controls::attr_controls(entities_attributes_panel* container) : attribute(container) {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    le_move_speed   = new QLineEdit("100", this);
    lbl_move_speed  = new QLabel(tr("Move speed"), this);
    lay_move_speed  = new QHBoxLayout(this);

    /* * * * * * * * * * * * * *
     * CONSTRAINTS AND MODELS  *
     * * * * * * * * * * * * * */

    le_move_speed->setValidator(new QDoubleValidator(0, 9999999, 2, this));
    gb_box->setTitle(tr("Controls"));

    /* * * * * * * *
     *   LAYOUTS   *
     * * * * * * * */

    lay_move_speed->addWidget(lbl_move_speed);
    lay_move_speed->addWidget(le_move_speed);
    lay_groupbox->addLayout(lay_move_speed);
}

attr_controls::~attr_controls() {

}

QString attr_controls::getCode() {
    QString code = attribute::allocation("controls");
    if(le_move_speed->text().toFloat() != 100)
            code += attribute::get("controls") + QString("->move_speed = ") + le_move_speed->text() + QString(";\n");
    return code;
}

bool attr_controls::verify_validity() {
    return !le_move_speed->text().isEmpty();
}

bool attr_controls::load(const QJsonObject &json) {
    attribute::load(json);
    if(json.contains("fields")) {
        QJsonObject fields = json.value("fields").toObject();
        if(fields.contains("move_speed"))
            le_move_speed->setText(QString::number(fields.value("move_speed").toInt()));
        else
            return false;
    } else
        return false;
    return true;
}

QJsonObject attr_controls::save() {
    QJsonObject object = attribute::save();
    object["type"] = "controls";
    QJsonObject fields;
    fields["move_speed"] = le_move_speed->text().toInt();
    object["fields"] = fields;
    return object;
}
