#pragma once
#include <QtWidgets/qwidget.h>
#include <QtCore/qobject.h>

class Exporter : public QWidget
{
 Q_OBJECT
public:
	explicit Exporter(QWidget* parent = nullptr);
	~Exporter();
private:
	
};

