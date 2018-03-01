#include "main.h"
#include "timer.h"
#include "boat.h"
#include "water.h"
#include "building.h"
#include "cannon.h"
#include "sphere.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Boat boat1;
Water water1;
Building building1;
Cannon cannon;
Sphere box;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw()
{
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
   //glm::vec3 eye ( 0, 5*cos(camera_rotation_angle*M_PI/180.0f),5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( 0, 15,20);
    glm::vec3 target (0, 0, 0);
    glm::vec3 up (0, 1, 0);

    /* Top View*/
    /*glm::vec3 eye ( boat1.position.x,boat1.position.y+45,boat1.position.z-2);
    glm::vec3 target (boat1.position.x,boat1.position.y,boat1.position.z);
    glm::vec3 up (0, 1, 0);*/

    // Follow Cam View
      /*  glm::vec3 eye ( boat1.position.x,boat1.position.y+10,boat1.position.z-10);
        glm::vec3 target (boat1.position.x,boat1.position.y,boat1.position.z+5);
        glm::vec3 up (0, 1, 0);*/
/* Boat View*/
//     glm::vec3 eye (boat1.position.x,boat1.position.y+3,boat1.position.z-2);
  //   glm::vec3 target (boat1.position.x,boat1.position.y+2,boat1.position.z-5);
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    water1.draw(VP);
    boat1.draw(VP);
    box.draw(VP);
    cannon.draw(VP,0,0,0);//boat1.position.x,boat1.position.y,boat1.position.z);
//building1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int canup = glfwGetKey(window, GLFW_KEY_A);
    int candwn= glfwGetKey(window, GLFW_KEY_D);
    int canw = glfwGetKey(window, GLFW_KEY_W);
    int cans= glfwGetKey(window, GLFW_KEY_S);
    if (left) {
        //boat1.cannon.up();
        boat1.left();
        cannon.left();
        // Do something
    }
    if (cans){
        boat1.rotation += 0.5;
        cannon.rotation += 0.5;
    }
    if(canw){
        boat1.rotation -= 0.5;
        cannon.rotation -= 0.5;
    }
    if(right)
    {
        boat1.right();
        cannon.right();
    }
    if(up) {
        //boat1.
        boat1.up();
        cannon.up();
    }
    if(down) {
        //boat1.cannon.down();
        boat1.down();
        cannon.down();
    }
    if(canup){
        cannon.move_up();
       // boat1.cannon.up();

}
    if(candwn){
        cannon.move_dwn();
        //boat1.cannon.down();
    }
}

void tick_elements() {
    //boat1.tick();
    //boat1.cannon.tick();
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    water1 = Water(0, 1, 0,COLOR_BLUE);
    boat1 = Boat(0, 4, 0);
    cannon = Cannon(0,4,0);
    box = Sphere(0,5,3,1);

    //building1 = Building(4,0,COLOR_GREEN);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();

            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(1.0f, 1.0f, 1.0f, 100.0f);
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
