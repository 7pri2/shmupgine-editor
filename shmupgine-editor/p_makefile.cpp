#include "p_makefile.h"

p_makefile::p_makefile(QWidget* parent) : QWidget(parent) {
    makefile = "";
    te_text_area    = new QTextEdit(this);
    mainlayout      = new QVBoxLayout(this);

    mainlayout->addWidget(te_text_area);
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
    makefile += QString("CXXFLAGS=") + project_data::Instance()->prj_config[COMPILER_FLAGS] + QString("-I$(HEADERS)\n");
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

    return makefile;
}

QString p_makefile::get_makefile() {
    return makefile;
}
