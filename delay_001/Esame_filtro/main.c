//
//  main.c
//  Esame_filtro
//
//  Created by Guglielmo Diana on 04/10/19.
//  Copyright © 2019 Guglielmo Diana. All rights reserved.
//

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define delay
#define normalize

/*
void in(int s, double *array, double (fn)(double));
void out(int s, double *array, double (fn)(double));
*/
// SERVE MALLOC, documentati!

//#define OUTPUT_FOR_COLL


#define OUTPUT_FOR_BACH_READ
#define SIZE_IN_SECONDS 2

#ifdef delay
#define DELAY_IN_SECONDS 0.5 // change this
#else
#define DELAY_IN_SECONDS 0 // DON'T CHANGE THIS
#endif


#define SAMPLE_RATE 44100
#define SIZE_IN_SAMPS ((int)(SIZE_IN_SECONDS * SAMPLE_RATE))
#define DELAY_IN_SAMPS ((int)(DELAY_IN_SECONDS * SAMPLE_RATE))
#define OUTPUT_IN_SAMPS (SIZE_IN_SAMPS + DELAY_IN_SAMPS)

void print_buffer(double* buffer, int size);

int main(int argc, const char * argv[]) {

    double *in;
    int i;
    double *out;
    
    in = (double *) malloc(SIZE_IN_SAMPS * sizeof(double)); //riserva una porzione di memoria per il programma di SIZE_IN_SAMPS per la dimensione di un numero double (8byte =64 bit)
    
    out = (double *) malloc(OUTPUT_IN_SAMPS * sizeof(double));
    
    double freqi = 100; //frequency 1
    double freqii = 250; //frequency 2
    
    for(i = 0; i < SIZE_IN_SAMPS; i++) {
        double fvar = freqi + ((freqii - freqi) * ((double)i/(double)SIZE_IN_SAMPS)); //interpolation of the glissato frequency in relation to sample rate
        
        double time_in_sec = (double)i/(double)SAMPLE_RATE;
        in[i] = sin(2 * M_PI * fvar * time_in_sec);
    }
    
    //print_buffer(in, SIZE_IN_SAMPS);

   ///////// delay /////////
    
    
#ifdef delay
    for(i = 0; i < DELAY_IN_SAMPS; i++){
        out[i] = in[i];
    }
    for( ; i < SIZE_IN_SAMPS; i++){
        out[i] = in[i] + in[ i - DELAY_IN_SAMPS ];
    }
    for( ; i < OUTPUT_IN_SAMPS; i++){
        out[i] = in[i - DELAY_IN_SAMPS];
    }
#else
    
    for (i = 0; i < SIZE_IN_SAMPS; i++) {
        out[i] = in[i];
    }
    
#endif


    
    /////////// normalize out ///////////
    
#ifdef normalize
    double c = 0;
    for(i = DELAY_IN_SAMPS; i < SIZE_IN_SAMPS; i++){
        double d = fabs(out[i]); //absolute value
        if(c < d){
            c = d; // finding the maximum value in absolute means
        }
    }
    for(i = 0; i < OUTPUT_IN_SAMPS; i++){
        out[i] = out[i] / c;//multiply all the array with 1/c
    }
    /*
    printf("normalized values\n");
    for (i = 0; i < s + a; i++){
        printf("%f ", out[i]);
    }
    printf("\n");
    */
#endif normalize
    print_buffer(out, OUTPUT_IN_SAMPS);
    
    free(in);
    free(out);//de-allocare la memoria
    
    return 0;
}

void print_buffer(double* buffer, int size)
{
    int i;
    for (i = 0; i < size; i++){
#ifdef OUTPUT_FOR_COLL
        printf("%d, %f;\n", i, buffer[i]);
#endif // OUTPUT_FOR_COLL
        
#ifdef OUTPUT_FOR_BACH_READ
        printf("%f ", buffer[i]);
#endif // OUTPUT_FOR_BACH_READ
    }
    printf("\n \n");
}
