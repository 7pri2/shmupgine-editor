#include "p_sounds.h"

p_sounds::p_sounds(QWidget *parent) : QWidget(parent) {
    /* * * * * * * *
     * ALLOCATION  *
     * * * * * * * */

    lv_sounds = new QListView(this);
    lv_musics = new QListView(this);

    btn_open =  new QPushButton(tr("Open"), this);
    btn_delete =new QPushButton(tr("Delete"), this);
    btn_play =  new QPushButton(tr("Play"), this);
    btn_stop =  new QPushButton(tr("Stop"), this);

    tw_categories = new QTabWidget(this);

    sounds_model =  new QStandardItemModel(this);
    musics_model =  new QStandardItemModel(this);

    lay_main =  new QHBoxLayout(this);
    lay_btn  =  new QVBoxLayout(this);

    mediaplayer = new QMediaPlayer(this);

    /* * * * * * * * * * * * * *
     * CONSTRAINTS AND MODELS  *
     * * * * * * * * * * * * * */

    lv_sounds->setModel(sounds_model);
    lv_musics->setModel(musics_model);
    tw_categories->addTab(lv_sounds, tr("&Sounds"));
    tw_categories->addTab(lv_musics, tr("&Musics"));
    lay_btn->setAlignment(Qt::AlignTop);

    /* * * * * * * *
     *   LAYOUTS   *
     * * * * * * * */

    lay_btn->addWidget(btn_open);
    lay_btn->addWidget(btn_delete);
    lay_btn->addWidget(btn_play);
    lay_btn->addWidget(btn_stop);

    lay_main->addWidget(tw_categories);
    lay_main->addLayout(lay_btn);

    /* * * * * * * *
     * CONNECTIONS *
     * * * * * * * */

    connect(btn_open, SIGNAL(clicked(bool)), this, SLOT(load_sound()));
    connect(btn_play, SIGNAL(clicked(bool)), this, SLOT(play_sound()));
    connect(btn_stop, SIGNAL(clicked(bool)), this, SLOT(stop_sound()));
}

p_sounds::~p_sounds() {

}

void p_sounds::load_sound() {
     QString filename = QFileDialog::getOpenFileName(this, tr("Open sound file"), "", tr("Sounds (*.mp3 *.ogg *.wav)"));
     if(!filename.isEmpty())
         append_sound(filename);
}

void p_sounds::append_sound(QString filename) {
    QStandardItem* new_sound = new QStandardItem(filename);
    new_sound->appendRow(new QStandardItem(filename));
    if(tw_categories->currentIndex() == 0) {
        sounds_model->appendRow(new_sound);
    } else {
        musics_model->appendRow(new_sound);
    }
}

#include <iostream>
void p_sounds::play_sound() {
    if(tw_categories->currentIndex() == 0) {
        mediaplayer->setMedia(QUrl::fromLocalFile(sounds_model->index(lv_sounds->currentIndex().row(), 0).child(0, 0).data().toString()));
    } else {
        mediaplayer->setMedia(QUrl::fromLocalFile(musics_model->index(lv_musics->currentIndex().row(), 0).child(0, 0).data().toString()));
    }
    mediaplayer->setVolume(100);
    mediaplayer->play();
}

void p_sounds::stop_sound() {
    mediaplayer->stop();
}
