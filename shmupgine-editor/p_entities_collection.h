#ifndef P_ENTITIES_COLLECTION_H
#define P_ENTITIES_COLLECTION_H

#include <QSplitter>
#include <QWidget>
#include "singleton.h"
#include "entities_attributes_panel.h"
#include "select_window.h"

class p_entities_collection : public entities_attributes_panel, public Singleton<p_entities_collection> {
    Q_OBJECT

    friend class Singleton<p_entities_collection>;

private:
    p_entities_collection(QWidget* parent = 0);
    p_entities_collection(const p_entities_collection&);
    virtual ~p_entities_collection();

    QSplitter*      splitter;
    QHBoxLayout*    mainlayout;
};

#endif // P_ENTITIES_COLLECTION_H
