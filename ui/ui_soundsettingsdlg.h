/********************************************************************************
** Form generated from reading UI file 'soundsettingsdlg.ui'
**
** Created: Mon 22. Dec 17:05:02 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDSETTINGSDLG_H
#define UI_SOUNDSETTINGSDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_soundSettingsDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *inputSoundDeviceLabel;
    QComboBox *inputSoundDeviceComboBox;
    QLineEdit *sampleRateLineEdit;
    QLabel *sampleRateLabel;
    QComboBox *outputSoundDeviceComboBox;
    QLabel *outputSoundDeviceLabel;
    QComboBox *frameLengthcomboBox;
    QLabel *frameLengthLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okPushButton;
    QPushButton *cancelPushButton;

    void setupUi(QDialog *soundSettingsDlg)
    {
        if (soundSettingsDlg->objectName().isEmpty())
            soundSettingsDlg->setObjectName(QString::fromUtf8("soundSettingsDlg"));
        soundSettingsDlg->resize(400, 208);
        verticalLayout = new QVBoxLayout(soundSettingsDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        inputSoundDeviceLabel = new QLabel(soundSettingsDlg);
        inputSoundDeviceLabel->setObjectName(QString::fromUtf8("inputSoundDeviceLabel"));

        gridLayout->addWidget(inputSoundDeviceLabel, 0, 0, 1, 1);

        inputSoundDeviceComboBox = new QComboBox(soundSettingsDlg);
        inputSoundDeviceComboBox->setObjectName(QString::fromUtf8("inputSoundDeviceComboBox"));

        gridLayout->addWidget(inputSoundDeviceComboBox, 0, 1, 1, 1);

        sampleRateLineEdit = new QLineEdit(soundSettingsDlg);
        sampleRateLineEdit->setObjectName(QString::fromUtf8("sampleRateLineEdit"));

        gridLayout->addWidget(sampleRateLineEdit, 2, 1, 1, 1);

        sampleRateLabel = new QLabel(soundSettingsDlg);
        sampleRateLabel->setObjectName(QString::fromUtf8("sampleRateLabel"));

        gridLayout->addWidget(sampleRateLabel, 2, 0, 1, 1);

        outputSoundDeviceComboBox = new QComboBox(soundSettingsDlg);
        outputSoundDeviceComboBox->setObjectName(QString::fromUtf8("outputSoundDeviceComboBox"));

        gridLayout->addWidget(outputSoundDeviceComboBox, 1, 1, 1, 1);

        outputSoundDeviceLabel = new QLabel(soundSettingsDlg);
        outputSoundDeviceLabel->setObjectName(QString::fromUtf8("outputSoundDeviceLabel"));

        gridLayout->addWidget(outputSoundDeviceLabel, 1, 0, 1, 1);

        frameLengthcomboBox = new QComboBox(soundSettingsDlg);
        frameLengthcomboBox->setObjectName(QString::fromUtf8("frameLengthcomboBox"));

        gridLayout->addWidget(frameLengthcomboBox, 3, 1, 1, 1);

        frameLengthLabel = new QLabel(soundSettingsDlg);
        frameLengthLabel->setObjectName(QString::fromUtf8("frameLengthLabel"));

        gridLayout->addWidget(frameLengthLabel, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okPushButton = new QPushButton(soundSettingsDlg);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));

        horizontalLayout->addWidget(okPushButton);

        cancelPushButton = new QPushButton(soundSettingsDlg);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));

        horizontalLayout->addWidget(cancelPushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(soundSettingsDlg);

        QMetaObject::connectSlotsByName(soundSettingsDlg);
    } // setupUi

    void retranslateUi(QDialog *soundSettingsDlg)
    {
        soundSettingsDlg->setWindowTitle(QApplication::translate("soundSettingsDlg", "Soundcard Settings", 0, QApplication::UnicodeUTF8));
        inputSoundDeviceLabel->setText(QApplication::translate("soundSettingsDlg", "Input Sound Device", 0, QApplication::UnicodeUTF8));
        sampleRateLabel->setText(QApplication::translate("soundSettingsDlg", "Sample Rate", 0, QApplication::UnicodeUTF8));
        outputSoundDeviceLabel->setText(QApplication::translate("soundSettingsDlg", "Output Sound Device", 0, QApplication::UnicodeUTF8));
        frameLengthLabel->setText(QApplication::translate("soundSettingsDlg", "Frame Length", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("soundSettingsDlg", "OK", 0, QApplication::UnicodeUTF8));
        cancelPushButton->setText(QApplication::translate("soundSettingsDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class soundSettingsDlg: public Ui_soundSettingsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDSETTINGSDLG_H
