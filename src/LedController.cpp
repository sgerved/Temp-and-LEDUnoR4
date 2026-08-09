//
// Created by sga on 09/08/2026.
//
#include "LedController.h"

void toggleLEDs(ModulinoPixels leds) {
    for (int i = 0; i < 8; i++) {
        if (i % 2 == 0) {
            leds.set(i, CYAN, 15);
        } else {
            leds.set(i, RED, 15);
        }

        delay(500);
        leds.show();
    }
    for (int i = 7; i >= 0; i--) {
        leds.set(i, WHITE, 0);
        delay(500);
        leds.show();
    }
}
