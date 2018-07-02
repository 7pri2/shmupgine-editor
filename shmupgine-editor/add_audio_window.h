#ifndef ADD_AUDIO_WINDOW_H
#define ADD_AUDIO_WINDOW_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <p_config_panel.h>

enum {
    SOUND = 0,
    MUSIC = 1
};

class add_audio_window : public QDialog {
    Q_OBJECT
public:
    explicit add_audio_window(int type);
    QStandardItem*  get_sound();
    static QStandardItem* get_sound(QString title, QString path);

signals:

public slots:
    void fields_filled();
    void load_sound();

private:
    QLineEdit*      le_title;
    QLabel*         lbl_title;
    QHBoxLayout*    lay_title;

    QLineEdit*      le_path;
    QLabel*         lbl_path;
    QHBoxLayout*    lay_path;
    QPushButton*    btn_load;

    QCheckBox*      chkbx_copy_it;

    QPushButton*    btn_ok;
    QPushButton*    btn_cancel;
    QHBoxLayout*    lay_btn;
    QLabel*         lbl_error;

    QVBoxLayout*    lay_mainlayout;

    int type;
};

#endif // ADD_AUDIO_WINDOW_H
