#ifndef ATTR_SPAWNER_H
#define ATTR_SPAWNER_H

#include "spawnslot.h"
#include "attribute.h"
#include "windows_panels.h"

class attr_spawner : public attribute {
    Q_OBJECT
public:
    attr_spawner(entities_attributes_panel* container);
    virtual ~attr_spawner();

    virtual QString getCode();

private slots:
    void new_tab(int tab);

private:
    QTabWidget* tw_spawnslots;
    QWidget*    newtab;
};

#endif // ATTR_SPAWNER_H
