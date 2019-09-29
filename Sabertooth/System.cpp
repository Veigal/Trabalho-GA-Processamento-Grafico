#include "System.h"
#include <GLFW/glfw3.h>

#define CAMADA_HIDRANTE 0
#define CAMADA_CARRO CAMADA_HIDRANTE +1
#define CAMADA_ASFALTO CAMADA_CARRO +1
#define CAMADA_BACKGROUND CAMADA_ASFALTO +1

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

	GLfloat topy = -0.51;
	GLfloat boty = topy - 0.12;
	GLfloat topx = 0.5;
	GLfloat botx = topx - (topy - boty)*0.75;


	GLfloat verticesHidrante[] =
	{
		// Positions         // Textures

		 topx, topy, 0.0f,   1.0f, 1.0f, // Top Right
		 topx, boty, 0.0f,   1.0f, 0.0f, // Bottom Right
		 botx, boty, 0.0f,   0.0f, 0.0f, // Bottom Left

		 botx, boty, 0.0f,   0.0f, 0.0f, // Bottom Left
		 botx, topy, 0.0f,   0.0f, 1.0f, // Top Left
		 topx, topy, 0.0f,   1.0f, 1.0f, // Top Right
	};


	topy = -0.405;
	boty = topy - 0.25;
	topx = 0.0;
	botx = topx - 0.5;


	GLfloat verticesCarro[] =
	{
		// Positions         // Textures

		 topx, topy, 0.0f,   0.5f, 1.0f, // Top Right
		 topx, boty, 0.0f,   0.5f, 0.75f, // Bottom Right
		 botx, boty, 0.0f,   0.0f, 0.75f, // Bottom Left

		 botx, boty, 0.0f,   0.0f, 0.75f, // Bottom Left
		 botx, topy, 0.0f,   0.0f, 1.0f, // Top Left
		 topx, topy, 0.0f,   0.5f, 1.0f, // Top Right
	};

	GLfloat verticasAsfalto[] =
	{
		// Positions         // Textures

		 1.0f,  1.0f, 0.0f,   0.7f, 1.0f, // Top Right
		 1.0f, -1.0f, 0.0f,   0.7f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left

		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f, // Top Left
		 1.0f,  1.0f, 0.0f,   0.7f, 1.0f, // Top Right
	};

	GLfloat verticesBackground[] =
	{
		// Positions         // Textures

		 1.0f,  1.0f, 0.0f,   0.7f, 1.0f, // Top Right
		 1.0f, -1.0f, 0.0f,   0.7f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left

		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f, // Top Left
		 1.0f,  1.0f, 0.0f,   0.7f, 1.0f, // Top Right
	};


	//
	coreShader.Use();

	coreShader.LoadTexture("bin/Images/hidranteok.png", "texture3", "hidrante");


	GLuint VBOHidrante, VAOHidrante;
	glGenVertexArrays(1, &VAOHidrante);
	glGenBuffers(1, &VBOHidrante);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAOHidrante);

	glBindBuffer(GL_ARRAY_BUFFER, VBOHidrante);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHidrante), verticesHidrante, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO



	//Carro
	coreShader.Use();

	coreShader.LoadTexture("bin/Images/carrook.png", "texture0", "carro");


	GLuint VBOCarro, VAOCarro;
	glGenVertexArrays(1, &VAOCarro);
	glGenBuffers(1, &VBOCarro);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAOCarro);

	glBindBuffer(GL_ARRAY_BUFFER, VBOCarro);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCarro), verticesCarro, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO



	//Asfalto
	coreShader.Use();

	coreShader.LoadTexture("bin/Images/camada 2.png", "texture1", "asfalto");


	GLuint VBOAsfalto, VAOAsfalto;
	glGenVertexArrays( 1, &VAOAsfalto );
	glGenBuffers( 1, &VBOAsfalto );

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray( VAOAsfalto );

	glBindBuffer( GL_ARRAY_BUFFER, VBOAsfalto );
	glBufferData( GL_ARRAY_BUFFER, sizeof( verticasAsfalto ), verticasAsfalto, GL_STATIC_DRAW );

	// Position attribute
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * ) 0 );
	glEnableVertexAttribArray( 0 );

	// Texture attribute
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * ) ( 3 * sizeof( GLfloat ) ) );
	glEnableVertexAttribArray( 1 );

	glBindVertexArray( 0 ); // Unbind VAO


	//Background
	coreShader.Use();

	coreShader.LoadTexture("bin/Images/background.png", "texture2", "background");



	GLuint VBOBackground, VAOBackground;
	glGenVertexArrays(1, &VAOBackground);
	glGenBuffers(1, &VBOBackground);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAOBackground);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBackground);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBackground), verticesBackground, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
//teste


	static double previousSeconds, elapsedSeconds;
	GLboolean spacePressed = false;
	GLfloat offsetx[CAMADA_BACKGROUND+1] = { 0,0,0,0 }, offsety[CAMADA_BACKGROUND+1] = {0,0,0,0}, z[CAMADA_BACKGROUND+1] = { 1.0, 1.0,1.0,1.0 }, k=0;
	while ( !glfwWindowShouldClose( window ) ) {

		glfwPollEvents();

#pragma region Input Handling

		if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) {
			glfwSetWindowShouldClose( window, GLFW_TRUE );
		}

		
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
			offsetx[1] = 0.5;
			previousSeconds = glfwGetTime();
			spacePressed = true;
		}

		elapsedSeconds = glfwGetTime() - previousSeconds;
		if (spacePressed) {
			if (elapsedSeconds >= 2) {
				spacePressed = false;
				offsetx[1] = 0.0;
				offsety[1] = 0.0;
			}
			else {
				if (elapsedSeconds >= 0.5) {
					offsety[1] = 0.5;
					offsetx[1] = 0.5;
				}
				else {
					if (elapsedSeconds >= 0.2) {
						offsety[1] = 0.75;
						offsetx[1] = 0.5;

					}
					else {
						if (elapsedSeconds >= 0.1) {
							offsety[1] = 0.25;
							offsetx[1] = 0.5;

						}
						else {
						}
					}
				}
			}
		}

#pragma endregion

		//glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



		for (int i = 0; i < CAMADA_BACKGROUND+1; i++) {     // Caso necessário ou conforme evento, deslocar camada 
			coreShader.Use();
			


			//Controla a posição do hidrante
			if (i == CAMADA_HIDRANTE) {
				k -= 0.005;
				glm::mat4 transform = glm::mat4(1.0f);
				transform = glm::translate(transform, glm::vec3(k, 0.0f, 0.0f));
				//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 0.0f));
				//Onde é montada a matriz de translação
				glUseProgram(coreShader.getProgram());
				glUniformMatrix4fv((glGetUniformLocation(coreShader.getProgram(), "matrix")), 1, GL_FALSE, glm::value_ptr(transform));

				//Checa a colisão e caso colidiu volta para o início da tela
				if ((0.45+k)<=0 && (0.45 + k) >= -0.2 && !spacePressed) {
					k=0.5;
				}
				if ((0.45 + k) <= -1.0) {
					k = 0.5;
				}
			}
			else {
				//Controla a posição dos demais objetos (sempre parados)
				glm::mat4 transform = glm::mat4(1.0f);
				glUseProgram(coreShader.getProgram());
				glUniformMatrix4fv((glGetUniformLocation(coreShader.getProgram(), "matrix")), 1, GL_FALSE, glm::value_ptr(transform));

			}
			switch (i)
			{
			case CAMADA_HIDRANTE:


				glBindVertexArray(VAOHidrante);
				offsetx[i] += 0;
				coreShader.UseTexture("hidrante");
				break;
			case CAMADA_CARRO:
				glBindVertexArray(VAOCarro);
				
				coreShader.UseTexture("carro");
				break;
			case CAMADA_ASFALTO:
				glBindVertexArray(VAOAsfalto);
				offsetx[i] += 0.001;
				coreShader.UseTexture("asfalto");
				break;
			case CAMADA_BACKGROUND:
				glBindVertexArray(VAOBackground);
				offsetx[i] += 0.00005;
				coreShader.UseTexture("background");
				break;
			}


			glUniform1f(      
				glGetUniformLocation(coreShader.getProgram(), "offsetx"), offsetx[i]);
		    glUniform1f(      
				glGetUniformLocation(coreShader.getProgram(), "offsety"), offsety[i]);
			glUniform1f(      
				glGetUniformLocation(coreShader.getProgram(), "layer_z"), z[i]);
			glUniform1f(
				glGetUniformLocation(coreShader.getProgram(), "id"), i);


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
