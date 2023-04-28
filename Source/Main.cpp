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

#include <atomic>
#include <cstdint>
#include <limits>
#include <optional>
#include <thread>
#include <vector>

namespace
{
   Color rayColor(const Scene& scene, const Ray& ray, int depth)
   {
      if (depth < 0)
      {
         return Color(0.0, 0.0, 0.0);
      }

      HitRecord hitRecord;
      if (scene.cast(ray, 0.001, MathUtils::kInfinity, hitRecord))
      {
         Point3 target = hitRecord.point + hitRecord.normal + MathUtils::randomUnitVec3();
         return 0.5 * rayColor(scene, Ray(hitRecord.point, target - hitRecord.point), depth - 1);
      }

      Vec3 unitDirection = glm::normalize(ray.getDirection());
      double t = 0.5 * (unitDirection.y + 1.0);

      return glm::mix(Color(1.0, 1.0, 1.0), Color(0.5, 0.7, 1.0), t);
   }

   void traceLine(const Scene& scene, const Camera& camera, uint32_t y, Image& image)
   {
      static const uint32_t kSamplesPerPixel = 100;
      static const int kMaxDepth = 50;

      for (uint32_t x = 0; x < image.getWidth(); ++x)
      {
         Color pixelColor(0.0, 0.0, 0.0);
         for (uint32_t i = 0; i < kSamplesPerPixel; ++i)
         {
            double u = (x + MathUtils::randomCentered()) / static_cast<double>(image.getWidth() - 1);
            double v = (y + MathUtils::randomCentered()) / static_cast<double>(image.getHeight() - 1);
            Ray ray = camera.getRay(u, v);

            pixelColor += rayColor(scene, ray, kMaxDepth);
         }
         pixelColor /= kSamplesPerPixel;

         image.setPixel(x, y, Pixel(pixelColor));
      }
   }

   void traceThread(const Scene& scene, const Camera& camera, Image& image, std::atomic<uint32_t>& lineCounter)
   {
      while (true)
      {
         uint32_t line = lineCounter.fetch_add(1);
         if (line >= image.getHeight())
         {
            break;
         }

         traceLine(scene, camera, line, image);
      }
   }

   void traceParallel(const Scene& scene, const Camera& camera, Image& image)
   {
      std::atomic<uint32_t> lineCounter;

      uint32_t numThreads = std::thread::hardware_concurrency();
      std::vector<std::thread> threads;
      threads.reserve(numThreads);

      for (uint32_t i = 0; i < numThreads; ++i)
      {
         threads.emplace_back(traceThread, std::ref(scene), std::ref(camera), std::ref(image), std::ref(lineCounter));
      }

      uint32_t lastNumCompleted = std::numeric_limits<uint32_t>::max();
      uint32_t numCompleted = 0;
      while (numCompleted < image.getHeight())
      {
         numCompleted = lineCounter.load();

         if (numCompleted != lastNumCompleted)
         {
            lastNumCompleted = numCompleted;
            LOG_INFO("Progress: " << static_cast<double>(std::min(numCompleted, image.getHeight()) * 100) / image.getHeight() << "%");
         }

         std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }

      for (std::thread& thread : threads)
      {
         thread.join();
      }
   }

   void traceSerial(const Scene& scene, const Camera& camera, Image& image)
   {
      for (uint32_t y = 0; y < image.getHeight(); ++y)
      {
         LOG_INFO("Progress: " << static_cast<double>(y * 100) / image.getHeight() << "%");

         traceLine(scene, camera, y, image);
      }
   }

   void trace(const Scene& scene, const Camera& camera, Image& image, bool parallel)
   {
      if (parallel)
      {
         traceParallel(scene, camera, image);
      }
      else
      {
         traceSerial(scene, camera, image);
      }
   }
}

int main(int argc, char* argv[])
{
   LOG_INFO("RayTracer running...");

   Image image(400, MathUtils::round<uint32_t>(400 / Camera::kAspectRatio));

   Scene scene;
   scene.add(std::make_unique<Sphere>(Point3(0.0, 0.0, 1.0), 0.5));
   scene.add(std::make_unique<Sphere>(Point3(0.0, -100.5, 1.0), 100.0));

   Camera camera;

   trace(scene, camera, image, false);

   if (std::optional<std::filesystem::path> outputPath = IOUtils::getAboluteProjectPath("Output/Diffuse.png"))
   {
      image.writeToFile(*outputPath);
   }

   LOG_INFO("Done!");

   return 0;
}
