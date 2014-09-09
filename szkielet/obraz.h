#ifndef OBRAZ_H
#define OBRAZ_H

int obrazVertexCount=4;
int rama_oVertexCount=80;

float obrazVertices[]={
  -0.7, -0.7, 0, 
  0.7, -0.7, 0, 
  0.7, 0.7, 0, 
  -0.7, 0.7, 0
};

float rama_oVertices[]={
  -1, -1, 0.2, 
	1, -1, 0.2, 
	1, -0.7, 0.2, 
	-1, -0.7, 0.2, 

	-1, -1, -0.2, 
	1, -1, -0.2, 
	1, -0.7, -0.2, 
	-1, -0.7, -0.2,

	-1, -1, -0.2, 
	-1, -0.7, -0.2, 
	-1, -0.7, 0.2, 
	-1, -1, 0.2, 
	
	1, -1, -0.2, 
	1, -0.7, -0.2, 
	1, -0.7, 0.2, 
	1, -1, 0.2,

	-1, -1, -0.2, 
	1, -1, -0.2, 
	1, -1, 0.2, 
	-1, -1, 0.2, 

	
	-1, -0.7, -0.2, 
	1, -0.7, -0.2, 
	1, -0.7, 0.2, 
	-1, -0.7, 0.2,

	-1, 1, 0.2, 
	1, 1, 0.2, 
	1, 0.7, 0.2, 
	-1, 0.7, 0.2, 

	-1, 1, -0.2, 
	1, 1, -0.2, 
	1, 0.7, -0.2, 
	-1, 0.7, -0.2,

	-1, 1, -0.2, 
	-1, 0.7, -0.2, 
	-1, 0.7, 0.2, 
	-1, 1, 0.2, 
	
	1, 1, -0.2, 
	1, 0.7, -0.2, 
	1, 0.7, 0.2, 
	1, 1, 0.2,

	-1, 1, -0.2, 
	1, 1, -0.2, 
	1, 1, 0.2, 
	-1, 1, 0.2, 

	
	-1, 0.7, -0.2, 
	1, 0.7, -0.2, 
	1, 0.7, 0.2, 
	-1, 0.7, 0.2,

	-1, -0.7, -0.2, 
	-0.7, -0.7, -0.2, 
	-0.7, 0.7, -0.2, 
	-1, 0.7, -0.2,

	1, -0.7, -0.2, 
	0.7, -0.7, -0.2, 
	0.7, 0.7, -0.2, 
	1, 0.7, -0.2, 

	-1, -0.7, 0.2, 
	-0.7, -0.7, 0.2, 
	-0.7, 0.7, 0.2, 
	-1, 0.7, 0.2,

	1, -0.7, 0.2, 
	0.7, -0.7, 0.2, 
	0.7, 0.7, 0.2, 
	1, 0.7, 0.2, 

	-1, -0.7, -0.2, 
	-1, -0.7, 0.2, 
	-1, 0.7, 0.2, 
	-1, 0.7, -0.2,

	1, -0.7, -0.2, 
	1, -0.7, 0.2, 
	1, 0.7, 0.2, 
	1, 0.7, -0.2,

	-0.7, -0.7, -0.2, 
	-0.7, -0.7, 0.2, 
	-0.7, 0.7, 0.2, 
	-0.7, 0.7, -0.2,

	0.7, -0.7, -0.2, 
	0.7, -0.7, 0.2, 
	0.7, 0.7, 0.2, 
	0.7, 0.7, -0.2,

};


float rama_oColors[]={
  1,0,0, 1,0,0, 1,0,0, 1,0,0,
	0,1,0, 0,1,0, 0,1,0, 0,1,0,
	0,0,1, 0,0,1, 0,0,1, 0,0,1,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	0,1,1, 0,1,1, 0,1,1, 0,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	0,1,0, 0,1,0, 0,1,0, 0,1,0,
	0,0,1, 0,0,1, 0,0,1, 0,0,1,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	0,1,1, 0,1,1, 0,1,1, 0,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	0,1,0, 0,1,0, 0,1,0, 0,1,0,
	0,0,1, 0,0,1, 0,0,1, 0,0,1,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	0,1,1, 0,1,1, 0,1,1, 0,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	0,1,1, 0,1,1, 0,1,1, 0,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
  
};

float obrazColors[]={
  1,0,0, 1,0,0, 1,0,0, 1,0,0
};

float rama_oTexVertices[]={
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
  0,0,	0,1,	1,1,	1,0,
};

float obrazTexVertices[]={
  0,0,	0,1,	1,1,	1,0
};
