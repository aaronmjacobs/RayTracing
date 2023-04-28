#pragma once

#include "Ray.h"
#include "VecTypes.h"

struct HitRecord
{
   Point3 point;
   Vec3 normal;
   double t = 0.0;
   bool frontFace = true;
};

class Primitive
{
public:
   virtual ~Primitive() = default;

   virtual bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};
