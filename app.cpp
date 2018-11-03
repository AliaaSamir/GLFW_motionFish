#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "D:\Aliaa\computer graphics\openGl\GLFWproject\headers\Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "D:\Aliaa\computer graphics\openGl\GLFWproject\headers\stb_image.h"

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_AUTO_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLFW ", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glew: load all OpenGL function pointers
	// ---------------------------------------

	if (glewInit() != GLEW_OK)
		cout << "Error intializing glew " << endl;
	cout << glGetString(GL_VERSION) << endl;

	
	// build and compile our shader zprogram
// ------------------------------------
	Shader fishShader("transform.vs", "transform.fs");
	Shader containShader("texture.vs", "texture.fs");
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
			//position				//color	   
								
		 0.46f, -0.5f,  0.0f,		1.0f, 0.1f, 0.0f,   //front
		 0.43f, -0.47f, 0.0f,		1.0f, 0.1f, 0.0f,
		 0.43f, -0.53f, 0.0f,		1.0f, 0.1f, 0.0f,
													
													
		 0.6f, -0.3f, 0.0f,			1.0f, 0.1f, 0.0f,	// middle top
		 0.6f, -0.7f, 0.0f,			1.0f, 0.1f, 0.0f,	// middle bottom
		 0.9f, -0.5f, 0.0f,			0.0f, 0.1f, 0.0f,	//tail start 
		 1.0f, -0.4f, 0.0f,			1.0f, 0.1f, 0.0f,	//tail top
		 1.0f, -0.6f, 0.0f,			0.0f, 0.1f, 0.0f,	//tail bottom
													
		 0.5f, -0.45f, 0.0f,		0.0f, 0.0f, 0.0f,	//eye
		 0.52f, -0.48f, 0.0f,		0.0f, 0.0f, 0.0f,	//eye
		 0.48f, -0.48f, 0.0f,		0.0f, 0.0f, 0.0f,	//eye
	
	};
	float containerVertices[] = {
		-1.0f, 1.0f, 0.0f,			0.0f, 0.0f, 0.0f,	0.0f, 1.0f,  //top right
		 1.0f, 1.0f, 0.0f,			0.0f, 0.0f, 0.0f,	1.0f, 1.0f,  //top left
		 1.0f,-1.0f, 0.0f,			0.0f, 0.0f, 0.0f,	1.0f, 0.0f,  //bottom left
		-1.0f,-1.0f, 0.0f,			0.0f, 0.0f, 0.0f,	0.0f, 0.0f  //bottom right
	};
	unsigned int indices[] = {  // note that we start from 0!
		
		0, 1, 3,	//first Triangle
		2, 3, 4,  // second Triangle
		3, 4, 5,  // third Triangle
		5, 6, 7,  // forth Triangle
		8, 9, 10,		  //eye Triangle
	};
	unsigned int VBO1,VBO2, VAO1, VAO2, EBO;
	glGenVertexArrays(1, &VAO1);
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//positin attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(containerVertices), containerVertices, GL_STATIC_DRAW);

	//positin attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// load and create a texture 
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("images.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		cout << "success in load texture" << endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	

	glm::mat4 transform;
	float flag, y,angle;
	flag = 0;
	y = 0.25f;
	angle = 45.0f;
	transform = glm::translate(transform, glm::vec3(0.6f, 0.2f, 0.0f));
	//transform = glm::rotate(transform, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.1f, 0.2f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//create transformation 

		/*if (flag == 0)
		{
			flag++; angle = -90; y = 0.5;
		}
		else if (flag == 1)
		{
			flag++; angle = 0;
		}
		else if (flag == 2)
		{
			flag++; angle = 90; y = -0.5;
		}
		else if (flag == 3)
		{
			flag = 0; angle = 0;
		}
		transform = glm::translate(transform, glm::vec3(-0.33f, y, 0.0f));
		transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	*/	
		
		y = -y;
		transform = glm::translate(transform, glm::vec3(-0.05f, y, 0.0f));
		//transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
		angle = -angle;
		if (flag > 50 )
		{
		transform = glm::translate(transform, glm::vec3(2.0f, y, 0.0f));
		flag = 0;
		}
		flag++;

		// bind Texture
	
		containShader.use();
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO2);
		glDrawArrays(GL_POLYGON, 0, 4);

		// get matrix's uniform location and set matrix
		fishShader.use();
		unsigned int transformLoc = glGetUniformLocation(fishShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		
		// render container
		glBindVertexArray(VAO1); 		
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, (void*)0);	

		glfwSwapInterval(30);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		

	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO1);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO1);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}