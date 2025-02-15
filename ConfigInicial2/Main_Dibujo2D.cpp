/*
	Practica  Dibujo de primitivas en 2D
	Arturo Meza
	12/02/2025
*/

#include<iostream>
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D   |   Luis Arturo Meza Sanchez", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		// x	y	  z			R	 G 	 B
		// Color blanco
		-0.46f,  0.37f,  0.0f,   1.0f, 1.0f, 1.0f,   // C 0
		-0.02f, -0.47f,  0.0f,   1.0f, 1.0f, 1.0f,   // D 1
		0.44f,  0.35f,   0.0f,   1.0f, 1.0f, 1.0f,    // E 2
		-0.34f, -0.78f,  0.0f,   1.0f, 1.0f, 1.0f,   // F 3
		-0.60f, -0.20f,  0.0f,   1.0f, 1.0f, 1.0f,	 // G 4
		0.31f, -0.79f,   0.0f,   1.0f, 1.0f, 1.0f,	 // H 5
		0.56f, -0.22f,   0.0f,   1.0f, 1.0f, 1.0f,	 // I 6
		-0.42f,  0.30f,  0.0f,   1.0f, 1.0f, 1.0f,   // J 7
		-0.19f, -0.17f,  0.0f,   1.0f, 1.0f, 1.0f,	 // K 8
		0.15f, -0.17f,   0.0f,   1.0f, 1.0f, 1.0f,	 // L 9
		0.00f,  0.00f,   0.0f,   1.0f, 1.0f, 1.0f,	 // M 10
		// Color amarillo
		 0.44f,  0.35f,  0.0f,   1.0f, 0.85f, 0.0f,  // E 11
		-0.42f,  0.30f,  0.0f,   1.0f, 0.85f, 0.0f,  // J 12
		-0.18f, -0.16f,  0.0f,   1.0f, 0.85f, 0.0f,  // K 13
		 0.15f, -0.17f,  0.0f,   1.0f, 0.85f, 0.0f,  // L 14
		 0.00f,  0.00f,  0.0f,   1.0f, 0.85f, 0.0f,  // M 15
		-0.28f,  0.69f,  0.0f,   1.0f, 0.85f, 0.0f,  // N 16
		 0.16f,  0.86f,  0.0f,   1.0f, 0.85f, 0.0f,  // O 17
		 0.26f,  0.67f,  0.0f,   1.0f, 0.85f, 0.0f,  // P 18
		 0.34f,  0.83f,  0.0f,   1.0f, 0.85f, 0.0f,  // Q 19
		 0.19f,  0.80f,  0.0f,   1.0f, 0.85f, 0.0f   // R 20
	};

	unsigned int indices[] = { 
		//		C A S C A R O N
		3,1,4,				// Fig 1
		0,1,4,				// Fig 2
		1,2,6,				// Fig 3
		1,5,6,				// Fig 4
		1,3,5,				// Fig 5
		1,8,10,				// Fig 6
		1,9,10,				// Fig 7
		//		 P O L L O
		12,13,15,			// Fig 8
		12,15,16,			// Fig 9
		18,15,16,			// Fig 10
		11,15,18,			// Fig 11
		11,15,14,			// Fig 12
		16,17,18,			// Fig 13
		18,19,20,			// Fig 14
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);
        //glPointSize(10);				// Dibujo de un punto
        //glDrawArrays(GL_POINTS,0,1);	// Dibujo de puntos
        //glDrawArrays(GL_LINES,0,2);
        //glDrawArrays(GL_LINE_LOOP,0,4);	// Dibujar lineas
        //glDrawArrays(GL_TRIANGLES,0,3);  
		
		
		// Dibujamos todo
		glDrawElements(GL_TRIANGLES, 42,GL_UNSIGNED_INT,0); 	

        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}