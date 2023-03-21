#include "chowdsp_sources/chowdsp_sources.h"
#include "chowdsp_dsp_utils/chowdsp_dsp_utils.h"
#include "chowdsp_filters/chowdsp_filters.h"

struct Osc303 {

    float pow = 0.0f;
    chowdsp::SawtoothWave<float> saw;
    juce::dsp::ProcessSpec spec;

    chowdsp::FirstOrderLPF< float > lp1;

    float breakpoint, breakpoint2;
    float amplitude, targetAmplitude;
    float cv;

    Osc303() {
        spec.maximumBlockSize = 2048;
        spec.numChannels = 1;
    }

    // set CV value, accepted range is 0v-5.0v
    void setPitchCV(float value) {
        cv = value;
        saw.setFrequency(16.35 * std::pow(2, value));
        lp1.calcCoefs(16.35 * std::pow(2, value) * 16, spec.sampleRate);
        breakpoint = cvToPw(value);
        breakpoint2 = cvToEdge(value);
        amplitude = cvToAmplitude(value);
        targetAmplitude = cvToTargetAmplitude(value);
        pow = cvToPow(value);
        // d_stdout("DSP osc CV %fV = freq %fHz", value, saw.getFrequency());
        // d_stdout("DSP cutoff from CV %f", 16.35 * std::pow(2, value) * 16);
        // d_stdout("bp %f bp2 %f amplitude %f targetAmplitude %f pow %f", breakpoint, breakpoint2, amplitude, targetAmplitude, pow);
    }

    void process(float* squareBuf, float* sawBuf, uint32_t frames) {
        float f;
        for (uint32_t i=0; i < frames; ++i)
        {   
            float out;
            sawBuf[i] = saw.processSample();
            f = (sawBuf[i]+1)/2;
            float _amp = amplitude;
            if (f > breakpoint) {
                if ((f - breakpoint) < breakpoint2) {
                    float y = (f - breakpoint)/breakpoint2;
                    y = smoothEdge(y);
                    out = y * 2 -1.0;
                } else {
                    out = 1.0;
                    float lastSegment = breakpoint + breakpoint2;
                    if ((f > lastSegment)) {
                        float pos = 1 - ((f - lastSegment)/(1.0 - lastSegment));
                        _amp = amplitude * (targetAmplitude + (pos * (1.0 - targetAmplitude)));
                    }
                }
            } else {
                out = -1.0;
            }
            out *= _amp * 0.646; // square is 0.6 time amplitude of ramp/saw

            float lp1_out = lp1.processSample(out);
            if ((f >= 0) && (f < breakpoint)) {
                out = out;
            } else out = lp1_out;
            squareBuf[i] = out;
        }
    }

    void prepare(float sampleRate, float defaultCV = 1.0) {
        spec.sampleRate = sampleRate * 4.0;
        saw.prepare(spec);

        setPitchCV(defaultCV);
    }

    inline float smoothEdge(float in) {
        return -1 * std::pow(1-in, pow) + 1;
    }

    inline float cvToPw(float in) {
        // d_stdout("Set pw to %f", 0.0625 * in + 0.290448528711551);
        return 0.0625 * in + 0.290448528711551;
    }

    inline float cvToEdge(float in) {
        in /= 5;
        float out = std::pow(0.94 * in - 1, 4);
        out = (out * 0.371393200647557) + 0.0380916103228264;
        // d_stdout("Set edge w for cv %f (%f) to %f", in*5, in, out);
        return out;
    }

    inline float cvToAmplitude(float in) {
        // d_stdout("New amp? %f", in);
        if (in < 2.0 && in >= 0.0) return 0.111 * in + 0.729;
        else return 0.0164 * in + 0.918;
    }

    inline float cvToTargetAmplitude(float in) {
        if (in < 1.5 && in >= 0.0) return -0.06 * in + 0.803;
        else return 0.0707 * in + 0.607;
    }

    inline float cvToPow(float in) {
        in /= 5;
        float out = (std::pow(in, 8) + 0.1 * in) * 0.9;
        return 33.0 * out + 2.879;
    }

};