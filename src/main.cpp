#include "main.h"
#include "timer.h"
#include "boat.h"
#include "water.h"
#include "monster.h"
#include "cannon.h"
#include "sphere.h"
#include "rock.h"
#include "segmentdisplay.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Boat boat;
Water water1;
vector<Sphere> fireball;
double camera_rotation_angle = 100, camera_y = 4, camera_zoom = 0, camera_look_x = -170, camera_look_y = 60;
color_t randcolor[] = {COLOR_GREEN, COLOR_WHITE, COLOR_CLAN,COLOR_YELLOW};
vector<Monster> monster(8);
vector<Monster> bossmonster;
vector<Rock> rock(50);
vector<Rock> gifts;
vector<Rock> biggifts;
Segmentdisplay score;
Segmentdisplay health;
Segmentdisplay game_time;
int i=0;
int killcnt=0;
bool is_audio=0;
int cnt=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
int flag = 0;
double start_timer;
double sound_timer;
glm::vec3 eye,target,up;
camera_view_t camera_view;

Timer t60(1.0 / 120);
Timer t1(1.0);
Timer t2(3.0);
Timer t3(9.1);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
double getRandDouble(double l, double r)
{
    return l + (((double)rand()) / RAND_MAX) * (r - l);
}

void draw()
{
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    if (camera_view == CAMERA_FOLLOW){
        eye = glm::vec3 (boat.position.x,boat.position.y+10,boat.position.z+15);
        target = glm::vec3(boat.position.x,boat.position.y+5,boat.position.z);
        up  = glm::vec3 (0, 1, 0);
    }

    else if (camera_view == CAMERA_DRIVER){
        eye  = glm::vec3(boat.position.x ,boat.position.y+3,boat.position.z-2*cos((boat.rotation)* PI / 180.0));
        target  = glm::vec3(boat.position.x - 4*sin(boat.rotation* PI / 180.0),boat.position.y+2,boat.position.z-6*cos((boat.rotation)* PI / 180.0));
        up = glm::vec3 (0, 1, 0);
    }

    else if (camera_view == CAMERA_TOP){
        eye  = glm::vec3(boat.position.x, boat.position.y+45, boat.position.z-2);
        target = glm::vec3 (boat.position.x,boat.position.y,boat.position.z);
        up = glm::vec3 (0, -1, 0);
    }

    else if (camera_view == CAMERA_NORMAL){
        eye = glm::vec3( 0, 15,20);
        target = glm::vec3(0, boat.position.y, 0);
        up = glm::vec3(0, 1, 0);
    }

    else if (camera_view == CAMERA_TOWER){
        eye = glm::vec3( 10*cos(camera_rotation_angle*M_PI/180.0f)-2, camera_y, 10*sin(camera_rotation_angle*M_PI/180.0f) + 11 );
        target = glm::vec3 (0, 3, -2);
        up = glm::vec3(0, 1, 0);
    }

    else if (camera_view == CAMERA_HELICOPTER){
        target = glm::vec3 (10, 0, 10);
        eye = glm::vec3 ( 10 + (20-camera_zoom/5)*cos(camera_look_x*M_PI/180.0f)*sin(camera_look_y*M_PI/180.0f), (20-camera_zoom/5)*cos(camera_look_y*M_PI/180.0f), 10 + (20-camera_zoom/5)*sin(camera_look_x*M_PI/180.0f)*sin(camera_look_y*M_PI/180.0f) );
        up  = glm::vec3 (0, 1, 0);
       }
    glm::mat4 VP;
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    if (camera_view != CAMERA_HELICOPTER)
        VP = Matrices.view * glm::scale(glm::vec3(exp(camera_zoom)));
    else
        VP = Matrices.view;
    if (camera_ortho)
        VP = Matrices.projectionO * VP;
    else
        VP = Matrices.projectionP * VP;

    // Scene render
    water1.draw(VP);
    boat.draw(VP);
    score.set_position(boat.position.x+3, boat.position.y+12, boat.position.z);
    score.update(score.view());
    health.set_position(boat.position.x-9.5, boat.position.y+12, boat.position.z);
    health.update(health.view());
    game_time.set_position(boat.position.x-3, boat.position.y+12, boat.position.z);
    game_time.update(game_time.view());
    score.draw(VP);
    health.draw(VP);
    game_time.draw(VP);

    for(int i=0;i<monster.size();i++)
        monster[i].draw(VP);

    for(int i=0;i<bossmonster.size();i++)
        bossmonster[i].draw(VP);

    for (int i=0;i<fireball.size();i++)
        fireball[i].draw(VP);

    for(int i=0;i<rock.size();i++)
        rock[i].draw(VP);

    for(int i=0;i<gifts.size();i++)
        gifts[i].draw(VP);

    for(int i=0;i<biggifts.size();i++)
        biggifts[i].draw(VP);

}
void add_fireball(){
fireball.push_back(Sphere(-1000,1000,-1000,2,COLOR_RED));
}
void fire_fireball()
{

    int i = fireball.size();
    printf("%d\n",i);
    if(i==0)
        add_fireball();


    if(i==1)
    {
        is_audio = true;
        sound_timer = glfwGetTime();
        fireball[i-1].position = glm::vec3 (boat.position.x- 6*sin(boat.rotation* PI / 180.0),boat.position.y+2,boat.position.z + 6*cos((boat.rotation+180)* PI / 180.0));//cannon.position.x, cannon.position.y , cannon.position.z);
        fprintf(stderr,"fire,%f %f %f\n",fireball[i-1].position.x,fireball[i-1].position.y,fireball[i-1].position.z);
        fireball[i-1].speed = glm::vec3(boat.speed.x-0.8*sin(boat.rotation*PI/180.0),boat.speed.y + 0.5,boat.speed.z-0.8*cos(boat.rotation*PI/180.0));
        add_fireball();
    }

}

void tick_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_S)) camera_rotation_angle += 5;
    if (glfwGetKey(window, GLFW_KEY_Z)) camera_y += 0.05;
    if (glfwGetKey(window, GLFW_KEY_X)) camera_y -= 0.05;

    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    int jump = glfwGetKey(window, GLFW_KEY_SPACE);

    if(jump)
        boat.jump();

    if(left)
        boat.left();

    if(right)
        boat.right();

    if(up)
        boat.forward();;

    if(down)
        boat.backward();

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        camera_look_x -= -360 + (xpos - prev_xpos) * 90 / width;
        camera_look_y -= -360 + (ypos - prev_ypos) * 90 / height;
        camera_look_x = camera_look_x > 360 ? camera_look_x - ((int) (camera_look_x / 360))*360 : camera_look_x;
        camera_look_y = camera_look_y > 360 ? camera_look_y - ((int) (camera_look_y / 360))*360 : camera_look_y;
        prev_xpos = xpos;
        prev_ypos = ypos;
    }
}

void game_over(){
    if(health.view() <= 0 || game_time.view() <=0)
        quit(window);
}

void tick_elements() {
    game_over();
    boat.tick();
    water1.tick();
    double cur = glfwGetTime();
    if(cur - start_timer > 4)
        boat.set_speed(0.5f);
    if(cur - sound_timer > 1)
        is_audio = false;

    //boat.sail.rotation+=6;
    for (int i=0;i<fireball.size();i++)
    {
        fireball[i].tick();
        if(fireball[i].position.y < 0){
            fireball.erase(fireball.begin()+i);
        }
    }

    for(int i=0;i<monster.size();i++)
    {
        monster[i].tick();
        if(monster[i].position.x<boat.position.x)
        {
            monster[i].position.x+=0.1;
            monster[i].head.position.x += 0.1;
        }
        else{
            monster[i].position.x-=0.1;
            monster[i].head.position.x -= 0.1;
        }
        if(monster[i].position.z<boat.position.z){
            monster[i].position.z+=0.1;
            monster[i].head.position.z += 0.1;
        }
        else{
            monster[i].position.z-=0.1;
            monster[i].head.position.z -= 0.1;
        }
        if(detect_collision(fireball[0].bounding_box(), monster[i].bounding_box()))
        {
            is_audio = true;
            sound_timer = glfwGetTime();
            score.add(10);
            killcnt ++;

            if(killcnt % 3 == 0){
                bossmonster.push_back(Monster(
                                          monster[i].position.x,
                                          monster[i].position.y,
                                          monster[i].position.z-1,
                                          4,1,
                                          2,
                                          randcolor[rand()%4],
                                      randcolor[rand()%4],
                        randcolor[rand()%4]

                        ));
                monster.erase(monster.begin() + i);

            }
            else
            {
                gifts.push_back(Rock(monster[i].position.x,monster[i].position.y,monster[i].position.z,2,0,false,monster[i].color));
                monster.erase(monster.begin() + i);
            }
            int k = rand()%2;
            monster.push_back(Monster(
                        getRandDouble(-300,300),
                        3,
                        getRandDouble(-1000,300),
                        2.5,
                        1,
                        k,
                        randcolor[rand()%4],
                    randcolor[rand()%4],
                    randcolor[rand()%4]
                    ));
            fireball.erase(fireball.begin());
            fprintf(stderr, "Fireball killed the monster, %d\n",killcnt);
            break;
        }

        if(detect_collision(boat.bounding_box(), monster[i].bounding_box()))
        {
            is_audio = true;
            sound_timer = glfwGetTime();
            monster.erase(monster.begin() + i);
            health.subtract(30);
            fprintf(stderr, "Boat killed the monster\n");
            break;
        }
    }

    for(int i=0;i<bossmonster.size();i++)
    {
        bossmonster[i].tick();
        if(bossmonster[i].position.x<boat.position.x)
        {
            bossmonster[i].position.x+=0.1;
            bossmonster[i].head.position.x += 0.1;
        }
        else{
            bossmonster[i].position.x-=0.1;
            bossmonster[i].head.position.x -= 0.1;
        }
        if(bossmonster[i].position.z<boat.position.z){
            bossmonster[i].position.z+=0.1;
            bossmonster[i].head.position.z += 0.1;
        }
        else{
            bossmonster[i].position.z-=0.1;
            bossmonster[i].head.position.z -= 0.1;
        }
        if(detect_collision(fireball[0].bounding_box(), bossmonster[i].bounding_box()))
        {
            is_audio = true;
            sound_timer = glfwGetTime();
            bossmonster[i].shootcnt += 1;
            fprintf(stderr, "%d %d\n",bossmonster[i].reqcnt,bossmonster[i].shootcnt);
            if(bossmonster[i].reqcnt == bossmonster[i].shootcnt)
            {
                score.add(30);
                biggifts.push_back(Rock(bossmonster[i].position.x,bossmonster[i].position.y+5,bossmonster[i].position.z,1,0,false,bossmonster[i].color));
                bossmonster.erase(bossmonster.begin() + i);
                fireball.erase(fireball.begin());
                fprintf(stderr, "Fireball killed the bossmonster\n");
            }
            fireball.erase(fireball.begin());
            break;
        }
        if(detect_collision(boat.bounding_box(), bossmonster[i].bounding_box()))
        {
            is_audio = true;
            sound_timer = glfwGetTime();
            bossmonster.erase(bossmonster.begin() + i);
            health.subtract(50);
            fprintf(stderr, "Boat killed the bossmonster\n");
            break;
        }
    }

    for(int i=0;i<gifts.size();i++)
    {
        if(detect_collision(boat.bounding_box(), gifts[i].bounding_box()))
        {
            is_audio = true;
            sound_timer = glfwGetTime();
            if(gifts[i].color.r == COLOR_GREEN.r){
                fprintf(stderr,"GREEN\n");
                health.add(15);
            }
            else if(gifts[i].color.r == COLOR_YELLOW.r){
                fprintf(stderr,"YELLOW\n");
                health.add(10);
            }
            else if(gifts[i].color.r == COLOR_CLAN.r){
                fprintf(stderr,"CLAN\n");
                boat.set_speed(1.0f);
                start_timer = glfwGetTime();
            }
            else if(gifts[i].color.r == COLOR_WHITE.r){
                fprintf(stderr,"WHITE\n");
                game_time.add(5);
            }
            gifts.erase(gifts.begin() + i);
        }
    }

    for(int i=0;i< biggifts.size();i++)
    {
        if(detect_collision(boat.bounding_box(), biggifts[i].bounding_box()))
        {
            is_audio = true;
            sound_timer = glfwGetTime();
            /* Add code for bonus*/
            boat.set_speed(1.3f);
            start_timer = glfwGetTime();
            biggifts.erase(biggifts.begin() + i);
        }
    }

    for(int i=0;i<rock.size();i++)
    {
        if(detect_collision(boat.bounding_box(), rock[i].bounding_box()))
        {
            is_audio = true;
            fprintf(stderr,"Collison occured with rock");
            sound_timer = glfwGetTime();
            health.subtract(10);
            rock.erase(rock.begin() + i);
            break;
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    water1 = Water(0, 0, 0,COLOR_BLUE);
    boat = Boat(0, 4, 0);
    char titlestr[50];
    sprintf(titlestr, "Score as much as possible");
    glfwSetWindowTitle(window,titlestr);
    for(int i=0;i<monster.size();i++)
    {
        int k = rand()%2;
        monster[i] = Monster(
                    getRandDouble(-300,300),
                    3,
                    getRandDouble(-1000,300),
                    2.5,
                    1,
                    k,
                    randcolor[rand()%4],
                randcolor[rand()%4],
                randcolor[rand()%4]
                );
    }
    for(int i=0;i<rock.size();i++)
    {
        rock[i] = Rock(
                    getRandDouble(-300,300),
                    8,
                    getRandDouble(-1000,300),
                    8,
                    0.3,
                    true,
                    COLOR_GREY
                    );
    }

    add_fireball();
    score.update(0);
    health.update(100);
    game_time.update(50);

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
    audio_init("assets/song.mp3");


    while (!glfwWindowShouldClose(window)) {
        if(is_audio)
            audio_play();

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
        if(t1.processTick()){
            game_time.subtract(1);
        }

        if (t2.processTick()){
            boat.iswind = false;
        }
        if (t3.processTick()){
            boat.iswind = true;
            boat.windir = getRandDouble(0,180);
            printf("Dfdsgdgdf\n");
//            /boat.blow_wind();
        }


        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
                (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
                    (abs(a.z - b.z) * 2 < (a.length + b.length));
}

void reset_screen() {
    Matrices.projectionO = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, 0.1f, 500.0f);
    Matrices.projectionP = glm::perspective(1.0f, 1.0f, 1.0f, 500.0f);
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
