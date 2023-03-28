#include <cmath>

inline float vcf_env_freq(float vcf_env, float Vco, float Vmod_amt, float Vacc, float A, float B, float C, float D, float E, float VaccMul) {
    float Vmod_scale = 6.9*Vmod_amt+1.3;
    float Vmod_bias = -1.2*Vmod_amt+3;
    float Vmod = (Vmod_scale * vcf_env + Vmod_bias) - 3.2f; // 3.2 == Q9 bias
    // guest formula
    // Ic,11 = (A*Vco + B)*e^(C*Vmod + D*Vacc +E)
    return (A * Vco + B) * std::exp(C * Vmod + D * (Vacc * VaccMul) + E); // + D * Vacc
}

inline float segment(float x, float lo_bp, float hi_bp, float lo_fac, float hi_fac) {
    float Xmapping = 1.0f/(hi_bp - lo_bp);
    float mappedX = Xmapping * (x - lo_bp);
    return (hi_fac - lo_fac) * mappedX + lo_fac;
}

inline float resToMul(float x) {
    float fac0 = 0.236;
    float fac1 = 0.389;
    float fac2 = 1.0;
    float bp0 = 0.0;
    float bp1 = 0.818;
    float bp2 = 1.0;
    if (x < bp1) return segment(x, bp0, bp1, fac0, fac1);
    else return segment(x, bp1, bp2, fac1, fac2);
}