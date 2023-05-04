#pragma once

#include "VecTypes.h"

class Material;

struct HitRecord
{
   Point3 point;
   Vec3 normal;
   Material* material = nullptr;
   double t = 0.0;
   bool frontFace = true;
};
