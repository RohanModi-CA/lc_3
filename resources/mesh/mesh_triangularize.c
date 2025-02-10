#include "lib/fast_obj.h"
#include <stdio.h>
#include "raylib.h"
#include "rlgl.h"
#include <stdlib.h>
#include "mesh_load.h"

/* Input a pointer to a mesh, and output the number of triangles the
 * post-triangularized mesh will have. */
static int _how_many_triangles(fastObjMesh *mesh)
{
	int face_count; int triangles; int face_vertices;

	face_count = mesh->face_count; triangles = 0;
	for(int face=0; face<face_count; ++face)
	{
		face_vertices = mesh->face_vertices[face];
		if(face_vertices >= 3)
		{
			// An n-side polygon will produce n-2 triangles after fanning.
			triangles += (face_vertices - 2);
		}
		else
		{
			fprintf(stderr, "mesh_triangularize: invalid OBJ, 2-vertex face.\n");
			exit(1);
		}
	}
	return triangles;
}

static fastObjMesh* _init_triangle_mesh(fastObjMesh *mesh_inp)
{
	// First we create the mesh:
	fastObjMesh *mesh_out = (fastObjMesh*) malloc(sizeof(fastObjMesh));
	
	/* Next we copy over the counts for the positions, textures, and normals. Those aren't changed, 
	 * since we aren't adding vertices, just faces. */
	mesh_out->position_count = mesh_inp->position_count;
	mesh_out->texcoord_count = mesh_inp->texcoord_count;
	mesh_out->normal_count = mesh_inp->normal_count;	

	/* Now we need to allocate memory for the lists of each. */
	mesh_out->positions = (float*) malloc( mesh_out->position_count * sizeof(float) );
	mesh_out->texcoords = (float*) malloc( mesh_out->texcoord_count * sizeof(float) );
	mesh_out->normals = (float*) malloc( mesh_out->normal_count * sizeof(float) );

	/* And now we actually copy them over */
	mesh_out->positions = mesh_inp->positions;
	mesh_out->texcoords = mesh_inp->texcoords;
	mesh_out->normals = mesh_inp->normals;


	/* We calculate the number of triangles we will need, and use 
	 * that to calculate the vertices, and allocate memory for it. */
	mesh_out->face_count = _how_many_triangles(mesh_inp);
	mesh_out->index_count = mesh_out->face_count * 3; 
	mesh_out->indices = (fastObjIndex*) malloc( mesh_out->index_count * sizeof(fastObjIndex));



	return mesh_out;
} // _init_triangle_mesh



static fastObjMesh* _mesh_triangularize(fastObjMesh *mesh)
{
	fastObjMesh *mesh_out;
	fastObjIndex v0, v1, v2; 

	// First we get the mesh to inspect it:

	/* Initialize, prepopulating p, t, n, their counts, and correct 
	 * face count, and malloc-ing correct space for the new index array .*/
	mesh_out = _init_triangle_mesh(mesh);

	/* Pass through all the triangles from the original mesh, but triangularize
	 * any non-triangles. */
	for(int face_inp=0, face_out=0, index_inp=0, index_out=0; face_inp < mesh->face_count; ++face_inp)
	{
		if (!(mesh->face_vertices[face_inp] == 3))
		{
			/* Now we implement fanning. We start at the first vertex, and we 
			 * connect that to every other vertex, except the one to its right and left. 
			 * in a pentagon, we will have the triangles: 012, 023, 034. Basically, we 
			 * will make triangles 0A(A+1), ensuring that all vertices are represented. */
			// For an n-sided shape, we will make (n-2) triangles.
			
		
			v0 = mesh->indices[index_inp];
			for(int i=0; i<(mesh->face_vertices[face_inp]-2); ++i)
			{
				v1 = mesh->indices[index_inp + i+1];
				v2 = mesh->indices[index_inp + i+2];

				// Now we set the triangle indices.
				mesh_out->indices[index_out] = v0;
				mesh_out->indices[index_out + 1] = v1;
				mesh_out->indices[index_out + 2] = v2;
				index_out += 3;
			}
			// Advance the index of the original mesh before iterating again:
			index_inp += mesh->face_vertices[face_inp];


		}
		else
		{
			mesh_out->indices[index_out] = mesh->indices[index_inp];
			mesh_out->indices[index_out + 1] = mesh->indices[index_inp + 1];
			mesh_out->indices[index_out + 2] = mesh->indices[index_inp + 2];
			++face_out; index_inp +=3; index_out += 3; 
		}
	}

	return mesh_out;
} // mesh_triangularize


fastObjMesh* mesh_triangularize_gen_triangularized_mesh(const char *fp)
{
	// Load Mesh
	fastObjMesh *mesh_original = mesh_load_init_mesh(fp);
	
	// Generate Triangularized Mesh
	fastObjMesh *mesh_triangularized = _mesh_triangularize(mesh_original);

	// Out with the old
	free(mesh_original);

	// In with the new
	return mesh_triangularized;
}


