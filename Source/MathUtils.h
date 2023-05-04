#pragma once

#include "VecTypes.h"

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

#include <limits>
#include <random>

namespace MathUtils
{
   constexpr double kInfinity = std::numeric_limits<double>::infinity();
   constexpr double kSmallNumber = 1e-8;

   template<typename O, typename I>
   O round(I value)
   {
      return static_cast<O>(value + static_cast<I>(0.5) * glm::sign(value));
   }

   double random()
   {
      static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
      static thread_local std::mt19937 generator(std::hash<std::thread::id>{}(std::this_thread::get_id())); // Seed using the thread ID to avoid all threads generating the same random values

      return distribution(generator);
   }

   double random(double min, double max)
   {
      return glm::mix(min, max, random());
   }

   double randomCentered()
   {
      return random(-0.5, 0.5);
   }

   Vec3 randomVec3()
   {
      return Vec3(random(), random(), random());
   }

   Vec3 randomVec3(double min, double max)
   {
      return Vec3(random(min, max), random(min, max), random(min, max));
   }

   Vec3 randomVec3InUnitSphere()
   {
      while (true)
      {
         Vec3 vec = randomVec3(-1.0, 1.0);
         if (glm::length2(vec) <= 1.0)
         {
            return vec;
         }
      }
   }

   Vec3 randomUnitVec3()
   {
      return glm::normalize(randomVec3InUnitSphere());
   }

   template<typename T>
   bool isNearlyZero(const T& value)
   {
      return glm::all(glm::epsilonEqual(value, T(0.0), kSmallNumber));
   }
}
