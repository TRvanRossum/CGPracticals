#include "grid.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

int Grid::isContainedAt(const Vec3Df & pos){
    //returns index that contains the position
    int indice = 0;
    return indice;
}

void Grid::putVertices(const std::vector<Vertex> & vertices){
    //put vertices in the corresponding voxels.
}

void Grid::drawCell(const Vec3Df & Min,const Vec3Df& Max) {

    const Vec3Df corners[8] =
    {
        Vec3Df(Min[0],Min[1],Min[2]),
        Vec3Df(Max[0],Min[1],Min[2]),
        Vec3Df(Min[0],Max[1],Min[2]),
        Vec3Df(Max[0],Max[1],Min[2]),
        Vec3Df(Min[0],Min[1],Max[2]),
        Vec3Df(Max[0],Min[1],Max[2]),
        Vec3Df(Min[0],Max[1],Max[2]),
        Vec3Df(Max[0],Max[1],Max[2])
    };


    static const unsigned short faceCorners[6][4] =
    {
        { 0,4,6,2 },
        { 5,1,3,7 },
        { 0,1,5,4 },
        { 3,2,6,7 },
        { 0,2,3,1 },
        { 6,4,5,7 }
    };

    glBegin(GL_QUADS);
    for (unsigned short f=0;f<6;++f)
    {
        const unsigned short* face = faceCorners[f];
        for(unsigned int v = 0; v<4; v++)
            glVertex3f(corners[face[v]][0], corners[face[v]][1], corners[face[v]][2]);

    }
    glEnd();

}

void Grid::drawGrid(){
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glLineWidth(1.0f);
    glColor3f(1.0f,1.0f,0.0f);
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    //Complete this function by calling draw cell several times.

    glPopAttrib();
}


