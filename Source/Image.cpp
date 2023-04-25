#include "Image.h"

#include "Core/Macros.h"

PRAGMA_BEGIN_DISABLE_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
PRAGMA_END_DISABLE_WARNINGS

bool Image::writeToFile(const std::filesystem::path& path)
{
   stbi_flip_vertically_on_write(1);
   return stbi_write_png(path.string().c_str(), width, height, sizeof(Pixel), pixels.get(), 0) != 0;
}
