#include "frustum.h"

Frustum::Frustum(glm::vec3 pos1,glm::vec3 pos2, float scl1, float scl2,int n,GLfloat vertex_color_data[])
{

    float angle = float(2.0*3.14)/float(n);
	float rotation[3][3] = {(float)cos(angle),(float)-sin(angle),0.0,(float)sin(angle),(float)cos(angle),0.0,0.0,0.0,1.0};
	float xarr1[n];
	float yarr1[n];
    float xarr2[n];
	float yarr2[n];
    this->position = pos1;
    // std::cout<<this->position.x<<" "<<this->position.y<<" "<<this->position.z<<std::endl;
	this->scale = {1.0,1.0,1.0};
    this->rotationx = 0;
    this->rotationy = 0;
    this->rotationz = 0;
	GLfloat vertex_buffer_data[2000];
    xarr1[0]=0.0;
	yarr1[0]=1.0*scl1;
	// printf("%f %f\n",xarr1[0],yarr1[0]);
	for(int i=1;i<n;i++)
	{
		float x =rotation[0][0]*xarr1[i-1] + rotation[0][1]*yarr1[i-1];
		float y =rotation[1][0]*xarr1[i-1] + rotation[1][1]*yarr1[i-1];
		xarr1[i] = x;
		yarr1[i] = y;
	}		

	//circle 1
	for(int i=0;i<n;i++)
	{
		vertex_buffer_data[9*i] = 0.0;
		vertex_buffer_data[9*i+1] = 0.0;
		vertex_buffer_data[9*i+2] = 0.0;

		vertex_buffer_data[9*i+3] = xarr1[i];
		vertex_buffer_data[9*i+4] = yarr1[i];
		vertex_buffer_data[9*i+5] = 0.0;

		vertex_buffer_data[9*i+6] = xarr1[(i+1)%n];
		vertex_buffer_data[9*i+7] = yarr1[(i+1)%n];
		vertex_buffer_data[9*i+8] = 0.0;

        // vertex_color_data[9*i]   = 0.8f;
		// vertex_color_data[9*i+1] = 0.1f;
		// vertex_color_data[9*i+2] = 0.1f;

		// vertex_color_data[9*i+3] = 0.8f;
		// vertex_color_data[9*i+4] = 0.1f;
		// vertex_color_data[9*i+5] = 0.1f;

		// vertex_color_data[9*i+6] = 0.8f;
		// vertex_color_data[9*i+7] = 0.1f;
		// vertex_color_data[9*i+8] = 0.1f;
        
	}
    xarr2[0]=0.0;
	yarr2[0]=1.0*scl2;
	for(int i=1;i<n;i++)
	{
		float x =rotation[0][0]*xarr2[i-1] + rotation[0][1]*yarr2[i-1];
		float y =rotation[1][0]*xarr2[i-1] + rotation[1][1]*yarr2[i-1];
		xarr2[i] = x;
		yarr2[i] = y;
	}

	//circle 2
    for(int i=0;i<n;i++)
	{
		vertex_buffer_data[9*(i+n)] = 0.0;
		vertex_buffer_data[9*(i+n)+1] = 0.0;
		vertex_buffer_data[9*(i+n)+2] = pos2.z-pos1.z;

		vertex_buffer_data[9*(i+n)+3] = xarr2[i];
		vertex_buffer_data[9*(i+n)+4] = yarr2[i];
		vertex_buffer_data[9*(i+n)+5] = pos2.z-pos1.z;

		vertex_buffer_data[9*(i+n)+6] = xarr2[(i+1)%n];
		vertex_buffer_data[9*(i+n)+7] = yarr2[(i+1)%n];
		vertex_buffer_data[9*(i+n)+8] = pos2.z-pos1.z;

        // vertex_color_data[9*(i+n)]   = 0.8f;
		// vertex_color_data[9*(i+n)+1] = 0.1f;
		// vertex_color_data[9*(i+n)+2] = 0.1f;

		// vertex_color_data[9*(i+n)+3] = 0.8f;
		// vertex_color_data[9*(i+n)+4] = 0.1f;
		// vertex_color_data[9*(i+n)+5] = 0.1f;

		// vertex_color_data[9*(i+n)+6] = 0.8f;
		// vertex_color_data[9*(i+n)+7] = 0.1f;
		// vertex_color_data[9*(i+n)+8] = 0.1f;

	}

	//triangle
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[9*(i+2*n)] = xarr1[i];
		vertex_buffer_data[9*(i+2*n)+1] = yarr1[i];
		vertex_buffer_data[9*(i+2*n)+2] = 0.0;

		vertex_buffer_data[9*(i+2*n)+3] = xarr2[i];
		vertex_buffer_data[9*(i+2*n)+4] = yarr2[i];
		vertex_buffer_data[9*(i+2*n)+5] = pos2.z-pos1.z;

		vertex_buffer_data[9*(i+2*n)+6] = xarr2[(i+1)%n];
		vertex_buffer_data[9*(i+2*n)+7] = yarr2[(i+1)%n];
		vertex_buffer_data[9*(i+2*n)+8] = pos2.z-pos1.z;

        // vertex_color_data[9*(i+2*n)]   = 0.1f;
		// vertex_color_data[9*(i+2*n)+1] = 0.8f;
		// vertex_color_data[9*(i+2*n)+2] = 0.1f;

		// vertex_color_data[9*(i+2*n)+3] = 0.1;
		// vertex_color_data[9*(i+2*n)+4] = 0.8f;
		// vertex_color_data[9*(i+2*n)+5] = 0.1f;

		// vertex_color_data[9*(i+2*n)+6] = 0.1f;
		// vertex_color_data[9*(i+2*n)+7] = 0.8f;
		// vertex_color_data[9*(i+2*n)+8] = 0.1f;
    }

	//triangle
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[9*(i+3*n)] = xarr2[(i+1)%n];
		vertex_buffer_data[9*(i+3*n)+1] = yarr2[(i+1)%n];
		vertex_buffer_data[9*(i+3*n)+2] = pos2.z-pos1.z;

		vertex_buffer_data[9*(i+3*n)+3] = xarr1[i];
		vertex_buffer_data[9*(i+3*n)+4] = yarr1[i];
		vertex_buffer_data[9*(i+3*n)+5] = 0.0;

		vertex_buffer_data[9*(i+3*n)+6] = xarr1[(i+1)%n];
		vertex_buffer_data[9*(i+3*n)+7] = yarr1[(i+1)%n];
		vertex_buffer_data[9*(i+3*n)+8] = 0.0;

        // vertex_color_data[9*(i+3*n)]   = 0.1f;
		// vertex_color_data[9*(i+3*n)+1] = 0.1f;
		// vertex_color_data[9*(i+3*n)+2] = 0.8f;

		// vertex_color_data[9*(i+3*n)+3] = 0.1f;
		// vertex_color_data[9*(i+3*n)+4] = 0.1f;
		// vertex_color_data[9*(i+3*n)+5] = 0.8f;

		// vertex_color_data[9*(i+3*n)+6] = 0.1f;
		// vertex_color_data[9*(i+3*n)+7] = 0.1f;
		// vertex_color_data[9*(i+3*n)+8] = 0.8f;
    }    
	this->object = create3DObject(GL_TRIANGLES,12*n, vertex_buffer_data,vertex_color_data, GL_FILL);
}

void Frustum::draw(glm::mat4 VP,glm::mat4 rotate)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(this->scale);
    glm::mat4 rotatex    = glm::rotate((float) (this->rotationx), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz), glm::vec3(0, 0, 1));
 
    Matrices.model *= (translate*rotate*scale*rotatez*rotatey*rotatex);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}