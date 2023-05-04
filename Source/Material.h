#pragma once

#include "MathUtils.h"
#include "VecTypes.h"

class Ray;
struct HitRecord;

class Material
{
public:
   virtual ~Material() = default;

   virtual bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const = 0;
};

class LambertianMaterial : public Material
{
public:
   LambertianMaterial(const Color& albedoColor)
      : albedo(albedoColor)
   {
   }

   bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override
   {
      Vec3 scatterDirection = hitRecord.normal + MathUtils::randomUnitVec3();
      if (MathUtils::isNearlyZero(scatterDirection))
      {
         scatterDirection = hitRecord.normal;
      }

      attenuation = albedo;
      scatteredRay = Ray(hitRecord.point, scatterDirection);
      return true;
   }

private:
   Color albedo;
};

class MetalMaterial : public Material
{
public:
   MetalMaterial(const Color& albedoColor)
      : albedo(albedoColor)
   {
   }

   bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override
   {
      Vec3 reflected = glm::reflect(ray.getDirection(), hitRecord.normal);

      attenuation = albedo;
      scatteredRay = Ray(hitRecord.point, reflected);
      return glm::dot(reflected, hitRecord.normal) > 0.0;
   }

private:
   Color albedo;
};
