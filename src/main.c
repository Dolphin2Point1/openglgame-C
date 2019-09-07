#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "cglm/cglm.h"
#include <stdio.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLFWwindow* window;

unsigned int VBO, VAO, EBO;

unsigned int shaderProgram;

int getGLPolygonMode = GL_FILL;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool fpressed;

void processInput(GLFWwindow *GLFWwindow) {
    if(glfwGetKey(GLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(GLFWwindow, true);
    if(glfwGetKey(GLFWwindow, GLFW_KEY_F) == GLFW_PRESS && !fpressed) {
        fpressed = true;
        if (getGLPolygonMode == GL_FILL) {
            getGLPolygonMode = GL_LINE;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else if (getGLPolygonMode == GL_LINE) {
            getGLPolygonMode = GL_POINT;
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        } else if (getGLPolygonMode == GL_POINT) {
            getGLPolygonMode = GL_FILL;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    } else if(glfwGetKey(GLFWwindow, GLFW_KEY_F) == GLFW_RELEASE && fpressed) {
        fpressed = false;
    }
}

int main() {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
            0.5f,  0.5f, 0.66f,  // top right
            0.5f, -0.5f, 1.0f,  // bottom right
            -0.5f, -0.5f, 1.0f,  // bottom left
            -0.5f,  0.5f, 0.3f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glGenBuffers(1, &VBO);

        //glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}
