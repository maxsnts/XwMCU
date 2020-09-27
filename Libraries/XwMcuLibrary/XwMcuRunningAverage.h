#ifndef XwMcuRunningAverage_h
#define XwMcuRunningAverage_h

#include <Arduino.h>

//******************************************************************************
class XwMcuRunningAverage
{
    public:
        XwMcuRunningAverage(byte samples);
        void Update(double value);
        double Get();
    private:
        byte nIndex;
        byte nSamples;
        double *Samples;
};

//******************************************************************************
XwMcuRunningAverage::XwMcuRunningAverage(byte samples)
{
    nSamples = samples;
    Samples = new double[samples];
}

//******************************************************************************
void XwMcuRunningAverage::Update(double value)
{
    Samples[nIndex++] = value;
    if (nIndex == nSamples)
        nIndex = 0;
}

//******************************************************************************
double XwMcuRunningAverage::Get()
{
    double sum;
    for (byte i=0; i < nSamples; i++)
        sum += Samples[i];
    return sum / nSamples;
}

#endif
