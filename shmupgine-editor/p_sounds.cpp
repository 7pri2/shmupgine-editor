#include "p_sounds.h"

p_sounds::p_sounds(QWidget *parent) : QWidget(parent) {
    /* * * * * * * *
     * ALLOCATION  *
     * * * * * * * */

    lv_sounds = new QListView(this);
    lv_musics = new QListView(this);

    btn_open =  new QPushButton(tr("Add"), this);
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

    connect(btn_open, SIGNAL(clicked(bool)), this, SLOT(add_sound()));
    connect(btn_play, SIGNAL(clicked(bool)), this, SLOT(play_sound()));
    connect(btn_stop, SIGNAL(clicked(bool)), this, SLOT(stop_sound()));
    connect(btn_delete, SIGNAL(clicked(bool)), this, SLOT(delete_sound()));
}

p_sounds::~p_sounds() {

}

void p_sounds::add_sound() {
    add_audio_window* adw;
    if(tw_categories->currentIndex() == SOUND) {
        adw = new add_audio_window(SOUND);
    } else {
        adw = new add_audio_window(MUSIC);
    }
    if(adw->exec()) {
        if(tw_categories->currentIndex() == SOUND) {
            sounds_model->appendRow(adw->get_sound());
        } else {
            musics_model->appendRow(adw->get_sound());
        }
    }
    delete adw;
}

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

QString p_sounds::select_sound_effect() {
    select_window *select  = new select_window(tr("Select a sound effect"), sounds_model);
    if(select->exec()) {
        return select->get_selected_item(-1);
    } else {
        return "";
    }
    delete select;
}

QString p_sounds::select_music() {
    select_window *select  = new select_window(tr("Select a music"), musics_model);
    if(select->exec()) {
        return select->get_selected_item(-1);
    } else {
        return "";
    }
    delete select;
}

bool p_sounds::load(const QJsonObject &config) {
    if(config.contains("sounds") && config["sounds"].isArray()) {
        QJsonArray sounds = config["sounds"].toArray();
        for(int i = 0; i < sounds.size(); ++i) {
            if(sounds[i].isObject()) {
                QJsonObject sound = sounds[i].toObject();
                if(sound.contains("title") && sound["title"].isString()
                    && sound.contains("path") && sound["path"].isString()) {
                    sounds_model->appendRow(add_audio_window::get_sound(sound["title"].toString(), sound["path"].toString()));
                }
            }
        }
    }
    if(config.contains("musics") && config["musics"].isArray()){
        QJsonArray musics = config["musics"].toArray();
        for(int i = 0; i < musics.size(); ++i) {
            if(musics[i].isObject()) {
                QJsonObject music = musics[i].toObject();
                if(music.contains("title") && music["title"].isString()
                    && music.contains("path") && music["path"].isString()) {
                    musics_model->appendRow(add_audio_window::get_sound(music["title"].toString(), music["path"].toString()));
                }
            }
        }
    }
    return true;
}

void p_sounds::delete_sound() {
    // We check if a song is selected
    QListView* view = tw_categories->currentIndex() == SOUND ? lv_sounds : lv_musics;
    QStandardItemModel* model = tw_categories->currentIndex() == SOUND ? sounds_model : musics_model;
    if(view->currentIndex().row() >= 0) {
        QMessageBox confirm;
        QCheckBox remove_from_disk(tr("Remove from disk"), this);
        confirm.setIcon(QMessageBox::Icon::Critical);
        confirm.addButton(QMessageBox::Yes);
        confirm.addButton(QMessageBox::No);
        confirm.setDefaultButton(QMessageBox::No);
        confirm.setText(tr("Are you sure you want to delete the selected audio file ?"));
        confirm.setCheckBox(&remove_from_disk);
        if(confirm.exec() == QMessageBox::Yes) {
            if(remove_from_disk.isChecked()) {
                QFile f(view->currentIndex().child(0, 0).data().toString());
                f.remove();
            }
            model->removeRow(view->currentIndex().row());
        }
    }
}

void p_sounds::save() {
    QFile out_audio(QDir(project_data::Instance()->prj_config[WORKING_DIR]).filePath(project_data::Instance()->audio_config_file));
    if(out_audio.open(QIODevice::WriteOnly)) {
        QJsonArray json_sounds;
        for(int i = 0; i < sounds_model->rowCount(); ++i) {
            qDebug() << i << "/" << sounds_model->rowCount();
            QJsonObject sound;
            sound["title"] = sounds_model->index(i, 0).data().toString();
            sound["path"] = sounds_model->index(i, 0).child(0, 0).data().toString();
            qDebug() << sound["title"] << sound["path"];
            json_sounds.append(sound);
        }
        QJsonArray json_musics;
        for(int i = 0; i < musics_model->rowCount(); ++i) {
            QJsonObject music;
            music["title"] = musics_model->index(i, 0).data().toString();
            music["path"] = musics_model->index(i, 0).child(0, 0).data().toString();
            qDebug() << musics_model->index(i, 0).data().toString() << musics_model->index(i, 0).child(0, 0).data().toString();
            json_musics.append(music);
        }
        QJsonObject json_audio;
        json_audio["sounds"] = json_sounds;
        json_audio["musics"] = json_musics;
        out_audio.write(QJsonDocument(json_audio).toJson());
        out_audio.close();
    }
}
