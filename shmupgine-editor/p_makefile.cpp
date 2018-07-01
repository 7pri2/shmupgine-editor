#include "p_makefile.h"
#include "p_config_panel.h"

p_makefile::p_makefile(QWidget* parent) : QWidget(parent) {
    makefile = "";
    btn_generate    = new QPushButton(tr("Generate makefile"), this);
    te_text_area    = new QTextEdit(this);
    mainlayout      = new QVBoxLayout(this);
    filename = "Makefile";

    mainlayout->addWidget(te_text_area);
    mainlayout->addWidget(btn_generate);
    te_text_area->setTabStopWidth(24);

    connect(te_text_area, SIGNAL(textChanged()), this, SLOT(emit_changes()));
    connect(btn_generate, SIGNAL(clicked(bool)), this, SLOT(generate_makefile()));
}

p_makefile::~p_makefile() {

}

QString p_makefile::generate_makefile() {
    makefile = QString(".SUFFIXES:\n\n");

    makefile += QString("GAME=") + project_data::Instance()->prj_config[NAME] + QString("\n\n");

    makefile += QString("LIB=lib/\n");
    makefile += QString("HEADERS=include/\n");
    makefile += QString("SRC=src/\n\n");

    makefile += QString("CXX=") + project_data::Instance()->prj_config[COMPILER_PATH] + QString("\n");
    makefile += QString("CXXFLAGS=") + project_data::Instance()->prj_config[COMPILER_FLAGS] + QString(" -I$(HEADERS)\n");
    makefile += QString("LDFLAGS=-L$(LIB) -lshmupgine -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio\n");
    makefile += QString("DEBUG=-g\n\n");

    makefile += QString("EXECUTABLES=$(GAME)\n");
    makefile += QString("LIBFILES=libshmupgine.a\n");
    makefile += QString("LIBS=$(patsubst %,$(LIB)%,$(LIBFILES))\n\n");

    makefile += QString("all: executables\n\n");

    makefile += QString("debug: CXXFLAGS+=$(DEBUG) -DDEBUG\n");
    makefile += QString("debug: all\n\n");

    makefile += QString("executables: $(EXECUTABLES)\n\n");

    makefile += QString("$(GAME): $(SRC)main.cpp $(HEADERS)shmupgine.h $(LIB)libshmupgine.a\n");
    makefile += QString("\t$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)\n\n");

    makefile += QString("clean:\n");
    makefile += QString("\t-rm -f $(EXECUTABLES)");

    te_text_area->setPlainText(makefile);
    return makefile;
}

QString p_makefile::get_makefile() {
    return makefile;
}

QString p_makefile::get_filename() {
    return filename;
}

void p_makefile::revert_changes() {
    te_text_area->setPlainText(makefile);
    emit_changes();
}

void p_makefile::save_changes() {
    makefile = te_text_area->toPlainText();
    emit_changes();
}

void p_makefile::emit_changes() {
    emit changes_made(this, makefile != te_text_area->toPlainText());
}

bool p_makefile::load_makefile(const QJsonObject &config) {
    if(config.contains("makefile") && config["makefile"].isString()) {
        QFile in_makefile;
        in_makefile.setFileName(QDir(p_config_panel::Instance()->get_project_working_dir()).filePath(config["makefile"].toString()));
        if(in_makefile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            filename = in_makefile.fileName();
            makefile = QString(in_makefile.readAll());
            te_text_area->setText(makefile);
            in_makefile.close();
        } else {
            qDebug() << in_makefile.fileName() << in_makefile.errorString();
            return false;
        }
    } else
        false;
}
