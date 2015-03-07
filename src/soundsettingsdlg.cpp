/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#include "soundsettingsdlg.h"
#include "ui_soundsettingsdlg.h"
#include <QMessageBox>
#include <iostream>
#include <math.h>
#include "static_settings.h"

#include <QDebug>
#include <QTextCodec>

using namespace std;

soundSettingsDlg::soundSettingsDlg(paWrapper *paw, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::soundSettingsDlg)
{
    m_ui->setupUi(this);
    this->paw = paw;

    qDebug()<<"Sound Settings Dialog: devcount " << paw->getDeviceCount();

    //fill sound device combo boxes:
    for(int i=0; i < paw->getDeviceCount(); i++)
    {
        /************************************************************
        ** Routine that convert ru sound device name to normal view
        ** Input : QString
        ** Output: QString: out
        *************************************************************/
        QByteArray inArray = QString(paw->getDeviceName(i)).toUtf8();
        QString out;

        for(int i=0; i<inArray.length(); i++)
        {
            if(inArray[i] != (char)4)
            {
                if(inArray[i+1] == (char)4)
                    out.append(QChar(1024+inArray[i]));
                else
                    out.append(QChar(inArray[i]));
            }
        }
        /***********************************************************/

        m_ui->inputSoundDeviceComboBox->addItem(out);
        m_ui->outputSoundDeviceComboBox->addItem(out);
    }

    m_ui->inputSoundDeviceComboBox->setCurrentIndex(paw->getInputDevice());
    m_ui->outputSoundDeviceComboBox->setCurrentIndex(paw->getOutputDevice());

    //fill sample rate text edit:
    QString tmpStr;
    tmpStr.sprintf("%d",(int) paw->getSampleRate());
    m_ui->sampleRateLineEdit->setText(tmpStr);

    //fill and select frameLength combo box:
    int frameLength;
    for(int i=0; i < NO_OF_FRAME_LENGTHS; i++)
    {
        frameLength = (int) (START_FRAME_LENGTH * pow(2,i));
        tmpStr.sprintf("%i", frameLength);

        m_ui->frameLengthcomboBox->addItem(tmpStr);

        if(paw->getFrameLength() == frameLength)
            m_ui->frameLengthcomboBox->setCurrentIndex(i);
    }

    connect(m_ui->okPushButton, SIGNAL(pressed()), this, SLOT(onAccept()));
    connect(m_ui->cancelPushButton, SIGNAL(pressed()), this, SLOT(reject()));
}

soundSettingsDlg::~soundSettingsDlg()
{
    delete m_ui;
}

void soundSettingsDlg::changeEvent(QEvent *e)
{
    switch (e->type())
    {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;

    default:
        break;
    }
}

void soundSettingsDlg::onAccept()
{
    paw->setFrameLength((int) (START_FRAME_LENGTH * pow(2,m_ui->frameLengthcomboBox->currentIndex())));

    int err = paw->setInputDevice(m_ui->inputSoundDeviceComboBox->currentIndex());
    err = paw->setOutputDevice(m_ui->outputSoundDeviceComboBox->currentIndex());

    QString message;
    if(err < 0)
    {
        message = paw->getErrorText(err);
        QMessageBox messageBox(QMessageBox::Critical, "Error", message);
        messageBox.exec();
        return;
    }
    err = paw->setSampleRate(m_ui->sampleRateLineEdit->text().toDouble());
    if(err < 0)
    {
        message = paw->getErrorText(err);
        QMessageBox messageBox(QMessageBox::Critical, "Error", message);
        messageBox.exec();
        return;
    }
    emit accept();
}
