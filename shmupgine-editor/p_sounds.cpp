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

    /* * * * * * * * * * * * * *
     * CONSTRAINTS AND MODELS  *
     * * * * * * * * * * * * * */

    lv_sounds->setModel(sounds_model);
    lv_musics->setModel(musics_model);
    tw_categories->addTab(lv_sounds, tr("&Sounds"));
    tw_categories->addTab(lv_musics, tr("&Musics"));

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
}

p_sounds::~p_sounds() {

}
