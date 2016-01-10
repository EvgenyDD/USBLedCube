#include "mainwindow.h"

#include <QMainWindow>
#include "soundsettingsdlg.h"

#include <math.h>
#include <iostream>

#include "static_settings.h"
#include "fftprocessor.h"

#include <QMessageBox>
#include "complexnumber.h"

#include "QDateTime"

//#define PLOT_HISTOGRAM

using namespace std;


// SLOTS
void MainWindow::onFrameProcessed(fftProcessor *fft)
{
    unsigned int n = fft->getfftSize()/2+1; //4097 samples; default band = 15000 Hz
    //double one_over_n = 1/((double) n); //to make it a little bit faster

    float VolPower = 0;
    float SpecPower = 0;
    float SpectreAVGPower = 0;

    static int OutMass[9] = {0};

    /*
 красные лампы — низкие частоты (диапазон до 200 Гц),
 жёлтые — средне-низкие (диапазон от 200 до 800 Гц),
 зелёные — средние (от 800 до 3500 Гц),
 синие — выше 3500 Гц
*/
    /*
для адекватного представления пересчитываем в дБ, с учетом максимальной величины
    в выборке по формуле 20lg(Ai/Amax), для напряжений
при необходимости используем различные сглаживающие окна для взвешивания входного
    сигнала во временной области, например Блэкмана-Харриса

Анализатор делается так:
-берем N выборок числом кратным степени 2 (2^к).
-производим комплексное БПФ, мнимые части заполняем нулями, получаем 2N значений,
-величину сигнала для каждой частоты получаем складывая квадраты действительной и
    мнимой части и извлекая из суммы кв. корень (ничего отбрасывать нельзя).
    Получаем N значений из которых значения от 0 до N/2-1 представляют спектр
    в области 0..Fs/2 (Fs-частота дискретизации), для анализатора можно использовать только эту часть,
    поскольку часть от N/2 до N симметрична.
- для представления выбираем базу Amax(максимально возможное значение велечины) и
    высчитываем значения в децибелах Di = 20lg(Ai/Amax) - это для напряжений,
    т.к. мощность пропорциональна квадрату напряжения то для мощности DP = 10lg(Ai/Amax).
-результаты выводите в удобном для Вас виде (столбики, палочки, точечки, линийки и т.п.).
-результаты комплексных БПФ используются для обработки (фильтрация, эквалайзинг,
    шумопонижение и т. п.) при необходимости.
-затем обратное БПФ для вывода звука.
//////////////////////////////////////////////////////
2. После этого делаем FFT. работает _только_ с выборками, длинна которых кратна 2^N.

3. Результат FFT обоабатываем следующим образом.
3.1 Создаём массив, в который будем заносить результат.
    Каждый член этого массива равен корню квадратному из суммы квадратов действительной и мнимой
    частей соответствующего члена результата преобразования. Иными словами,
    y = sqrt( re(x(i))^2 + im(x(i))^2 ), где x = результат FFT,
    re(x(i)) вещественная часть i-го элемента, im(x(i)) - мнимая часть i-го элемента.
3.2 Далее вычисляем "мощность" выборки путём почленного суммирования массива y, power = sum(y).
3.3 А после этого делаем следующее y(i) = 10 * log10( y(i) / power ). По идее,
    это есть нормировка частот на общую мощьность выборки. Этот момент я отыскал
    методом научного тыка. Может он и неправильный, однако, результаты очень-очень
    (до единиц) похожи на те, которые отдаёт Adobe Audition при спектральном анализе.
3.4 После этого отбрасываем половину массива-результата, так как она содержит
    "отрицательные" частоты, симетричные началу координат.

4. Далее разбиваем полученную выборку на заданное количество частей и в
    каждой части производим усреднени путём нахождения среднего арифметического.
    Отмечу, что скорее всего, правильней будет разбить выборку-результат равномерно
    не в линейном, а в логарифмическом мастабе. Придётся повозиться, однако кажись,
    WinAmp делает имеено так.
      */
    //Hz
    //63
    //160
    //400
    //1k
    //2k5
    //6k25
    //16k

    // get FFT values
    for(unsigned int i=0; i<n; i++)
    {
#if 0
        //log+abs fft:
        mainCurveYData[i] = 20.0 * log10(one_over_n * fft->fftOutAbs[i]);
#elif 1
        //abs fft:
        mainCurveYData[i] = sqrt(fft->fftOut[i][0]*fft->fftOut[i][0] + fft->fftOut[i][1]*fft->fftOut[i][1]);
        //mainCurveYData[i] = 20*log10(mainCurveYData[i]);
#else
        //real input:
        mainCurveYData[i] = fft->fftIn[i];
#endif
    }

    // get power of volume by calculating average of FFT results
    for(unsigned int i=0; i<n; i++)
        VolPower += mainCurveYData[i];
    VolPower /= n;

    if(++VolumeRBptr == VOL_RB_SIZE) VolumeRBptr = 0; // increment pointer to the Volume Ring Buffer
    VolumeRB[VolumeRBptr] = VolPower;

    VolMinPower = VolMaxPower;  //reset values
    VolMaxPower = 0;            //reset values
    for(int i=0; i<VOL_RB_SIZE; i++)
    {
        // define Min and Max volume from the Volume Ring Buffer
        if(VolumeRB[i]>VolMaxPower) VolMaxPower = VolumeRB[i];
        if(VolumeRB[i]<VolMinPower) VolMinPower = VolumeRB[i];
    }

    int val = map(VolPower, VolMinPower, VolMaxPower, 0, 8); //map volume to cube size

#define ZERO_VOL 0.0003 //"capture" zero volume
    OutMass[8] = VolPower>ZERO_VOL ? val : 0;//(8*VolPower/VolMaxPower); // 0 if no sound

    // smooth volume value transition
    static int prevVol=0;
    if(VolumeCheckSmooth->isChecked())
    {
        if(prevVol > 0)         prevVol--;
        if(prevVol<OutMass[8])  prevVol = OutMass[8];
        OutMass[8] = prevVol;
    }

    // Show spectre on graph
    if(++GraphRBptr == GRAPH_RB_SIZE) GraphRBptr = 0; // increment pointer to the Graph Spectre Ring Buffer

    float tempGrVal = 0;
    // find max graph spectre value
    for(unsigned int i=0; i<n; i++)
        if(mainCurveYData[i]>tempGrVal) tempGrVal = mainCurveYData[i];
    // ...and put it in ring buffer
    GraphRB[GraphRBptr] = tempGrVal;

    tempGrVal = 0;
    // find max spectre value in last seconds
    for(int i=0; i<GRAPH_RB_SIZE; i++)
        if(tempGrVal < GraphRB[i]) tempGrVal = GraphRB[i];

    mainPlot->setAxisScale(QwtPlot::yLeft, 0, 100);

    if(tempGrVal < 20*ZERO_VOL)
    {
        for(unsigned int i=0; i<n; i++)
            subCurveYData[i] = mainCurveYDataNormed[i] = 0;
    }
    else
    {
        for(unsigned int i=0; i<n; i++)
        {
            // Norm the graph spectre values
            mainCurveYDataNormed[i] = 100*mainCurveYData[i]/tempGrVal;

            // Slow down the peaks on the graph
            if(subCurveYData[i] < mainCurveYDataNormed[i])
                subCurveYData[i] = mainCurveYDataNormed[i];
            if(subCurveYData[i] > 2) subCurveYData[i] -= 2;
        }
    }

#ifndef PLOT_HISTOGRAM
    mainCurve->setSamples(mainCurveXData, mainCurveYDataNormed, n);
    subCurve->setSamples(mainCurveXData, subCurveYData, n);
#else
    QVector<QwtIntervalSample> samples( n );
    for ( uint i = 0; i < n; i++ )
    {
        QwtInterval interval( double( i ), i + 1.0 );
        interval.setBorderFlags( QwtInterval::ExcludeMaximum );

        samples[i] = QwtIntervalSample( mainCurveYData[i], interval );
    }
    histogram->setData( new QwtIntervalSeriesData( samples ) );
#endif

    float f[8] = {0};

    for(unsigned int i=0; i<20; i++)         f[0]+= mainCurveYData[i];
    for(unsigned int i=20; i<80; i++)        f[1]+= mainCurveYData[i];
    for(unsigned int i=80; i<160; i++)       f[2]+= mainCurveYData[i];
    for(unsigned int i=160; i<250; i++)      f[3]+= mainCurveYData[i];
    for(unsigned int i=250; i<500; i++)      f[4]+= mainCurveYData[i];
    for(unsigned int i=500; i<1000; i++)     f[5]+= mainCurveYData[i];
    for(unsigned int i=1000; i<2000; i++)    f[6]+= mainCurveYData[i];
    for(unsigned int i=2000; i<n; i++)       f[7]+= mainCurveYData[i];
    f[0] /= (20-0);
    f[1] /= (80-20);
    f[2] /= (160-80);
    f[3] /= (250-160);
    f[4] /= (500-250);
    f[5] /= (1000-500);
    f[6] /= (2000-1000);
    f[7] /= (n-2000);

    f[0] *= 1.0;//((float)spinBox->value()/100.0);
    f[1] *= 0.7;
    f[2] *= 1.7;
    f[3] *= 1.8;
    f[4] *= 4.5;
    f[5] *= 8.0;
    f[6] *= 16.0;
    f[7] *= 32.0;

    // Correct spectre values by multipluing them on the variable constant
    for(int i=0; i<8; i++)
    {
        f[i] *= specMult;
        SpecPower += f[i];
    }

    if(++SpectreRBptr == SPECTRE_RB_SIZE) SpectreRBptr = 0; // increment pointer to the Spectre Ring Buffer
    SpectreRB[SpectreRBptr] = SpecPower;

    // Find the average spectre power of the Spectre Ring Buffer
    for(int i=0; i<SPECTRE_RB_SIZE; i++)
        SpectreAVGPower += SpectreRB[i];
    SpectreAVGPower /= SPECTRE_RB_SIZE;

#define MIN_SPECTRE_POWER   14
#define MAX_SPECTRE_POWER   (64-8*2)
#define SPECTRE_INCR_VAL    (0.5/2)

    // if average spectre power is too low [no leds light] -> increase multiplier
    if(SpectreAVGPower < MIN_SPECTRE_POWER && OutMass[8] > 1)
        specMult += SPECTRE_INCR_VAL;

    // if average spectre power is too high [all leds light] -> decrease multiplier
    if(SpectreAVGPower > MAX_SPECTRE_POWER && OutMass[8] > 1)
    {
        if(specMult > 1)
            specMult -= SPECTRE_INCR_VAL;
        else if(specMult > 0.02) //multiplier can't be < 0
            specMult -=0.02;
    }

    // smooth spectre values transition
    for(int i=0; i<8; i++)
    {
        if(SpectreCheckSmooth->isChecked())
        {
            if(OutMass[i] > 0)  OutMass[i]--;       //decrease by 1 value of each spectre channel
            if(OutMass[i]<f[i]) OutMass[i] = f[i];  //update spectre channel if it lower then new value
        }
        else
            OutMass[i] = f[i];
    }

    Cube->SetEqGraph(&OutMass[0]);              //paint spectre & volume on cube
    mainPlot->replot();                         //replot the spectre plot in window

    qDebug()<<"> Vmax="<<VolMaxPower<<" Vmin="<<VolMinPower<<" Vpwr="<<VolPower<<" Vptr="<<VolumeRBptr<<"  MULT="<<specMult;

    //Measure callback interval [256 Samples - 15000 Hz - is 70ms]
    //    static uint prevv = 0;
    //    QDateTime setTime = QDateTime::fromString ( QString("2016-01-05T17:26:09"), Qt::ISODate);
    //    QDateTime current = QDateTime::currentDateTime();
    //    uint msecs = setTime.time().msecsTo(current.time());
    //    qDebug()<<" msec is "<<msecs-prevv;
    //    prevv = msecs;
}
