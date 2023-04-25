#include "Core/Log.h"

#include "Image.h"

#include <PlatformUtils/IOUtils.h>

#include <cstdint>
#include <optional>

int main(int argc, char* argv[])
{
   LOG_INFO("RayTracer running...");

   Image image(256, 256);

   for (uint32_t y = 0; y < image.getHeight(); ++y)
   {
      for (uint32_t x = 0; x < image.getWidth(); ++x)
      {
         double r = x / static_cast<double>(image.getWidth() - 1);
         double g = y / static_cast<double>(image.getHeight() - 1);
         double b = 0.25;

         image.setPixel(x, y, Pixel(r, g, b));
      }
   }

   if (std::optional<std::filesystem::path> outputPath = IOUtils::getAboluteProjectPath("Output/FirstImage.png"))
   {
      image.writeToFile(*outputPath);
   }

   LOG_INFO("Done!");

   return 0;
}
