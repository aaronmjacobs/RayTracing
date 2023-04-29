cmake_minimum_required(VERSION 3.16)
project(RayTracing VERSION 0.0.0 LANGUAGES CXX C)

set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

add_executable(${PROJECT_NAME} "")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_definitions(${PROJECT_NAME} PUBLIC RAYTRACER_DEBUG=$<CONFIG:Debug>)
target_compile_definitions(${PROJECT_NAME} PUBLIC RAYTRACER_WITH_DEBUG_INFO=$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>)

include("${PROJECT_SOURCE_DIR}/Source.cmake")
include("${PROJECT_SOURCE_DIR}/Libraries.cmake")
