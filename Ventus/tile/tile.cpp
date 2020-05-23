#include "tile.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../main.h"
#include "../shader/shader_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

// TODO: Optimize vertices memory storage

namespace {

const float vertices[] = { 
	0.1f,  0.1f, 0.0f, 1.0f, 1.0f, // top right
	0.1f, -0.1f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.1f, -0.1f, 0.0f, 0.0f, 0.0f, // bottom left
	-0.1f,  0.1f, 0.0f, 0.0f, 1.0f // top left
};

const unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
};

}

Tile::Tile(const std::string& texture_path, const unsigned int shader_program) : shader_program_(shader_program) {
	Init(texture_path);

	// Move this
	view_matrix_ =  glm::scale(glm::mat4(1.0f), glm::vec3(0.5625f, 1.0f, 1.0f));
}

void Tile::Draw() {
	glUseProgram(shader_program_);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_);
	glUniformMatrix4fv(glGetUniformLocation(shader_program_, "M"), 1, GL_FALSE, glm::value_ptr(model_matrix_));
	glUniformMatrix4fv(glGetUniformLocation(shader_program_, "V"), 1, GL_FALSE, glm::value_ptr(view_matrix_));
	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Tile::Init(const std::string& texture_path) {
	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texture_path.c_str(), &width, &height, &channels, 0);
	assert(data);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &ebo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glUseProgram(shader_program_);
	glUniform1i(glGetUniformLocation(shader_program_, "textCoord"), 0);
}