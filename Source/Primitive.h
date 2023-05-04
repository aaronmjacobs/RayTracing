#pragma once

class Ray;
struct HitRecord;

class Primitive
{
public:
   virtual ~Primitive() = default;

   virtual bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};
