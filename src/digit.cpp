#include "main.h"
#include "digit.h"
#include "polygon.h"

Digit::Digit(float x, float y, color_t color,int digit)
{
    float PI = 3.14;
    float scx = 0.1;
    float scy = 0.01;
    this->scx = 0.1;
    this->scx = 0.01;
    float len = 2*scx;
    float bdt = 2*scy;
    if(digit==0||digit==2||digit==3||digit==5||digit==6||digit==7||digit==8||digit==9)
    {
        Rect b = Rect(x+len/2,y,COLOR_BLACK,scx,scy,0);
        this->vec.push_back(b); //1
    }
    if(digit==0||digit==4||digit==5||digit==6||digit==8||digit==9||digit=='L')
    {
        Rect b = Rect(x,y-len/2,COLOR_BLACK,scx,scy,PI/2);
        this->vec.push_back(b); //2
    }
    if(digit==0||digit==1||digit==2||digit==3||digit==4||digit==7||digit==8||digit==9)
    {
        Rect b = Rect(x+len,y-len/2,COLOR_BLACK,scx,scy,PI/2);
        this->vec.push_back(b); //3
    }
    if(digit==2||digit==3||digit==4||digit==5||digit==6||digit==8||digit==9||digit=='c'||digit=='r')
    {
        Rect b = Rect(x+len/2,y-len,COLOR_BLACK,scx,scy,0);
        this->vec.push_back(b); //4
    }
    if(digit==0||digit==2||digit==6||digit==6||digit==8||digit=='c'||digit=='r'||digit=='L'||digit=='v')
    {
        Rect b = Rect(x,y-3*(len/2),COLOR_BLACK,scx,scy,PI/2);
        this->vec.push_back(b); //5
    }
    if(digit==0||digit==1||digit==3||digit==4||digit==5||digit==6||digit==7||digit==8||digit==9||digit=='v')
    {
        Rect b = Rect(x+len,y-3*(len/2),COLOR_BLACK,scx,scy,PI/2);
        this->vec.push_back(b);//6
    }
    if(digit==0||digit==2||digit==3||digit==5||digit==6||digit==8||digit==9||digit=='c'||digit=='L'||digit=='v')
    {
        Rect b = Rect(x+len/2,y-2*len,COLOR_BLACK,scx,scy,0);
        this->vec.push_back(b); //7
    }

}

void Digit::draw(glm::mat4 VP) {

    for(auto i:this->vec)
        i.draw(VP);
}


