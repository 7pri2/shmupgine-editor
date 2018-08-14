#ifndef ATTR_SPAWNER_H
#define ATTR_SPAWNER_H

#include "attribute.h"
#include "windows_panels.h"

class attr_spawner : public attribute {
    Q_OBJECT
public:
    attr_spawner(entities_attributes_panel* container);
    virtual ~attr_spawner();

    virtual bool load(const QJsonObject& json);
    virtual QJsonObject save();

    virtual QString getCode();
    virtual bool verify_validity();

private slots:
    void new_tab(int tab);
    void update_tab_name(QString name);

private:
    QTabWidget* tw_spawnslots;
    QWidget*    newtab;
};

#endif // ATTR_SPAWNER_H
