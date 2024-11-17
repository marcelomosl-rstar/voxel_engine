#include <glad/glad.h>
// Glad has to be first
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

// Include Classes
#include "Objects/Chunk.h"
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

    if (window == NULL) {
        std::cout << "Failed to init window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    Shader shaderProgram("src/Shaders/Default.vert", "src/Shaders/Default.frag");

    Chunk chunk;

    VAO vao;
    vao.Bind();

    VBO vbo(chunk.vertices.data(), chunk.vertices.size() * sizeof(GLfloat));
    EBO ebo(chunk.indices.data(), chunk.indices.size() * sizeof(GLuint));

    // Adjust vertex attribute pointers for 3D positions only
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    vao.Unbind();
    ebo.Unbind();
    vbo.Unbind();

    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    double prevTime = 0.0;
    double crrntTime = 0.0;
    double timeDiff = 0.0;
    unsigned int counter = 0;

    std::cout << "Vertex data size: " << chunk.vertices.size() << std::endl;
    std::cout << "Index data size: " << chunk.indices.size() << std::endl;

    while (!glfwWindowShouldClose(window)) {

        // FPS tracking stuff
        crrntTime = glfwGetTime();
        timeDiff = crrntTime - prevTime;
        counter++;
        if (timeDiff >= 1.0 / 30.0) {
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);

            std::string newTitle = "Voxel Engine - FPS " + FPS;

            glfwSetWindowTitle(window, newTitle.c_str());
        }

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both color and depth buffers
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set to wireframe mode

        shaderProgram.Activate();

        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        vao.Bind();

        for (size_t i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f); // Identity matrix
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, float(i))); // Example translation

            // Set the uniform for the model matrix in the shader
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

            // Draw the chunk here
            glDrawElements(GL_TRIANGLES, chunk.indices.size(), GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}