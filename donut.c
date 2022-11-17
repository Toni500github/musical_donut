#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vlc/vlc.h>

int main(int argc, char* argv[]) 
{
    libvlc_instance_t * inst;
    libvlc_media_player_t *mp;
    libvlc_media_t *m;
     
    /* Load the VLC engine */
    inst = libvlc_new (0, NULL);
    
    printf("Enter the name of the music you would like to play: ");
    char file_name[256];
    scanf("%256s", &file_name);
    printf("%s\n", file_name);
    m = libvlc_media_new_path (inst, file_name);

    /* Create a media player playing environement */
    mp = libvlc_media_player_new_from_media (m);

    /* No need to keep the media now */
    libvlc_media_release (m);
     
    /* play the media_player */
    libvlc_media_player_play (mp);
    
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    float input;
    printf("Insert speed: ");
    scanf("%f", &input);
    float Xspeed = 7.044 / pow(10, input);
    float Yspeed = 3.522 / pow(10, input);
    printf("\n%f\n", Xspeed);
    printf("\x1b[2J");
    for(;;) {
        memset(b,32,1760);
        memset(z,0,7040);
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
                int y= 12 + 15 * D * (l * h * n + t * m);
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

    /* Stop playing */
    libvlc_media_player_stop (mp);

    /* Free the media_player */
    libvlc_media_player_release (mp);    

    libvlc_release (inst);
     
    return 0;
}