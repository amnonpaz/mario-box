#include "sounds.h"

namespace sounds {

const int marioFreqs[] = {660, 660, 0, 660, 0, 510, 660, 0, 770, 0, 375};
const int marioDurs[]  = {100, 100, 100, 100, 100, 100, 100, 100, 100, 300, 100};
const int count = sizeof(marioFreqs) / sizeof(marioFreqs[0]);

const Sequence g_marioSeq(count, marioFreqs, marioDurs);

}