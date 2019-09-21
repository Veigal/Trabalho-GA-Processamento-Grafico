#include "System.h"



System::System()
{
}


System::~System()
{
}

int System::GLFWInit()
{

	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
	glfwWindowHint( GLFW_SAMPLES, 4 );

	window = glfwCreateWindow( WIDTH, HEIGHT, "Sabertooth", nullptr, nullptr );

	glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

	if ( window == nullptr ) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent( window );

	glewExperimental = GL_TRUE;

	if ( glewInit() != GLEW_OK ) {
		std::cout << "Failed no init GLEW." << std::endl;
		return EXIT_FAILURE;
	}

	glViewport( 0, 0, screenWidth, screenHeight );

	return EXIT_SUCCESS;

}

int System::OpenGLSetup()
{

	glEnable( GL_BLEND );	// Enables blending ( glBlendFunc )
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glEnable( GL_DEPTH_TEST );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CW );

	return EXIT_SUCCESS;
}

int System::SystemSetup()
{

	coreShader = Shader( "Shaders/Core/core.vert", "Shaders/Core/core.frag" );
	coreShader.Use();

	return EXIT_SUCCESS;
}

void System::Run()
{

	GLfloat vertices0[] =
	{
		// Positions         // Textures

		 1.0f,  1.0f, 0.0f,   0.7f, 1.0f, // Top Right
		 1.0f, -1.0f, 0.0f,   0.7f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left

		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f, // Top Left
		 1.0f,  1.0f, 0.0f,   0.7f, 1.0f, // Top Right
	};

	GLfloat vertices1[] =
	{
		// Positions         // Textures

		 1.0f,  1.0f, 0.0f,   0.7f, 4.0f, // Top Right
		 1.0f, -1.0f, 0.0f,   0.7f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left

		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   0.0f, 4.0f, // Top Left
		 1.0f,  1.0f, 0.0f,   0.7f, 4.0f, // Top Right
	};

	GLfloat vertices2[] =
	{
		// Positions         // Textures

		 1.0f,  1.0f, 0.0f,   0.7f, 1.0f, // Top Right
		 1.0f, -1.0f, 0.0f,   0.7f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left

		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f, // Top Left
		 1.0f,  1.0f, 0.0f,   0.7f, 1.0f, // Top Right
	};


	//Carro
	coreShader.Use();

	coreShader.LoadTexture("bin/Images/carro.png", "texture0", "carro");


	GLuint VBO0, VAO0;
	glGenVertexArrays(1, &VAO0);
	glGenBuffers(1, &VBO0);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO



	//Grama
	coreShader.Use();

	coreShader.LoadTexture("bin/Images/grama.png", "texture1", "grama");


	GLuint VBO1, VAO1;
	glGenVertexArrays( 1, &VAO1 );
	glGenBuffers( 1, &VBO1 );

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray( VAO1 );

	glBindBuffer( GL_ARRAY_BUFFER, VBO1 );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices1 ), vertices1, GL_STATIC_DRAW );

	// Position attribute
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * ) 0 );
	glEnableVertexAttribArray( 0 );

	// Texture attribute
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * ) ( 3 * sizeof( GLfloat ) ) );
	glEnableVertexAttribArray( 1 );

	glBindVertexArray( 0 ); // Unbind VAO


	//Background
	coreShader.Use();

	coreShader.LoadTexture("bin/Images/background.jpg", "texture2", "background");



	GLuint VBO2, VAO2;
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
//teste

	GLfloat offsetx[3] = { 0,0,0 }, offsety[3] = {0,0,0}, z[3] = { 1.0, 1.0,1.0 };
	while ( !glfwWindowShouldClose( window ) ) {

		glfwPollEvents();

#pragma region Input Handling

		if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) {
			glfwSetWindowShouldClose( window, GLFW_TRUE );
		}

#pragma endregion

		//glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



		for (int i = 0; i < 3; i++) {     // Caso necessário ou conforme evento, deslocar camada 
			coreShader.Use();
			switch (i)
			{
			case 0:
				glBindVertexArray(VAO0);
				offsetx[i] += 0.001;
				coreShader.UseTexture("carro");
				break;
			case 1:
				glBindVertexArray(VAO1);
				offsetx[i] += 0.001;
				coreShader.UseTexture("grama");
				break;
			case 2:
				glBindVertexArray(VAO2);
				offsetx[i] += 0.00005;
				coreShader.UseTexture("background");
				break;
			}


			glUniform1f(      
				glGetUniformLocation(coreShader.getProgram(), "offsetx"), offsetx[i]);
		    glUniform1f(      
				glGetUniformLocation(coreShader.getProgram(), "offsety"), offsetx[i]);
			glUniform1f(      
				glGetUniformLocation(coreShader.getProgram(), "layer_z"), z[i]);
			glUniform1f(
				glGetUniformLocation(coreShader.getProgram(), "id"), i);
			// bind Texture
			/*
			coreShader.Use();
			if (i == 0) {
				//glActiveTexture(GL_TEXTURE0);
				coreShader.UseTexture("grama");
			}
			else {
				//glActiveTexture(GL_TEXTURE1);
				coreShader.UseTexture("background");
			}
			*/
			glUniform1i(glGetUniformLocation(coreShader.getProgram(), "sprite"), 0);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays( GL_TRIANGLES, 0, 6 );
		}

		glBindVertexArray( 0 );
		

		glfwSwapBuffers( window );
	}


}

void System::Finish()
{
	coreShader.Delete();

	glfwTerminate();
}
