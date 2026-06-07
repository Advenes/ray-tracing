#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "../external/imgui/imgui.h"
#include "../external/imgui/backends/imgui_impl_glfw.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"
#include "../utils/timer.h"

class ui {
private:
    GLFWwindow* window = nullptr;
    std::function<std::chrono::milliseconds()> onRenderPressed;
    std::function<std::chrono::milliseconds()> onRenderToImagePressed;
    int *samples_per_pixel;
    int *max_bounces;
    int *img_width;
    int *img_height;
public:
    ui() {}

    ~ui() {
        close_ui();
    }

    void create_ui(GLFWwindow *w, int *samples, int *max_b, int *img_w, int *img_h,
        const std::function<std::chrono::milliseconds()>& renderFunc,
        const std::function<std::chrono::milliseconds()>& renderToImgFunc
        ) {
        window = w;
        onRenderPressed = renderFunc;
        onRenderToImagePressed = renderToImgFunc;
        samples_per_pixel = samples;
        max_bounces = max_b;
        img_width = img_w;
        img_height = img_h;
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
    }

    void render_ui() {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Renderer 1.0");
            ImGui::Text("settings:");

            ImGui::SliderInt("Samples per pixel", samples_per_pixel, 1, 128);
            ImGui::SliderInt("Max bounces", max_bounces, 1, 128);
            ImGui::InputInt("Image Width", img_width, 32, 2048);
            ImGui::InputInt("Image Height", img_height, 32, 2048);

            if (ImGui::Button("Render")) {
                onRenderPressed();
            }
            if (ImGui::Button("Render to image")) {
                auto time = onRenderToImagePressed();
                ImGui::Text("Render time: %lld ms", time.count());
            }

            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }


    void close_ui() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
};