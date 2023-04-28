set(SRC_DIR "${PROJECT_SOURCE_DIR}/Source")

target_sources(${PROJECT_NAME} PRIVATE
   "${SRC_DIR}/Camera.h"
   "${SRC_DIR}/Image.cpp"
   "${SRC_DIR}/Image.h"
   "${SRC_DIR}/Main.cpp"
   "${SRC_DIR}/MathUtils.h"
   "${SRC_DIR}/Pixel.h"
   "${SRC_DIR}/Primitive.h"
   "${SRC_DIR}/Ray.h"
   "${SRC_DIR}/Scene.h"
   "${SRC_DIR}/Sphere.h"
   "${SRC_DIR}/VecTypes.h"

   "${SRC_DIR}/Core/Assert.h"
   "${SRC_DIR}/Core/Log.cpp"
   "${SRC_DIR}/Core/Log.h"
   "${SRC_DIR}/Core/Macros.h"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${SRC_DIR}")

get_target_property(SOURCE_FILES ${PROJECT_NAME} SOURCES)
source_group(TREE "${SRC_DIR}" PREFIX Source FILES ${SOURCE_FILES})
