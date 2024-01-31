#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <portaudio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define BUFFER_SIZE 1024

typedef struct {
    SNDFILE *sndfile;
    SF_INFO sfinfo;
    PaStream *stream;
} SoundData;

SoundData data;

// Callback function for PortAudio
static int paCallback(const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo *timeInfo,
                      PaStreamCallbackFlags statusFlags, void *userData) {
    SoundData *data = (SoundData *)userData;
    sf_count_t numRead = sf_readf_float(data->sndfile, outputBuffer, framesPerBuffer);

    if (numRead < framesPerBuffer) {
        sf_seek(data->sndfile, 0, SEEK_SET);  // Loop the audio when it reaches the end
    }

    return paContinue;
}

void startDonut(float speed){
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    float Xspeed = speed / 100;
    float Yspeed = Xspeed / 2;
    printf("\x1b[2J");
    while (1) {
        memset(b, 32, 1760);
        memset(z, 0, 7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
        }
        A += Xspeed;
        B += Yspeed;
        usleep(30000);
    }

}

void end(){
    printf("\nCya!\n");
    int err = Pa_StopStream(data.stream);

    if (err != paNoError) {
        fprintf(stderr, "PortAudio stream stopping failed: %s\n", Pa_GetErrorText(err));
    }

    err = Pa_CloseStream(data.stream);

    if (err != paNoError) {
        fprintf(stderr, "PortAudio stream closing failed: %s\n", Pa_GetErrorText(err));
    }

    Pa_Terminate();
    sf_close(data.sndfile);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [speed]\n", argv[0]);
        return 1;
    }
    
    float speed = 8;
    if (argc >= 3) {
        speed = atoi(argv[2]);
    }
    
    data.sndfile = sf_open(argv[1], SFM_READ, &data.sfinfo);

    if (!data.sndfile) {
        fprintf(stderr, "Error opening file: %s\n", sf_strerror(NULL));
        return 1;
    }

    PaError err = Pa_Initialize();

    if (err != paNoError) {
        fprintf(stderr, "PortAudio initialization failed: %s\n", Pa_GetErrorText(err));
        sf_close(data.sndfile);
        return 1;
    }

    err = Pa_OpenDefaultStream(&data.stream, 0, data.sfinfo.channels, paFloat32,
                               data.sfinfo.samplerate, BUFFER_SIZE, paCallback, &data);

    if (err != paNoError) {
        fprintf(stderr, "PortAudio stream opening failed: %s\n", Pa_GetErrorText(err));
        sf_close(data.sndfile);
        Pa_Terminate();
        return 1;
    }

    err = Pa_StartStream(data.stream);

    if (err != paNoError) {
        fprintf(stderr, "PortAudio stream starting failed: %s\n", Pa_GetErrorText(err));
        sf_close(data.sndfile);
        Pa_CloseStream(data.stream);
        Pa_Terminate();
        return 1;
    }
    
    /* if pressed CTRL+C (aka interrupt) it will execute the void end and free memory */
    signal(SIGINT, end);
    signal(SIGTERM, end);
    
    startDonut(speed);

    return 0;
}
