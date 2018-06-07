#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QIntValidator>

#define CROSS_1 "\u2A09"
#define CROSS_2 "\u2717"

#define MAXHEIGHT  125

class entities_attributes_panel;

class attribute : public QWidget {
    Q_OBJECT
public:
    explicit attribute(entities_attributes_panel* parent);
    ~attribute();

    void    setId_parent(int id);
    int     getId_parent();

    // Code generation
    virtual QString getCode();
    QString allocation(QString allocate_attr);
    QString get(QString get_attr);

    virtual bool verify_validity();

public slots:
    void delete_attribute();

protected:
    QCheckBox*      cb_enabled;
    QGroupBox*      gb_box;
    QVBoxLayout*    lay_groupbox;
    QPushButton*    btn_delete;

    int id_parent;
    entities_attributes_panel*  container;

private:
    QVBoxLayout*    lay_mainlayout;
};

#endif // ATTRIBUTE_H
