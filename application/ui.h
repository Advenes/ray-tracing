#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "../external/imgui/imgui.h"
#include "../external/imgui/backends/imgui_impl_glfw.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"
#include "../utils/timer.h"


inline bool DrawVec3Control(const char* label, vec3& value)
{
    double values[3] = { value.x(), value.y(), value.z() };

    bool changed = ImGui::DragScalarN(label, ImGuiDataType_Double, values,3, 0.05f);

    if (changed)
    {
        value.e[0] = values[0];
        value.e[1] = values[1];
        value.e[2] = values[2];
    }

    return changed;
}

class ui {
private:
    GLFWwindow* window = nullptr;
    std::function<std::chrono::milliseconds()> onRenderPressed;
    std::function<std::chrono::milliseconds()> onRenderToImagePressed;
    int *samples_per_pixel;
    int *max_bounces;
    int *img_width;
    int *img_height;
    vec3 *cam_pos;
    vec3 *cam_look;
    double *vfov;
public:

    ~ui() {
        close_ui();
    }

    void create_ui(GLFWwindow *w, int *samples, int *max_b, int *img_w, int *img_h, vec3 *cam_position, vec3 *cam_looking_spot, double *vertical_fov,
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
        cam_pos = cam_position;
        cam_look = cam_looking_spot;
        vfov = vertical_fov;
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

        {ImGui::Begin("Renderer 1.0");

            ImGui::Text("Settings");

            if (ImGui::CollapsingHeader("Rendering Options", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushItemWidth(120);

                ImGui::SliderInt("Samples per pixel", samples_per_pixel, 1, 128);
                ImGui::SliderInt("Max bounces", max_bounces, 1, 128);

                if (ImGui::Button("Render"))
                {
                    auto timeMS = onRenderPressed();
                    auto seconds = std::chrono::duration<double>(timeMS).count();
                    std::clog << timeMS << " in seconds: " << seconds << "s\n";
                }

                ImGui::PopItemWidth();
            }

            if (ImGui::CollapsingHeader("Camera Options", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushItemWidth(120);

                DrawVec3Control("Camera Position", *cam_pos);
                DrawVec3Control("Camera Direction", *cam_look);

                double min = 1.0;
                double max = 128.0;
                ImGui::SliderScalar("Camera Vertical Fov", ImGuiDataType_Double, vfov, &min, &max, "%.1f");

                ImGui::PopItemWidth();
            }

            if (ImGui::CollapsingHeader("Rendering To Image", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushItemWidth(100);

                ImGui::InputInt("Image Width", img_width, 32, 2048);
                ImGui::InputInt("Image Height", img_height, 32, 2048);

                if (ImGui::Button("Render to image"))
                {
                    auto timeMS = onRenderToImagePressed();
                    auto seconds = std::chrono::duration<double>(timeMS).count();
                    std::clog << timeMS << " in seconds: " << seconds << "s\n";
                }

                ImGui::PopItemWidth();
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
