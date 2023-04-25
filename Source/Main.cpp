#include "Core/Log.h"

#include "Image.h"
#include "MathUtils.h"
#include "Ray.h"
#include "VecTypes.h"

#include <glm/glm.hpp>

#include <PlatformUtils/IOUtils.h>

#include <cstdint>
#include <optional>

namespace
{
   Color rayColor(const Ray& ray)
   {
      Vec3 unitDirection = glm::normalize(ray.getDirection());
      double t = 0.5 * (unitDirection.y + 1.0);

      return glm::mix(Color(1.0, 1.0, 1.0), Color(0.5, 0.7, 1.0), t);
   }
}

int main(int argc, char* argv[])
{
   LOG_INFO("RayTracer running...");

   static const double kAspectRatio = 16.0 / 9.0;

   double viewportHeight = 2.0;
   double viewportWidth = viewportHeight * kAspectRatio;
   double focalLength = 1.0;

   Point3 origin(0.0, 0.0, 0.0);
   Vec3 horizontal(viewportWidth, 0.0, 0.0);
   Vec3 vertical(0.0, viewportHeight, 0.0);
   Point3 lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 + Vec3(0.0, 0.0, focalLength);

   Image image(400, MathUtils::round<uint32_t>(400 / kAspectRatio));

   for (uint32_t y = 0; y < image.getHeight(); ++y)
   {
      LOG_INFO("Progress: " << static_cast<double>(y * 100) / image.getHeight() << "%");

      for (uint32_t x = 0; x < image.getWidth(); ++x)
      {
         double u = x / static_cast<double>(image.getWidth() - 1);
         double v = y / static_cast<double>(image.getHeight() - 1);

         Point3 location = lowerLeftCorner + u * horizontal + v * vertical;
         Ray ray(origin, location - origin);
         image.setPixel(x, y, Pixel(rayColor(ray)));
      }
   }

   if (std::optional<std::filesystem::path> outputPath = IOUtils::getAboluteProjectPath("Output/Gradient.png"))
   {
      image.writeToFile(*outputPath);
   }

   LOG_INFO("Done!");

   return 0;
}
