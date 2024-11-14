#include <glad/glad.h>
// Glad has to be first
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

// Include Classes
#include "Objects/Cube.h"
#include "OpenGL/Camera.h"
#include "OpenGL/EBO.h"
#include "OpenGL/VAO.h"
#include "OpenGL/VBO.h"
#include "Shaders/Shader.h"
#include "Shaders/Texture.h"

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 720;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Voxel Engine", nullptr, nullptr);

    std::cout << window << std::endl;

    if (window == NULL) {
        std::cout << "Failed to init window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shaderProgram("src/Shaders/Default.vert", "src/Shaders/Default.frag");

    VAO vao1;
    vao1.Bind();

    Cube cube;

    VBO vbo(cube.vertices.data(), cube.vertices.size() * sizeof(GLfloat));
    EBO ebo(cube.indices.data(), cube.indices.size() * sizeof(GLuint));

    vao1.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao1.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float),
        (void*)(3 * sizeof(float)));
    vao1.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float),
        (void*)(6 * sizeof(float)));

    vao1.Unbind();
    ebo.Unbind();
    vbo.Unbind();

    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    double prevTime = 0.0;
    double crrntTime = 0.0;
    double timeDiff = 0.0;
    unsigned int counter = 0;

    std::vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
    };

    while (!glfwWindowShouldClose(window)) {
        crrntTime = glfwGetTime();

        timeDiff = crrntTime - prevTime;

        counter++;

        // FPS tracking stuff
        if (timeDiff >= 1.0 / 30.0) {
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);

            std::string newTitle = "Voxel Engine - FPS " + FPS;

            glfwSetWindowTitle(window, newTitle.c_str());
        }

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set to wireframe mode

        shaderProgram.Activate();

        camera.Inputs(window);

        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        vao1.Bind();

        glfwPollEvents();

        for (size_t i = 0; i < cubePositions.size(); i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glDrawElements(GL_TRIANGLES, cube.indices.size(), GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
    }

    vao1.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}