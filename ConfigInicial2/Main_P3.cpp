/*
	Proyecciones, Transformaciones y Shaders
	Meza Sanchez Luis Arturo
	Fecha de entrega: 21 / Feb / 2025
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecciones y transformaciones basicas | Luis Arturo Meza Sanchez", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
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


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection

	//Para la vista ortogonal 
	/*
	GLfloat vertices[] = {
	   -0.5f*500, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f * 500, -0.5f * 500, 0.5f * 500,  1.0f, 0.0f,0.0f,
		0.5f * 500,  0.5f * 500, 0.5f * 500,  1.0f, 0.0f,0.0f,
		0.5f * 500,  0.5f * 500, 0.5f * 500,  1.0f, 0.0f,0.0f,
		-0.5f * 500,  0.5f * 500, 0.5f * 500, 1.0f, 0.0f,0.0f,
		-0.5f * 500, -0.5f * 500, 0.5f * 500, 1.0f, 0.0f,0.0f,
		-0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,//Back
		 0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
		 0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
		 0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
		-0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
		-0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
		 0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,1.0f,
		 0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,1.0f,
		 0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 0.0f,1.0f,
		 0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 0.0f,1.0f,
		 0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f,1.0f,
		 0.5f * 500,  -0.5f * 500, 0.5f * 500, 0.0f, 0.0f,1.0f,
		-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,0.0f,
		-0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,0.0f,
		-0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,0.0f,
		-0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,0.0f,
		-0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 1.0f,0.0f,
		-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,0.0f,
		-0.5f * 500, -0.5f * 500, -0.5f * 500, 0.0f, 1.0f,1.0f,
		0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,1.0f,
		0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 1.0f,1.0f,
		0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 1.0f,1.0f,
		-0.5f * 500, -0.5f * 500,  0.5f * 500, 0.0f, 1.0f,1.0f,
		-0.5f * 500, -0.5f * 500, -0.5f * 500, 0.0f, 1.0f,1.0f,
		-0.5f * 500,  0.5f * 500, -0.5f * 500, 1.0f, 0.2f,0.5f,
		0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 0.2f,0.5f,
		0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.2f,0.5f,
		0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.2f,0.5f,
		-0.5f * 500,  0.5f * 500,  0.5f * 500, 1.0f, 0.2f,0.5f,
		-0.5f * 500,  0.5f * 500, -0.5f * 500, 1.0f, 0.2f,0.5f,
	};
		*/

		//Para la vista en perspectiva

		// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,

		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
		//     
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		//	
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		//	
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	//PAra la vista en perspectiva 
	projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar

	//Para la vista ortogonal
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);

		//Matriz para comenzar a manipular la vista 

		view = glm::translate(view, glm::vec3(-7.0f, 0.0f, -10.0f));
		model = glm::rotate(model, 1.5f, glm::vec3(0.0f, 2.0f, 0.0f)); // use to compare orthographic and perspective projection
		model = glm::scale(model, glm::vec3(0.5f, 4.0f, 0.0f));



		//view = glm::translate( view, glm::vec3( screenWidth / 2, screenHeight / 5,-800.0f ) ); // use with orthographic projection
		//con la ultima instruccion se puede observar el recorte 

		//Comunicación por variables del codigo al shader 
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);


		//Primer cubo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.5f, -1.5f, 0.0f));
		model = glm::rotate(model, -0.2f, glm::vec3(0.5f, 1.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Segundo cubo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.0f, -1.5f, 0.0f));
		model = glm::rotate(model, 3.5f, glm::vec3(4.5f, 0.0f, 0.6f)); 
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//// Tercer cubo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.5f, -1.5f, 0.0f));
		model = glm::rotate(model, 1.5f, glm::vec3(45.0f, 0.0f, 0.3f)); 
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuarto cubo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(5.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 1.2f, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//// Quinto cubo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 4.0f, glm::vec3(0.7f, 5.3f, 1.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Sexto cubo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.0f, 3.0f, 0.0f));
		model = glm::rotate(model, 16.0f, glm::vec3(1.0f, 10.0f, 12.9f)); // use to compare orthographic and perspective projection
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;



}