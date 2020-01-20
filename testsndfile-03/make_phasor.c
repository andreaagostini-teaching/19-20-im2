/*
** Copyright (C) 1999-2012 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in
**       the documentation and/or other materials provided with the
**       distribution.
**     * Neither the author nor the names of any contributors may be used
**       to endorse or promote products derived from this software without
**       specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
** ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<math.h>

#include	<sndfile.h>

#ifndef		M_PI
#define		M_PI		3.14159265358979323846264338
#endif

#define     SECONDS             10
#define		SAMPLE_RATE			44100
#define		SAMPLE_COUNT		(SAMPLE_RATE * SECONDS)
#define		AMPLITUDE			1.0
#define		FREQ			    440.
#define     STEP                (FREQ / SAMPLE_RATE)

int main(void)
{
    SNDFILE	*file;
	SF_INFO	sfinfo;
	double	*buffer;

    buffer = malloc(SAMPLE_COUNT * sizeof(double));
                    
	if (buffer == NULL) {
        printf ("Error: Malloc failed.\n");
		return 1;
    }

	memset(&sfinfo, 0, sizeof(sfinfo));

	sfinfo.samplerate	= SAMPLE_RATE;
	sfinfo.frames		= SAMPLE_COUNT;
	sfinfo.channels		= 1;
	sfinfo.format		= (SF_FORMAT_WAV | SF_FORMAT_PCM_24);

	if (!(file = sf_open("/Users/andreaagostini/Dropbox/SMET/im2_1920/testsndfile-03/sine.wav", SFM_WRITE, &sfinfo))) {
        printf("Error : Not able to open output file.\n");
		free(buffer);
		return 1;
    }

    // homework (daft punk)
    // come controllo l'ampiezza del phasor?
    buffer[0] = 0;
    for (int k = 1; k < SAMPLE_COUNT; k++) {
        buffer[k] = fmod(buffer[k-1] + STEP, 1.);
    }
    
	if (sf_write_double(file, buffer, SAMPLE_COUNT) != SAMPLE_COUNT)
		puts(sf_strerror(file));

	sf_close(file);
	free(buffer);
	return 0;
} /* main */

