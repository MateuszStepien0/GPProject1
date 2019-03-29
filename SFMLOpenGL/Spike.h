#ifndef SPIKE_H
#define SPIKE_H

#include <gl/glew.h>

const int SPIKE_VERTICES = 20;	// Total Number of Vertices
const int SPIKE_INDICES = 10;	    // Total Number of Indexes
const int SPIKE_UVS = 40; 	    // Total Number of UVs

static const GLfloat spikeVertices[] =
{
	// Front Face
	-1.00f, -1.00f,  1.00f,	// [0]	// ( 0)
	 1.00f, -1.00f,  1.00f,	// [1]	// ( 1)
	 0.0f,   1.00f,  0.0f,	// [2]	// ( 2)
	 0.0f,   1.00f,  0.0f,	// [3]	// ( 3)

	// Back Face
	 1.00f, -1.00f, -1.00f,	// [5]	// ( 4)
	-1.00f, -1.00f, -1.00f, // [4]	// ( 5)
	 0.0f,   1.00f,  0.0f,	// [7]	// ( 6)
	 0.0f,   1.00f,  0.0f,	// [6]	// ( 7)

	// Bottom Face
	-1.00f, -1.00f, -1.00f, // [4]	// ( 8)
	 1.00f, -1.00f, -1.00f, // [5]	// ( 9)
	 1.00f, -1.00f,  1.00f, // [1]	// (10)
	-1.00f, -1.00f,  1.00f, // [0]	// (11)

	// Left Face
	-1.00f, -1.00f, -1.00f, // [4]	// (12)
	-1.00f, -1.00f,  1.00f, // [0]	// (13)
	 0.0f,   1.00f,  0.0f,  // [3]	// (14)
	 0.0f,   1.00f,  0.0f,  // [7]	// (15)

	// Right Face
	 1.00f, -1.00f,  1.00f, // [1]	// (16)
	 1.00f, -1.00f, -1.00f, // [5]	// (17)
	 0.0f,   1.00f,  0.0f,  // [6]	// (18)
	 0.0f,   1.00f,  0.0f,  // [2]	// (19)
};

static GLfloat spikeUvs[2 * 4 * 5] = {

	// Front Face
	0.0, 0.25,
	0.25, 0.25,
	0.25, 0.5,
	0.0, 0.5,

	0.0, 0.25,
	0.25, 0.25,
	0.25, 0.5,
	0.0, 0.5,

	0.0, 0.5,
	0.25, 0.5,
	0.25, 0.75,
	0.0, 0.75,

	0.0, 0.25,
	0.25, 0.25,
	0.25, 0.5,
	0.0, 0.5,

	0.0, 0.25,
	0.25, 0.25,
	0.25, 0.5,
	0.0, 0.5,
};

static const GLuint spikeIndices[] =
{
	// Front Face
	0, 1, 2,
	2, 3, 0,

	// Back Face
	4, 5, 6,
	6, 7, 4,

	// Bottom Face
	8, 9, 10,
	10, 11, 8,

	// Left Face
	12, 13, 14,
	14, 15, 12,

	// Right Face
	16, 17, 18,
	18, 19, 16
};
#endif
