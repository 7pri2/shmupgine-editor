#include "attr_physics.h"
#include "entities_attributes_panel.h"

attr_physics::attr_physics(entities_attributes_panel* container) : attribute(container) {
    /* * * * * * * * * * *
     * MEMORY ALLOCATION *
     * * * * * * * * * * */

    /* Allocation des QSpinBox */
    dial_angle  = new QDial(this);
    sb_velocity = new QSpinBox(this);
    sb_angle    = new QSpinBox(this);

    /* Allocation des QLabel */
    lbl_angle       = new QLabel(tr("Angle"), this);
    lbl_velocity    = new QLabel(tr("Velocity"), this);

    /* Allocation des layouts */
    lay_angle 		= new QHBoxLayout(this);
    lay_velocity 	= new QHBoxLayout(this);
    lay_sb_angle    = new QVBoxLayout(this);

    /* * * * * * * * * * * * * *
     * CONSTRAINTS AND MODELS  *
     * * * * * * * * * * * * * */

    /* Application des validateurs */
    /*s_angle->setValidator(new QIntValidator(0, 359, this));
    sb_velocity->setValidator(new QDoubleValidator(-99999, 99999, 2, this));*/
    sb_angle->setRange(0,359);
    dial_angle->setRange(0, 359);
    sb_velocity->setMinimum(0);

    /* * * * * * * *
     *   LAYOUTS   *
     * * * * * * * */

    /* Mise en place du layout d'angle */
    lay_sb_angle->addWidget(dial_angle);
    lay_sb_angle->addWidget(sb_angle);
    lay_angle->addWidget(lbl_angle);
    lay_angle->addLayout(lay_sb_angle);

    /* Mise en place du layout de velocite */
    lay_velocity->addWidget(lbl_velocity);
    lay_velocity->addWidget(sb_velocity);

    gb_box->setTitle(tr("Physics"));

    /* Mise en palce de tous les layouts */
    lay_groupbox->addLayout(lay_angle);
    lay_groupbox->addLayout(lay_velocity);

    setFixedHeight(sizeHint().height());

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(dial_angle, SIGNAL(valueChanged(int)), sb_angle, SLOT(setValue(int)));
    connect(sb_angle, SIGNAL(valueChanged(int)), dial_angle, SLOT(setValue(int)));
}

attr_physics::~attr_physics() {}

QString attr_physics::getCode() {
    QString code = attribute::allocation("physics");
    if(sb_angle->value() != 0)
        code += attribute::get("physics") + QString("->set_force_angle(") + QString::number(sb_angle->value()) + QString(");\n");
    if(sb_velocity->value() != 0)
        code += attribute::get("physics") + QString("->set_velocity(") + QString::number(sb_velocity->value()) + QString(");\n");
    return code;
}

bool attr_physics::verify_validity() {
    return !sb_velocity->text().isEmpty() && sb_velocity->value() >= 0 ;
}

bool attr_physics::load(const QJsonObject &json) {
    attribute::load(json);
    if(json.contains("fields")) {
        QJsonObject fields = json.value("fields").toObject();
        if(fields.contains("angle") && fields.contains("velocity")) {
            sb_angle->setValue(fields.value("angle").toInt());
            sb_velocity->setValue(fields.value("velocity").toInt());
        } else
            return false;
    } else
        return false;
    return true;
}

QJsonObject attr_physics::save() {
    QJsonObject o, fields;
    o["type"] = "physics";
    fields["angle"] = sb_angle->value();
    fields["velocity"] = sb_velocity->value();
    o["fields"] = fields;
    return o;
}
