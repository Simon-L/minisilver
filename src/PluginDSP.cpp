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
}

void PluginDSP::initParameter(uint32_t index, Parameter& parameter)
{
    switch (index) {
    case kParamGain:
        parameter.ranges.min = -90.0f;
        parameter.ranges.max = 30.0f;
        parameter.ranges.def = -0.0f;
        parameter.hints = kParameterIsAutomatable;
        parameter.name = "Gain";
        parameter.shortName = "Gain";
        parameter.symbol = "gain";
        parameter.unit = "dB";
        return;
    case kParamD:
        parameter.hints = kParameterIsOutput;
        return;
    }
}

float PluginDSP::getParameterValue(uint32_t index) const
{
    switch (index) {
    case kParamD:
        return 0.314f;
    case kParamGain:
        return fGainDB;
    }
    return 0.0;
}

void PluginDSP::setParameterValue(uint32_t index, float value)
{
    switch (index) {
    case kParamGain:
        fGainDB = value;
        fGainLinear = DB_CO(CLAMP(value, -90.0, 30.0));
        return;
    }
}

void PluginDSP::activate()
{
    fSmoothGain->flush();
}

void PluginDSP::run(const float** inputs, float** outputs, uint32_t frames)
{
    // get the left and right audio inputs
    const float* const inpL = inputs[0];
    const float* const inpR = inputs[1];

    // get the left and right audio outputs
    float* const outL = outputs[0];
    float* const outR = outputs[1];

    // apply gain against all samples
    for (uint32_t i=0; i < frames; ++i)
    {
        const float gain = fSmoothGain->process(fGainLinear);
        outL[i] = inpL[i] * gain;
        outR[i] = inpR[i] * gain;
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

const char* PluginDSP::getLabel() const noexcept {return "__DPFLABEL__";}
const char* PluginDSP::getDescription() const {return "__DPFDESCRIPTION__";}
const char* PluginDSP::getLicense() const noexcept {return "ISC";}
const char* PluginDSP::getMaker() const noexcept {return "Jean Pierre Cimalando, falkTX, __YOURNAME__";}
uint32_t PluginDSP::getVersion() const noexcept {return d_version(1, 0, 0);}
int64_t PluginDSP::getUniqueId() const noexcept {return d_cconst('a', 'b', 'c', 'd');}

// --------------------------------------------------------------------------------------------------------------------

Plugin* createPlugin()
{
    return new PluginDSP();
}

// --------------------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
