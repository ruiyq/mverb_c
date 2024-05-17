#pragma once

enum
{
	DAMPINGFREQ = 0,
	DENSITY,
	BANDWIDTHFREQ,
	DECAY,
	PREDELAY,
	SIZE,
	GAIN,
	MIX,
	EARLYMIX,
	NUM_PARAMS
};


typedef struct {
	float buffer[609];	//max delay 0.0127s for 48k
	int index;
	int Length;
	float Feedback;
}Allpass;

typedef struct {
	float buffer[4272];	//max delay 0.089s for 48k
	int index1, index2, index3, index4;
	int Length;
	float Feedback;
}StaticAllpassFourTap;

typedef struct {
	float buffer[4800];	//max delay 0.1s for 48k
	int index;
	int Length;
	float Feedback;
}StaticDelayLine;

typedef struct {
	float buffer[7200];	//max delay 0.15s for 48k
	int index1, index2, index3, index4;
	int Length;
	float Feedback;
}StaticDelayLineFourTap;

typedef struct {
	float buffer[4272];	//max delay 0.089s for 48k
	int index1, index2, index3, index4, index5, index6, index7, index8;
	int Length;
	float Feedback;
}StaticDelayLineEightTap;

enum FilterType
{
	LOWPASS,
	HIGHPASS,
	BANDPASS,
	NOTCH,
	FilterTypeCount
};

typedef struct {
	float sampleRate;
	float frequency;
	float q;
	float f;

	float low;
	float high;
	float band;
	float notch;

	float* out;
}StateVariable;

typedef struct {
	Allpass allpass0;							//0.0048s for 48k
	Allpass allpass1;							//0.0036s
	Allpass allpass2;							//0.0127s
	Allpass allpass3;							//0.0093s

	StaticAllpassFourTap allpassFourTap0;		//0.020s
	StaticAllpassFourTap allpassFourTap1;		//0.060s
	StaticAllpassFourTap allpassFourTap2;		//0.030s
	StaticAllpassFourTap allpassFourTap3;		//0.089s
	StateVariable bandwidthFilter[2];
	StateVariable damping[2];
	StaticDelayLine predelay;					//max delay 100ms
	
	StaticDelayLineFourTap staticDelayLine0;	//0.15s
	StaticDelayLineFourTap staticDelayLine1;	//0.12s
	StaticDelayLineFourTap staticDelayLine2;	//0.14s
	StaticDelayLineFourTap staticDelayLine3;	//0.11s
	
	StaticDelayLineEightTap earlyReflectionsDelayLine0;		//0.089s
	StaticDelayLineEightTap earlyReflectionsDelayLine1;		//0.069s
	float SampleRate, DampingFreq, Density1, Density2, BandwidthFreq, PreDelayTime, Decay, Gain, Mix, EarlyMix, Size;
	float MixSmooth, EarlyLateSmooth, BandwidthSmooth, DampingSmooth, PredelaySmooth, SizeSmooth, DensitySmooth, DecaySmooth;
	float PreviousLeftTank, PreviousRightTank;
	int ControlRate, ControlRateCounter;
}mverb;

void mverbInit(mverb* mverb_t);
void mverbProcess(mverb* mverb_t, float** inputs, float** outputs, int sampleFrames);
void mverbReset(mverb* mverb_t);
void mverbSetParameter(mverb* mverb_t, int index, float value);
void mverbSetSampleRate(mverb* mverb_t, float sr);