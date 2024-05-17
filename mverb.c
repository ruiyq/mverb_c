#include<math.h>
#include "mverb.h"


//Allpass
void AllpassSetLength(Allpass* allpass_t, int length)
{
	allpass_t->Length = length;
}

void AllpassSetFeedback(Allpass* allpass_t, float feedback)
{
	allpass_t->Feedback = feedback;
}

void AllpassClear(Allpass* allpass_t)
{
	memset(allpass_t->buffer, 0, sizeof(allpass_t->buffer));
	allpass_t->index = 0;
}

float AllpassProcess(Allpass* allpass_t, float input)
{
	float output;
	float bufout;
	bufout = allpass_t->buffer[allpass_t->index];
	float temp = input * -allpass_t->Feedback;
	output = bufout + temp;
	allpass_t->buffer[allpass_t->index] = input + ((bufout + temp) * allpass_t->Feedback);
	if (++allpass_t->index >= allpass_t->Length) allpass_t->index = 0;
	return output;
}

void AllpassInit(Allpass* allpass_t)
{
	AllpassSetLength(allpass_t, 608);
	AllpassClear(allpass_t);
	allpass_t->Feedback = 0.5;
}

//StaticAllpassFourTap
void StaticAllpassFourTapSetIndex(StaticAllpassFourTap *staticAllpassFourTap_t, int Index1, int Index2, int Index3, int Index4)
{
	staticAllpassFourTap_t->index1 = Index1;
	staticAllpassFourTap_t->index2 = Index2;
	staticAllpassFourTap_t->index3 = Index3;
	staticAllpassFourTap_t->index4 = Index4;
}

float StaticAllpassFourTapGetIndex(StaticAllpassFourTap* staticAllpassFourTap_t, int Index)
{
	switch (Index)
	{
	case 0:
		return staticAllpassFourTap_t->buffer[staticAllpassFourTap_t->index1];
		break;
	case 1:
		return staticAllpassFourTap_t->buffer[staticAllpassFourTap_t->index2];
		break;
	case 2:
		return staticAllpassFourTap_t->buffer[staticAllpassFourTap_t->index3];
		break;
	case 3:
		return staticAllpassFourTap_t->buffer[staticAllpassFourTap_t->index4];
		break;
	default:
		return staticAllpassFourTap_t->buffer[staticAllpassFourTap_t->index1];
		break;
	}
}

void StaticAllpassFourTapSetLength(StaticAllpassFourTap* staticAllpassFourTap_t, int length)
{
	staticAllpassFourTap_t->Length = length;
}

void StaticAllpassFourTapClear(StaticAllpassFourTap* staticAllpassFourTap_t)
{
	memset(staticAllpassFourTap_t->buffer, 0, sizeof(staticAllpassFourTap_t->buffer));
	staticAllpassFourTap_t->index1 = 0;
	staticAllpassFourTap_t->index2 = 0;
	staticAllpassFourTap_t->index3 = 0;
	staticAllpassFourTap_t->index4 = 0;
}

void StaticAllpassFourTapSetFeedback(StaticAllpassFourTap* staticAllpassFourTap_t, float feedback)
{
	staticAllpassFourTap_t->Feedback = feedback;
}

float StaticAllpassFourTapProcess(StaticAllpassFourTap* staticAllpassFourTap_t, float input)
{
	float output;
	float bufout;

	bufout = staticAllpassFourTap_t->buffer[staticAllpassFourTap_t->index1];
	float temp = input * -staticAllpassFourTap_t->Feedback;
	output = bufout + temp;
	staticAllpassFourTap_t->buffer[staticAllpassFourTap_t->index1] = input + ((bufout + temp) * staticAllpassFourTap_t->Feedback);

	if (++staticAllpassFourTap_t->index1 >= staticAllpassFourTap_t->Length)
		staticAllpassFourTap_t->index1 = 0;
	if (++staticAllpassFourTap_t->index2 >= staticAllpassFourTap_t->Length)
		staticAllpassFourTap_t->index2 = 0;
	if (++staticAllpassFourTap_t->index3 >= staticAllpassFourTap_t->Length)
		staticAllpassFourTap_t->index3 = 0;
	if (++staticAllpassFourTap_t->index4 >= staticAllpassFourTap_t->Length)
		staticAllpassFourTap_t->index4 = 0;

	return output;
}

void StaticAllpassFourTapInit(StaticAllpassFourTap* staticAllpassFourTap_t)
{
	StaticAllpassFourTapSetLength(staticAllpassFourTap_t, 4271);
	StaticAllpassFourTapClear(staticAllpassFourTap_t);
	staticAllpassFourTap_t->Feedback = 0.5;
}


//StaticDelayLine
void StaticDelayLineSetLength(StaticDelayLine* staticDelayLine_t, int length)
{
	staticDelayLine_t->Length = length;
}

void StaticDelayLineClear(StaticDelayLine* staticDelayLine_t)
{
	memset(staticDelayLine_t->buffer, 0, sizeof(staticDelayLine_t->buffer));
	staticDelayLine_t->index = 0;
}

float StaticDelayLineProcess(StaticDelayLine* staticDelayLine_t, float input)
{
	float output = staticDelayLine_t->buffer[staticDelayLine_t->index];
	staticDelayLine_t->buffer[staticDelayLine_t->index++] = input;
	if (staticDelayLine_t->index >= staticDelayLine_t->Length)
		staticDelayLine_t->index = 0;
	return output;
}

void StaticDelayLineInit(StaticDelayLine* staticDelayLine_t)
{
	StaticDelayLineSetLength(staticDelayLine_t, 4799);
	StaticDelayLineClear(staticDelayLine_t);
}

//StaticDelayLineFourTap
void StaticDelayLineFourTapSetLength(StaticDelayLineFourTap* staticDelayLineFourTap_t, int length)
{
	staticDelayLineFourTap_t->Length = length;
}

void StaticDelayLineFourTapSetIndex(StaticDelayLineFourTap* staticDelayLineFourTap_t, int Index1, int Index2, int Index3, int Index4)
{
	staticDelayLineFourTap_t->index1 = Index1;
	staticDelayLineFourTap_t->index2 = Index2;
	staticDelayLineFourTap_t->index3 = Index3;
	staticDelayLineFourTap_t->index4 = Index4;
}


float StaticDelayLineFourTapGetIndex(StaticDelayLineFourTap* staticDelayLineFourTap_t, int Index)
{
	switch (Index)
	{
	case 0:
		return staticDelayLineFourTap_t->buffer[staticDelayLineFourTap_t->index1];
		break;
	case 1:
		return staticDelayLineFourTap_t->buffer[staticDelayLineFourTap_t->index2];
		break;
	case 2:
		return staticDelayLineFourTap_t->buffer[staticDelayLineFourTap_t->index3];
		break;
	case 3:
		return staticDelayLineFourTap_t->buffer[staticDelayLineFourTap_t->index4];
		break;
	default:
		return staticDelayLineFourTap_t->buffer[staticDelayLineFourTap_t->index1];
		break;
	}
}

void StaticDelayLineFourTapClear(StaticDelayLineFourTap* staticDelayLineFourTap_t)
{
	memset(staticDelayLineFourTap_t->buffer, 0, sizeof(staticDelayLineFourTap_t->buffer));
	staticDelayLineFourTap_t->index1 = 0;
	staticDelayLineFourTap_t->index2 = 0;
	staticDelayLineFourTap_t->index3 = 0;
	staticDelayLineFourTap_t->index4 = 0;
}

float StaticDelayLineFourTapProcess(StaticDelayLineFourTap* staticDelayLineFourTap_t, float input)
{
	float output = staticDelayLineFourTap_t->buffer[staticDelayLineFourTap_t->index1];
	staticDelayLineFourTap_t->buffer[staticDelayLineFourTap_t->index1++] = input;
	if (staticDelayLineFourTap_t->index1 >= staticDelayLineFourTap_t->Length)
		staticDelayLineFourTap_t->index1 = 0;
	if (++staticDelayLineFourTap_t->index2 >= staticDelayLineFourTap_t->Length)
		staticDelayLineFourTap_t->index2 = 0;
	if (++staticDelayLineFourTap_t->index3 >= staticDelayLineFourTap_t->Length)
		staticDelayLineFourTap_t->index3 = 0;
	if (++staticDelayLineFourTap_t->index4 >= staticDelayLineFourTap_t->Length)
		staticDelayLineFourTap_t->index4 = 0;
	return output;
}

void StaticDelayLineFourTapInit(StaticDelayLineFourTap* staticDelayLineFourTap_t)
{
	StaticDelayLineFourTapSetLength(staticDelayLineFourTap_t, 7199);
	StaticDelayLineFourTapClear(staticDelayLineFourTap_t);
}

//StaticDelayLineEightTap
void StaticDelayLineEightTapSetLength(StaticDelayLineEightTap* staticDelayLineEightTap_t, int length)
{
	staticDelayLineEightTap_t->Length = length;
}

void StaticDelayLineEightTapSetIndex(StaticDelayLineEightTap* staticDelayLineEightTap_t, int Index1, int Index2, int Index3, int Index4, int Index5, int Index6, int Index7, int Index8)
{
	staticDelayLineEightTap_t->index1 = Index1;
	staticDelayLineEightTap_t->index2 = Index2;
	staticDelayLineEightTap_t->index3 = Index3;
	staticDelayLineEightTap_t->index4 = Index4;
	staticDelayLineEightTap_t->index5 = Index5;
	staticDelayLineEightTap_t->index6 = Index6;
	staticDelayLineEightTap_t->index7 = Index7;
	staticDelayLineEightTap_t->index8 = Index8;
}

float StaticDelayLineEightTapGetIndex(StaticDelayLineEightTap* staticDelayLineEightTap_t, int Index)
{
	switch (Index)
	{
	case 0:
		return staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index1];
		break;
	case 1:
		return staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index2];
		break;
	case 2:
		return staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index3];
		break;
	case 3:
		return staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index4];
		break;
	case 4:
		return staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index5];
		break;
	case 5:
		return staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index6];
		break;
	case 6:
		return staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index7];
		break;
	case 7:
		return staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index8];
		break;
	default:
		return staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index1];
		break;
	}
}

void StaticDelayLineEightTapClear(StaticDelayLineEightTap * staticDelayLineEightTap_t)
{
	memset(staticDelayLineEightTap_t->buffer, 0, sizeof(staticDelayLineEightTap_t->buffer));
	staticDelayLineEightTap_t->index1 = 0;
	staticDelayLineEightTap_t->index2 = 0;
	staticDelayLineEightTap_t->index3 = 0;
	staticDelayLineEightTap_t->index4 = 0;
	staticDelayLineEightTap_t->index5 = 0;
	staticDelayLineEightTap_t->index6 = 0;
	staticDelayLineEightTap_t->index7 = 0;
	staticDelayLineEightTap_t->index8 = 0;
}

float StaticDelayLineEightTapProcess(StaticDelayLineEightTap* staticDelayLineEightTap_t, float input)
{
	float output = staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index1];
	staticDelayLineEightTap_t->buffer[staticDelayLineEightTap_t->index1++] = input;
	if (staticDelayLineEightTap_t->index1 >= staticDelayLineEightTap_t->Length)
		staticDelayLineEightTap_t->index1 = 0;
	if (++staticDelayLineEightTap_t->index2 >= staticDelayLineEightTap_t->Length)
		staticDelayLineEightTap_t->index2 = 0;
	if (++staticDelayLineEightTap_t->index3 >= staticDelayLineEightTap_t->Length)
		staticDelayLineEightTap_t->index3 = 0;
	if (++staticDelayLineEightTap_t->index4 >= staticDelayLineEightTap_t->Length)
		staticDelayLineEightTap_t->index4 = 0;
	if (++staticDelayLineEightTap_t->index5 >= staticDelayLineEightTap_t->Length)
		staticDelayLineEightTap_t->index5 = 0;
	if (++staticDelayLineEightTap_t->index6 >= staticDelayLineEightTap_t->Length)
		staticDelayLineEightTap_t->index6 = 0;
	if (++staticDelayLineEightTap_t->index7 >= staticDelayLineEightTap_t->Length)
		staticDelayLineEightTap_t->index7 = 0;
	if (++staticDelayLineEightTap_t->index8 >= staticDelayLineEightTap_t->Length)
		staticDelayLineEightTap_t->index8 = 0;
	return output;
}

void StaticDelayLineEightTapInit(StaticDelayLineEightTap* staticDelayLineEightTap_t)
{
	StaticDelayLineEightTapSetLength(staticDelayLineEightTap_t, 4271);
	StaticDelayLineEightTapClear(staticDelayLineEightTap_t);
}

//StateVariable
void StateVariableReset(StateVariable * stateVariable_t)
{
	stateVariable_t->low = 0;
	stateVariable_t->high = 0;
	stateVariable_t->band = 0;
	stateVariable_t->notch = 0;
}

void StateVariableSetSampleRate(StateVariable* stateVariable_t, float sampleRate)
{
	stateVariable_t->sampleRate = sampleRate * 4;
	stateVariable_t->f = 2.0 * sinf(3.141592654 * stateVariable_t->frequency / stateVariable_t->sampleRate);
}

void StateVariableFrequency(StateVariable* stateVariable_t, float frequency)
{
	stateVariable_t->frequency = frequency;
	stateVariable_t->f = 2.0 * sinf(3.141592654 * stateVariable_t->frequency / stateVariable_t->sampleRate);
}

void StateVariableResonance(StateVariable* stateVariable_t, float resonance)
{
	stateVariable_t->q = 2 - 2 * resonance;
}

void StateVariableType(StateVariable* stateVariable_t, int type)
{
	switch (type)
	{
	case LOWPASS:
		stateVariable_t->out = &stateVariable_t->low;
		break;

	case HIGHPASS:
		stateVariable_t->out = &stateVariable_t->high;
		break;

	case BANDPASS:
		stateVariable_t->out = &stateVariable_t->band;
		break;

	case NOTCH:
		stateVariable_t->out = &stateVariable_t->notch;
		break;

	default:
		stateVariable_t->out = &stateVariable_t->low;
		break;
	}
}

float StateVariableProcess(StateVariable* stateVariable_t, float input)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		stateVariable_t->low += stateVariable_t->f * stateVariable_t->band + 1e-25;
		stateVariable_t->high = input - stateVariable_t->low - stateVariable_t->q * stateVariable_t->band;
		stateVariable_t->band += stateVariable_t->f * stateVariable_t->high;
		stateVariable_t->notch = stateVariable_t->low + stateVariable_t->high;
	}
	return *stateVariable_t->out;
}

void StateVariableInit(StateVariable* stateVariable_t)
{
	StateVariableSetSampleRate(stateVariable_t, 44100.);
	StateVariableFrequency(stateVariable_t, 1000.);
	StateVariableResonance(stateVariable_t, 0);
	StateVariableType(stateVariable_t, LOWPASS);
	StateVariableReset(stateVariable_t);
}


//mverb
void mverbInit(mverb* mverb_t)
{
	mverb_t->DampingFreq = 0.9;
	mverb_t->BandwidthFreq = 0.9;
	mverb_t->SampleRate = 44100.;
	mverb_t->Decay = 0.5;
	mverb_t->Gain = 1.;
	mverb_t->Mix = 1.;
	mverb_t->Size = 1.;
	mverb_t->EarlyMix = 1.;
	mverb_t->PreviousLeftTank = 0.;
	mverb_t->PreviousRightTank = 0.;
	mverb_t->PreDelayTime = 100 * (mverb_t->SampleRate / 1000);
	mverb_t->MixSmooth = 0;
	mverb_t->EarlyLateSmooth = 0;
	mverb_t->BandwidthSmooth = 0;
	mverb_t->DampingSmooth = 0;
	mverb_t->PredelaySmooth = 0;
	mverb_t->SizeSmooth = 0;
	mverb_t->DecaySmooth = 0;
	mverb_t->DensitySmooth = 0.;
	mverb_t->ControlRate = mverb_t->SampleRate / 1000;
	mverb_t->ControlRateCounter = 0;
	mverb_t->Density1 = 0.5;
	mverb_t->Density2 = 0.0;
	AllpassInit(&mverb_t->allpass0);
	AllpassInit(&mverb_t->allpass1);
	AllpassInit(&mverb_t->allpass2);
	AllpassInit(&mverb_t->allpass3);
	StaticAllpassFourTapInit(&mverb_t->allpassFourTap0);
	StaticAllpassFourTapInit(&mverb_t->allpassFourTap1);
	StaticAllpassFourTapInit(&mverb_t->allpassFourTap2);
	StaticAllpassFourTapInit(&mverb_t->allpassFourTap3);
	StaticDelayLineInit(&mverb_t->predelay);
	StaticDelayLineFourTapInit(&mverb_t->staticDelayLine0);
	StaticDelayLineFourTapInit(&mverb_t->staticDelayLine1);
	StaticDelayLineFourTapInit(&mverb_t->staticDelayLine2);
	StaticDelayLineFourTapInit(&mverb_t->staticDelayLine3);
	StaticDelayLineEightTapInit(&mverb_t->earlyReflectionsDelayLine0);
	StaticDelayLineEightTapInit(&mverb_t->earlyReflectionsDelayLine1);
	StateVariableInit(&mverb_t->bandwidthFilter[0]);
	StateVariableInit(&mverb_t->bandwidthFilter[1]);
	StateVariableInit(&mverb_t->damping[0]);
	StateVariableInit(&mverb_t->damping[1]);

	mverbReset(mverb_t);
}
void mverbProcess(mverb* mverb_t, float** inputs, float** outputs, int sampleFrames)
{
	float bandwidthLeft, bandwidthRight, earlyReflectionsL, earlyReflectionsR, predelayMonoInput, smearedInput, leftTank, rightTank, accumulatorL, accumulatorR;
	float OneOverSampleFrames = 1. / sampleFrames;
	float MixDelta = (mverb_t->Mix - mverb_t->MixSmooth) * OneOverSampleFrames;
	float EarlyLateDelta = (mverb_t->EarlyMix - mverb_t->EarlyLateSmooth) * OneOverSampleFrames;
	float BandwidthDelta = (((mverb_t->BandwidthFreq * 18400.) + 100.) - mverb_t->BandwidthSmooth) * OneOverSampleFrames;
	float DampingDelta = (((mverb_t->DampingFreq * 18400.) + 100.) - mverb_t->DampingSmooth) * OneOverSampleFrames;
	float PredelayDelta = ((mverb_t->PreDelayTime * 200 * (mverb_t->SampleRate / 1000)) - mverb_t->PredelaySmooth) * OneOverSampleFrames;
	float SizeDelta = (mverb_t->Size - mverb_t->SizeSmooth) * OneOverSampleFrames;
	float DecayDelta = (((0.7995f * mverb_t->Decay) + 0.005) - mverb_t->DecaySmooth) * OneOverSampleFrames;
	float DensityDelta = (((0.7995f * mverb_t->Density1) + 0.005) - mverb_t->DensitySmooth) * OneOverSampleFrames;
	for (int i = 0; i < sampleFrames; ++i) {
		float left = inputs[0][i];
		float right = inputs[1][i];
		mverb_t->MixSmooth += MixDelta;
		mverb_t->EarlyLateSmooth += EarlyLateDelta;
		mverb_t->BandwidthSmooth += BandwidthDelta;
		mverb_t->DampingSmooth += DampingDelta;
		mverb_t->PredelaySmooth += PredelayDelta;
		mverb_t->SizeSmooth += SizeDelta;
		mverb_t->DecaySmooth += DecayDelta;
		mverb_t->DensitySmooth += DensityDelta;
		if (mverb_t->ControlRateCounter >= mverb_t->ControlRate) {
			mverb_t->ControlRateCounter = 0;
			StateVariableFrequency(&mverb_t->bandwidthFilter[0], mverb_t->BandwidthSmooth);
			StateVariableFrequency(&mverb_t->bandwidthFilter[1], mverb_t->BandwidthSmooth);
			StateVariableFrequency(&mverb_t->damping[0], mverb_t->DampingSmooth);
			StateVariableFrequency(&mverb_t->damping[1], mverb_t->DampingSmooth);
		}
		++mverb_t->ControlRateCounter;
		StaticDelayLineSetLength(&mverb_t->predelay, mverb_t->PredelaySmooth);
		mverb_t->Density2 = mverb_t->DecaySmooth + 0.15;
		if (mverb_t->Density2 > 0.5)
			mverb_t->Density2 = 0.5;
		if (mverb_t->Density2 < 0.25)
			mverb_t->Density2 = 0.25;
		StaticAllpassFourTapSetFeedback(&mverb_t->allpassFourTap1, mverb_t->Density2);
		StaticAllpassFourTapSetFeedback(&mverb_t->allpassFourTap3, mverb_t->Density2);
		StaticAllpassFourTapSetFeedback(&mverb_t->allpassFourTap0, mverb_t->Density1);
		StaticAllpassFourTapSetFeedback(&mverb_t->allpassFourTap2, mverb_t->Density1);
		bandwidthLeft = StateVariableProcess(&mverb_t->bandwidthFilter[0], left);
		bandwidthRight = StateVariableProcess(&mverb_t->bandwidthFilter[1], right);
		earlyReflectionsL = StaticDelayLineEightTapProcess(&mverb_t->earlyReflectionsDelayLine0, bandwidthLeft * 0.5 + bandwidthRight * 0.3)
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine0, 2) * 0.6
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine0, 3) * 0.4
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine0, 4) * 0.3
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine0, 5) * 0.3
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine0, 6) * 0.1
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine0, 7) * 0.1
			+ (bandwidthLeft * 0.4 + bandwidthRight * 0.2) * 0.5;
		earlyReflectionsR = StaticDelayLineEightTapProcess(&mverb_t->earlyReflectionsDelayLine1, bandwidthLeft * 0.3 + bandwidthRight * 0.5)
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine1, 2) * 0.6
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine1, 3) * 0.4
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine1, 4) * 0.3
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine1, 5) * 0.3
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine1, 6) * 0.1
			+ StaticDelayLineEightTapGetIndex(&mverb_t->earlyReflectionsDelayLine1, 7) * 0.1
			+ (bandwidthLeft * 0.2 + bandwidthRight * 0.4) * 0.5;
		predelayMonoInput = StaticDelayLineProcess(&mverb_t->predelay, (bandwidthRight + bandwidthLeft) * 0.5f);
		smearedInput = predelayMonoInput;
		/*for (int j = 0; j<4; j++)
			smearedInput = allpass[j](smearedInput);*/
		smearedInput = AllpassProcess(&mverb_t->allpass0, smearedInput);
		smearedInput = AllpassProcess(&mverb_t->allpass1, smearedInput);
		smearedInput = AllpassProcess(&mverb_t->allpass2, smearedInput);
		smearedInput = AllpassProcess(&mverb_t->allpass3, smearedInput);
		leftTank = StaticAllpassFourTapProcess(&mverb_t->allpassFourTap0, smearedInput + mverb_t->PreviousRightTank);
		leftTank = StaticDelayLineFourTapProcess(&mverb_t->staticDelayLine0, leftTank);
		leftTank = StateVariableProcess(&mverb_t->damping[0], leftTank);
		leftTank = StaticAllpassFourTapProcess(&mverb_t->allpassFourTap1, leftTank);
		leftTank = StaticDelayLineFourTapProcess(&mverb_t->staticDelayLine1, leftTank);
		rightTank = StaticAllpassFourTapProcess(&mverb_t->allpassFourTap2, smearedInput + mverb_t->PreviousLeftTank);
		rightTank = StaticDelayLineFourTapProcess(&mverb_t->staticDelayLine2, rightTank);
		rightTank = StateVariableProcess(&mverb_t->damping[1], rightTank);
		rightTank = StaticAllpassFourTapProcess(&mverb_t->allpassFourTap3, rightTank);
		rightTank = StaticDelayLineFourTapProcess(&mverb_t->staticDelayLine3, rightTank);
		mverb_t->PreviousLeftTank = leftTank * mverb_t->DecaySmooth;
		mverb_t->PreviousRightTank = rightTank * mverb_t->DecaySmooth;
		accumulatorL = (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine2, 1))
			+ (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine2, 2))
			- (0.6 * StaticAllpassFourTapGetIndex(&mverb_t->allpassFourTap3, 1))
			+ (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine3, 1))
			- (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine0, 1))
			- (0.6 * StaticAllpassFourTapGetIndex(&mverb_t->allpassFourTap1, 1))
			- (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine1, 1));
		accumulatorR = (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine0, 2))
			+ (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine0, 3))
			- (0.6 * StaticAllpassFourTapGetIndex(&mverb_t->allpassFourTap1, 2))
			+ (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine1, 2))
			- (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine2, 3))
			- (0.6 * StaticAllpassFourTapGetIndex(&mverb_t->allpassFourTap3, 2))
			- (0.6 * StaticDelayLineFourTapGetIndex(&mverb_t->staticDelayLine3, 2));
		accumulatorL = ((accumulatorL * mverb_t->EarlyMix) + ((1 - mverb_t->EarlyMix) * earlyReflectionsL));
		accumulatorR = ((accumulatorR * mverb_t->EarlyMix) + ((1 - mverb_t->EarlyMix) * earlyReflectionsR));
		left = (left + mverb_t->MixSmooth * (accumulatorL - left)) * mverb_t->Gain;
		right = (right + mverb_t->MixSmooth * (accumulatorR - right)) * mverb_t->Gain;
		outputs[0][i] = left;
		outputs[1][i] = right;
	}
}
void mverbReset(mverb* mverb_t)
{
	float SampleRate = mverb_t->SampleRate;
	float Size = mverb_t->Size;
	mverb_t->ControlRateCounter = 0;
	StateVariableSetSampleRate(&mverb_t->bandwidthFilter[0], SampleRate);
	StateVariableSetSampleRate(&mverb_t->bandwidthFilter[1], SampleRate);
	StateVariableReset(&mverb_t->bandwidthFilter[0]);
	StateVariableReset(&mverb_t->bandwidthFilter[1]);
	StateVariableSetSampleRate(&mverb_t->damping[0], SampleRate);
	StateVariableSetSampleRate(&mverb_t->damping[1], SampleRate);
	StateVariableReset(&mverb_t->damping[0]);
	StateVariableReset(&mverb_t->damping[1]);
	StaticDelayLineClear(&mverb_t->predelay);
	StaticDelayLineSetLength(&mverb_t->predelay, mverb_t->PreDelayTime);
	AllpassClear(&mverb_t->allpass0);
	AllpassClear(&mverb_t->allpass1);
	AllpassClear(&mverb_t->allpass2);
	AllpassClear(&mverb_t->allpass3);
	AllpassSetLength(&mverb_t->allpass0, 0.0048 * SampleRate);
	AllpassSetLength(&mverb_t->allpass1, 0.0036 * SampleRate);
	AllpassSetLength(&mverb_t->allpass2, 0.0127 * SampleRate);
	AllpassSetLength(&mverb_t->allpass3, 0.0093 * SampleRate);
	AllpassSetFeedback(&mverb_t->allpass0, 0.75);
	AllpassSetFeedback(&mverb_t->allpass1, 0.75);
	AllpassSetFeedback(&mverb_t->allpass2, 0.625);
	AllpassSetFeedback(&mverb_t->allpass3, 0.625);
	StaticAllpassFourTapClear(&mverb_t->allpassFourTap0);
	StaticAllpassFourTapClear(&mverb_t->allpassFourTap1);
	StaticAllpassFourTapClear(&mverb_t->allpassFourTap2);
	StaticAllpassFourTapClear(&mverb_t->allpassFourTap3);
	StaticAllpassFourTapSetLength(&mverb_t->allpassFourTap0, 0.020 * SampleRate * Size);
	StaticAllpassFourTapSetLength(&mverb_t->allpassFourTap1, 0.060 * SampleRate * Size);
	StaticAllpassFourTapSetLength(&mverb_t->allpassFourTap2, 0.030 * SampleRate * Size);
	StaticAllpassFourTapSetLength(&mverb_t->allpassFourTap3, 0.089 * SampleRate * Size);
	StaticAllpassFourTapSetFeedback(&mverb_t->allpassFourTap0, mverb_t->Density1);
	StaticAllpassFourTapSetFeedback(&mverb_t->allpassFourTap1, mverb_t->Density2);
	StaticAllpassFourTapSetFeedback(&mverb_t->allpassFourTap2, mverb_t->Density1);
	StaticAllpassFourTapSetFeedback(&mverb_t->allpassFourTap3, mverb_t->Density2);
	StaticAllpassFourTapSetIndex(&mverb_t->allpassFourTap0, 0, 0, 0, 0);
	StaticAllpassFourTapSetIndex(&mverb_t->allpassFourTap1, 0, 0.006 * SampleRate * Size, 0.041 * SampleRate * Size, 0);
	StaticAllpassFourTapSetIndex(&mverb_t->allpassFourTap2, 0, 0, 0, 0);
	StaticAllpassFourTapSetIndex(&mverb_t->allpassFourTap3, 0, 0.031 * SampleRate * Size, 0.011 * SampleRate * Size, 0);
	StaticDelayLineFourTapClear(&mverb_t->staticDelayLine0);
	StaticDelayLineFourTapClear(&mverb_t->staticDelayLine1);
	StaticDelayLineFourTapClear(&mverb_t->staticDelayLine2);
	StaticDelayLineFourTapClear(&mverb_t->staticDelayLine3);
	StaticDelayLineFourTapSetLength(&mverb_t->staticDelayLine0, 0.15 * SampleRate * Size);
	StaticDelayLineFourTapSetLength(&mverb_t->staticDelayLine1, 0.12 * SampleRate * Size);
	StaticDelayLineFourTapSetLength(&mverb_t->staticDelayLine2, 0.14 * SampleRate * Size);
	StaticDelayLineFourTapSetLength(&mverb_t->staticDelayLine3, 0.11 * SampleRate * Size);
	StaticDelayLineFourTapSetIndex(&mverb_t->staticDelayLine0, 0, 0.067 * SampleRate * Size, 0.011 * SampleRate * Size, 0.121 * SampleRate * Size);
	StaticDelayLineFourTapSetIndex(&mverb_t->staticDelayLine1, 0, 0.036 * SampleRate * Size, 0.089 * SampleRate * Size, 0);
	StaticDelayLineFourTapSetIndex(&mverb_t->staticDelayLine2, 0, 0.0089 * SampleRate * Size, 0.099 * SampleRate * Size, 0);
	StaticDelayLineFourTapSetIndex(&mverb_t->staticDelayLine3, 0, 0.067 * SampleRate * Size, 0.0041 * SampleRate * Size, 0);
	StaticDelayLineEightTapClear(&mverb_t->earlyReflectionsDelayLine0);
	StaticDelayLineEightTapClear(&mverb_t->earlyReflectionsDelayLine1);
	StaticDelayLineEightTapSetLength(&mverb_t->earlyReflectionsDelayLine0, 0.089 * SampleRate);
	StaticDelayLineEightTapSetIndex(&mverb_t->earlyReflectionsDelayLine0, 0, 0.0199 * SampleRate, 0.0219 * SampleRate, 0.0354 * SampleRate, 0.0389 * SampleRate, 0.0414 * SampleRate, 0.0692 * SampleRate, 0);
	StaticDelayLineEightTapSetLength(&mverb_t->earlyReflectionsDelayLine1, 0.069 * SampleRate);
	StaticDelayLineEightTapSetIndex(&mverb_t->earlyReflectionsDelayLine1, 0, 0.0099 * SampleRate, 0.011 * SampleRate, 0.0182 * SampleRate, 0.0189 * SampleRate, 0.0213 * SampleRate, 0.0431 * SampleRate, 0);
}
void mverbSetParameter(mverb* mverb_t, int index, float value)
{
	float Size;
	float SampleRate = mverb_t->SampleRate;
	switch (index) {
	case DAMPINGFREQ:
		mverb_t->DampingFreq = 1. - value;
		break;
	case DENSITY:
		mverb_t->Density1 = value;
		break;
	case BANDWIDTHFREQ:
		mverb_t->BandwidthFreq = value;
		break;
	case PREDELAY:
		mverb_t->PreDelayTime = value;
		break;
	case SIZE:
		mverb_t->Size = (0.95 * value) + 0.05;
		Size = mverb_t->Size;
		StaticAllpassFourTapClear(&mverb_t->allpassFourTap0);
		StaticAllpassFourTapClear(&mverb_t->allpassFourTap1);
		StaticAllpassFourTapClear(&mverb_t->allpassFourTap2);
		StaticAllpassFourTapClear(&mverb_t->allpassFourTap3);
		StaticAllpassFourTapSetLength(&mverb_t->allpassFourTap0, 0.020 * SampleRate * Size);
		StaticAllpassFourTapSetLength(&mverb_t->allpassFourTap1, 0.060 * SampleRate * Size);
		StaticAllpassFourTapSetLength(&mverb_t->allpassFourTap2, 0.030 * SampleRate * Size);
		StaticAllpassFourTapSetLength(&mverb_t->allpassFourTap3, 0.089 * SampleRate * Size);
		StaticAllpassFourTapSetIndex(&mverb_t->allpassFourTap1, 0, 0.006 * SampleRate * Size, 0.041 * SampleRate * Size, 0);
		StaticAllpassFourTapSetIndex(&mverb_t->allpassFourTap3, 0, 0.031 * SampleRate * Size, 0.011 * SampleRate * Size, 0);
		StaticDelayLineFourTapClear(&mverb_t->staticDelayLine0);
		StaticDelayLineFourTapClear(&mverb_t->staticDelayLine1);
		StaticDelayLineFourTapClear(&mverb_t->staticDelayLine2);
		StaticDelayLineFourTapClear(&mverb_t->staticDelayLine3);
		StaticDelayLineFourTapSetLength(&mverb_t->staticDelayLine0, 0.15 * SampleRate * Size);
		StaticDelayLineFourTapSetLength(&mverb_t->staticDelayLine1, 0.12 * SampleRate * Size);
		StaticDelayLineFourTapSetLength(&mverb_t->staticDelayLine2, 0.14 * SampleRate * Size);
		StaticDelayLineFourTapSetLength(&mverb_t->staticDelayLine3, 0.11 * SampleRate * Size);
		StaticDelayLineFourTapSetIndex(&mverb_t->staticDelayLine0, 0, 0.067 * SampleRate * Size, 0.011 * SampleRate * Size, 0.121 * SampleRate * Size);
		StaticDelayLineFourTapSetIndex(&mverb_t->staticDelayLine1, 0, 0.036 * SampleRate * Size, 0.089 * SampleRate * Size, 0);
		StaticDelayLineFourTapSetIndex(&mverb_t->staticDelayLine2, 0, 0.0089 * SampleRate * Size, 0.099 * SampleRate * Size, 0);
		StaticDelayLineFourTapSetIndex(&mverb_t->staticDelayLine3, 0, 0.067 * SampleRate * Size, 0.0041 * SampleRate * Size, 0);
		break;
	case DECAY:
		mverb_t->Decay = value;
		break;
	case GAIN:
		mverb_t->Gain = value;
		break;
	case MIX:
		mverb_t->Mix = value;
		break;
	case EARLYMIX:
		mverb_t->EarlyMix = value;
		break;
	}
}
void mverbSetSampleRate(mverb* mverb_t, float sr)
{
	mverb_t->SampleRate = sr;
	mverb_t->ControlRate = mverb_t->SampleRate / 1000;
	mverbReset(mverb_t);
}
