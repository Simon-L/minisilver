#include <math.h>
#include <sst/filters/HalfRateFilter.h>
#include "chowdsp_filters/chowdsp_filters.h"

struct AcidFilter {

	float y1{0.0}, y2{0.0}, y3{0.0}, y4{0.0}; // stages
	float a{0.0}; // tuning
	float k{0.0}; // the K
	float rgc{0.0}; // resonance gain compensation
	float Fs{0.0};
	float last_output{0.0};

	float Fc{0.0}, Res{0.0};

	float dL4 alignas(16)[4], dR4 alignas(16)[4]; // L+R arrays of 4 floats for downsampler

	// Using 1st order (?) and steep
	sst::filters::HalfRate::HalfRateFilter hrfUp = sst::filters::HalfRate::HalfRateFilter(1, true);
    sst::filters::HalfRate::HalfRateFilter hrfDn = sst::filters::HalfRate::HalfRateFilter(1, true);

    chowdsp::FirstOrderHPF< float > hpf1; // input DC blocker
    chowdsp::FirstOrderHPF< float > hpf2; // fb filter
    chowdsp::FirstOrderHPF< float > hpf3; // output filter

    juce::dsp::ProcessSpec spec;
    chowdsp::NthOrderFilter<float, 8> OutputLPF;

	float downsample4() {
		hrfDn.process_block_D2(dL4, dR4, 4); // down 4 samples to 2, inplace
		hrfDn.process_block_D2(dL4, dR4, 2); // down 2 samples to 1, inplace
		return dL4[0];
	}

	void prepare(float Sr, float cutoff = 4440.0f, float resonance = 0.75f) {
		// Sr is outside samplerate, internal is 4x;
		Fs = 4 * Sr;
		calcCoeffs(cutoff, resonance);
		hpf1.calcCoefs(50.0f, Fs); // input DC blocker
		hpf2.calcCoefs(200.0f, Fs); // fb filter
		hpf3.calcCoefs(80.0f, Fs); // output filter

		spec.sampleRate = Fs;
		spec.numChannels = 1;
		OutputLPF.prepare(spec);
		OutputLPF.setCutoffFrequency(60000.0f);
		OutputLPF.setQValue(0.5f);
	}

	void setDCBlockerCutoff(float f) {
		hpf1.calcCoefs(f, Fs);
	}

	void setFeedbackCutoff(float f) {
		hpf2.calcCoefs(f, Fs);
	}

	void setOutputCutoff(float f) {
		hpf3.calcCoefs(f, Fs);
	}

	void print() {
		d_stdout("Res %f rgc %f k %f", Res, rgc, k);
	}

	void calcCoeffs(float Fc, float Resonance) {
		this->Fc = Fc;
		Res = Resonance;
		// tuning formulas based on antto's work from KVR Open303 thread
		float fx = Fc/Fs * std::sqrt(2.0);
		a = (fx * M_PI) / (1.0 + fx * 5.6147717 + fx * fx * 2.7919823);
		k = 0.446671158 * (1.0 + a * 2.1717123) / (0.026274774 + -0.12935774 * a * a);

		rgc = (1.0 + Resonance * (k/17.0 - 1.0)); // Resonance Gain Compensation ;P~
		k = k*Resonance; // now K is the feedback level based on the Resonance param
	}

	float processSample(float* x) {
    	float _x;

    	// 4x oversampled filter (based on kunn's filter from KVR Open303 thread)
    	for (int i = 0; i < 4; ++i)
    	{	
			_x = hpf1.processSample(x[i]); // input HPF DC block

    		float fb = _x - k * last_output;
    		fb = std::tanh(fb*rgc)/rgc;
    		fb = hpf2.processSample(fb);

			y1 += 2 * a * (fb - y1 + y2);
			y2 +=  a * (y1 - 2 * y2 + y3);
			y3 +=  a * (y2 - 2 * y3 + y4);
			y4 +=  a * (y3 - 2 * y4);
			last_output = y4 * rgc;

			dL4[i] = hpf3.processSample(last_output);
    	}

    	for (int i = 0; i < 4; ++i)
    	{
    		dL4[i] = OutputLPF.processSample(0, dL4[i]);
    	}

		return downsample4();
	}
	
};