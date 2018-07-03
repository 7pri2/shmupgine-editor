#include "add_audio_window.h"

add_audio_window::add_audio_window(int type) {
    le_title    = new QLineEdit(this);
    le_path     = new QLineEdit(this);
    lbl_title   = new QLabel(tr("Title"), this);
    lbl_path    = new QLabel(tr("Path"), this);
    btn_load    = new QPushButton("...", this);
    btn_ok      = new QPushButton("Ok", this);
    btn_cancel  = new QPushButton("Cancel", this);
    lbl_error   = new QLabel(tr(""), this);

    chkbx_copy_it   = new QCheckBox(tr("Copy to project directory"), this);

    lay_mainlayout  = new QVBoxLayout(this);
    lay_path        = new QHBoxLayout(this);
    lay_title       = new QHBoxLayout(this);
    lay_btn         = new QHBoxLayout(this);

    this->type = type;

    // Resize button
    btn_load->setMaximumWidth(BTN_WIDTH);

    lay_path->addWidget(lbl_path);
    lay_path->addWidget(le_path);
    lay_path->addWidget(btn_load);

    lay_title->addWidget(lbl_title);
    lay_title->addWidget(le_title);

    lay_btn->addWidget(btn_ok);
    lay_btn->addWidget(btn_cancel);

    lay_mainlayout->addLayout(lay_title);
    lay_mainlayout->addLayout(lay_path);
    lay_mainlayout->addWidget(chkbx_copy_it);
    lay_mainlayout->addLayout(lay_btn);
    lay_mainlayout->addWidget(lbl_error);

    btn_ok->setDefault(true);
    btn_ok->setEnabled(false);
    lbl_error->hide();
    lbl_error->setProperty("class", "error");

    this->setLayout(lay_mainlayout);
    this->setProperty("class", "background");
    chkbx_copy_it->setChecked(true);

    connect(le_path, SIGNAL(textChanged(QString)), this, SLOT(fields_filled()));
    connect(le_title, SIGNAL(textChanged(QString)), this, SLOT(fields_filled()));
    connect(btn_load, SIGNAL(clicked(bool)), this, SLOT(load_sound()));
    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btn_ok, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

QStandardItem* add_audio_window::get_sound() {
    QStandardItem* new_sound = new QStandardItem(le_title->text());
    if(chkbx_copy_it->isChecked()) {
        QDir new_file(p_config_panel::Instance()->get_project_working_dir());
        if(!new_file.cd("res")) {
            new_file.mkdir(new_file.filePath("res"));
            new_file.cd("res");
        }
        if(!new_file.cd("audio")) {
            new_file.mkdir("audio");
            new_file.cd("audio");
        }
        QString dir = type == SOUND ? "sounds" : "musics";
        if(!new_file.cd(dir)) {
            new_file.mkdir(dir);
            new_file.cd(dir);
        }
        qDebug() << new_file.filePath(QFileInfo(le_path->text()).fileName());
        QFile::copy(le_path->text(), new_file.filePath(QFileInfo(le_path->text()).fileName()));
        new_sound->appendRow(new QStandardItem(new_file.filePath(QFileInfo(le_path->text()).fileName())));
    } else {
        new_sound->appendRow(new QStandardItem(le_path->text()));
    }
    return new_sound;
}

QStandardItem* add_audio_window::get_sound(QString title, QString path) {
    QStandardItem* new_sound = new QStandardItem(title);
    new_sound->appendRow(new QStandardItem(path));
    return new_sound;
}

void add_audio_window::load_sound() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open sound file"), "", tr("Sounds (*.mp3 *.ogg *.wav)"));
    if(!filename.isEmpty()) {
        le_path->setText(filename);
        le_title->setText(QFileInfo(filename).baseName());
    }
}

void add_audio_window::fields_filled() {
    if(!le_path->text().isEmpty() && !le_title->text().isEmpty()) {
        btn_ok->setEnabled(true);
    } else {
        btn_ok->setEnabled(false);
    }
}
