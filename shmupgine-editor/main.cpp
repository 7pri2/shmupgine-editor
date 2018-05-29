#include <QApplication>
#include "windows_panels.h"

#include <iostream>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QFile stylesheet_file(":qss/nightmode.qss");
	stylesheet_file.open(QFile::ReadOnly);
	QString stylesheet = QLatin1String(stylesheet_file.readAll());

	app.setStyleSheet(stylesheet);

    w_editor::Instance()->show();
    return app.exec();
}
