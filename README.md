# GLFW_motionFish

## Installing 
* Fist for installing GLFW library follow this tutorial: 
    (https://www.youtube.com/watch?v=OR4fNpBjmq8)
    
* There is a need for:
* GLEW library for openGl functions you can find it in this link. 
    http://www.glfw.org/

* GLM library for mathematics needed for transformation.
    https://glm.g-truc.net/0.9.8/index.html

* Then you will need to add some library to your project 
    [stb_image.h](https://github.com/AliaaSamir/GLFW_motionFish/blob/master/stb_image.h)       for adding image for texture.  
    [shader.h](https://github.com/AliaaSamir/GLFW_motionFish/blob/master/Shader.h)             for shader. 

    and the shaders itself. 
     Fragment Shader [transform.fs](https://github.com/AliaaSamir/GLFW_motionFish/blob/master/transform.fs) and [texture.fs](https://github.com/AliaaSamir/GLFW_motionFish/blob/master/texture.fs).
     Vertex Shader   [transform.vs](https://github.com/AliaaSamir/GLFW_motionFish/blob/master/transform.vs) and [texture.vs](https://github.com/AliaaSamir/GLFW_motionFish/blob/master/texture.vs).


## Program description
This program is simple for startting with GLFW so contains simple transformation and texture to output a fish move in sea 
###

![](https://media.giphy.com/media/5UrVo5LYFBEE1kfZxV/giphy.gif)

### Basic parts
   The program consist of two main parts
   * First container which have the sea texture in Quad shape.
   this part has its owen shader 
  
	Shader containShader("texture.vs", "texture.fs");

   and bufferes to manage the vertices attribute 
 
	   float containerVertices[] = {
			-1.0f, 1.0f, 0.0f,			0.0f, 0.0f, 0.0f,	0.0f, 1.0f,  //top right
			 1.0f, 1.0f, 0.0f,			0.0f, 0.0f, 0.0f,	1.0f, 1.0f,  //top left
			 1.0f,-1.0f, 0.0f,			0.0f, 0.0f, 0.0f,	1.0f, 0.0f,  //bottom left
			-1.0f,-1.0f, 0.0f,			0.0f, 0.0f, 0.0f,	0.0f, 0.0f  //bottom right
		};

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
 
   * Second part which is for drawing the fish similar to first one 
   
   **Texture** 
   * Here is part of code show load and create a texture 
   ```

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
	//your own image path as first parameter 
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
```

  * In render loop you need to **Bind** texture before drawing
   ```
   		// bind Texture
		containShader.use();
		glBindTexture(GL_TEXTURE_2D, texture);
		//bind drawing vertex array buffer   
		glBindVertexArray(VAO2);
		glDrawArrays(GL_POLYGON, 0, 4);
		
 ```
  **Transformation** 
   * Here is an example in our code 'translate' you may want to use 'rotate' or 'scale'
  ```
  glm::mat4 transform;
  transform = glm::translate(transform, glm::vec3(-0.05f, y, 0.0f));
  ```
   * In render loop you need to get matrix's uniform location and set matrix
  
  		// get matrix's uniform location and set matrix
		fishShader.use();
		unsigned int transformLoc = glGetUniformLocation(fishShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

 
## useful tutorial 
* this link will help you so much

    https://learnopengl.com/Getting-started/OpenGL
* and so this playlist

    https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2


