#ifndef SOUNDS_H_
#define SOUNDS_H_

#include <Arduino.h>
#include <avr/pgmspace.h>

namespace sounds {

// Melody is a PROGMEM array of interleaved {freq, duration_code} pairs.
// Duration codes use musical notation: 4 = quarter, 8 = eighth, etc.
// Negative values denote dotted notes (e.g. -4 = dotted quarter = quarter * 1.5).
// Frequency 0 is a rest.
class Sequence {
  public:
    Sequence(const int* melody, int numNotes, int tempo)
        : _melody(melody), _numNotes(numNotes), _tempo(tempo) {}

    void play() const {
        int wholenote = (60000 * 4) / _tempo;
        for (int i = 0; i < _numNotes * 2; i += 2) {
            int freq = (int)pgm_read_word_near(_melody + i);
            int divider = (int)pgm_read_word_near(_melody + i + 1);
            int dur;
            if (divider > 0) {
                dur = wholenote / divider;
            } else {
                dur = (wholenote / abs(divider)) * 3 / 2;
            }
            if (freq > 0) {
                tone(_speakerPin, freq, dur * 9 / 10);
            }
            delay(dur);
            noTone(_speakerPin);
        }
    }

  private:
    const int* _melody;
    int _numNotes;
    int _tempo;
    static const int _speakerPin = 9;
};

extern const Sequence g_marioSeq;

}

#endif
