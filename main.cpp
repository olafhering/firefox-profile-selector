#include <QApplication>
#include "ffps.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Ffps ffps;
	if (app.arguments().count() > 1)
		ffps.seturl(app.arguments().at(1));
	ffps.show();
	return app.exec();
}

