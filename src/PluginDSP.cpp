/*
 * ImGui plugin example
 * Copyright (C) 2021 Jean Pierre Cimalando <jp-dev@inbox.ru>
 * Copyright (C) 2021-2022 Filipe Coelho <falktx@falktx.com>
 * SPDX-License-Identifier: ISC
 */

#include "DistrhoPlugin.hpp"
#include "CParamSmooth.hpp"

#include <memory>

// --------------------------------------------------------------------------------------------------------------------

#ifndef MIN
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )
#endif

#ifndef MAX
#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#endif

#ifndef CLAMP
#define CLAMP(v, min, max) (MIN((max), MAX((min), (v))))
#endif

#ifndef DB_CO
#define DB_CO(g) ((g) > -90.0f ? powf(10.0f, (g) * 0.05f) : 0.0f)
#endif

START_NAMESPACE_DISTRHO

// --------------------------------------------------------------------------------------------------------------------

class PluginDSP : public Plugin
{
    enum Parameters {
        kParamGain = 0,
        kParamA,
        kParamB,
        kParamC,
        kParamD,
        kParamCount
    };

    double fSampleRate = getSampleRate();
    float fGainDB = 0.0f;
    float fGainLinear = 1.0f;
    std::unique_ptr<CParamSmooth> fSmoothGain = std::make_unique<CParamSmooth>(20.0f, fSampleRate);

public:
   /**
      Plugin class constructor.@n
      You must set all parameter values to their defaults, matching ParameterRanges::def.
    */
    PluginDSP()
        : Plugin(kParamCount, 0, 0) // parameters, programs, states
    {
    }

protected:
    // ----------------------------------------------------------------------------------------------------------------
    // Init

   /**
      Initialize the parameter @a index.@n
      This function will be called once, shortly after the plugin is created.
    */
    void initParameter(uint32_t index, Parameter& parameter) override
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

    // ----------------------------------------------------------------------------------------------------------------
    // Internal data

   /**
      Get the current value of a parameter.@n
      The host may call this function from any context, including realtime processing.
    */
    float getParameterValue(uint32_t index) const override
    {
        switch (index) {
        case kParamD:
            return 0.314f;
        case kParamGain:
            return fGainDB;
        }
    }

   /**
      Change a parameter value.@n
      The host may call this function from any context, including realtime processing.@n
      When a parameter is marked as automatable, you must ensure no non-realtime operations are performed.
      @note This function will only be called for parameter inputs.
    */
    void setParameterValue(uint32_t index, float value) override
    {
        switch (index) {
        case kParamGain:
            fGainDB = value;
            fGainLinear = DB_CO(CLAMP(value, -90.0, 30.0));
            return;
        }
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Audio/MIDI Processing

   /**
      Activate this plugin.
    */
    void activate() override
    {
        fSmoothGain->flush();
    }

   /**
      Run/process function for plugins without MIDI input.
      @note Some parameters might be null if there are no audio inputs or outputs.
    */
    void run(const float** inputs, float** outputs, uint32_t frames) override
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

    // ----------------------------------------------------------------------------------------------------------------
    // Callbacks (optional)

   /**
      Optional callback to inform the plugin about a sample rate change.@n
      This function will only be called when the plugin is deactivated.
      @see getSampleRate()
    */
    void sampleRateChanged(double newSampleRate) override
    {
        fSampleRate = newSampleRate;
        fSmoothGain->setSampleRate(newSampleRate);
    }

    // ----------------------------------------------------------------------------------------------------------------
    
    // Information
    /**
       Get the plugin label.@n
       This label is a short restricted name consisting of only _, a-z, A-Z and 0-9 characters.
     */
     const char* getLabel() const noexcept override {return "__DPFLABEL__";}
    /**
       Get an extensive comment/description about the plugin.@n
       Optional, returns nothing by default.
     */
     const char* getDescription() const override {return "__DPFDESCRIPTION__";}
    /**
       Get the plugin author/maker.
     */
     const char* getMaker() const noexcept override {return "Jean Pierre Cimalando, falkTX, __YOURNAME__";}
    /**
       Get the plugin license (a single line of text or a URL).@n
       For commercial plugins this should return some short copyright information.
     */
     const char* getLicense() const noexcept override {return "ISC";}
    /**
       Get the plugin version, in hexadecimal.
       @see d_version()
     */
     uint32_t getVersion() const noexcept override {return d_version(1, 0, 0);}
    /**
       Get the plugin unique Id.@n
       This value is used by LADSPA, DSSI and VST plugin formats.
       @see d_cconst()
     */
     int64_t getUniqueId() const noexcept override {return d_cconst('a', 'b', 'c', 'd');}

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginDSP)
};

// --------------------------------------------------------------------------------------------------------------------

Plugin* createPlugin()
{
    return new PluginDSP();
}

// --------------------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
