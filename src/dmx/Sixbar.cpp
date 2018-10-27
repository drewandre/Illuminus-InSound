#include "Sixbar.h"

Sixbar::Sixbar(uint16_t startingDMXAddressConfig)
{
  startingDMXAddress = startingDMXAddressConfig;
}

Sixbar::~Sixbar() {}

void Sixbar::draw(const CRGB &rgb)
{
  DmxSimple.write(redChannel, rgb.r);
  DmxSimple.write(greenChannel, rgb.g);
  DmxSimple.write(blueChannel, rgb.b);
}