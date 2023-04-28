#pragma once

#include "Ray.h"
#include "Primitive.h"

#include <memory>
#include <utility>
#include <vector>

class Scene
{
public:
   void clear()
   {
      primitives.clear();
   }

   void add(std::unique_ptr<Primitive> primitive)
   {
      if (primitive)
      {
         primitives.emplace_back(std::move(primitive));
      }
   }

   bool cast(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const
   {
      bool anyHit = false;
      double closestHit = tMax;
      for (const std::unique_ptr<Primitive>& primitive : primitives)
      {
         if (primitive->hit(ray, tMin, closestHit, hitRecord))
         {
            anyHit = true;
            closestHit = hitRecord.t;
         }
      }

      return anyHit;
   }

private:
   std::vector<std::unique_ptr<Primitive>> primitives;
};
