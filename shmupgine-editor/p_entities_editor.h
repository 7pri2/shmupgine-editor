#ifndef P_ENTITIES_EDITOR_H
#define P_ENTITIES_EDITOR_H

#include "singleton.h"
#include "entities_attributes_panel.h"

class p_entities_editor : public entities_attributes_panel, public Singleton<p_entities_editor> {
    Q_OBJECT

    friend class Singleton<p_entities_editor>;

private:
    p_entities_editor(QWidget* parent = 0);
    p_entities_editor(const p_entities_editor&);
    virtual ~p_entities_editor();
};
#endif // P_ENTITIES_EDITOR_H
