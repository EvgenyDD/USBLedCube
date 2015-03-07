/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#include "pawrapper.h"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include <QTextCodec>

using namespace std;

PaStream *stream;
PaError err;

int paWrapper::processingCallback(const void *inputBuffer,
                                  void *outputBuffer,
                                  unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo* timeInfo,
                                  PaStreamCallbackFlags statusFlags)
{
  (void) inputBuffer; // Prevent unused variable warning.
  (void) outputBuffer; // Prevent unused variable warning.
  (void) framesPerBuffer; // Prevent unused variable warning.
  (void) timeInfo; // Prevent unused variable warning.
  (void) statusFlags; // Prevent unused variable warning.
  return 0;
}

paWrapper::paWrapper()
{
    qDebug() << "paWrapper::paWrapper()";
    isRunning = false; //currently nothing is running
    initAudio();
}

void paWrapper::initAudio()
{
    qDebug() << "paWrapper::initAudio()";
    int selectedDevice = Pa_GetDefaultOutputDevice();

    int err = Pa_Initialize();
    if( err != paNoError )
        qDebug() << "PortAudio error:" << Pa_GetErrorText( err );

    int noOfAudioDevices = Pa_GetDeviceCount();
    selectedHostApi = Pa_GetDefaultHostApi();
    const PaDeviceInfo* di;

    qDebug() << Pa_GetHostApiCount() << " host apis available";
    qDebug() << noOfAudioDevices << " audio devices available";

    for(int i=0; i<noOfAudioDevices; i++)
    {
        di = Pa_GetDeviceInfo(i);

        /************************************************************
        ** Routine that convert ru sound device name to normal view
        ** Input : QString
        ** Output: QString: out
        *************************************************************/
        QByteArray inArray = QString(di->name).toUtf8();
        QString out;

        for(int k=0; k<inArray.length(); k++)
        {
            if(inArray[k] != (char)4)
            {
                if(inArray[k+1] == (char)4)
                    out.append(QChar(1024+inArray[k]));
                else
                    out.append(QChar(inArray[k]));
            }
        }
        /***********************************************************/
        qDebug() << "Device " << i << ": " << out;


        if(i==selectedDevice)
        {
            suggestedLatency = di->defaultLowInputLatency;
        }
    }

    outputStreamParam.channelCount = 1;
    outputStreamParam.device = Pa_GetDefaultOutputDevice();
    outputStreamParam.sampleFormat = paFloat32;
    outputStreamParam.suggestedLatency = suggestedLatency;
    outputStreamParam.hostApiSpecificStreamInfo = NULL;

    inputStreamParam.channelCount = 1;
    inputStreamParam.device = Pa_GetDefaultInputDevice();
    inputStreamParam.sampleFormat = paFloat32;
    inputStreamParam.suggestedLatency = suggestedLatency;
    inputStreamParam.hostApiSpecificStreamInfo = NULL;

    if(outputStreamParam.device > 0)
        sampleRate = getDefaultSampleRate(outputStreamParam.device);
    else
        sampleRate = 44100.0;

    frameLength = 1024; //set to a useful value

    qDebug() << " Default output device is " << Pa_GetDefaultOutputDevice();
    qDebug() << " Default input device is " << Pa_GetDefaultOutputDevice();
}

paWrapper::~paWrapper()
{
    qDebug() << "paWrapper::~paWrapper()";

    int err = Pa_Terminate();
    if( err != paNoError )
        qDebug() << "PortAudio error (Pa_Terminate): " << Pa_GetErrorText( err );
}

int paWrapper::startAudio(void)
{
    if(isRunning) return pawErrorAudioIsRunning;

    isRunning = true;

    err = Pa_OpenStream(&stream,
                      &inputStreamParam,
                      &outputStreamParam,
                      sampleRate,
                      frameLength,
                      paNoFlag,
                      &paWrapper::paStaticCallback,
                      this);

    if(err != paNoError)
    {
        isRunning=false;
        return err;
    }
    else
        qDebug() << "Stream opened!";

    int err = Pa_StartStream( stream );
    if(err != paNoError)
        isRunning=false;
    else
        qDebug() << "Stream started!";

    return err;
}

int paWrapper::stopAudio(void)
{
    int err=-1;
    if(isRunning)
    {
        err = Pa_AbortStream( stream );
        isRunning=false;

        if( err != paNoError ) return err;

        err = Pa_CloseStream( stream );
    }
    return err;
}

int paWrapper::runOnce(void)
{
    int err = startAudio();
    if( err != paNoError ) return err;

    // Sleep
    Pa_Sleep(4000);

    err = stopAudio();
    return err;
}

/**
  The wrapper for user messages. Replace text messages here for user convenience.
*/
const char* paWrapper::getErrorText(int errorId)
{
    switch(errorId)
    {
    case paInvalidChannelCount:
        return "No output channels available or device busy";
        break;

    case pawErrorAudioIsRunning:
        return "The audio processing is already running";
        break;

    default:
        return Pa_GetErrorText(errorId);
    }
}

