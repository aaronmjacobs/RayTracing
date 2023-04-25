#pragma once

#include <glm/glm.hpp>

#include <cstdint>
#include <limits>

struct Pixel
{
   uint8_t r = 0;
   uint8_t g = 0;
   uint8_t b = 0;

   static uint8_t quantize(double value)
   {
      return static_cast<uint8_t>(glm::max(0.0, glm::min(value, 1.0) - std::numeric_limits<double>::epsilon()) * 256);
   }

   Pixel() = default;

   Pixel(uint8_t red, uint8_t green, uint8_t blue)
      : r(red)
      , g(green)
      , b(blue)
      {
      }

   Pixel(double red, double green, double blue)
      : r(quantize(red))
      , g(quantize(green))
      , b(quantize(blue))
      {
      }
};
