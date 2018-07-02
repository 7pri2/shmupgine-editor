#ifndef P_SOUNDS_H
#define P_SOUNDS_H

#include <QWidget>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTabWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMediaPlayer>
#include <QMessageBox>
#include "singleton.h"
#include "add_audio_window.h"
#include "select_window.h"

class p_sounds : public QWidget, public Singleton<p_sounds> {
    Q_OBJECT

    friend class Singleton<p_sounds>;

public:
    QString select_sound_effect();
    QString select_music();
    bool    load(const QJsonObject& json);

signals:

public slots:
    void add_sound();
    void play_sound();
    void stop_sound();
    void delete_sound();

private:
    p_sounds(QWidget *parent = 0);
    p_sounds(const p_sounds&);
    virtual ~p_sounds();

    QListView*      lv_sounds;
    QListView*      lv_musics;

    QPushButton*    btn_open;
    QPushButton*    btn_delete;
    QPushButton*    btn_play;
    QPushButton*    btn_stop;

    QTabWidget*     tw_categories;

    QStandardItemModel* sounds_model;
    QStandardItemModel* musics_model;

    QVBoxLayout*    lay_btn;
    QHBoxLayout*    lay_main;

    QMediaPlayer*   mediaplayer;
};

#endif // P_SOUNDS_H
