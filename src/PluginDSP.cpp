/*
 * ImGui plugin example
 * Copyright (C) 2021 Jean Pierre Cimalando <jp-dev@inbox.ru>
 * Copyright (C) 2021-2022 Filipe Coelho <falktx@falktx.com>
 * SPDX-License-Identifier: ISC
 */
#include "PluginDSP.hpp"

START_NAMESPACE_DISTRHO

PluginDSP::PluginDSP()
    : Plugin(kParamCount, 0, 0) // parameters, programs, states
{
    for (int i = 0; i < kParamCount; ++i)
    {
        d_stdout("DSP %d -> %s (%s)", i, params.properties[i].name.buffer(), params.properties[i].symbol.buffer());
    }
}

void PluginDSP::activate()
{
    fSmoothGain->flush();
}

void PluginDSP::run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount)
{

    // get the left and right audio outputs
    float* const outL = outputs[0];
    float* const outR = outputs[1];

    // apply gain against all samples
    for (uint32_t i=0; i < frames; ++i)
    {
        const float gain = fSmoothGain->process(fGainLinear);
        outL[i] = 0.0 * gain;
        outR[i] = 0.0 * gain;
    }
}

void PluginDSP::sampleRateChanged(double newSampleRate)
{
    fSampleRate = newSampleRate;
    fSmoothGain->setSampleRate(newSampleRate);
}

int PluginDSP::publicMethod()
{
    return 42;
}

// --------------------------------------------------------------------------------------------------------------------

Plugin* createPlugin()
{
    return new PluginDSP();
}

// --------------------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
