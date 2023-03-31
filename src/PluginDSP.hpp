#include "DistrhoPlugin.hpp"
#include "CParamSmooth.hpp"

#include "MiniSilver.hpp"

#include "303/AcidSynth.hpp"

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
    double fSampleRate = getSampleRate();
    // std::unique_ptr<CParamSmooth> fSmoothGain = std::make_unique<CParamSmooth>(20.0f, fSampleRate);

    MiniSilverParameters params;

    AcidSynth synth;

public:
/**
Plugin class constructor.@n
You must set all parameter values to their defaults, matching ParameterRanges::def.
*/
    PluginDSP();

    int publicMethod();
protected:
// ----------------------------------------------------------------------------------------------------------------
// Init

// void initAudioPort(bool input, uint32_t index, AudioPort& port) override;
// void initPortGroup(uint32_t groupId, PortGroup& portGroup) override;

/**
Initialize the parameter @a index.@n
This function will be called once, shortly after the plugin is created.
*/
    void initParameter(uint32_t index, Parameter& parameter) override;

// ----------------------------------------------------------------------------------------------------------------
// Internal data

/**
Get the current value of a parameter.@n
The host may call this function from any context, including realtime processing.
*/
    float getParameterValue(uint32_t index) const override;

/**
Change a parameter value.@n
The host may call this function from any context, including realtime processing.@n
When a parameter is marked as automatable, you must ensure no non-realtime operations are performed.
@note This function will only be called for parameter inputs.
*/
    void setParameterValue(uint32_t index, float value) override;

// ----------------------------------------------------------------------------------------------------------------
// Audio/MIDI Processing

    bool accent = false;
    int nextGateOff = -1;
    void handleMidi(const MidiEvent* event);

/**
Activate this plugin.
*/
    void activate() override;

/**
Run/process function for plugins without MIDI input.
@note Some parameters might be null if there are no audio inputs or outputs.
*/
    void run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount) override;

// ----------------------------------------------------------------------------------------------------------------
// Callbacks (optional)

/**
Optional callback to inform the plugin about a sample rate change.@n
This function will only be called when the plugin is deactivated.
@see getSampleRate()
*/
    void sampleRateChanged(double newSampleRate) override;

// ----------------------------------------------------------------------------------------------------------------

// Information
/**
Get the plugin label.@n
This label is a short restricted name consisting of only _, a-z, A-Z and 0-9 characters.
*/
    const char* getLabel() const noexcept override;
/**
Get an extensive comment/description about the plugin.@n
Optional, returns nothing by default.
*/
    const char* getDescription() const override;
/**
Get the plugin author/maker.
*/
    const char* getMaker() const noexcept override;
/**
Get the plugin license (a single line of text or a URL).@n
For commercial plugins this should return some short copyright information.
*/
    const char* getLicense() const noexcept override;
/**
Get the plugin version, in hexadecimal.
@see d_version()
*/
    uint32_t getVersion() const noexcept override;
/**
Get the plugin unique Id.@n
This value is used by LADSPA, DSSI and VST plugin formats.
@see d_cconst()
*/
    int64_t getUniqueId() const noexcept override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginDSP)
};

END_NAMESPACE_DISTRHO
