#pragma once

#include "MathUtils.h"
#include "VecTypes.h"

#include <glm/glm.hpp>
#include <glm/gtc/color_space.hpp>

#include <cstdint>
#include <limits>

struct Pixel
{
   uint8_t r = 0;
   uint8_t g = 0;
   uint8_t b = 0;

   static uint8_t quantize(double value)
   {
      return static_cast<uint8_t>(glm::clamp(value, 0.0, MathUtils::kAlmostOne) * 256);
   }

   Pixel() = default;

   Pixel(uint8_t red, uint8_t green, uint8_t blue)
      : r(red)
      , g(green)
      , b(blue)
   {
   }

   explicit Pixel(const Color& color)
   {
      Color srgbColor = glm::convertLinearToSRGB(color);

      r = quantize(srgbColor.r);
      g = quantize(srgbColor.g);
      b = quantize(srgbColor.b);
   }
};
