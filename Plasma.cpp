//
//  Plasma.cpp
//  GauntletII
//
//  Created by Robert Atkins on 26/09/13.
//  Copyright (c) 2013 Robert Atkins. All rights reserved.
//

#import "Effect.h"

class Plasma : public Effect {
    
public:
    
    Plasma(CRGB *leds, int width, int height) : Effect(leds, width, height) {
    }
    
    void start() {
      uint16_t time = 0;
      for (int j=0;j<12;j++) {
        for (int cycles = 0; cycles < 256; cycles++) {
            calcFrame(time);
            time += 128;
        }
        blank(); 
      }
    }
    //sin(distance(x, y, (128 * sin(-t) + 128), (128 * cos(-t) + 128)) / 40.74)s
    // v = sin(10 * (x * sin(time / 2) + y * cos(time / 3)) + time)

     void blank() {
        clearLeds();
        LEDS.show();
        delay(32 * random(16));
    }
    
    void calcFrame(int time) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int16_t v = 0;
                uint16_t wibble = sin8(time);
                v += sin16(x * wibble * 8 + time);
                v += cos16(y * (128 - wibble) * 4 + time);
                v += sin16(y * x * cos8(-time) / 2);
                pixel(x, y) = CHSV((v >> 8) +64, 200, 200);
            }
        }
        LEDS.show();
    }
    
    uint8_t sin8(uint16_t x) {
        return (sin16(x) >> 8) + 64;
    }
    
    uint8_t cos8(uint16_t x) {
        return (cos16(x) >> 8) + 64;
    }

};
