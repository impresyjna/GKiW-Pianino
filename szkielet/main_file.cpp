#include <windows.h> 
#include "gl\glew.h"
#include "gl\glut.h"
#include "stdio.h" 
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "tga.h"
#include "cube.h"
#include <fstream>
#include <string>

using namespace std; 

GLuint tapeta;
GLuint podloga; 
GLuint sufit;
TGAImg img;  

void rysuj_z_tex(GLuint *uchwyt, float *ver, float *vertexture, int vercount) {
	glBindTexture(GL_TEXTURE_2D,*uchwyt);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer( 3, GL_FLOAT, 0, ver);
	glTexCoordPointer( 2, GL_FLOAT, 0, vertexture);
	glDrawArrays( GL_QUADS, 0, vercount);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
};
void macierz_tla() {
	glm::mat4 M;

	M=glm::mat4(1.0f); //m zawiera macierz jednostkow¹(I)
	M=glm::rotate(M,-90.0f,glm::vec3(0.0f,0.0f,1.0f));
	M=glm::rotate(M,-90.0f,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::scale(M,glm::vec3(4.0f,4.0f,4.0f));

	glm::mat4 V=glm::lookAt(
		glm::vec3(3.0f, 0.0f,-4.0f),
		glm::vec3(0.0f,-1.1f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f));

	glm::mat4 P=glm::perspective(75.0f, 1.0f, 1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(V*M));
};

void displayFrame(void) {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Rysowanie podlogi,sufitu i scian */
	macierz_tla(); 
	rysuj_z_tex(&podloga,podlogaVertices,podlogatexVertices,podlogaVertexCount); 
	rysuj_z_tex(&sufit,sufitVertices,sufittexVertices,sufitVertexCount); 
	rysuj_z_tex(&tapeta,scianyVertices,scianytexVertices,scianyVertexCount); 

	glutSwapBuffers();
}


void wczytaj_teksture(GLuint *uchwyt, char *plik){
	if (img.Load(plik)==IMG_OK) {
		glGenTextures(1,&*uchwyt); //Zainicjuj uchwyt tex
		glBindTexture(GL_TEXTURE_2D,*uchwyt); //Przetwarzaj uchwyt tex
		if (img.GetBPP()==24) //Obrazek 24bit
			glTexImage2D(GL_TEXTURE_2D,0,3,img.GetWidth(),img.GetHeight(),0,
			GL_RGB,GL_UNSIGNED_BYTE,img.GetImg());
		else if (img.GetBPP()==32) //Obrazek 32bit
			glTexImage2D(GL_TEXTURE_2D,0,4,img.GetWidth(),img.GetHeight(),0,
			GL_RGBA,GL_UNSIGNED_BYTE,img.GetImg());
		else {
			//Obrazek 16 albo 8 bit, takimi siê nie przejmujemy
		}
	} else {
		//b³¹d
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_TEXTURE_2D); 
};

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1366,768);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Program OpenGL");        
	glutDisplayFunc(displayFrame);

	//Tutaj kod inicjujacy	
	glewInit();

	/*Wczytywanie wszystkich tekstur */
	wczytaj_teksture(&tapeta, "texture/sciana2.tga"); 
	wczytaj_teksture(&podloga, "texture/deski.tga"); 
	wczytaj_teksture(&sufit, "texture/sufit1.tga"); 


	glutMainLoop();	

	glDeleteTextures(1,&sufit);
	glDeleteTextures(1,&tapeta);
	glDeleteTextures(1,&podloga);

	return 0;
}