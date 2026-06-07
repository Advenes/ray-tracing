cmake_minimum_required(VERSION 3.20)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
find_package(OpenGL REQUIRED)

add_executable(raytracer main.cpp
        utils/vec3.h
        utils/color.h
        utils/delta.h
        utils/ray.h
        hittable/hittable.h
        hittable/sphere.h
        hittable/hittable_list.h
        math/constants.h
        utils/common_includes.h
        camera/camera.h
        material/material.h
        material/lambertian.h
        material/metal.h
        material/fuzzy_metal.h
        application/application.h

        # glad
        external/glad/src/glad.c

        # imgui
        external/imgui/imgui.h
        external/imgui/imgui.cpp
        external/imgui/imgui_demo.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imconfig.h
        external/imgui/imgui_internal.h
        external/imgui/imstb_rectpack.h
        external/imgui/imstb_textedit.h
        external/imgui/imstb_truetype.h

        # ImGui Backends
        external/imgui/backends/imgui_impl_glfw.h
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.h
        external/imgui/backends/imgui_impl_opengl3.cpp
        camera/camera_controller.h
        utils/timer.h
)


target_include_directories(raytracer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    external/glad/include
    external/glfw/include
    external/imgui
    external/imgui/backends
)

target_link_libraries(raytracer PRIVATE glfw)

if(APPLE)
    target_link_libraries(raytracer PRIVATE "-framework OpenGL")
else()
    target_link_libraries(raytracer PRIVATE OpenGL::GL)
endif()