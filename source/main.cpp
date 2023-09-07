#include <switch.h>

#include <stdio.h>
#include <string>

#define DIGIT_RANGE 10
#define OEM_DAY_RANGE 367

bool gen;
bool display_keys;

int oem_key_year[2];
int oem_key_5[5];
int oem_key_5_random[5];
int retail_key_1[3];
int retail_key_2[7];

int oem_key_day;
int digit;
int sum7;

int sw_clock;

using namespace std;

void gen_oem_day() {
    gen = true;
    while(gen)  {
        oem_key_day = rand() % OEM_DAY_RANGE;

        if(oem_key_day == 0) {
            gen = true;
        } else {
            gen = false;
        }
    }
}

void gen_oem_year() {
    gen = true;
    while(gen)  {
        for(digit=0; digit<2; ++digit)
            oem_key_year[digit] = rand() % DIGIT_RANGE;

        if(
            (oem_key_year[0] == 9 && oem_key_year[1] >= 5) || 
            (oem_key_year[0] == 0 && oem_key_year[1] < 3)
        ) {
            gen = false;
        } else {
            gen = true;
        }
    }
}

void gen_5digits_oem() {
    gen = true;
    while(gen) {
        for(digit=0; digit<5; ++digit)
        oem_key_5[digit] = rand() % DIGIT_RANGE;

        sum7 = oem_key_5[0] + oem_key_5[1] + oem_key_5[2] + oem_key_5[3] + oem_key_5[4];

        if(sum7 % 7 == 0) {
            gen = false;
        } else {
            gen = true;
        }
    }
}

void gen_5digits_random_oem() {
    for(digit=0; digit<5; ++digit)
        oem_key_5_random[digit] = rand() % DIGIT_RANGE;   
}

void gen_3digits_retail() {
    gen = true;
    while(gen) {
        for(digit=0; digit<3; ++digit)
            retail_key_1[digit] = rand() % DIGIT_RANGE;

        if(
            (retail_key_1[0] == 3 && retail_key_1[1] == 3 && retail_key_1[2] == 3) || 
            (retail_key_1[0] == 4 && retail_key_1[1] == 4 && retail_key_1[2] == 4) || 
            (retail_key_1[0] == 5 && retail_key_1[1] == 5 && retail_key_1[2] == 5) || 
            (retail_key_1[0] == 6 && retail_key_1[1] == 6 && retail_key_1[2] == 6) || 
            (retail_key_1[0] == 7 && retail_key_1[1] == 7 && retail_key_1[2] == 7) || 
            (retail_key_1[0] == 8 && retail_key_1[1] == 8 && retail_key_1[2] == 8) || 
            (retail_key_1[0] == 9 && retail_key_1[1] == 9 && retail_key_1[2] == 9)
        ) {
            gen = true;
        } else {
            gen = false;
        }
    }
}

void gen_7digits_retail() {
    gen = true;
    while(gen) {
        for(digit=0; digit<7; ++digit)
            retail_key_2[digit] = rand() % DIGIT_RANGE;

        sum7 = retail_key_2[0] + retail_key_2[1] + retail_key_2[2] + retail_key_2[3] + retail_key_2[4] + retail_key_2[5] + retail_key_2[6];

        if(sum7 % 7 == 0) {
            gen = false;
        } else {
            gen = true;
        }
    }
}

int main(void) {
    sw_clock = 1;
    srand(sw_clock);

    // init switch
    consoleInit(NULL);

    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    PadState pad;

    printf("Press A to generate a windows 95 Key.\n");

    while (appletMainLoop()) {
        padUpdate(&pad);

        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus) break; // Quit

        gen_3digits_retail();
        gen_7digits_retail();
        gen_oem_day();
        gen_oem_year();
        gen_5digits_oem();
        gen_5digits_random_oem();

        // Create out strings to display
        // if A is pressed
        if (kDown & HidNpadButton_A) {
            string winKey = "Win95 Retail Key: " + 
                to_string(retail_key_1[0]) + 
                to_string(retail_key_1[1]) + 
                to_string(retail_key_1[2]) +
                
                " - " +

                to_string(retail_key_2[0]) +
                to_string(retail_key_2[1]) +
                to_string(retail_key_2[2]) +
                to_string(retail_key_2[3]) +
                to_string(retail_key_2[4]) +
                to_string(retail_key_2[5]) +
                to_string(retail_key_2[6]) +

                "\n" +

                "Win95 OEM Key: 03" +

                to_string(oem_key_day) +
                to_string(oem_key_year[0]) +
                to_string(oem_key_year[1]) +

                "-OEM-00" +

                to_string(oem_key_5[0]) +
                to_string(oem_key_5[1]) +
                to_string(oem_key_5[2]) +
                to_string(oem_key_5[3]) +
                to_string(oem_key_5[4]) +

                "-" +

                to_string(oem_key_5_random[0]) +
                to_string(oem_key_5_random[1]) +
                to_string(oem_key_5_random[2]) +
                to_string(oem_key_5_random[3]) +
                to_string(oem_key_5_random[4]) +

                "\n";
                
            printf(winKey.c_str());
        }
    }

    return 0;
}