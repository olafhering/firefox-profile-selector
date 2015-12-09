#ifndef FFPS_H
#define FFPS_H

#include <QtGui>

class Ffps : public QWidget
{
	Q_OBJECT
public:
	Ffps(QWidget *parent = 0);
	void seturl(QString arg1);

private slots:
	void Run();
	void Quit();
	void FillList(QWidget *top);
	void EnableRunButton();

private:
	QLineEdit *exe;
	QLineEdit *url;
	QString profiles_dir;
	QString profiles_ini;
	QSettings *ini;
	QLabel *label;
	QListWidget *list;
	QVBoxLayout *vlay;
	QCheckBox *tab_instead_window;
	QCheckBox *private_window;
	QPushButton *btn_exit;
	QPushButton *btn_run;
};

#endif

