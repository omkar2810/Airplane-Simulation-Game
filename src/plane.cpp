#include "plane.h"
#include "main.h"

Plane::Plane(glm::vec3 pos) {

    GLfloat vertex_color_data[2000];
    int n = 20;
    for(int i=0;i<n;i++)
    {
      //circle 1  
      {
        vertex_color_data[9*i]   = rgb(105);
		vertex_color_data[9*i+1] = rgb(105);
		vertex_color_data[9*i+2] = rgb(105);

		vertex_color_data[9*i+3] = rgb(105);
		vertex_color_data[9*i+4] = rgb(105);
		vertex_color_data[9*i+5] = rgb(105);

		vertex_color_data[9*i+6] = rgb(105);
		vertex_color_data[9*i+7] = rgb(105);
		vertex_color_data[9*i+8] = rgb(105);
      } 
      //cirle2 
      {
        vertex_color_data[9*(i+n)]   = rgb(105);
		vertex_color_data[9*(i+n)+1] = rgb(105);
		vertex_color_data[9*(i+n)+2] = rgb(105);

		vertex_color_data[9*(i+n)+3] = rgb(105);
		vertex_color_data[9*(i+n)+4] = rgb(105);
		vertex_color_data[9*(i+n)+5] = rgb(105);

		vertex_color_data[9*(i+n)+6] = rgb(105);
		vertex_color_data[9*(i+n)+7] = rgb(105);
		vertex_color_data[9*(i+n)+8] = rgb(105);
      }

      {
        vertex_color_data[9*(i+2*n)]   = rgb(128);	
        vertex_color_data[9*(i+2*n)+1] = rgb(128);
		vertex_color_data[9*(i+2*n)+2] = rgb(128);

		vertex_color_data[9*(i+2*n)+3] = rgb(128);
		vertex_color_data[9*(i+2*n)+4] = rgb(128);
		vertex_color_data[9*(i+2*n)+5] = rgb(128);

		vertex_color_data[9*(i+2*n)+6] = rgb(128);
		vertex_color_data[9*(i+2*n)+7] = rgb(128);
		vertex_color_data[9*(i+2*n)+8] = rgb(128);
      } 
      {  
        vertex_color_data[9*(i+3*n)]   = rgb(119);
		vertex_color_data[9*(i+3*n)+1] = rgb(136);
		vertex_color_data[9*(i+3*n)+2] = rgb(153);

		vertex_color_data[9*(i+3*n)+3] = rgb(128);
		vertex_color_data[9*(i+3*n)+4] = rgb(128);
		vertex_color_data[9*(i+3*n)+5] = rgb(128);

		vertex_color_data[9*(i+3*n)+6] = rgb(47);
		vertex_color_data[9*(i+3*n)+7] = rgb(79);
		vertex_color_data[9*(i+3*n)+8] = rgb(79);
      } 
    }   

    this->barrel = 0;
    this->loop = 0;
    this->score = 0;
    this->ver_acc = 0;
    this->ver_acc = -0.0001;
    this->hor_acc = 0.005;
    this->hor_vel = 0.0;
    this->position = pos;
    this->rotationx = 0;
    this->rotationy = 0;
    this->rotationz = 0;
    this->rotation = glm::mat4(1.0);
    this->loc_x = {1,0,0};
    this->loc_y = {0,1,0};
    this->loc_z = {0,0,1};
    this->fuel = 10;
    Frustum frus = Frustum(pos,{pos.x,pos.y,pos.z-1.1},0.2,0.08,20,vertex_color_data);
    this->vec.push_back(frus);
    Frustum frus1 = Frustum({pos.x,pos.y,pos.z},{pos.x,pos.y,pos.z+0.2},0.2,0.15,20,vertex_color_data);
    this->vec.push_back(frus1);
    frus1 = Frustum(pos,{pos.x,pos.y,pos.z-1.7},0.2,0,20,vertex_color_data);
    this->vec.push_back(frus1);

    static const GLfloat vertex_buffer_data[] = {
        -1.0, 0.0, 0,
         1.0, 0.0, 0,
         0.0, 1.0, 0,
    };
    static const GLfloat vertex_colo_data[] = {
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
    };

    this->scale = {0.6,0.6,1.0};
    this->position = pos;
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data,vertex_colo_data, GL_FILL);

}

void Plane::draw(glm::mat4 VP)
{
   for(auto &x:this->vec)
        x.draw(VP,this->rotation);     

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 align = glm::translate(this->position);
    glm::mat4 dealign = glm::translate(glm::vec3(-0.4*this->loc_z.x,-0.4*this->loc_z.y,-0.4*this->loc_z.z));

    glm::mat4 translate = glm::translate (glm::vec3(this->position.x,this->position.y,this->position.z));
    glm::mat4 scale = glm::scale(this->scale);
    glm::mat4 rotat = glm::rotate(float(-3.14/2),glm::vec3(1,0,0));
    Matrices.model *= (dealign*translate*this->rotation*rotat*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Plane::move(float x, float y,float z) {
     
    this->position.x +=x;
    this->position.y +=y;
    this->position.z +=z;

    for(auto &i:this->vec)
    {
        i.position.z +=z;
        i.position.x +=x;
        i.position.y +=y;
    }    
}

void Plane::rotate( float x, float y,float z) {
    
    this->rotationx += x;
    this->rotationy += y;
    this->rotationz += z;

    glm::vec3 rotx(this->rotation[0][0],this->rotation[1][0],this->rotation[2][0]);
    glm::vec3 roty(this->rotation[0][1],this->rotation[1][1],this->rotation[2][1]);
    glm::vec3 rotz(this->rotation[0][2],this->rotation[1][2],this->rotation[2][2]);

    this->loc_x = {rotx[0],roty[0],rotz[0]};
    this->loc_y = {rotx[1],roty[1],rotz[1]};
    this->loc_z = {rotx[2],roty[2],rotz[2]};
    
    glm::mat4 rotatex    = glm::rotate((float) (x), glm::vec3(1,0,0));
    glm::mat4 rotatey    = glm::rotate((float) (y), glm::vec3(0,1,0));
    glm::mat4 rotatez    = glm::rotate((float) (z), glm::vec3(0,0,1));
    this->rotation *= rotatez*rotatey*rotatex;   
}

void Plane::tick()
{
    if(this->barrel)
    {
        this->move(-0.05*this->loc_z.x,-0.05*this->loc_z.y,-0.05*this->loc_z.z);    
        this->rotate(0.0,0.0,0.05);
        if(this->rotationz>=6.28)
            this->barrel = 0;
    }
    if(this->loop)
    {
        this->move(-0.05*this->loc_z.x,-0.05*this->loc_z.y,-0.05*this->loc_z.z);    
        this->rotate(0.05,0.0,0.0);
        if(this->rotationx>=6.28)
            this->loop = 0;
    }
    if(this->fuel<=0.0)
    {
        this->ver_vel = std::max(this->ver_acc+this->ver_vel,-0.05f);
        this->move(0,this->ver_vel,0);
    }
    // this->hor_vel = std::max(-0.001f+this->hor_vel,0.0f);
    
}

