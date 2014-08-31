#ifndef pianino_h
#define pianino_h

int pudloVertexCount=160;
int movingpokrywaVertexCount=44;

float pudloVertices[]={
	-1.5,-1.0,-0.5,
	-1.5, 1.0,-0.5,
	 1.5, 1.0,-0.5,
	 1.5,-1.0,-0.5,

	 -1.5,-1.0,0.5,
	-1.5, 1.0,0.5,
	 1.5, 1.0,0.5,
	 1.5,-1.0,0.5,

	 -1.5, -1.0, -0.5,
	 -1.5, -1.0, 0.5,
	 1.5, -1.0, 0.5,
	 1.5, -1.0, -0.5,

	 -1.5, -1.0, -0.5,
	 -1.5, 1.0, -0.5,
	 -1.5, 1.0, 0.5,
	 -1.5, -1.0, 0.5,

	 1.5, -1.0, -0.5,
	 1.5, 1.0, -0.5,
	 1.5, 1.0, 0.5,
	 1.5, -1.0, 0.5,

	 -1.5, 1.0, -0.5,
	 -1.5, 1.0, -0.35,
	 1.5, 1.0, -0.35,
	 1.5, 1.0, -0.5,

	 -1.5, 1.0, 0.5,
	 -1.5, 1.0, 0.35,
	 1.5, 1.0, 0.35,
	 1.5, 1.0,0.5,

	 -1.5, 1.0, 0.35,
	 -1.35, 1.0, 0.35,
	 -1.35, 1.0, -0.35,
	 -1.5, 1.0, -0.35,
	 
	 1.5, 1.0, 0.35,
	 1.35, 1.0, 0.35,
	 1.35, 1.0, -0.35,
	 1.5, 1.0, -0.35,

	 -1.35, 1.0, 0.35,
	 -1.35, -1.0, 0.35,
	 -1.35, -1.0, -0.35,
	 -1.35, 1.0, -0.35,

	 1.35, 1.0, 0.35,
	 1.35, -1.0, 0.35,
	 1.35, -1.0, -0.35,
	 1.35, 1.0, -0.35,

	 -1.35, -0.85, -0.35,
	 -1.35, -0.85, 0.35,
	 1.35, -0.85, 0.35,
	 1.35, -0.85, -0.35,

	 -1.35, -1.0, -0.35,
	 -1.35, 1.0, -0.35,
	 1.35, 1.0, -0.35,
	 1.35, -1.0, -0.35,

	 -1.35, -1.0, 0.35,
	 -1.35, 1.0, 0.35,
	 1.35, 1.0, 0.35,
	 1.35, -1.0, 0.35,

	 -1.5, 1.001, 0.0, 
	 -1.5, 1.001, 0.5,
	 1.5, 1.001, 0.5, 
	 1.5, 1.001, 0.0,
	
	 -1.5, 1.001, 0.0, 
	 -1.5, 1.10, 0.0, 
	 -1.5, 1.10, 0.5,
	 -1.5, 1.001, 0.5,

	 1.5, 1.001, 0.0, 
	 1.5, 1.10, 0.0, 
	 1.5, 1.10, 0.5,
	 1.5, 1.001, 0.5,

	 -1.5, 1.001, 0.0,
	 1.5, 1.001, 0.0,
	 1.5, 1.10, 0.0,
	 -1.5, 1.10, 0.0,

	 -1.5, 1.001, 0.5,
	 1.5, 1.001, 0.5,
	 1.5, 1.10, 0.5,
	 -1.5, 1.10, 0.5,

	 -1.5, 1.10, 0.0, 
	 -1.6, 1.10, 0.0, 
	 -1.6, 1.10, 0.5, 
	 -1.5, 1.10, 0.5,

	 1.5, 1.10, 0.0, 
	 1.6, 1.10, 0.0, 
	 1.6, 1.10, 0.5, 
	 1.5, 1.10, 0.5,

	 -1.6, 1.10, 0.0, 
	 1.6, 1.10, 0.0, 
	 1.6, 1.20, 0.0,
	 -1.6, 1.20, 0.0,

	 -1.6, 1.10, 0.5, 
	 -1.6, 1.10, 0.6,
	 1.6, 1.10, 0.6, 
	 1.6, 1.10, 0.5,

	 -1.6, 1.10, 0.6,
	 -1.6, 1.20, 0.6,
	 1.6, 1.20, 0.6,
	 1.6, 1.10, 0.6,

	 -1.6, 1.10, 0.0,
	 -1.6, 1.10, 0.6,
	 -1.6, 1.20, 0.6,
	 -1.6, 1.20, 0.0,

	 1.6, 1.10, 0.0,
	 1.6, 1.10, 0.6,
	 1.6, 1.20, 0.6,
	 1.6, 1.20, 0.0,

	 -1.6, 1.20, 0.0, 
	 -1.6, 1.20, 0.6,
	 1.6, 1.20, 0.6,
	 1.6, 1.20, 0.0,

	 -1.5, 0.4, -0.5,
	 -1.5, 0.0, -0.5,
	 -1.5, 0.0, -0.8,
	 -1.5, 0.3, -0.8,

	 1.5, 0.4, -0.5,
	 1.5, 0.0, -0.5,
	 1.5, 0.0, -0.8,
	 1.5, 0.3, -0.8,

	 -1.4, 0.4, -0.5,
	 -1.4, 0.0, -0.5,
	 -1.4, 0.0, -0.8,
	 -1.4, 0.3, -0.8,

	 1.4, 0.4, -0.5,
	 1.4, 0.0, -0.5,
	 1.4, 0.0, -0.8,
	 1.4, 0.3, -0.8,

	 -1.5, 0.0, -0.5, 
	 -1.5, 0.0, -0.8, 
	 -1.4, 0.0, -0.8, 
	 -1.4, 0.0, -0.5,

	 1.5, 0.0, -0.5, 
	 1.5, 0.0, -0.8, 
	 1.4, 0.0, -0.8, 
	 1.4, 0.0, -0.5,

	 -1.5, 0.0, -0.8,
	 -1.4, 0.0, -0.8,
	 -1.4, 0.3, -0.8, 
	 -1.5, 0.3, -0.8, 

	 1.5, 0.0, -0.8,
	 1.4, 0.0, -0.8,
	 1.4, 0.3, -0.8, 
	 1.5, 0.3, -0.8, 

	 -1.5, 0.4, -0.5,
	 -1.5, 0.3, -0.8,
	 -1.4, 0.3, -0.8, 
	 -1.4, 0.4, -0.5,

	 1.5, 0.4, -0.5,
	 1.5, 0.3, -0.8,
	 1.4, 0.3, -0.8, 
	 1.4, 0.4, -0.5,

	 -1.4, 0.0, -0.5,
	 -1.4, 0.0, -0.8, 
	 1.4, 0.0, -0.8,
	 1.4, 0.0, -0.5,

	 -1.4, 0.1, -0.5,
	 -1.4, 0.1, -0.8, 
	 1.4, 0.1, -0.8,
	 1.4, 0.1, -0.5,

	 -1.4, 0.0, -0.8,
	 -1.4, 0.1, -0.8,
	 1.4, 0.1, -0.8,
	 1.4, 0.0, -0.8,
};

float movingpokrywaVertices[]={
	-1.5,-0.10,0.0,
	-1.5, -0.10,-0.5,
	 1.5, -0.10,-0.5,
	 1.5,-0.10,0.0,

	 1.5, -0.10, 0.0,
	 1.5, -0.10, -0.5,
	 1.5, 0.0, -0.5,
	 1.5, 0.0, 0.0,

	 -1.5, -0.10, 0.0,
	 -1.5, -0.10, -0.5,
	 -1.5, 0.0, -0.5,
	 -1.5, 0.0, 0.0,

	 -1.5, -0.10, 0.0,
	 1.5, -0.10, 0.0, 
	 1.5, 0.0, 0.0,
	 -1.5, 0.0, 0.0,

	 -1.5, -0.10, -0.5,
	 1.5, -0.10, -0.5, 
	 1.5, 0.0, -0.5,
	 -1.5, 0.0, -0.5,

	 -1.6, 0.0, 0.0,
	 1.6, 0.0, 0.0,
	 1.6, 0.0, -0.6,
	 -1.6, 0.0, -0.6,

	 -1.6, 0.0, 0.0,
	 -1.6, 0.0, -0.6, 
	 -1.6, 0.1, -0.6,
	 -1.6, 0.1, 0.0,

	 1.6, 0.0, 0.0,
	 1.6, 0.0, -0.6, 
	 1.6, 0.1, -0.6,
	 1.6, 0.1, 0.0,

	 -1.6, 0.0, 0.0,
	 -1.6, 0.1, 0.0, 
	 1.6, 0.1, 0.0,
	 1.6, 0.0, 0.0, 

	 -1.6, 0.0, -0.6,
	 -1.6, 0.1, -0.6, 
	 1.6, 0.1, -0.6,
	 1.6, 0.0, -0.6, 

	 -1.6, 0.1, 0.0,
	 1.6, 0.1, 0.0,
	 1.6, 0.1, -0.6,
	 -1.6, 0.1, -0.6
};

float pudloColors[]={
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	0,0,1, 0,0,1, 0,0,1, 0,0,1,
	0,0,1, 0,0,1, 0,0,1, 0,0,1,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
};

float pudlotexVertices[]={
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0
}; 

float movingpokrywaColor[]={
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	0,0,1, 0,0,1, 0,0,1, 0,0,1,
	0,0,1, 0,0,1, 0,0,1, 0,0,1,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
};

float movingpokrywaTex[]={
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0,
	0,0,		0,1,		1,1,		1,0, 
	0,0,		0,1,		1,1,		1,0,
};
#endif
