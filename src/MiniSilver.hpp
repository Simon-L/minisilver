enum Parameters {
    kCutoff = 0,
    kResonance,
    kEnvMod,
    kDecay,
    kAccent,
    kHoldVca,
    kWaveform,
    kTuning,
    kVcaDec,
    kParamCount
};

struct MiniSilverParameters
{
    // Parameter(uint32_t h,const char * n,const char * s,const char * u,float def,float min,float max),
    Parameter properties[kParamCount] = {
        Parameter(kParameterIsAutomatable, "Cutoff frequency", "cutoff_freq", "", 0.5f, 0.0, 1.0), // Cutoff
        Parameter(kParameterIsAutomatable, "Resonance", "resonance", "", 0.5f, 0.0, 1.0), // Resonance
        Parameter(kParameterIsAutomatable, "Env Mod", "env_mod", "", 0.5f, 0.0, 1.0), // EnvMod
        Parameter(kParameterIsAutomatable, "Decay", "decay", "", 0.5f, 0.0, 1.0), // Decay
        Parameter(kParameterIsAutomatable, "Accent", "accent", "", 0.5f, 0.0, 1.0), // Accent
        Parameter(kParameterIsAutomatable|kParameterIsBoolean, "Hold VCA", "hold_vca", "", 0.0f, 0.0, 1.0), // HoldVca
        Parameter(kParameterIsAutomatable|kParameterIsBoolean, "Waveform", "waveform", "", 0.0f, 0.0, 1.0), // Waveform
        Parameter(kParameterIsAutomatable, "Tuning", "tuning", "", 0.5f, 0.0, 1.0), // Tuning
        Parameter(kParameterIsAutomatable, "VCA Dec", "vca_dec", "", 0.5f, 0.0, 1.0) // VcaDec
    };

    float values[kParamCount];

    MiniSilverParameters() {
        for (int i = 0; i < kParamCount; ++i)
        {
            values[i] = properties[i].ranges.def;
        }
    }
};