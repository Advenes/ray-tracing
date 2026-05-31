
#pragma once
#include <cstdlib>
#include <vector>

#include "../camera/camera.h"
#include "../hittable/hittable_list.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ui.h"


class application {
public:
    application(int* width, int* height, hittable_list& world, camera& camera) : width(width), height(height), world(world), camera(camera) {}

    void run() {
        init_glfw_window();

        ui.create_ui(window, &camera.samples_per_pixel, &camera.max_bounces, &camera.img_width, &camera.img_height,
            [this](){camera.render_to_window(world, pixel_buffer.data());},
            [this](){camera.render(world);}

            );

        init_texture();
        init_framebuffer();
        render();
    }

private:

    void init_glfw_window() {
        if ( !glfwInit() ) return;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


        window = glfwCreateWindow(*width, *height, "raytracing", nullptr, nullptr);
        if (!window) { glfwTerminate(); exit(EXIT_FAILURE); }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "GLAD exploded";
            exit(EXIT_FAILURE);
        }
    }


    void init_texture() {
        pixel_buffer.resize(*width * *height * 3);

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *width, *height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, *width, *height, GL_RGB, GL_UNSIGNED_BYTE, pixel_buffer.data());
    }

    void init_framebuffer() {
        glGenFramebuffers(1, &framebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    void update_texture(const GLuint id, const std::vector<unsigned char> &buffer, const int &w, const int &h) {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
    }

    void update_framebuffer(const GLuint id, const int &w, const int &h) {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
        glBlitFramebuffer(0, 0, w, h, 0, h, w, 0, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    }

    void render()
    {
        glfwPollEvents();

        glfwGetFramebufferSize(window, width, height);

        int last_width = *width;
        int last_height = *height;

        camera.render_to_window(world, pixel_buffer.data());

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            glfwGetFramebufferSize(window, width, height);

            glViewport(0, 0, *width, *height);
            glClear(GL_COLOR_BUFFER_BIT);

            if (*width != last_width || *height != last_height) {
                last_width = *width;
                last_height = *height;

                pixel_buffer.resize(*width * *height * 3);
                camera.render_to_window(world, pixel_buffer.data());

            }

            update_texture(textureID, pixel_buffer, *width, *height);
            update_framebuffer(framebufferID, *width, *height);

            ui.render_ui();
            glfwSwapBuffers(window);

        }
        glDeleteTextures(1, &textureID);
        glDeleteFramebuffers(1, &framebufferID);
        glfwTerminate();
    }

private:
    int *width;
    int *height;
    double aspect_ratio;
    hittable_list& world;
    camera& camera;
    GLFWwindow* window;

    ui ui;

    std::vector<unsigned char> pixel_buffer;
    GLuint textureID;
    GLuint framebufferID;
};
