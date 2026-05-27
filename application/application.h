
#include <cstdlib>
#include <vector>

#include "../camera/camera.h"
#include "../hittable/hittable_list.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class application {
public:
    application(const int width, const hittable_list& world, const camera& camera) : width(width), world(world), camera(camera) {}

    void run() {
        init_glfw_window();
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


        window = glfwCreateWindow(width, height, "raytracing", nullptr, nullptr);
        if (!window) { glfwTerminate(); exit(EXIT_FAILURE); }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "GLAD exploaded";
            exit(EXIT_FAILURE);
        }
    }


    void init_texture() {
        pixel_buffer.resize(width * height * 3);

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    }

    void init_framebuffer() {
        glGenFramebuffers(1, &framebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    void render()
    {
        glfwPollEvents();
        camera.render_to_window(world, pixel_buffer.data(), width, height);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixel_buffer.data());

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            int display_width, display_height;
            glfwGetFramebufferSize(window, &display_width, &display_height);

            glViewport(0, 0, display_width, display_height);

            glClear(GL_COLOR_BUFFER_BIT);

            glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
            glBlitFramebuffer(0,0, width, height, 0, display_height, display_width, 0, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            glfwSwapBuffers(window);

        }
        glDeleteTextures(1, &textureID);
        glDeleteFramebuffers(1, &framebufferID);
        glfwTerminate();
        return;
    }

private:
    int width;
    double aspect_ratio = 16.0 / 9.0;
    int height = width / aspect_ratio;
    hittable_list world;
    camera camera;
    GLFWwindow* window;
    std::vector<unsigned char> pixel_buffer;
    GLuint textureID;
    GLuint framebufferID;
};
