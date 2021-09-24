#pragma once

#include <QtWidgets/qwidget.h>
#include <QtCore/qobject.h>
#include "GrannyMod.h"
#include "ui_Importer.h"

class Importer : public QWidget,public Ui::Importer
{
  Q_OBJECT
 public:
	 explicit Importer(QWidget* parent = nullptr);
	 void setmaxlobals(ImpInterface* I, Interface* GI, ImpNode* impnode);//apprently gi and i get nullpointer running thought qt mocing process
	 void setGlobals(std::string* filename);
	 bool LoadMeshs(granny_mesh* gmesh);
	 void fillvector(granny_mesh* gmesh);

	 ~Importer();
public slots:
     void setOptions();
signals:
	
private:

	std::string* fiilename;
	GrannyMod* grmod;
};

