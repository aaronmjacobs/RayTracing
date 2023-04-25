#pragma once

#include "Core/Assert.h"

#include "Pixel.h"

#include <cstdint>
#include <cstring>
#include <filesystem>
#include <memory>
#include <span>

class Image
{
public:
   Image() = default;

   Image(uint32_t imageWidth, uint32_t imageHeight)
      : pixels(std::make_unique<Pixel[]>(imageWidth * imageHeight))
      , width(imageWidth)
      , height(imageHeight)
   {
      ASSERT(width < 65536 && height < 65536);
      std::memset(pixels.get(), 0, width * height * sizeof(Pixel));
   }

   uint32_t getWidth() const
   {
      return width;
   }

   uint32_t getHeight() const
   {
      return height;
   }

   uint32_t getNumPixels() const
   {
      return width * height;
   }

   std::span<const Pixel> getPixels() const
   {
      return std::span<const Pixel>(pixels.get(), getNumPixels());
   }

   Pixel getPixel(uint32_t index) const
   {
      ASSERT(index < getNumPixels());
      return pixels[index];
   }

   Pixel getPixel(uint32_t x, uint32_t y) const
   {
      return getPixel(x + y * width);
   }

   void setPixel(uint32_t index, Pixel value)
   {
      ASSERT(index < getNumPixels());
      pixels[index] = value;
   }

   void setPixel(uint32_t x, uint32_t y, Pixel value)
   {
      setPixel(x + y * width, value);
   }

   bool writeToFile(const std::filesystem::path& path);

private:
   std::unique_ptr<Pixel[]> pixels;

   uint32_t width = 0;
   uint32_t height = 0;
};
