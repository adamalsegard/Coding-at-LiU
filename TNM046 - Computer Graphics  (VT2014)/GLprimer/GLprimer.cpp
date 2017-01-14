/*
 * A C++ framework for OpenGL programming in TNM046 for MT1 2014.
 *
 * This is a small, limited framework, designed to be easy to use
 * for students in an introductory computer graphics course in
 * the first year of a M Sc curriculum. It uses custom code
 * for some things that are better solved by external libraries
 * like GLEW and GLM, but the emphasis is on simplicity and
 * readability, not generality.
 * For the window management, GLFW 3.0 is used for convenience.
 * The framework should work in Windows, MacOS X and Linux.
 * Some Windows-specific stuff for extension loading is still
 * here. GLEW could have been used instead, but for clarity
 * and minimal dependence on other code, we rolled our own extension
 * loading for the things we need. That code is short-circuited on
 * platforms other than Windows. This code is dependent only on
 * the GLFW and OpenGL libraries. OpenGL 3.3 or higher is required.
 *
 * Author: Stefan Gustavson (stegu@itn.liu.se) 2013-2014
 * This code is in the public domain.
 */

// File and console I/O for logging and error reporting
#include <iostream>
//Lägg till bibliotek, kommer visa framerate FPS :)
#include "Utilities.hpp"
//Lägger till skuggor, tjoho!
#include "Shader.hpp"
//Genererar trianglar med function, woopwoop!
#include "TriangleSoup.hpp"
//För kul matte
#include <math.h>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// In MacOS X, tell GLFW to include the modern OpenGL headers.
// Windows does not want this, so we make this Mac-only.
// Coolt!
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

// GLFW 3.x, to handle the OpenGL window
#include <GLFW/glfw3.h>


/*
 * main(argc, argv) - the standard C++ entry point for the program
 */
int main(int argc, char *argv[]) {

    using namespace std;

	int width, height;

	//const double M_PI = 3.14;

    const GLFWvidmode *vidmode;  // GLFW struct to hold information about the display
	GLFWwindow *window;    // GLFW struct to hold information about the window

    Shader myShader;    //Declare a shader

    TriangleSoup myShape; //Generate triangle

    float time; // Declare the same variable as in Vertex shader
    GLint location_time;


    //4x4 matris composite + tom
    GLfloat Tcomp[16] = {0};
    GLfloat Tlight[16] = {0};
    GLfloat M[16] = {0};

    //Perspektive
    GLfloat MV[16] = {0};
    GLfloat P[16] = {0};


    // Initialise GLFW
    glfwInit();

    // Determine the desktop size
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Make sure we are getting a GL context of at least version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Exclude old legacy cruft from the context. We don't need it, and we don't want it.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    cout<< "Gick bra hit" << endl;

    // Open a square window (aspect 1:1) to fill half the screen height
    window = glfwCreateWindow(vidmode->height/4, vidmode->height/4, "GLprimer", glfwGetPrimaryMonitor(), NULL);
    if (!window)
    {
        cout << "Unable to open window. Terminating." << endl;
        glfwTerminate(); // No window was opened, so we can't continue in any useful way
        return -1;
    }

    // Make the newly created window the "current context" for OpenGL
    // (This step is strictly required, or things will simply not work)
    glfwMakeContextCurrent(window);

    // Show some useful information on the GL context
    cout << "GL vendor:       " << glGetString(GL_VENDOR) << endl;
    cout << "GL renderer:     " << glGetString(GL_RENDERER) << endl;
    cout << "GL version:      " << glGetString(GL_VERSION) << endl;
    cout << "Desktop size:    " << vidmode->width << "x" << vidmode->height << " pixels" << endl;


    // Load extensions (only needed in Microsoft Windows)
    Utilities::loadExtensions();

    //Baksidan ritas ej
    glEnable(GL_CULL_FACE);

    myShader.createShader("vertex.glsl", "fragment.glsl");


    glfwSwapInterval(0); // Do not wait for screen refresh between frames


    location_time = glGetUniformLocation(myShader.programID, "time");
    if(location_time == -1){ //If the variable was not found, -1 was returned.
        cout << "Unable to locate variable 'time' in shader!" << endl;
    }


    // Generate a shape
    //myShape.createTriangle();
    //myShape.createSphere(1, 50);
    myShape.createBox(0.2, 0.2, 1.0);


    //Transformations and light
    GLint location_Tcomp;
    location_Tcomp = glGetUniformLocation(myShader.programID, "Tcomp");
    GLint location_Tlight;
    location_Tlight = glGetUniformLocation(myShader.programID, "Tlight");

    //Perspektive
    GLint location_MV;
    location_MV = glGetUniformLocation(myShader.programID, "MV");
    GLint location_P;
    location_P = glGetUniformLocation(myShader.programID, "P");


    // Main loop
    while(!glfwWindowShouldClose(window))
    {

		// Get window size. It may start out different from the requested
        // size, and will change if the user resizes the window.
        glfwGetWindowSize( window, &width, &height );
        // Set viewport. This is the pixel rectangle we want to draw into.
        glViewport( 0, 0, width, height ); // The entire window

		// Set the clear color and depth, and clear the buffers for drawing
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Visa FPS
        Utilities::displayFPS(window);


        //Show outlines of background, Fill or Line
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Kalla på Shadern!
        glUseProgram(myShader.programID);


        /* ---- Rendering code should go here ---- */


        time = (float)glfwGetTime(); //Number of seconds since the program was started
        glUseProgram(myShader.programID); // Activate the shader to set its variables
        glUniform1f(location_time, time); // Copy the value of time to the shader program


        glUniformMatrix4fv(location_Tcomp, 1, GL_FALSE, Tcomp); //Copy the value of the composite transformation matrix
        glUniformMatrix4fv(location_Tlight, 1, GL_FALSE, Tlight);

        //Lab 4
        glUniformMatrix4fv(location_MV, 1, GL_FALSE, MV);
        glUniformMatrix4fv(location_P, 1, GL_FALSE, P);


        //Transformations
        mat4identity(Tcomp);
        mat4identity(M);


        double RotTime = (M_PI/2)*glfwGetTime();
        mat4roty (M, RotTime);
        mat4mult(M, Tcomp, Tcomp);

        mat4rotx(M, 0.2);
        mat4mult(M, Tcomp, Tcomp);


        //Light
        mat4identity(Tlight);
        //double RotLightTime = (M_PI/2)*glfwGetTime();
        //mat4roty (M, RotLightTime);
        //mat4mult(M, Tlight, Tlight);

        //Perspektive
        mat4identity(P);
        mat4perspective(P, M_PI/4, 1.0, 0.1, 100.0);


        mat4identity(MV);
        mat4translate(M, 0.0, 0.0, -2.0);
        mat4mult(M, Tcomp, MV);



        //Draw the shape!
        myShape.render();


		// Swap buffers, i.e. display the image and prepare for next frame.
        glfwSwapBuffers(window);

		// Poll events (read keyboard and mouse input)
		glfwPollEvents();

        // Exit if the ESC key is pressed (and also if the window is closed).
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
          glfwSetWindowShouldClose(window, GL_TRUE);
        }

    }

    // Close the OpenGL window and terminate GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

