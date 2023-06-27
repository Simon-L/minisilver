#include "chowdsp_sources/chowdsp_sources.h"
#include "chowdsp_dsp_utils/chowdsp_dsp_utils.h"
#include "chowdsp_filters/chowdsp_filters.h"

struct OscMetal {

    float pow = 0.0f;
    chowdsp::SquareWave<float> sq1;
    chowdsp::SquareWave<float> sq2;
    chowdsp::SquareWave<float> sq3;
    chowdsp::SquareWave<float> sq4;
    chowdsp::SquareWave<float> sq5;
    chowdsp::SquareWave<float> sq6;
    juce::dsp::ProcessSpec spec;

    float cv;

    // set CV value, accepted range is 0v-5.0v
    void setPitchCV(float value) {
        cv = value;
        // 205.3, 369.6, 304.4, 522.7, 800, 540
        sq1.setFrequency(205.3);
        sq2.setFrequency(369.6);
        sq3.setFrequency(304.4);
        sq4.setFrequency(522.7);
        sq5.setFrequency(800);
        sq6.setFrequency(540);
    }

    void process(float* buf, uint32_t frames) {
        float f;
        for (uint32_t i=0; i < frames; ++i)
        {   
            float out =
                sq1.processSample() +
                sq2.processSample() +
                sq3.processSample() +
                sq4.processSample() +
                sq5.processSample() +
                sq6.processSample();
            out *= 0.166;
            buf[i] = out;
        }
    }

    void prepare(float sampleRate, float defaultCV = 1.0) {
        spec.maximumBlockSize = 2048;
        spec.numChannels = 1;
        spec.sampleRate = sampleRate * 4.0;
        sq1.prepare(spec);
        sq2.prepare(spec);
        sq3.prepare(spec);
        sq4.prepare(spec);
        sq5.prepare(spec);
        sq6.prepare(spec);

        setPitchCV(defaultCV);
    }

};