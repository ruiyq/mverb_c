#include<stdio.h>
#include<stdlib.h>
#include "mverb.h"

#define BLOCKSIZE 512
int main(int argc, char* argv[])
{
	FILE* fin, *fout;
	short inOut[2 * BLOCKSIZE];
	float ptr[2][BLOCKSIZE];
	float *buf[2];
	char header[46];
	int ch = 2;

	buf[0] = ptr[0];
	buf[1] = ptr[1];

	fin = fopen(argv[1], "rb"); 
	fread(header, 1, 44, fin);
	fout = fopen(argv[2], "wb");
	fwrite(header, 1, 44, fout);

	mverb mverb;
	mverbInit(&mverb);
	mverbSetSampleRate(&mverb, 44100);
	mverbSetParameter(&mverb, DAMPINGFREQ, 0.0);
	mverbSetParameter(&mverb, DENSITY, 0.5);
	mverbSetParameter(&mverb, BANDWIDTHFREQ, 1.0);
	mverbSetParameter(&mverb, DECAY, 0.5);
	mverbSetParameter(&mverb, PREDELAY, 0.0);
	mverbSetParameter(&mverb, SIZE, 0.63);
	mverbSetParameter(&mverb, MIX, 0.35);
	mverbSetParameter(&mverb, EARLYMIX, 0.68);
	mverbSetParameter(&mverb, GAIN, 1.0);

	int sample_num;
	while (1) {
		sample_num = fread(inOut, sizeof(short), BLOCKSIZE * ch, fin);
		if (sample_num == 0)
			break;

		for (int i = 0; i < sample_num / ch; i++) {
			buf[0][i] = inOut[2 * i] / 32768.0;
			buf[1][i] = inOut[2 * i + 1] / 32768.0;
		}

		mverbProcess(&mverb, &buf[0], &buf[0], sample_num / ch);

		for (int i = 0; i < sample_num / ch; i++) {
			inOut[2 * i] = buf[0][i] * 32768;
			inOut[2 * i + 1] = buf[1][i] * 32768;
		}

		fwrite(inOut, sizeof(short), sample_num, fout);

	}

	fclose(fin);
	fclose(fout);

	printf("hello world!\n");

	return 0;
}