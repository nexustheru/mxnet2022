/********************************************************************************
** Form generated from reading UI file 'Importer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTER_H
#define UI_IMPORTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Importer
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *filenameLabel;
    QLineEdit *filenameLineEdit;
    QLabel *skeletonLabel;
    QCheckBox *skeletonCheckBox;
    QLabel *meshLabel;
    QCheckBox *meshCheckBox;
    QLabel *animationsLabel;
    QCheckBox *animationsCheckBox;
    QLabel *materialLabel;
    QCheckBox *materialCheckBox;
    QTextEdit *textEdit;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *Importer)
    {
        if (Importer->objectName().isEmpty())
            Importer->setObjectName(QString::fromUtf8("Importer"));
        Importer->resize(792, 359);
        formLayoutWidget = new QWidget(Importer);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 771, 121));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        filenameLabel = new QLabel(formLayoutWidget);
        filenameLabel->setObjectName(QString::fromUtf8("filenameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, filenameLabel);

        filenameLineEdit = new QLineEdit(formLayoutWidget);
        filenameLineEdit->setObjectName(QString::fromUtf8("filenameLineEdit"));
        filenameLineEdit->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, filenameLineEdit);

        skeletonLabel = new QLabel(formLayoutWidget);
        skeletonLabel->setObjectName(QString::fromUtf8("skeletonLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, skeletonLabel);

        skeletonCheckBox = new QCheckBox(formLayoutWidget);
        skeletonCheckBox->setObjectName(QString::fromUtf8("skeletonCheckBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, skeletonCheckBox);

        meshLabel = new QLabel(formLayoutWidget);
        meshLabel->setObjectName(QString::fromUtf8("meshLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, meshLabel);

        meshCheckBox = new QCheckBox(formLayoutWidget);
        meshCheckBox->setObjectName(QString::fromUtf8("meshCheckBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, meshCheckBox);

        animationsLabel = new QLabel(formLayoutWidget);
        animationsLabel->setObjectName(QString::fromUtf8("animationsLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, animationsLabel);

        animationsCheckBox = new QCheckBox(formLayoutWidget);
        animationsCheckBox->setObjectName(QString::fromUtf8("animationsCheckBox"));

        formLayout->setWidget(3, QFormLayout::FieldRole, animationsCheckBox);

        materialLabel = new QLabel(formLayoutWidget);
        materialLabel->setObjectName(QString::fromUtf8("materialLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, materialLabel);

        materialCheckBox = new QCheckBox(formLayoutWidget);
        materialCheckBox->setObjectName(QString::fromUtf8("materialCheckBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, materialCheckBox);

        textEdit = new QTextEdit(Importer);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 140, 601, 211));
        textEdit->setReadOnly(true);
        label = new QLabel(Importer);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(630, 210, 141, 141));
        label->setPixmap(QPixmap(QString::fromUtf8("icon/icon.jpg")));
        pushButton = new QPushButton(Importer);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(700, 140, 75, 24));

        retranslateUi(Importer);

        QMetaObject::connectSlotsByName(Importer);
    } // setupUi

    void retranslateUi(QWidget *Importer)
    {
        Importer->setWindowTitle(QCoreApplication::translate("Importer", "Form", nullptr));
        filenameLabel->setText(QCoreApplication::translate("Importer", "Filename", nullptr));
        skeletonLabel->setText(QCoreApplication::translate("Importer", "Skeleton", nullptr));
        meshLabel->setText(QCoreApplication::translate("Importer", "Mesh", nullptr));
        animationsLabel->setText(QCoreApplication::translate("Importer", "Animation", nullptr));
        materialLabel->setText(QCoreApplication::translate("Importer", "Material", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("Importer", "Import", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Importer: public Ui_Importer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTER_H
