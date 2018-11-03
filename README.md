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


## program discription
This program is simple for startting with GLFW so contains simple transformation and texture to output a fish move in sea 
###

![](https://media.giphy.com/media/5UrVo5LYFBEE1kfZxV/giphy.gif)

### basic parts
   the program consist of two main parts
   * first container which have the sea texture in Quad shape.this part has its owen shader 
   '''
   Shader containShader("texture.vs", "texture.fs");
   '''
   and bufferes to manage the vertices attribute 
   '''
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
   '''
   

## useful tutorial 
* this link will help you so much

    https://learnopengl.com/Getting-started/OpenGL
* and so this playlist

    https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2


