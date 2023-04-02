#include "chowdsp_dsp_utils/chowdsp_dsp_utils.h"

#include "ADAREnvelope.h"
#include "WowFilter.h"
#include "Osc303.hpp"
#include "AcidFilter.hpp"
#include "SlideFilter.hpp"
#include "AcidFormulas.hpp"

struct AcidSynth
{   
    static constexpr int BLOCK_SIZE{32};
    float squareBuffer[4];
    float sawBuffer[4];
    Osc303 osc;
    AcidFilter filter;
    WowFilter wowFilter;
    SlideFilter slideFilter;

    float vcfDecTime = 1.223;
    float vcaDecTime = 2.0;

    float freq = 0.0;

    float Vcutoff = 3.398;
    float Resonance = 1.0;
    float Envmod = 0.887;
    float Accent = 1.0;

    float A = 2.22;
    float B = 0.31;
    float C = 0.434;
    float D = 0.372;
    float E = 4.549;
    float VaccMul = 2.566;
    inline void setFormulaA(float value) { A = value; }
    inline void setFormulaB(float value) { B = value; }
    inline void setFormulaC(float value) { C = value; }
    inline void setFormulaD(float value) { D = value; }
    inline void setFormulaE(float value) { E = value; }
    inline void setFormulaVaccMul(float value) { VaccMul = value; }

    sst::surgext_rack::dsp::envelopes::ADAREnvelope vca_env;
    sst::surgext_rack::dsp::envelopes::ADAREnvelope vcf_env;

    float OutputLPFFreq = 45630.0;
    float OutputLPResonance = 0.27;

    float sampleRate;

    float note_cv;
    uint8_t wfm = 1; // 1 == saw, 0 == square
    void useSawWaveform() { wfm = 1; d_stdout("Using wfm SAW"); }
    void useSquareWaveform() { wfm = 0; d_stdout("Using wfm PULSE"); }

    inline void setCutoff(float value) { Vcutoff = value; }
    inline void setResonance(float value) { Resonance = value; }
    inline void setEnvmod(float value) { Envmod = value; }
    inline void setAccent(float value) { Accent = value; }
    inline void setDecay(float value) { vcfDecTime = value; }
    inline void setVcaDecay(float value) { vcaDecTime = value; }

    bool gate = false;
    bool accent = false;
    bool slide = false;

    inline void setMidiNote(uint8_t m) { note_cv = (std::clamp((int)m, 12, 72) - 12) / 12.0; }
    inline void slideMidiNote(uint8_t m) { slide = true; note_cv = (std::clamp((int)m, 12, 72) - 12) / 12.0; }

    void gateOn(bool accent) {
        gate = true;
        slide = false;
        this->accent = accent;
        vcf_env.attackFrom(0.0, 3, false, false); // from, shape, isDigital, isGated
        vca_env.attackFrom(0.0, 1, false, false); // from, shape, isDigital, isGated
    }

    void gateOff() {
        gate = false;
    }

    void panic() {
        gate = false;
    }

    void prepare(float sampleRate) {
        this->sampleRate = sampleRate;
        osc.prepare(sampleRate);
        osc.setPitchCV(1.0f);

        vca_env.activate(sampleRate);
        vcf_env.activate(sampleRate);
        wowFilter.prepare(sampleRate);
        slideFilter.prepare(sampleRate);

        filter.prepare(sampleRate, 300.0, 0.66);
    }
    
    float process() {
        vcf_env.process(-9.482, accent ? -2.223 : vcfDecTime, 3, 1, false); // atk, dec, atk shape, dec shape, gate

        float Vacc = wowFilter.processSample(accent ? vcf_env.output * 9.91 * (Accent * 0.15) : 0.0f);
        freq = vcf_env_freq(vcf_env.output, Vcutoff, Envmod, Vacc, A, B, C, D, E, (VaccMul * resToMul(Resonance)));

        if (freq >= (sampleRate * 4.0 * 0.495)) {
            d_stdout("!!!!! limit freq %f", freq);
        }

        if (freq > 80000.0f) {
            d_stdout("Aoutch! %f", freq);
        }

        filter.calcCoeffs(freq, Resonance);

        slideFilter.processSample(note_cv);

        osc.setPitchCV((slide ? slideFilter.lastSample : note_cv));
        osc.process(squareBuffer, sawBuffer, 4);

        float filt;
        if (wfm == 0) filt = filter.processSample(squareBuffer);
        else if (wfm == 1) filt = filter.processSample(sawBuffer);
        else filt = 0.0f;

        vca_env.process(-10.2877, gate ? vcaDecTime : -7.38f, 1, 1, false); // atk, dec, atk shape, dec shape, gate

        float amp = vca_env.output + (accent ? vcf_env.output * 1.2 * Accent : 0.0f);
        return filt * amp;
    }
};
