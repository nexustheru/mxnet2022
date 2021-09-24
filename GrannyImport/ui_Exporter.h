/********************************************************************************
** Form generated from reading UI file 'Exporter.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTER_H
#define UI_EXPORTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Exporter
{
public:

    void setupUi(QWidget *Exporter)
    {
        if (Exporter->objectName().isEmpty())
            Exporter->setObjectName(QString::fromUtf8("Exporter"));
        Exporter->resize(400, 300);

        retranslateUi(Exporter);

        QMetaObject::connectSlotsByName(Exporter);
    } // setupUi

    void retranslateUi(QWidget *Exporter)
    {
        Exporter->setWindowTitle(QCoreApplication::translate("Exporter", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Exporter: public Ui_Exporter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTER_H
