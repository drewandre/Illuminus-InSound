#include "Sixbar.h"

void Sixbar::draw(const CRGB &rgb)
{
  DmxSimple.write(redChannel, rgb.r);
  DmxSimple.write(greenChannel, rgb.g);
  DmxSimple.write(blueChannel, rgb.b);
}