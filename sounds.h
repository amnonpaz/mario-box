#ifndef SOUNDS_H_
#define SOUNDS_H_

#include <Arduino.h>

namespace sounds {

struct Note {
    int freq;
    int duration;
};

class Sequence {
  public:
    // This constructor now takes raw arrays safely
    Sequence(int size, const int freqs[], const int durations[]) {
        _numNotes = (size > MAX_NOTES) ? MAX_NOTES : size; // Don't overflow
        for (int i = 0; i < _numNotes; ++i) {
            _notes[i] = {freqs[i], durations[i]};
        }
    }

    void play() const {
        for (int i = 0; i < _numNotes; ++i) {
            if (_notes[i].freq > 0) {
                tone(_speakerPin, _notes[i].freq, _notes[i].duration);
            }
            // 1.3x duration creates a nice gap between notes
            delay(_notes[i].duration * 1.3);
        }
    }

  private:
    static const int MAX_NOTES = 64; // Set your max song length here
    Note _notes[MAX_NOTES];          // Allocated once at startup
    int _numNotes = 0;
    const int _speakerPin = 9;
};

extern const Sequence g_testSeq;
extern const Sequence g_marioSeq;

}

#endif