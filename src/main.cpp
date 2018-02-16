#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "lake.h"
#include "triangle.h"
#include "pacman.h"
#include "tramp.h"
#include "math.h"
#include "magnet.h"
#include "string"
#include "magRec.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Ball balls[40];
Ground ground;
Lake lake;
Triangle triangle[7];
Pacman pacman;
Tramp tramp;
Magnet magnet;
Magrec magRec;
int score = 0;
int ind = 0;
int level = 1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
bool colliding(Pacman pacman,Ball ball);
Timer t60(1.0 / 60);
bool collidingPor(Pacman pacman,Triangle triangle);
bool collidingPlank(Pacman pacman,Ball ball);
void dispScore();
void endGame();
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i = 0; i < 40; i++)
    {  
        if(balls[i].flag == 1)
            balls[i].draw(VP);
    }
    ground.draw(VP);
    lake.draw(VP);
    for(int i = 0 ; i < 7 ; i++)
    {    
        if(triangle[i].flag == 1)
                triangle[i].draw(VP);
    }
    pacman.draw(VP);
    tramp.draw(VP);
    if(level == 2 || level == 4)
    {    magnet.draw(VP);
        magRec.draw(VP);
    }
}   

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int flag = 0;
    int flag1 = 0;
    int flag_right = 0;
    int flag_left = 0;
    double r;
    double phi;
    int move_right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int move_left = glfwGetKey(window, GLFW_KEY_LEFT);
    int move_up = glfwGetKey(window, GLFW_KEY_UP);
    int move_down = glfwGetKey(window, GLFW_KEY_DOWN);
    

    if(move_right)
    {
        screen_center_x+=0.08;
        reset_screen(0.0);
    }
    if(move_left)
    {
        screen_center_x-=0.08;
        reset_screen(0.0);
    }
    if(move_up)
    {
        screen_center_y += 0.05;
        reset_screen(0.0);
    }
    if(move_down)
    {
        screen_center_y -= 0.05;
        reset_screen(0.0);
    }
    if(pacman.position.x == -1.0f && pacman.position.y == -2.2f)
    {
    
        float x = -0.7f;
        float y = -2.5f;
        pacman.set_position(x,y);
    }
    
    else if(pacman.position.x == 1.0f && pacman.position.y == -2.2f)
    {
        float x = 0.7f;
        float y = -2.5f;
        pacman.set_position(x,y);
    }
    
    
    else if(pacman.position.x > -0.73f && pacman.position.x < 0.73f)
    {
           
            
           if(pacman.position.y <= -2.2f)
           { 
                if(left)
                {   
                   // pacman.position.x -= 0.02f;
                   // printf("%f ",pacman.position.x);
                   pacman.position.y = lake.centreY-sqrt(0.74f*0.74f-(pacman.position.x)*(pacman.position.x));
               
                }
                if(right)
                {
                   
                   pacman.position.y = lake.centreY-sqrt(0.74f*0.74f-(pacman.position.x)*(pacman.position.x));
                   

                }
           }
            if(left && pacman.position.x <= -0.64f && pacman.position.y <= -2.734f)
            {
                pacman.position.x = -1.0;
                pacman.position.y = -2.0;
            }
            if(right && pacman.position.x >= 0.65f && pacman.position.y <= -2.734f)
            {
                pacman.position.x = 1.0;
                pacman.position.y = -2.0;
            }
            if(up && pacman.position.y <= -2.734f)
            {   
                pacman.speedY = 0.1;

                flag1 = 1;
                if(pacman.position.y <= 4)
                {
                    pacman.speedY = pacman.speedY+pacman.acceleration;
                    pacman.position.y += pacman.speedY;
                    pacman.rotation -= 2;
                }
            }
            if(flag1 == 0)
            {
                pacman.speedY += pacman.acceleration;
                pacman.position.y += pacman.speedY;
                if(pacman.position.y >= -2.5)
                {
                    pacman.rotation -= 2;

                }
                float y = lake.centreY-sqrt(0.72f*0.72f-(pacman.position.x)*(pacman.position.x));
                if(pacman.position.y < y)
                {
                    pacman.position.y = y;
                }
                if (left) {
    
                   pacman.position.x -=pacman.speedX-0.02f;
                   pacman.rotation += 3;
                   // printf("%f ",pacman.position.x);

                }
                if ( right ) {
            
                    pacman.position.x +=pacman.speedX-0.02f;
                    pacman.rotation -= 3;

                   // printf("%f ",pacman.position.x);

                }
            }   
            if(pacman.speedY >= 0.1)
                pacman.speedY = 0;

    }
    else if(pacman.position.x <= -0.73f || pacman.position.x > 0.73f)
    { 
        if (left) {
        
           pacman.position.x -=pacman.speedX;
           pacman.rotation += 10;
        }
        if ( right ) {
    
            pacman.position.x +=pacman.speedX;
            pacman.rotation -= 10;
        }
        if (up && pacman.position.y <= -2.000000 && pacman.position.y <= -1.95)
        {   
            pacman.speedY = 0.13;
            flag = 1;
            if(pacman.position.y <= 3.1)
            {   
                pacman.speedY = pacman.speedY+pacman.acceleration;
                pacman.position.y += pacman.speedY;
               
            }
            
        }
        if (flag == 0 && pacman.position.y >= -2.2)
        {   
            pacman.speedY += pacman.acceleration;
            pacman.position.y += pacman.speedY;
            
        }
        
        int flag1 = 0;
        if(pacman.position.x >= 2.2f && pacman.position.x <=3.4f)
        {   
            flag1 = 1;
            if(pacman.position.y <= tramp.centreY + pacman.radius-0.2f)
            {   
                pacman.speedY = 0.2;
                pacman.speedY = pacman.speedY+pacman.acceleration;
                pacman.position.y += pacman.speedY;
            }
        }
        if(flag1 == 0 && pacman.position.x >= 2.2f && pacman.position.x <=3.4f)
        {   
            if(pacman.position.y >= tramp.centreY + pacman.radius-0.2f)
            {   

                pacman.speedY += pacman.acceleration;
                pacman.position.y += pacman.speedY;
            }
        }
        if(right && pacman.position.x >= 4.0)
        {
            screen_center_x += pacman.speedX+0.01;
            reset_screen(0.0);
        }
        if(left && pacman.position.x >= 4.0)
        {
            screen_center_x -= pacman.speedX+0.01;
            reset_screen(0.0);   
        }
        if(left && pacman.position.x <= -4.0)
        {
            screen_center_x -= pacman.speedX+0.01;
            reset_screen(0.0);
        }
        if(right && pacman.position.x <= -4.0)
        {
            screen_center_x -= pacman.speedX+0.01;
            reset_screen(0.0);
        }
    
       
    }
    if(pacman.position.x >= -3.5 && pacman.position.x <= 1.0 && (level == 2 || level == 4))
    {
        if(pacman.position.y >= 1.5 && pacman.position.y <= 3.1)
        {
            pacman.position.x -= 0.11;
        }
    }
    if(score < 0)
    {   
        endGame();
        
    }
}

void tick_elements() {
    
    
    for(int i =0;i<40;i++)
    {
        balls[i].tick();
        // printf("Balls %d x Top %f  ",i,balls[i].xTop);
    }

        if(pacman.moveX)
        {   
           
            pacman.position.x += pacman.speedX;
            pacman.rotation -= 10;
            if(pacman.position.y <= -1.9 && pacman.position.y >= -2.6)
            {   
                // printf("%d X",pacman.moveX);
                pacman.moveX = 0;
            }
                
    
        }
        // printf("X:%f  ",pacman.position.x);
        // printf("Y:%f  ",pacman.position.y);
        
        int x = 0;
        for(int i = 0;i<40;i++)
        {   
            
            if(balls[i].flag1)
            {
    
                if(collidingPlank(pacman,balls[i]))
                {
                
    
                    balls[i].flag = 0;
                   
                    int HI1 = 5,HI2 = 5,LO1 = -6,LO2=-2;
                    float x1 = LO1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI1-LO1)));
                    float x2 = LO2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI2-LO2)));
                    balls[i].set_position(x1,x2);
                    double theta=atan2(pacman.speedY,pacman.speedX);
                    double speed=sqrt(pacman.speedX*pacman.speedX+pacman.speedY*pacman.speedY);
                    pacman.speedX=speed*cos(2*balls[i].angle-theta);
                    pacman.speedY=speed*sin(2*balls[i].angle-theta);
                   
                    pacman.moveX = 1;
                    score += 100;
                    dispScore();
                    
                }
            }
            else if(colliding(pacman,balls[i]) && (pacman.position.y > balls[i].position.y) && (balls[i].flag1 == 0) && (pacman.speedY < 0))
            {   
                pacman.speedY = 0.1;
                
                balls[i].flag = 0;
                int HI1 = 5,HI2 = 5,LO1 = -6,LO2=-2;
                float x1 = LO1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI1-LO1)));
                float x2 = LO2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI2-LO2)));
                balls[i].set_position(x1,x2);
                score += 100;
                dispScore();
                
                
            }   
           
            
        }
        if(score >= 0 && score <= 500)
        {
            level = 1;
        }
        if(score > 500 && score <= 1000)
        {
            level = 2;
        }
        if(score > 1000 && score <= 1500)
        {
            level = 3;
        }
        if(score > 1500 && score <= 2000)
        {
            level = 4;
        }
        if(level == 1)
        {
            triangle[0].flag = 1;
        }
        if(level == 2)
        {
            for(int i = 0 ; i < 3 ; i++)
            {
                triangle[i].flag = 1;
            }
        }
        if(level == 3)
        {
            for(int i = 0 ; i < 5 ; i++)
            {
    
                triangle[i].flag = 1;
    
            }
        }
        if(level == 4)
        {
            for(int i = 0 ; i < 7 ; i++)
            {
                triangle[i].flag = 1;
            }
        }
    
        
         pacman.speedX = 0.04f;
        for(int i = 0 ; i < 7 ;i++)
        {   
            if(triangle[i].flag == 1)
                triangle[i].movePorcupine();
        }
        
        // printf("%lf %lf %lf ",triangle.position.x,triangle.xLeft, 
        // triangle.xRight );
        
        for(int i = 0 ; i < 7 ;i ++)
        {
            if(collidingPor(pacman,triangle[i]) && (triangle[i].flag == 1))
            {
                triangle[i].flag = 0;
                
                score -= 10;
                dispScore();
            }
        }
    


}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    float x1,x2; 
    int HI1 = 10,HI2 = 5,LO1 = -10,LO2=-2;
  
    for(int i = 0;i < 40;i++)
    {   
        x1 = LO1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI1-LO1)));
        x2 = LO2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI2-LO2)));
        balls[i] = Ball(x1,x2 , SG,0.009f);
        

        balls[i].speed = -balls[i].speed;
        if(i%3 == 0)
        {   
            if(balls[i].radius = 0.19)
                balls[i].attachPlank(M_PI/6,0.5,1);
            else
                balls[i].attachPlank(M_PI/4,0.5,1);

        }
    }
    
    ground.createRectangle();
    lake.createLake();
    pacman = Pacman(-2.0f,-2.2f);
    for(int i = 0 ; i < 7 ;i++)
    {   
        float temp;
        float LO2 = 0.05,HI2 = 0.14;
        temp = LO2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI2-LO2)));
        triangle[i] = Triangle(0.3,3,temp);
    }

    tramp.createTramp();
    magnet = Magnet(-2.7,2.3);
    magRec.magrec();
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (0, 0, 0, 0.0f); // R, G, B, A
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


void reset_screen(float zoom) {
    screen_zoom+=zoom;
    // cout<<screen_zoom<<endl;
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

bool colliding(Pacman pacman,Ball ball)
{
    float xd = pacman.position.x - ball.position.x;
    float yd = pacman.position.y - ball.position.y;

    float sumRadius = pacman.radius + ball.radius;
    float sqrRadius = sumRadius * sumRadius;

    float distSqr = (xd * xd) + (yd * yd);

    if (distSqr <= sqrRadius)
    {
        
        return true;
    }

    return false;
}
bool collidingPor(Pacman pacman,Triangle triangle)
{
   
        // printf("Px %lf Py %lf Pt%lf \n",triangle.xLeft,triangle.xRight,triangle.yBot);
        // printf("Ax %lf Ay %lf \n",pacman.position.x,pacman.position.y);
        
    if((pacman.position.x >= triangle.xLeft) && (pacman.position.x <= triangle.xRight) )
    {   
        // printf("Haha");
        
        if((pacman.position.y <= 0.5+triangle.yBot) && (pacman.position.y >= triangle.yBot-pacman.radius+0.1) )
        {
            return true;
        }
    }

    return false;
}
bool collidingPlank(Pacman pacman,Ball ball)
{  
   double slope = -cos(ball.angle)/sin(ball.angle);
    
   if(pacman.position.x <= ball.position.x+ball.xBot && pacman.position.x >= ball.position.x+ball.xTop)
   {
    
    if(abs(pacman.position.y - (slope*(pacman.position.x - ball.position.x+ball.xTop) + ball.position.y+ball.yTop)) <= 0.35)
    {
        

        
        return true;
    }
   }
  
   return false;
}
void dispScore(){
//    cout << ball2.score << endl;
    string e = "Player Score: ";
    string s = to_string(score);
    string p = "  Level: ";
    string l = to_string(level);
    

    s = e+s + p + l ;
    glfwSetWindowTitle(window, const_cast<char*>(s.c_str()));
}
void endGame(){
//    cout << ball2.score << endl;
    string s = " Game Over ";
    // s = e+s;
    glfwSetWindowTitle(window, const_cast<char*>(s.c_str()));
    ind++;
    if(ind == 120)
    {
        exit(0);
    }

}   