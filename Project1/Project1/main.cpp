#if defined(_WIN32)
#include <windows.h>
#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "trackball.h"
#include "argumentParser.h"
#include <stdio.h>
#include <string.h>

//START READING HERE!!!


//////Predefined global variables

//Use the enum values to define different rendering modes 
//The mode is used by the function display and the mode is 
//chosen during execution with the keys 1-9
enum DisplayModeType {TRIANGLE=1, FACE=2, CUBE=3, ARM=4, MESH=5,};

DisplayModeType DisplayMode = CUBE;

unsigned int W_fen = 800;  // screen width
unsigned int H_fen = 800;  // screen height

// Global variables for the light position.
float lightX = 0.0, lightY = 0.0, lightZ = 0.0;

float LightPos[4] = {1,2,0.4,1};
std::vector<float> MeshVertices;
std::vector<unsigned int> MeshTriangles;

//Declare your own global variables here:
float globalXIncVal = 0.0;
float handAngleRot = 0.0;
float armAngleRot = 0.0;

////////// Draw Functions 

//function to draw coordinate axes with a certain length (1 as a default)
void drawCoordSystem(float length=1)
{
	//draw simply colored axes
	
	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//deactivate the lighting state
	glDisable(GL_LIGHTING);
	//draw axes
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(length,0,0);

		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,length,0);

		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,length);
	glEnd();
	
	//reset to previous state
	glPopAttrib();
}

/**
 * Several drawing functions for you to work on
*/

void drawTriangle()
{
	//a simple example of a drawing function for a triangle
	//1) try changing its color to red
	//2) try changing its vertex positions
	//3) add a second triangle in blue
	//4) add a global variable (initialized at 0), which represents the 
	// x-coordinate of the first vertex of each triangle
	//5) go to the function animate and increment this variable 
	//by a small value - observe the animation.

	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glColor3f(1,0,0);
	glNormal3f(0,0,1);
	glBegin(GL_TRIANGLES);
		glVertex3f(0 + globalXIncVal,0,0);
		glVertex3f(1 + globalXIncVal,0,0);
		glVertex3f(1 + globalXIncVal,1,0);
	glEnd();

	glColor3f(0, 0, 1);
	glNormal3f(0, 0, 1);
	glBegin(GL_TRIANGLES);
		glVertex3f(1 + globalXIncVal, 0, 0);
		glVertex3f(2 + globalXIncVal, 0, 0);
		glVertex3f(2 + globalXIncVal, 1, 0);
	glEnd();

	//reset to previous state
	glPopAttrib();
}

void drawTriangleAdapted(int index1, int index2, int index3)
{
	//a simple example of a drawing function for a triangle
	//1) try changing its color to red
	//2) try changing its vertex positions
	//3) add a second triangle in blue
	//4) add a global variable (initialized at 0), which represents the 
	// x-coordinate of the first vertex of each triangle
	//5) go to the function animate and increment this variable 
	//by a small value - observe the animation.

	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glColor3f(0.5, 0.5, 0.5);
	float v1 = MeshVertices[index1];
	float v2 = MeshVertices[index2];
	float v3 = MeshVertices[index3];

	/*glColor3f(1, 0, 0);
	glNormal3f(0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(0 + globalXIncVal, 0, 0);
	glVertex3f(1 + globalXIncVal, 0, 0);
	glVertex3f(1 + globalXIncVal, 1, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glNormal3f(0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(1 + globalXIncVal, 0, 0);
	glVertex3f(2 + globalXIncVal, 0, 0);
	glVertex3f(2 + globalXIncVal, 1, 0);
	glEnd();*/

	//reset to previous state
	glPopAttrib();
}

void drawUnitFace()
{
	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glColor3f(1, 1, 1);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
		glVertex3f(1, 1, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
	glEnd();
	//1) draw a unit quad in the x,y plane oriented along the z axis
	//2) make sure the orientation of the vertices is positive (counterclock wise)
	//3) What happens if the order is inversed?
		// answer to 3: a unit quad is drawn with the filled-in side at the other side.

	//reset to previous state
	glPopAttrib();
}

void drawUnitCube()
{
	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	drawUnitFace();

	glPushMatrix();
	glTranslatef(1, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawUnitFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -1);
	glRotatef(180, 0, -1, 0);
	glTranslatef(-1, 0, 0);
	drawUnitFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -1);
	glRotatef(270, 0, 1, 0);
	drawUnitFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -1);
	glRotatef(90, 1, 0, 0);
	drawUnitFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, -1);
	glRotatef(90, 1, 0, 0);
	drawUnitFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(270, 1, 0, 0);
	drawUnitFace();
	glPopMatrix();

	/*
	// Placing it correctly.
	glTranslatef(0, 1, 1);
	// Resetting rotations.
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	// Instructions for drawing the cube.
	glTranslatef(0, 0, 1);
	drawUnitFace();
	glTranslatef(0, 1, -1);
	glRotatef(180, 1, 0, 0);
	drawUnitFace();
	glTranslatef(0, 0, -1);
	glRotatef(90, 1, 0, 0);
	drawUnitFace();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 1);
	drawUnitFace();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 1);
	drawUnitFace();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 1);
	drawUnitFace();
	//1) draw a cube using your function drawUnitFace
	//rely on glTranslate, glRotate, glPushMatrix, and glPopMatrix
	//the latter two influence the model matrix, as seen during the course.
	//glPushMatrix stores the current matrix and puts a copy on 
	//the top of a stack.
	//glPopMatrix pops the top matrix on the stack

	glPopMatrix();*/

	//reset to previous state
	glPopAttrib();
}

void drawArm()
{
	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	drawUnitCube();
	glRotatef(armAngleRot, 1, 0, 0);
	//glTranslatef(0, 0, 1);
	drawUnitCube();
	glRotatef(handAngleRot, 1, 0, 0);
	//glTranslatef(0, 0, 1);
	drawUnitCube();
	//produce a three-unit arm (upperarm, forearm, hand) making use of your 
	//function drawUnitCube to define each of them
	//1) define 3 global variables that control the angles 
	//between the arm parts
	//and add cases to the keyboard function to control these values
	
	//2) use these variables to define your arm
	//use glScalef to achieve different arm length
	//use glRotate/glTranslate to correctly place the elements
	
	//3 optional) make an animated snake out of these boxes 
	//(an arm with 10 joints that moves using the animate function)

	//reset to previous state
	glPopAttrib();
}

void drawLight()
{
	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//deactivate the lighting state
	glDisable(GL_LIGHTING);
	//yellow sphere at light position
	glColor3f(1, 1, 0);

	// Correcting lightPos:
	LightPos[0] += lightX;
	LightPos[1] += lightY;
	LightPos[2] += lightZ;

	// resetting the variables:
	lightX = 0;
	lightY = 0;
	lightZ = 0;

	glPushMatrix();
	glTranslatef(LightPos[0], LightPos[1], LightPos[2]);
	glutSolidSphere(0.1, 20, 20);
	glPopMatrix();

	//reset to previous state
	glPopAttrib();
	//1) use glutSolidSphere to draw a sphere at the light's position LightPos
	//use glTranslatef to move it to the right location
	//to make the light source bright, follow the drawCoordSystem function
	//to deactivate the lighting temporarily and draw it in yellow

	//2) make the light position controllable via the keyboard function

	//3) add normal information to all your faces of the previous functions
	//and observe the shading after pressing 'L' to activate the lighting
	//you can use 'l' to turn it off again

}


void drawMesh()
{
	printf("Mesh triangle size: %d", MeshTriangles.size());
	//1) use the mesh data structure;
	//each triangle is defined with 3 consecutive indices in the MeshTriangles table
	//these indices correspond to vertices stored in the MeshVertices table.
	//provide a function that draws these triangles.

	//2) compute the normals of these triangles

	//3) try computing a normal per vertex as the average of the adjacent face normals
	// call glNormal3f with the corresponding values before each vertex
	// What do you observe with respect to the lighting?

	//4) try loading your own model (export it from Blender as a Wavefront obj) and replace the provided mesh file.

	/**
	Due to the David.obj not loading, I will provide pseudocode on how to do this:
		1. Look for the three individual vertices per triangle.
		2. Draw these vertices. This results in a triangle.
		3. Compute the normal per triangle. This can be done by:
			3a. Call the three vertices v1, v2 and v3.
			3b. Calculate distances d1 = v2 - v1, d2 = v3 - v1.
			3c. Calculate normal: N = d1 x d2 (x is for cross product).
		4. Repeat this for every triangle.
	**/

}


void display( )
{
	//set the light to the right position
    glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	drawLight();
	drawCoordSystem();

	switch( DisplayMode )
	{
	case TRIANGLE:
		drawMesh();
		drawTriangle();
		break;
	case FACE:
		drawUnitFace();
		break;
	case CUBE:
		drawUnitCube();
		break;
	case ARM:
		drawArm();
		break;

	default:
		drawMesh();
		break;
	}
}


/**
 * Animation
 */
void animate( )
{
	//globalXIncVal += 0.005;
}


//take keyboard input into account
void keyboard(unsigned char key, int x, int y)
{
    printf("key %d pressed at %d,%d\n",key,x,y);
    fflush(stdout);

	if ((key>='1')&&(key<='9'))
	{
		DisplayMode= (DisplayModeType) (key-'0');
		return;
	}
	
	switch (key)
    {
	case 27:     // touche ESC
        exit(0);
	case 'L':
		//turn lighting on
		glEnable(GL_LIGHTING);
		break;
	case 'l':
		//turn lighting off
		glDisable(GL_LIGHTING);
		break;
	case 'q':
		handAngleRot += 0.5;
		break;
	case 'w':
		armAngleRot += 0.5;
		break;
	case 'a':
		handAngleRot -= 0.5;
		break;
	case 's':
		armAngleRot -= 0.5;
		break;
	case 'i':
		lightX += 0.05;
		break;
	case 'I':
		lightX -= 0.05;
		break;
	case 'o':
		lightY += 0.05;
		break;
	case 'O':
		lightY -= 0.05;
		break;
	case 'p':
		lightZ += 0.05;
		break;
	case 'P':
		lightZ -= 0.05;
		break;
    }
}


//Nothing needed below this point
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 
//STOP READING //STOP READING //STOP READING 





void displayInternal(void);
void reshape(int w, int h);
bool loadMesh(const char * filename);
void init()
{
    glDisable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

	//int MatSpec [4] = {1,1,1,1};
 //   glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
 //   glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,10);


    // Enable Depth test
    glEnable( GL_DEPTH_TEST );
	
	//glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
	//Draw frontfacing polygons as filled
    glPolygonMode(GL_FRONT,GL_FILL);
	//draw backfacing polygons as outlined
    glPolygonMode(GL_BACK,GL_LINE);
	glShadeModel(GL_SMOOTH);
	loadMesh("David.obj");
}


//load mesh
//this code is NOT how you should load a mesh... it is a bit hacky...
void centerAndScaleToUnit (std::vector<float> & vertices)
{
	if (vertices.size()%3!=0)
	{
		cout<<"ERROR while loading!!!\n";
		return;
	}		
	
	float x=0;
	float y=0;
	float z=0;
    for  (unsigned int i = 0; i < vertices.size (); i+=3)
	{ 
		x += vertices[i];
        y += vertices[i+1];
        z += vertices[i+2];
	}    


	x /= vertices.size ()/3;
	y /= vertices.size ()/3;
	z /= vertices.size ()/3;

    float maxD = 0;
    for (unsigned int i = 0; i < vertices.size (); i+=3){
        float dX= (vertices[i]-x);
        float dY= (vertices[i+1]-y);
        float dZ= (vertices[i+2]-z);

		float m = sqrt(dX*dX+dY*dY+dZ*dZ);
        if (m > maxD)
            maxD = m;
    }
	float center[]={x,y,z};
    for  (unsigned int i = 0; i < vertices.size (); i+=3)
	{
			vertices[i] = (vertices[i] - x) / maxD;
			vertices[i+1] = (vertices[i+1] - y) / maxD;
			vertices[i+2] = (vertices[i+2] - z) / maxD;
	}
}

bool loadMesh(const char * filename)
{
    const unsigned int LINE_LEN=256;
    char s[LINE_LEN];
    FILE * in;
#ifdef WIN32
    errno_t error=fopen_s(&in, filename,"r");
    if (error!=0)
#else
        in = fopen(filename,"r");
    if (!(in))
#endif
        return false;

	//temp stuff
    float x, y, z;
    std::vector<int> vhandles;



    while(in && !feof(in) && fgets(s, LINE_LEN, in))
    {
        // vertex
        if (strncmp(s, "v ", 2) == 0)
        {
            if (sscanf_s(s, "v %f %f %f", &x, &y, &z))
                MeshVertices.push_back(x);
				MeshVertices.push_back(y);
				MeshVertices.push_back(z);
        }
        // face
        else if (strncmp(s, "f ", 2) == 0)
        {
            int component(0), nV(0);
            bool endOfVertex(false);
            char *p0, *p1(s+2); //place behind the "f "

            vhandles.clear();

            while (*p1 == ' ') ++p1; // skip white-spaces

            while (p1)
            {
                p0 = p1;

                // overwrite next separator

                // skip '/', '\n', ' ', '\0', '\r' <-- don't forget Windows
                while (*p1 != '/' && *p1 != '\r' && *p1 != '\n' &&
                       *p1 != ' ' && *p1 != '\0')
                    ++p1;

                // detect end of vertex
                if (*p1 != '/') endOfVertex = true;

                // replace separator by '\0'
                if (*p1 != '\0')
                {
                    *p1 = '\0';
                    p1++; // point to next token
                }

                // detect end of line and break
                if (*p1 == '\0' || *p1 == '\n')
                    p1 = 0;


                // read next vertex component
                if (*p0 != '\0')
                {
                    switch (component)
                    {
                    case 0: // vertex
                        vhandles.push_back(atoi(p0)-1);
                        break;

                    case 1: // texture coord
                        //assert(!vhandles.empty());
                        //assert((unsigned int)(atoi(p0)-1) < texcoords.size());
                        //_bi.set_texcoord(vhandles.back(), texcoords[atoi(p0)-1]);
                        break;

                    case 2: // normal
                        //assert(!vhandles.empty());
                        //assert((unsigned int)(atoi(p0)-1) < normals.size());
                        //_bi.set_normal(vhandles.back(), normals[atoi(p0)-1]);
                        break;
                    }
                }

                ++component;

                if (endOfVertex)
                {
                    component = 0;
                    nV++;
                    endOfVertex = false;
                }
            }


            if (vhandles.size()>3)
            {
                //model is not triangulated, so let us do this on the fly...
                //to have a more uniform mesh, we add randomization
                unsigned int k=(false)?(rand()%vhandles.size()):0;
                for (unsigned int i=0;i<vhandles.size()-2;++i)
                {
                    MeshTriangles.push_back(vhandles[(k+0)%vhandles.size()]);
					MeshTriangles.push_back(vhandles[(k+i+1)%vhandles.size()]);
					MeshTriangles.push_back(vhandles[(k+i+2)%vhandles.size()]);
                }
            }
            else if (vhandles.size()==3)
            {
                MeshTriangles.push_back(vhandles[0]);
				MeshTriangles.push_back(vhandles[1]);
				MeshTriangles.push_back(vhandles[2]);
            }
            else
            {
                std::cout<<"TriMesh::LOAD: Unexpected number of face vertices (<3). Ignoring face \n";
            }
        }
        memset(&s, 0, LINE_LEN);
    }
    fclose(in);
    centerAndScaleToUnit (MeshVertices);
	return true;
}




/**
 * Programme principal
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    // couches du framebuffer utilisees par l'application
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    // position et taille de la fenetre
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(W_fen,H_fen);
    glutCreateWindow(argv[0]);

    init( );
	
    // Initialize viewpoint
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-4);
    tbInitTransform();     
    tbHelp();
         
    

	// cablage des callback
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(displayInternal);
    glutMouseFunc(tbMouseFunc);    // traqueboule utilise la souris
    glutMotionFunc(tbMotionFunc);  // traqueboule utilise la souris
    glutIdleFunc(animate);

    // lancement de la boucle principale
    glutMainLoop();
    
    return 0;  // instruction jamais exécutée
}

/**
 * Fonctions de gestion opengl à ne pas toucher
 */
// Actions d'affichage
// Ne pas changer
void displayInternal(void)
{
    // Effacer tout
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT); // la couleur et le z
    

    glLoadIdentity();  // repere camera

    tbVisuTransform(); // origine et orientation de la scene

    display( );    

    glutSwapBuffers();
    glutPostRedisplay();
}
// pour changement de taille ou desiconification
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho (-1.1, 1.1, -1.1,1.1, -1000.0, 1000.0);
    gluPerspective (50, (float)w/h, 1, 10);
    glMatrixMode(GL_MODELVIEW);
}

