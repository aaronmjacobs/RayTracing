#pragma once

#include "Primitive.h"

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

class Sphere : public Primitive
{
public:
   Sphere() = default;

   Sphere(const Point3& sphereCenter, double sphereRadius)
      : center(sphereCenter)
      , radius(glm::max(0.0, sphereRadius))
   {
   }

   const Point3& getCenter() const
   {
      return center;
   }

   void setCenter(const Point3& newCenter)
   {
      center = newCenter;
   }

   double getRadius() const
   {
      return radius;
   }

   void setRadius(double newRadius)
   {
      radius = glm::max(0.0, newRadius);
   }

   bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override
   {
      Vec3 toOrigin = ray.getOrigin() - center;

      double halfB = glm::dot(toOrigin, ray.getDirection());
      double c = glm::length2(toOrigin) - radius * radius;
      double discriminant = halfB * halfB - c;

      if (discriminant < 0.0)
      {
         return false;
      }

      double discriminantSqrt = glm::sqrt(discriminant);
      double root = -halfB - discriminantSqrt;
      if (root < tMin || root > tMax)
      {
         root = -halfB + discriminantSqrt;
         if (root < tMin || root > tMax)
         {
            return false;
         }
      }

      record.point = ray.at(root);
      record.normal = (record.point - center) / radius;
      record.t = root;
      record.frontFace = glm::dot(record.normal, ray.getDirection()) <= 0.0;
      if (!record.frontFace)
      {
         record.normal = -record.normal;
      }
      return true;
   }

private:
   Point3 center;
   double radius = 0.0;
};
