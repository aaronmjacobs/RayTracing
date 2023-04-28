#pragma once

#include <glm/glm.hpp>

#include <random>

namespace MathUtils
{
   template<typename O, typename I>
   O round(I value)
   {
      return static_cast<O>(value + static_cast<I>(0.5) * glm::sign(value));
   }

   double randomNormalized()
   {
       static std::uniform_real_distribution<double> distribution(0.0, 1.0);
       static std::mt19937 generator;

       return distribution(generator);
   }

   double randomCentered()
   {
       static std::uniform_real_distribution<double> distribution(-0.5, 0.5);
       static std::mt19937 generator;

       return distribution(generator);
   }
}
