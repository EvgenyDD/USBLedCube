/********************************************************************************
** Form generated from reading UI file 'soundsettingsdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDSETTINGSDLG_H
#define UI_SOUNDSETTINGSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

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
            soundSettingsDlg->setObjectName(QStringLiteral("soundSettingsDlg"));
        soundSettingsDlg->resize(400, 208);
        verticalLayout = new QVBoxLayout(soundSettingsDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        inputSoundDeviceLabel = new QLabel(soundSettingsDlg);
        inputSoundDeviceLabel->setObjectName(QStringLiteral("inputSoundDeviceLabel"));

        gridLayout->addWidget(inputSoundDeviceLabel, 0, 0, 1, 1);

        inputSoundDeviceComboBox = new QComboBox(soundSettingsDlg);
        inputSoundDeviceComboBox->setObjectName(QStringLiteral("inputSoundDeviceComboBox"));

        gridLayout->addWidget(inputSoundDeviceComboBox, 0, 1, 1, 1);

        sampleRateLineEdit = new QLineEdit(soundSettingsDlg);
        sampleRateLineEdit->setObjectName(QStringLiteral("sampleRateLineEdit"));

        gridLayout->addWidget(sampleRateLineEdit, 2, 1, 1, 1);

        sampleRateLabel = new QLabel(soundSettingsDlg);
        sampleRateLabel->setObjectName(QStringLiteral("sampleRateLabel"));

        gridLayout->addWidget(sampleRateLabel, 2, 0, 1, 1);

        outputSoundDeviceComboBox = new QComboBox(soundSettingsDlg);
        outputSoundDeviceComboBox->setObjectName(QStringLiteral("outputSoundDeviceComboBox"));

        gridLayout->addWidget(outputSoundDeviceComboBox, 1, 1, 1, 1);

        outputSoundDeviceLabel = new QLabel(soundSettingsDlg);
        outputSoundDeviceLabel->setObjectName(QStringLiteral("outputSoundDeviceLabel"));

        gridLayout->addWidget(outputSoundDeviceLabel, 1, 0, 1, 1);

        frameLengthcomboBox = new QComboBox(soundSettingsDlg);
        frameLengthcomboBox->setObjectName(QStringLiteral("frameLengthcomboBox"));

        gridLayout->addWidget(frameLengthcomboBox, 3, 1, 1, 1);

        frameLengthLabel = new QLabel(soundSettingsDlg);
        frameLengthLabel->setObjectName(QStringLiteral("frameLengthLabel"));

        gridLayout->addWidget(frameLengthLabel, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okPushButton = new QPushButton(soundSettingsDlg);
        okPushButton->setObjectName(QStringLiteral("okPushButton"));

        horizontalLayout->addWidget(okPushButton);

        cancelPushButton = new QPushButton(soundSettingsDlg);
        cancelPushButton->setObjectName(QStringLiteral("cancelPushButton"));

        horizontalLayout->addWidget(cancelPushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(soundSettingsDlg);

        QMetaObject::connectSlotsByName(soundSettingsDlg);
    } // setupUi

    void retranslateUi(QDialog *soundSettingsDlg)
    {
        soundSettingsDlg->setWindowTitle(QApplication::translate("soundSettingsDlg", "Soundcard Settings", 0));
        inputSoundDeviceLabel->setText(QApplication::translate("soundSettingsDlg", "Input Sound Device", 0));
        sampleRateLabel->setText(QApplication::translate("soundSettingsDlg", "Sample Rate", 0));
        outputSoundDeviceLabel->setText(QApplication::translate("soundSettingsDlg", "Output Sound Device", 0));
        frameLengthLabel->setText(QApplication::translate("soundSettingsDlg", "Frame Length", 0));
        okPushButton->setText(QApplication::translate("soundSettingsDlg", "OK", 0));
        cancelPushButton->setText(QApplication::translate("soundSettingsDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class soundSettingsDlg: public Ui_soundSettingsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDSETTINGSDLG_H
