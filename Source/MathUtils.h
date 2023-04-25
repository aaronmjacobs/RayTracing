#pragma once

#include <glm/glm.hpp>

namespace MathUtils
{
   template<typename O, typename I>
   O round(I value)
   {
      return static_cast<O>(value + static_cast<I>(0.5) * glm::sign(value));
   }
}
