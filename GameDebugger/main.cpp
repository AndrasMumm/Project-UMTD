// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

#include "shader.hpp"
#include "texture.hpp"
#include "controls.hpp"

#include <Game\board.h>
#include <Game\gamestate.h>

typedef vector<vec3> vvec3;

void createBlancBoard(Board* board,float gridSize, vvec3& vertices, vvec3& uvices);
void addTile(vec3 tl, vec3 br, int type, vvec3& vertices, vvec3& uvices);
int screen_width = 1920 / 2;
int screen_height = 1080 / 2;
int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(screen_width, screen_height, "SpielEntkäferer", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, screen_width / 2, screen_height / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glDisable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	GLuint pos_offID = glGetUniformLocation(programID, "POS_OFF");

	// Load the texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("HexMap.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	vvec3 vertices;
	vvec3 uvices;
	GameState& game = GameState::getInstance();
	vvint path = game.board.generatePath();

	float gridSize = game.board.width / screen_width > game.board.height / screen_height ? 2.0f / game.board.width : 2.0f / game.board.height;


	Tile* start = game.board.getTile(0, 5);
	game.enemys.push_back(new Enemy(.005f,1,1,1,1,1,1,start->x,start->y,start->tileID,0,-1,path[0]));

	Enemy* e = game.enemys.back();
	vec3 pos_off = vec3(*(e->x)*gridSize, -*(e->y)*gridSize, 0.0f);

	createBlancBoard(&game.board,gridSize, vertices, uvices);

	float y_off = 1;

	float x_off = -1;

	vertices.push_back(vec3(x_off, y_off-gridSize, .02f));
	vertices.push_back(vec3(x_off, y_off, .02f));
	vertices.push_back(vec3(x_off+gridSize, y_off, .02f));

	uvices.push_back(vec3(0, 0, 1));
	uvices.push_back(vec3(0, 0, 1));
	uvices.push_back(vec3(0, 0, 1));

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvices.size() * sizeof(uvices[0]), uvices.data(), GL_STATIC_DRAW);

	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;


		// compute game update

		e->update(1);

		pos_off = vec3(*(e->x) * gridSize, -*(e->y) * gridSize, 0.0f);



		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniform3f(pos_offID, pos_off.x, pos_off.y, pos_off.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size()*3); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

void createBlancBoard(Board* board, float gridSize, vvec3& vertices, vvec3& uvices) {
	

	for (int x = 0; x < board->width; x++) {
		for (int y = 0; y < board->height; y++) {
			
			float px = -1 + x * gridSize;
			float pxp = px + gridSize;
			float py = 1 - y * gridSize;
			float pyp = py - gridSize;

			addTile(vec3(px, py, 0.0f), vec3(pxp, pyp, 0.0f), board->getTile(x,y)->type, vertices, uvices);
		}
	}
}

void addTile(vec3 tl, vec3 br, int type, vvec3& vertices, vvec3& uvices) {
	
	vec3 bl = vec3(tl.x, br.y, 0);
	vec3 tr = vec3(br.x, tl.y, 0);

	float u_offset = 0;
	float v_offset = 0;

	switch (type){
	case 0x1:
	case 0x5:
	case 0x9:
	case 0xd:
		u_offset = .25f;
		break;
	case 0x2:
	case 0x6:
	case 0xA:
	case 0xE:
		u_offset = .5f;
		break;
	case 0x3:
	case 0x7:
	case 0xb:
	case 0xf:
		u_offset = .75f;
		break;
	default:
		u_offset = 0;
	}

	switch (type) {
	case 0x4:
	case 0x5:
	case 0x6:
	case 0x7:
		v_offset = .25f;
		break;
	case 0x8:
	case 0x9:
	case 0xA:
	case 0xB:
		v_offset = .5f;
		break;
	case 0xC:
	case 0xD:
	case 0xE:
	case 0xf:
		v_offset = .75f;
		break;
	default:
		v_offset = 0;
	}

	v_offset = 1 - v_offset;

	vertices.push_back(tr);
	vertices.push_back(tl);
	vertices.push_back(bl);
	vertices.push_back(bl);
	vertices.push_back(br);
	vertices.push_back(tr);


	uvices.push_back(vec3(u_offset + 0.25f, v_offset - 0.25f, -1));
	uvices.push_back(vec3(u_offset + 0.0f, v_offset - 0.25f, -1));
	uvices.push_back(vec3(u_offset + 0.0f, v_offset - 0.0f, -1));

	uvices.push_back(vec3(u_offset + 0.0f, v_offset - 0.0f, -1));
	uvices.push_back(vec3(u_offset + 0.25f, v_offset - 0.0f, -1));
	uvices.push_back(vec3(u_offset + 0.25f, v_offset - 0.25f, -1));


}