#include "chowdsp_wdf/chowdsp_wdf.h"

namespace wdft = chowdsp::wdft;
struct WowFilter {

	float R = 0.0;

	wdft::ResistorT<double> Rpot { (1 - R) * 50.0e3 };
	wdft::ResistorT<double> Rin { 47e3 + R * 50.0e3 };
	wdft::CapacitorT<double> C1 { 1e-6 };

	wdft::ResistorT<double> Rout { 102e3 };
	
	wdft::WDFSeriesT<double, decltype (C1), decltype (Rpot)> s2{ C1, Rpot };
	wdft::WDFParallelT<double, decltype (s2), decltype (Rout)> p1{ s2, Rout };
	wdft::WDFSeriesT<double, decltype (p1), decltype (Rin)> s1{ p1, Rin };

	wdft::IdealVoltageSourceT<double, decltype (s1)> vEnv { s1 };
   
	double lastSample;

	bool prepared = false;
	void prepare (double sampleRate) {
		C1.prepare (sampleRate);
		prepared = true;
	}

	void setResonancePot(float wiper) {
		R = std::clamp((double)wiper, 0.001, 0.999);
		Rpot.setResistanceValue((1 - R) * 50.0e3);
		Rin.setResistanceValue(47e3 + R * 50.0e3);
	}
	
	inline double processSample (double x) {
		vEnv.setVoltage (x);

		vEnv.incident (s1.reflected());
		s1.incident (vEnv.reflected());

		lastSample = -1.0f * wdft::voltage<double> (Rout);
		return lastSample;
	}
};