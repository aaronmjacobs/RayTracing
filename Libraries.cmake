set(LIB_DIR "${PROJECT_SOURCE_DIR}/Libraries")

# GLM
set(GLM_INSTALL_ENABLE OFF CACHE INTERNAL "GLM install")
set(GLM_TEST_ENABLE OFF CACHE INTERNAL "Build unit tests")
add_subdirectory("${LIB_DIR}/glm")
target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_FORCE_CTOR_INIT)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_FORCE_DEPTH_ZERO_TO_ONE)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_FORCE_RADIANS)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

# PlatformUtils
add_subdirectory("${LIB_DIR}/PlatformUtils")
target_link_libraries(${PROJECT_NAME} PUBLIC PlatformUtils)

# PPK_ASSERT
set(PPK_DIR "${LIB_DIR}/PPK_ASSERT")
target_sources(${PROJECT_NAME} PRIVATE "${PPK_DIR}/src/ppk_assert.h" "${PPK_DIR}/src/ppk_assert.cpp")
set_source_files_properties("${PPK_DIR}/src/ppk_assert.cpp" PROPERTIES SKIP_PRECOMPILE_HEADERS ON) # Don't use PCH for ppk_assert.cpp to avoid warnings
target_include_directories(${PROJECT_NAME} PUBLIC "${PPK_DIR}/src")
source_group("Libraries\\PPK_ASSERT" "${PPK_DIR}/src")

# stb
set(STB_DIR "${LIB_DIR}/stb")
target_sources(${PROJECT_NAME} PRIVATE "${STB_DIR}/stb_image.h")
target_include_directories(${PROJECT_NAME} PUBLIC "${STB_DIR}")
source_group("Libraries\\stb" "${STB_DIR}")

# templog
set(TEMPLOG_DIR "${LIB_DIR}/templog")
target_sources(${PROJECT_NAME} PRIVATE
   "${TEMPLOG_DIR}/config.h"
   "${TEMPLOG_DIR}/logging.h"
   "${TEMPLOG_DIR}/templ_meta.h"
   "${TEMPLOG_DIR}/tuples.h"
   "${TEMPLOG_DIR}/type_lists.h"
   "${TEMPLOG_DIR}/imp/logging.cpp"
)
target_include_directories(${PROJECT_NAME} PUBLIC "${TEMPLOG_DIR}")
source_group("Libraries\\templog" "${TEMPLOG_DIR}")
