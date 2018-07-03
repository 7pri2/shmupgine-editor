#include "add_image_window.h"

add_image_window::add_image_window() {
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
    le_path->setReadOnly(true);

    connect(le_path, SIGNAL(textChanged(QString)), this, SLOT(fields_filled()));
    connect(le_title, SIGNAL(textChanged(QString)), this, SLOT(fields_filled()));
    connect(btn_load, SIGNAL(clicked(bool)), this, SLOT(load_image()));
    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btn_ok, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

QStandardItem* add_image_window::get_image() {
    QStandardItem* new_image = new QStandardItem(le_title->text());
    if(chkbx_copy_it->isChecked()) {
        QDir new_file(p_config_panel::Instance()->get_project_working_dir());
        if(!new_file.cd("res")) {
            new_file.mkdir(new_file.filePath("res"));
            new_file.cd("res");
        }
        if(!new_file.cd("image")) {
            new_file.mkdir("image");
            new_file.cd("image");
        }
        qDebug() << new_file.filePath(QFileInfo(le_path->text()).fileName());
        QFile::copy(le_path->text(), new_file.filePath(QFileInfo(le_path->text()).fileName()));
        new_image->appendRow(new QStandardItem(new_file.filePath(QFileInfo(le_path->text()).fileName())));
    } else {
        new_image->appendRow(new QStandardItem(le_path->text()));
    }
    new_image->setIcon(QIcon(file_icon));
    new_image->appendRow(new QStandardItem(QString::number(file_icon.width())));   // width
    new_image->appendRow(new QStandardItem(QString::number(file_icon.height())));  // height
    return new_image;
}

QStandardItem* add_image_window::get_image(QString title, QString path) {
    QStandardItem* new_image = new QStandardItem(title);
    new_image->appendRow(new QStandardItem(path));
    return new_image;
}

void add_image_window::load_image() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open image file"), "", tr("images (*.jpg *.bmp *.png)"));
    if(!filename.isEmpty()) {
        le_path->setText(filename);
        le_title->setText(QFileInfo(filename).baseName());
        file_icon.load(filename);
    }
}

void add_image_window::fields_filled() {
    if(!le_path->text().isEmpty() && !le_title->text().isEmpty()) {
        btn_ok->setEnabled(true);
    } else {
        btn_ok->setEnabled(false);
    }
}
