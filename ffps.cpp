#include <unistd.h>
#include <QCoreApplication>
#include <QFileInfo>
#include <QProcess>
#include "ffps.h"

Ffps::Ffps(QWidget *parent)
	: QWidget(parent)
{
	bool found = false;
	QString home = "HOME=";
	QStringList envs = QProcess::systemEnvironment();

	QWidget *top = this;
	vlay = new QVBoxLayout(top);

	exe = new QLineEdit("/usr/bin/firefox", top);
	vlay->addWidget(exe);

	url = new QLineEdit(top);
	vlay->addWidget(url);


	foreach (const QString &env, envs) {
		if (!env.startsWith(home, Qt::CaseSensitive))
			continue;
		home = env.right(env.length() - home.length());
		found = true;
		break;
	}

	label = new QLabel;
	vlay->addWidget(label);
	if (!found) {
		label->setText(home + " not found in environment.");
	} else {
		QFileInfo file;

		profiles_dir = home + "/.mozilla/firefox";
		profiles_ini = profiles_dir + "/profiles.ini";
		label->setText(profiles_ini);

		file.setFile(profiles_ini);
		if (file.isFile())
			FillList(top);
		else {
			if (file.exists())
				label->setText(profiles_ini + " is not a file.");
			else
				label->setText(profiles_ini + " not found.");
		}
	}

	btn_exit = new QPushButton("Exit", top);
	connect(btn_exit, SIGNAL(clicked()), top, SLOT(Quit()));
	vlay->addWidget(btn_exit);
}

void Ffps::FillList(QWidget *top)
{
	ini = new QSettings(profiles_ini, QSettings::IniFormat, top);

	list = new QListWidget(top);
	vlay->addWidget(list);

	QStringList profile_names = ini->childGroups();
	foreach (const QString &profile, profile_names) {
		QListWidgetItem *item;
		QString line, name, is_relative, path, is_default;

		name = ini->value(profile + "/Name").toString();
		is_relative = ini->value(profile + "/isRelative").toString();
		path = ini->value(profile + "/Path").toString();
		is_default = ini->value(profile + "/Default").toString();

		line += profile + ": " + name;
		line += ", relative: " + is_relative;
		line += ", path: " + path;

		item = new QListWidgetItem(name, list, QListWidgetItem::Type);
		if (is_default.toInt()) {
			QFont font = item->font();
			font.setBold(true);
			item->setFont(font);
		}
		item->setToolTip(line);
		list->addItem(item);
		continue;
	}

	tab_instead_window = new QCheckBox("Tab instead of Window", top);
	vlay->addWidget(tab_instead_window);

	private_window = new QCheckBox("Private Window", top);
	vlay->addWidget(private_window);

	if (list->count()) {
		btn_run = new QPushButton("Run", top);
		btn_run->setEnabled(false);
		connect(btn_run, SIGNAL(clicked()), top, SLOT(Run()));
		vlay->addWidget(btn_run);
	}
	list->setSortingEnabled(true);
	list->sortItems(Qt::AscendingOrder);
	connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), top, SLOT(Run()));
	connect(list, SIGNAL(itemSelectionChanged()), top, SLOT(EnableRunButton()));
}

void Ffps::Run()
{
	QByteArray profile_char, ff_char;
	QString profile;
	QListWidgetItem *item;
	int i = 0;
	char *argv[10] = { };

	item = list->currentItem();
	if (item)
		profile = item->text();
	profile_char = profile.toLatin1();
	ff_char = exe->text().toLatin1();

	argv[i] = new char[exe->text().toLocal8Bit().size() + 1];
	strcpy(argv[i], exe->text().toLocal8Bit().constData());
	i++;

	argv[i] = strdup("-P");
	i++;

	argv[i] = profile_char.data();
	i++;

	if (tab_instead_window->isChecked()) {
		argv[i] = strdup("--new-tab");
		i++;
	} else {
		argv[i] = strdup("--new-window");
		i++;
	}

	if (private_window->isChecked()) {
		argv[i] = strdup("--private-window");
		i++;
	}

	if (url->text().count()) {
		argv[i] = new char[url->text().toLocal8Bit().size() + 1];
		strcpy(argv[i], url->text().toLocal8Bit().constData());
		i++;
	}

	argv[i] = NULL;

	::execvp(argv[0], argv);

	QPushButton *btn = new QPushButton();
	connect(btn, SIGNAL(clicked()), this, SLOT(Quit()));
	btn->setText(profile);
	btn->show();
}
void Ffps::Quit()
{
	QCoreApplication::quit();
}

void Ffps::EnableRunButton()
{
	btn_run->setEnabled(true);
}

void Ffps::seturl(QString arg1)
{
	url->insert(arg1);
}
