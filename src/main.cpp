#include "main.h"
#include "timer.h"
#include "plane.h"
#include "frustum.h"
#include "mountain.h"
#include "water.h"
#include "missile.h"
#include "compass.h"
#include "altitude.h"
#include "gauge.h"
#include "para.h"
#include "cannon.h"
#include "fuel.h"
#include "smoke.h"
#include "speed.h"
#include "digit.h"
using namespace std;

GLMatrices Matrices;
GLMatrices ortho;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Plane plane;
Frustum f;
Mountain m;
Water w;
Water sand;
Compass compass;
Altitude alti;
Gauge gauge;
Speed mt;
glm::vec3 camera_vec = {plane.position.x,plane.position.y+1.5,plane.position.z+1};
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
glm::vec3 eye ( plane.position.x+1, 2, 5 );
glm::vec3 up (0, 1, 0);
glm::vec3 target (plane.position.x, plane.position.y, plane.position.z);
int counter = 0;
int cam = 0;
int check_no = 0;
float rad = 3.0f;
Timer t60(1.0 / 60);

vector<Missile> misl_vec;
vector<Para> para_vec;
vector<Mountain> mount_vec;
vector<Canon> canon_vec;
vector<Fuel> fuel_vec;
vector<Smoke> smoke_vec;
vector<Digit> dig_vec;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    ortho.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    glm::vec3 eye1(0,0,1);
    glm::vec3 target1 (0, 0, 0);
    glm::vec3 up1 (0, 1, 0);
    ortho.view = glm::lookAt(eye1,target1,up1);
    glm::mat4 VP1 = ortho.projection*ortho.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    plane.draw(VP);
    // f.draw(VP);
    // m.draw(VP);
    w.draw(VP);
    compass.draw(VP1);
    alti.draw(VP1);
    gauge.draw(VP1,plane.fuel);
    canon_vec[check_no].draw(VP);
    mt.draw(VP1,plane.hor_vel);

    for(auto &x:misl_vec)
        x.draw(VP);
    for(auto &x:para_vec)
        x.draw(VP); 
    for(auto &x:mount_vec)
        x.draw(VP);
    for(auto &x:fuel_vec)
        x.draw(VP);
    for(auto &x:smoke_vec)
        x.draw(VP);          
    for(auto i:dig_vec)
        i.draw(VP1);              
}

void tick_input(GLFWwindow *window) 
{
    if(plane.barrel||plane.loop)
        return;

    int W = glfwGetKey(window, GLFW_KEY_UP);
    int S = glfwGetKey(window, GLFW_KEY_DOWN);
    int A  = glfwGetKey(window, GLFW_KEY_LEFT);
    int D = glfwGetKey(window, GLFW_KEY_RIGHT);
    int Q = glfwGetKey(window, GLFW_KEY_Q);
    int E = glfwGetKey(window, GLFW_KEY_E);
   
    int T = glfwGetKey(window, GLFW_KEY_T);
    int G = glfwGetKey(window, GLFW_KEY_G);
   
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int SPC = glfwGetKey(window, GLFW_KEY_SPACE);
    int tw= glfwGetKey(window, GLFW_KEY_2);
    int flw = glfwGetKey(window, GLFW_KEY_3);
    int top = glfwGetKey(window, GLFW_KEY_4);
    int pln = glfwGetKey(window, GLFW_KEY_5);
    int hel = glfwGetKey(window, GLFW_KEY_6);
    int tow = glfwGetKey(window,GLFW_KEY_7);
    int mis = glfwGetKey(window,GLFW_KEY_A);
    int bom = glfwGetKey(window,GLFW_KEY_D);
    int B = glfwGetKey(window, GLFW_KEY_B);
    int L = glfwGetKey(window, GLFW_KEY_L);

    if(plane.fuel<=0.0)
        return;

   
    //plane rotations
    if(Q)
        plane.rotate(0.00,0.0,0.05);
    if(E)
        plane.rotate(0.0,0.0,-0.05);
    if(A)
        plane.rotate(0.0,0.05,0.0);
    if(D)
        plane.rotate(0.0,-0.05,0.0);
    // if(T)
    //     plane.rotate(-0.05,0.0,0.0);
    // if(G)
    //     plane.rotate(0.05,0.0,0.0);    
    if(B)
    {
        plane.barrel = 1;
        plane.rotationz = 0;
        target = {plane.position.x,plane.position.y,plane.position.z};
        eye.x = plane.position.x + 2*plane.loc_x.x - 3*plane.loc_z.x;
        eye.y = plane.position.y + 2*plane.loc_x.y - 3*plane.loc_z.y;
        eye.z = plane.position.z + 2*plane.loc_x.z - 3*plane.loc_z.z;
    }    
    if(L)
    {
        plane.loop = 1;
        plane.rotationx=0;        
        target = {plane.position.x,plane.position.y,plane.position.z};
        eye.x = plane.position.x + 2*plane.loc_x.x - 2*plane.loc_z.x;
        eye.y = plane.position.y + 2*plane.loc_x.y - 2*plane.loc_z.y;
        eye.z = plane.position.z + 2*plane.loc_x.y - 2*plane.loc_z.z;
    }
    glm::vec3 rotx(plane.rotation[0][0],plane.rotation[1][0],plane.rotation[2][0]);
    glm::vec3 roty(plane.rotation[0][1],plane.rotation[1][1],plane.rotation[2][1]);
    glm::vec3 rotz(plane.rotation[0][2],plane.rotation[1][2],plane.rotation[2][2]);


    //plane movement
    if(SPC)
    {
        plane.move(0.0,0.05,0.0);
        plane.fuel = std::max(plane.fuel-0.0045,0.0);        
    }    

    // if(left)
    //     plane.move(-0.05*plane.loc_x.x,-0.05*plane.loc_x.y,-0.05*plane.loc_x.z);
    // if(right)
    //     plane.move(0.05*plane.loc_x.x,0.05*plane.loc_x.y,0.05*plane.loc_x.z);
    if(S)
    {
        // plane.move(0.05*plane.loc_z.x,0.05*plane.loc_z.y,0.05*plane.loc_z.z);
        plane.move(0.0,-0.05,0.0);
        plane.fuel = std::max(plane.fuel-0.0045,0.0);
    }    
    if(W)
    {
        plane.hor_vel = min(0.08f,plane.hor_vel+plane.hor_acc);
        plane.move(-plane.hor_vel*plane.loc_z.x,-plane.hor_vel*plane.loc_z.y,-plane.hor_vel*plane.loc_z.z);
        plane.fuel = std::max(plane.fuel-0.0045,0.0);
        
    }
    else
    {
        plane.hor_vel = std::max(-0.001f+plane.hor_vel,0.0f);
        plane.move(-plane.hor_vel*plane.loc_z.x,-plane.hor_vel*plane.loc_z.y,-plane.hor_vel*plane.loc_z.z);
    }
    
    //camera controls
    if(flw)
        cam=0;
    if(top)
        cam=1;
    if(pln)
        cam=2;      
    if(hel)
    {   
        rad = 3.0;             
        cam=3;
    }           
    if(tow)
    {
        cam=4;
        eye.x = plane.position.x + 8*plane.loc_x.x - 2*plane.loc_z.x ;
        eye.y = plane.position.y + 8*plane.loc_x.y - 2*plane.loc_z.y+6;
        eye.z = plane.position.z + 8*plane.loc_x.y - 2*plane.loc_z.z;
    }    
    //missile           
    if(mis&&counter==0)
    {
        counter = 120;
        glm::vec3 dir(plane.position.x - 2.0*plane.loc_z.x,plane.position.y - 2.0*plane.loc_z.y,plane.position.z - 2.0*plane.loc_z.z);
        Missile m = Missile(dir,plane.loc_z,plane.rotation,1);
        misl_vec.push_back(m);
    }    
    if(bom&&counter==0)
    {
        counter = 120;
        Missile m = Missile(plane.position,glm::vec3(0,1,0),glm::mat4(1.0),2);
        misl_vec.push_back(m);
    }
}

void adjust_cam()
{
    if(plane.barrel||plane.loop)
    {
        up = {0,1,0};
        return;
    }    

    if(cam==0)
    {
        //Follow cam view
        eye.x = plane.position.x + plane.loc_z.x + plane.loc_y.x;
        eye.y = plane.position.y + plane.loc_z.y + plane.loc_y.y;
        eye.z = plane.position.z + plane.loc_z.z + plane.loc_y.z;
        up = plane.loc_y;
    }
    if(cam==1)
    {
        //Top view
        eye.x = plane.position.x;
        eye.y = plane.position.y+10;
        eye.z = plane.position.z+2;
        up = {0,1,0};
    }
    if(cam==2)
    {
        //Plane view
        eye.x = plane.position.x - 2*plane.loc_z.x;
        eye.y = plane.position.y - 2*plane.loc_z.y;
        eye.z = plane.position.z - 2*plane.loc_z.z;
        target.x = eye.x - 0.2*plane.loc_z.x;
        target.y = eye.y - 0.2*plane.loc_z.y;
        target.z = eye.z - 0.2*plane.loc_z.z;

    }
    if(cam==3)
    {
        //helicopter view

        int height,width;
        glfwGetWindowSize(window,&height,&width);
        double xpos,ypos;
        glfwGetCursorPos(window,&xpos,&ypos);
        double phi = 0.005*(width/2-xpos);
        double theta = 0.005*(height/2-ypos);
        eye.x = plane.position.x + rad*cos(theta)*sin(phi);
        eye.y = plane.position.y + rad*sin(theta);
        eye.z = plane.position.z + rad*cos(phi)*cos(theta);
        up = {0,1,0};
    }
    if(cam==4)
    {
        target = plane.position;
    }
}

void tick_elements() {

    if(plane.position.y<=0)
        quit(window);    
    plane.tick();
    counter=max(counter-1,0);
    alti.poly.position.y = -3.6 + (plane.position.y-1.0)*0.05;
    compass.rotation = -plane.rotationy;
    camera_rotation_angle += 1;
    for(auto &x:misl_vec)
        x.tick();
    for(auto &x:para_vec)
        x.tick();    

     
    canon_vec[check_no].tick(plane.position);
    if(canon_vec[check_no].counter==120)
    {
        canon_vec[check_no].counter=0;
        glm::vec3 pos = plane.position;
        glm::vec3 dir = {pos.x-canon_vec[check_no].position.x,pos.y-canon_vec[check_no].position.y,pos.z-canon_vec[check_no].position.z};
        float dist = glm::length(dir);
        dir = glm::normalize(dir);    
        dir = {-dir.x,-dir.y,-dir.z};
        if(dist<40)
        {
            Missile m = Missile(canon_vec[check_no].position,dir,canon_vec[check_no].rotation*glm::rotate(float(3.14),glm::vec3(1,0,0)),3);
            misl_vec.push_back(m);
        }    
    }   

    compass.tick(plane.position,canon_vec[check_no].position);     
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Plane({5.0,5.0,0.0});
    Para p = Para(glm::vec3(5.0,10.0,-4.0));
    para_vec.push_back(p);

    
    // canon_vec.push_back(ca); 
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    ortho.MatrixID = glGetUniformLocation(programID, "MVP");


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
    // glfwSetScrollCallback(window, scroll_callback);
    initGL (window, width, height);
    generate_scene();
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            target = {plane.position.x,plane.position.y,plane.position.z};
            up = {0,1,0};   
            tick_elements();
            adjust_cam();
            check_collision();
            // cout<<plane.position.x<<" "<<plane.position.z<<endl;
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void generate_scene()
{   
    w = Water(glm::vec3(-48,-1,48),64,1,0.3);
    // sand = Water(glm::vec3(-108,-2.2,108),64,2,0.5);
    compass = Compass(1);
    alti = Altitude(1);
    gauge = Gauge(1);
    mt = Speed(1);
    draw_score();
    //mountains
    {
        Mountain m = Mountain(glm::vec3(-10,0.2,10),64,1,0.2);
        mount_vec.push_back(m);
        m = Mountain(glm::vec3(15,0.4,-15),32,1,0.1);
        mount_vec.push_back(m);
        m = Mountain(glm::vec3(-40,0.4,30),64,1,0.05);
        mount_vec.push_back(m);

        m = Mountain(glm::vec3(-5,0.2,-20),32,1,0.2);
        mount_vec.push_back(m);

        m = Mountain(glm::vec3(20,0.4,30),64,1,0.1);
        mount_vec.push_back(m);

        m = Mountain(glm::vec3(5,1.0,0),32,2,0.1);
        mount_vec.push_back(m);
        m = Mountain(glm::vec3(-25,0.8,-15),32,2,0.2);
        mount_vec.push_back(m);

        m = Mountain(glm::vec3(-35,0.8,-30),32,3,0.1);
        mount_vec.push_back(m);

        m = Mountain(glm::vec3(-35,0.8,20),64,3,0.1);
        mount_vec.push_back(m);

        m = Mountain(glm::vec3(0,0.8,40),64,3,0.1);
        mount_vec.push_back(m);

        m = Mountain(glm::vec3(35,0.8,-10),64,3,0.1);
        mount_vec.push_back(m);

        m = Mountain(glm::vec3(5,0.9,-30),32,3,0.1);
        mount_vec.push_back(m);
    }
    //cannons
    {
        Canon ca = Canon(glm::vec3(5,1.8,37));
        canon_vec.push_back(ca);
        ca = Canon(glm::vec3(-32,1.8,-32));
        canon_vec.push_back(ca);
        ca = Canon(glm::vec3(-30,1.8,15));
        canon_vec.push_back(ca);
        ca = Canon(glm::vec3(40,1.8,-14));
        canon_vec.push_back(ca);
        ca = Canon(glm::vec3(7,1.8,-32));
        canon_vec.push_back(ca);
    }
    //fuel
    {
        Fuel fu = Fuel(glm::vec3(0,3.5,0));
        fuel_vec.push_back(fu);
        fu = Fuel(glm::vec3(-38,3.5,28));
        fuel_vec.push_back(fu);
        fu = Fuel(glm::vec3(0,3.0,-24));
        fuel_vec.push_back(fu);
        fu = Fuel(glm::vec3(23,3.0,26));
        fuel_vec.push_back(fu);
        
    }
    //smoke
    {
        for(int i=0;i<5;i++)
        {
            float x = rand()%70 -35;
            float z = rand()%70 -35;
            
            Smoke sm = Smoke(glm::vec3(x,5.0,z),(float)(i%2)*(3.14/2));
            smoke_vec.push_back(sm);
        }    
    }
    Para p = Para(glm::vec3(15.0,8.0,14.0));
    para_vec.push_back(p);
    p = Para(glm::vec3(-25.0,8.0,-4.0));
    para_vec.push_back(p);  

}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height))&&
           (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void check_collision()
{
    for(auto &x:misl_vec)
    {   
        bounding_box_t a;
        a.height = 0.1;
        a.width = 0.1;
        a.depth = 0.1;
        a.x = x.position.x + 0.5*x.dir.x;
        a.y = x.position.y + 0.5*x.dir.y;
        a.z = x.position.z + 0.5*x.dir.z;

        if(x.type==3)
        {
            //plane
            for(int i=0;i<4;i++)
            {
                bounding_box_t b;
                b.height = 0.35 - i*0.05;
                b.width = 0.35 - i*0.05;
                b.depth = 0.35 - i*0.05;
                b.x= plane.position.x -i*0.5*plane.loc_z.x;
                b.y= plane.position.y -i*0.5*plane.loc_z.y;
                b.z= plane.position.z -i*0.5*plane.loc_z.z; 
                if(detect_collision(a,b))
                {
                    plane.fuel = max(plane.fuel-1.5,0.0);
                    x.position.y = -10;
                    cout<<"Collision3"<<endl;
                    break;
                } 
            }
               
        }
        else
        {
            //parachute
            for(auto &y : para_vec)
            {
                bounding_box_t b;
                
                b.height = 0.45*1.41;
                b.width = 0.45*1.41;
                b.depth = 0.45*1.41;
                b.x = y.position.x;
                b.y = y.position.y - 0.45;
                b.z = y.position.z;
                // cout<<"x: "<<b.x<<" y: "<<b.y<<" z: "<<b.z<<endl;
                if(detect_collision(a,b))
                {
                    y.position.y = -10;
                    for(auto &az:y.vec)
                        az.position.y = -10;
                    plane.score += 5;   
                    draw_score(); 
                    cout<<"collision"<<endl;
                    break;
                }    
                
            }       
            //checkpoint
            for(auto &y:canon_vec)
            {
                bounding_box_t c;

                c.height = 0.3*1.414;
                c.width = 1.414;
                c.depth = 2.4 * 0.8;
                c.x = y.position.x;
                c.y = y.position.y -0.3;
                c.z = y.position.z-0.6;  
                if(detect_collision(a,c))
                {
                    cout<<"collision1"<<endl;
                    y.position.y = 100;
                    y.base.position.y = 100;
                    y.pipe.position.y = 100;
                    y.axil.position.y = 100;
                    plane.score += 20;
                    draw_score();
                    check_no = min(4,check_no+1);
                    cout<<"check_no:"<<check_no<<endl;
                    break;
                }   
            }                        
        } 
    }
    //volcano
    for(auto &x:mount_vec)
    {
        if(x.type==3)
            continue;
        bounding_box_t a;
        a.x = x.position.x + (x.siz*x.block*sqrt(2))/2.0;
        a.z = x.position.z - (x.siz*x.block*sqrt(2))/2.0;
        a.y = x.position.y + 2;
        if(x.type==2)
        {
            a.width = (x.siz/8.0)*x.block*sqrt(2);
            a.depth = (x.siz/8.0)*x.block*sqrt(2);
            a.height = 6;
        }    
        if(x.type==1)
        {
            a.y = x.position.y + 1.5;
            a.width = (x.siz/4.0)*x.block*sqrt(2);
            a.depth = (x.siz/4.0)*x.block*sqrt(2);
            a.height = 1.5;
        }

        for(int i=0;i<4;i++)
        {
                bounding_box_t b;
                b.height = 0.5 - i*0.05;
                b.width = 0.5 - i*0.05;
                b.depth = 0.5 - i*0.05;
                b.x= plane.position.x -i*0.5*plane.loc_z.x;
                b.y= plane.position.y -i*0.5*plane.loc_z.y;
                b.z= plane.position.z -i*0.5*plane.loc_z.z; 
                if(detect_collision(a,b))
                {
                    // cout<<"Volcano"<<endl;
                    plane.fuel = 0.0;
                    break;
                } 
        }

    }
    //fuel
    for(auto &x:fuel_vec)
    {
        bounding_box_t a;
        a.x = x.position.x;
        a.y = x.position.y;
        a.z = x.position.z + 0.4/sqrt(2);
        a.height = a.width = a.depth = 0.8/sqrt(2);
        for(int i=0;i<4;i++)
        {
            bounding_box_t b;
            b.height = 0.35 - i*0.05;
            b.width = 0.35 - i*0.05;
            b.depth = 0.35 - i*0.05;
            b.x= plane.position.x -i*0.5*plane.loc_z.x;
            b.y= plane.position.y -i*0.5*plane.loc_z.y;
            b.z= plane.position.z -i*0.5*plane.loc_z.z; 
            if(detect_collision(a,b))
            {
                x.position.y = -10;
                x.base.position.y = -10;
                plane.fuel = 11.0f;
                cout<<"Fuel"<<endl;
                break;
            }    
        }
    }
    //ring
    for(auto &x:smoke_vec)
    {
        bounding_box_t a,b,c;
        a.x=x.position.x;
        a.y=x.position.y;
        a.z=x.position.z;
        a.height=0.8;
        a.width=0.4;
        a.depth=0.4;

        b.x=plane.position.x;
        b.y=plane.position.y;
        b.z=plane.position.z;
        b.height=0.2;
        b.width=0.2;
        b.height=0.2;

        if(detect_collision(a,b))
        {
            x.position.y = -10;
            plane.score += 5;
            draw_score();
        }    
    }
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(90.0f),1.0f, 0.1f, 500.0f);
}

float rgb(int a)
{
    return (float)a/256.0f;
}

void draw_score()
{
    dig_vec.clear();
    int score = plane.score;
    int dig1 = score/1000;
    int dig2 = (score/100)%10;
    int dig3 = (score/10)%10;
    int dig4 = score%10;
    float x = -3.9;
    Digit dig = Digit(x,3.8,COLOR_BLACK,5);
    dig_vec.push_back(dig);
    x+=0.25;
    dig = Digit(x,3.8,COLOR_BLACK,int('c'));
    dig_vec.push_back(dig);
    x+=0.25;
    dig = Digit(x,3.8,COLOR_BLACK,int('r'));
    dig_vec.push_back(dig);
    x+=0.25;
    x+=0.15;
    if(dig1>0)
    {
        dig = Digit(x,3.8,COLOR_BLACK,dig1);
        dig_vec.push_back(dig);
        x+=0.25;
    }
    if(dig2>0)
    {
        dig = Digit(x,3.8,COLOR_BLACK,dig2);
        dig_vec.push_back(dig);
        x+=0.25;
    }
    if(dig3>0)
    {
        dig = Digit(x,3.8,COLOR_BLACK,dig3);
        dig_vec.push_back(dig);
        x+=0.25;
    }
    dig = Digit(x,3.8,COLOR_BLACK,dig4);
    dig_vec.push_back(dig);
    x+=0.25;

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if(cam!=3)
        return;
    cout<<"hi"<<endl;

    if(yoffset==1)
    {
        if(rad>=1.0)
        {
            rad -= 0.05;
        }
    }
    else
    {
        if(rad<=5.0)
        {
            rad += 0.05;
        }
    }
}