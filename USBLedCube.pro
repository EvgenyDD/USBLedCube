# -------------------------------------------------
# Project Definition
# -------------------------------------------------

TARGET = USB_Led_Cube
TEMPLATE = app

QT += widgets
QT += svg
QTPLUGIN += windowsprintersupport

include(C:/Qt/QWT/qwt.pri)

#DESTDIR      = bin/

QT += printsupport


SOURCES +=  src/main.cpp \
            src/mainwindow.cpp \
            src/pawrapper.cpp \
            src/soundsettingsdlg.cpp \
            src/fftprocessor.cpp \
    src/usbhid.cpp


HEADERS +=  inc/mainwindow.h \
            inc/pawrapper.h \
            inc/soundsettingsdlg.h \
            inc/static_settings.h \
            inc/fftw/fftw3.h \
    src/usbhid.h \
    inc/usbhid.h


FORMS +=    ui/mainwindow.ui \
            ui/soundsettingsdlg.ui

INCLUDEPATH += inc/ \
            inc/pa/ \
            inc/audioprocessor_examples/ \
            inc/fftw

# input to output copy example:
#SOURCES += src/audioprocessor_examples/audioprocessor_io_copy.cpp
#HEADERS += inc/audioprocessor_examples/audioprocessor_io_copy.h

# noise out example:
#SOURCES += src/audioprocessor_examples/audioprocessor_noise.cpp
#HEADERS += inc/audioprocessor_examples/audioprocessor_noise.h

# sine out example:
#SOURCES += src/audioprocessor_examples/audioprocessor_sine.cpp
#HEADERS += inc/audioprocessor_examples/audioprocessor_sine.h

# fft example:
SOURCES += src/audioprocessor_examples/audioprocessor_fft.cpp
HEADERS += inc/audioprocessor_examples/audioprocessor_fft.h

# statical linked portaudio
HEADERS +=  inc/pa/portaudio.h
SOURCES +=  src/pa/pa_front.c \
            src/pa/pa_debugprint.c \
            src/pa/pa_allocation.c \
            src/pa/pa_stream.c \
            src/pa/pa_converters.c \
            src/pa/pa_cpuload.c \
            src/pa/pa_process.c \
            src/pa/pa_dither.c \
            src/pa/pa_ringbuffer.c

# ------------ Linux/Unix specific options ----------------
# ------------ Windows specific options ----------------
win32:DEFINES += PA_NO_ASIO # PA_NO_WMME

win32:SOURCES += src/pa/pa_win_ds.c \
                 src/pa/pa_win_hostapis.c \
                 src/pa/pa_win_util.c \
                 src/pa/pa_win_ds_dynlink.c \
                 src/pa/pa_win_waveformat.c \
                 src/pa/pa_win_wmme.c # src/pa/pa_asio.cpp


#specify path to direct-x SDK header directory
#win32:INCLUDEPATH += inc\dx

INCLUDEPATH += "C:/Program Files (x86)/Microsoft DirectX SDK (November 2008)/Include"


win32:LIBS +=   -ldsound \
                -lwinmm \
                -lole32 \

win32:LIBS +=   -lfftw3-3 \
                -L$$PWD/lib/fftw
