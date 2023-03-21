#include "chowdsp_wdf/chowdsp_wdf.h"

namespace wdft = chowdsp::wdft;
struct SlideFilter {
	wdft::ResistorT<double> r1 { 100.0e3 };
	wdft::CapacitorT<double> c1 { .22e-6 };
	
	wdft::WDFSeriesT<double, decltype (r1), decltype (c1)> s1 { r1, c1 };
	wdft::IdealVoltageSourceT<double, decltype (s1)> vSource { s1 };
   
	double lastSample;

	void setRackParameters(float rMod, float cMod) {
		float newR = 100.0e3 + 99.9e3 * rMod;
		float newC = 220e-9 + 219.9e-9 * cMod;
		r1.setResistanceValue(newR);
		c1.setCapacitanceValue(newC);
	}

	bool prepared = false;
	void prepare (double sampleRate) {
		c1.prepare (sampleRate);
		prepared = true;
	}
	
	inline double processSample (double x) {
		vSource.setVoltage (x);

		vSource.incident (s1.reflected());
		s1.incident (vSource.reflected());

		lastSample = -1 * wdft::voltage<double> (c1);
		return lastSample;
	}
};