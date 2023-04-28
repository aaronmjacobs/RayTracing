#include "Core/Log.h"

#include "Camera.h"
#include "Image.h"
#include "MathUtils.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "VecTypes.h"

#include <glm/glm.hpp>

#include <PlatformUtils/IOUtils.h>

#include <cstdint>
#include <optional>

namespace
{
   Color rayColor(const Scene& scene, const Ray& ray)
   {
      HitRecord hitRecord;
      if (scene.cast(ray, 0.0, 100.0, hitRecord))
      {
         return Color((hitRecord.normal + Vec3(1.0)) * 0.5);
      }

      Vec3 unitDirection = glm::normalize(ray.getDirection());
      double t = 0.5 * (unitDirection.y + 1.0);

      return glm::mix(Color(1.0, 1.0, 1.0), Color(0.5, 0.7, 1.0), t);
   }
}

int main(int argc, char* argv[])
{
   LOG_INFO("RayTracer running...");

   static const uint32_t kSamplesPerPixel = 100;

   Image image(400, MathUtils::round<uint32_t>(400 / Camera::kAspectRatio));

   Scene scene;
   scene.add(std::make_unique<Sphere>(Point3(0.0, 0.0, 1.0), 0.5));
   scene.add(std::make_unique<Sphere>(Point3(0.0, -100.5, 1.0), 100.0));

   Camera camera;

   for (uint32_t y = 0; y < image.getHeight(); ++y)
   {
      LOG_INFO("Progress: " << static_cast<double>(y * 100) / image.getHeight() << "%");

      for (uint32_t x = 0; x < image.getWidth(); ++x)
      {
         Color pixelColor(0.0, 0.0, 0.0);
         for (uint32_t i = 0; i < kSamplesPerPixel; ++i)
         {
            double u = (x + MathUtils::randomCentered()) / static_cast<double>(image.getWidth() - 1);
            double v = (y + MathUtils::randomCentered()) / static_cast<double>(image.getHeight() - 1);
            Ray ray = camera.getRay(u, v);

            pixelColor += rayColor(scene, ray);
         }
         pixelColor /= kSamplesPerPixel;

         image.setPixel(x, y, Pixel(pixelColor));
      }
   }

   if (std::optional<std::filesystem::path> outputPath = IOUtils::getAboluteProjectPath("Output/Multisample.png"))
   {
      image.writeToFile(*outputPath);
   }

   LOG_INFO("Done!");

   return 0;
}
