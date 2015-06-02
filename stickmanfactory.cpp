#include "stickmanfactory.h"

#include "giantstickman.h"
#include "largestickman.h"
#include "normalstickman.h"
#include "tinystickman.h"

Stickman *StickmanFactory::create(const std::string size, const std::vector<QPixmap> &sprites)
{
    if (size == "tiny")
        return new TinyStickman(sprites);
    if (size == "normal")
        return new NormalStickman(sprites);
    if (size == "large")
        return new LargeStickman(sprites);
    if (size == "giant")
        return new GiantStickman(sprites);
    return NULL;
}

