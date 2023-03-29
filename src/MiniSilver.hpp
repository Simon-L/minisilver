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

inline float linear(float x, float lo_bp, float hi_bp, float lo_y, float hi_y) {
    float Xmapping = 1.0f/(hi_bp - lo_bp);
    float mappedX = Xmapping * (x - lo_bp);
    return (hi_y - lo_y) * mappedX + lo_y;
}

inline float paramLog(float x, float bpx, float bpy, float min, float max) {
    float bpy_mapped = (max - min) * bpy + min;
    if (x < bpx) return linear(x, 0.0f, bpx, min, bpy_mapped);
    else return linear(x, bpx, 1.0f, bpy_mapped, max);
}

static constexpr float cutoffLogBpX{0.5};
static constexpr float cutoffLogBpY{0.1};
static constexpr float cutoffLogMin{0.85};
static constexpr float cutoffLogMax{7.4};

static constexpr float envModLogBpX{0.5};
static constexpr float envModLogBpY{0.1};
static constexpr float envModLogMin{0.25};
static constexpr float envModLogMax{0.887};

inline void configParameter(Parameter* p, uint32_t h,const char * n,const char * s,const char * u,float def,float min,float max) { p->hints = h;  p->name = n;  p->symbol= s;  p->unit = u;  p->ranges.def = def;  p->ranges.min = min;  p->ranges.max = max;}

struct MiniSilverParameters
{
    Parameter properties[kParamCount];

    float values[kParamCount];
    int v_waveform;

    MiniSilverParameters() {
        for (int i = 0; i < kParamCount; ++i)
        {
            values[i] = properties[i].ranges.def;
        }

        configParameter(&properties[kCutoff], kParameterIsAutomatable, "Cutoff frequency", "cutoff_freq", "", 0.5f, 0.0, 1.0); // Cutoff
        configParameter(&properties[kResonance], kParameterIsAutomatable, "Resonance", "resonance", "", 0.5f, 0.0, 1.0); // Resonance
        configParameter(&properties[kEnvMod], kParameterIsAutomatable, "Env Mod", "env_mod", "", 0.5f, 0.0, 1.0); // EnvMod
        configParameter(&properties[kDecay], kParameterIsAutomatable, "Decay", "decay", "", -2.223f, -2.223, 1.223); // Decay
        configParameter(&properties[kAccent], kParameterIsAutomatable, "Accent", "accent", "", 0.5f, 0.0, 1.0); // Accent
        configParameter(&properties[kHoldVca], kParameterIsAutomatable|kParameterIsBoolean, "Hold VCA", "hold_vca", "", 0.0f, 0.0, 1.0); // HoldVca
        configParameter(&properties[kWaveform], kParameterIsAutomatable|kParameterIsBoolean, "Waveform", "waveform", "", 0.0f, 0.0, 1.0); // Waveform
        configParameter(&properties[kTuning], kParameterIsAutomatable, "Tuning", "tuning", "", 0.5f, 0.0, 1.0); // Tuning
        configParameter(&properties[kVcaDec], kParameterIsAutomatable, "VCA Dec", "vca_dec", "", 2.0f, -2.5, 4.0); // VcaDec
    }

    float* get(uint index) {
        if (index >= kParamCount)
            return nullptr;
        return &values[index];
    }

    void set(uint index, float value) {
        if (index >= kParamCount)
            return;
        values[index] = value;
    }
};