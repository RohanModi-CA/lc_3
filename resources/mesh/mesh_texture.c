#include <string.h>
#include <math.h>
#include <stdio.h>
#include "lib/fast_obj.h"
#include "lib/stb_image.h"
#include "../lib/raylib/raylib.h"


// "Normalize" the coordinate (which could be anything) to the range [0,1]. 
static float _normalize_coordinate(float coordinate)
{
	if(coordinate >= 0 && coordinate <= 1)
	{
		return coordinate;
	}

	else if(coordinate > 1)
	{
		return coordinate - floor(coordinate);
	}
	else if(coordinate < 0)
	{
		return coordinate - floor(coordinate); // floor(-4.1) is -5, -4.1 - -5 = 0.9, intended behavior. 
	}
	else
	{
		fprintf(stderr, "mesh_texture: Logic error in normalization.");
	}

	return 0;
} // _normalize_coordinate


static struct fastObjImageContent _read_image_to_image_content(const char* filepath_to_image)
{
	struct fastObjImageContent im_cont_out;
	unsigned char *image_data = stbi_load(filepath_to_image, &im_cont_out.width, &im_cont_out.height,&im_cont_out.n_channels, STBI_default);

	if(!(image_data))
	{
		fprintf(stderr, "mesh_texture._get_color_at_pixel error, could not open texture image.");
		exit(1);
	}

	im_cont_out.pixel_array = image_data;

	return im_cont_out;
}


static Color _get_color_at_pixel(struct fastObjImageContent im_cont, float u, float v)
{
	unsigned char r = 0, g = 0, b = 0, a = 255;
	int n_channels = im_cont.n_channels;
	int width = im_cont.width;
	int height = im_cont.height;
	unsigned char *image_data = im_cont.pixel_array; // Just copy the pointer to a more convenient name. Not copying the list.

	int x = (int) (width * _normalize_coordinate(u));
	int y = (int) (width * _normalize_coordinate(v));
	
	if(n_channels >= 3) // rgb(a)
	{
		// Get the red, green, blue:
		r = image_data[ n_channels * (y * width + x) + 0];
		g = image_data[ n_channels * (y * width + x) + 1];
		b = image_data[ n_channels * (y * width + x) + 2];

		if(n_channels == 4)
		{
			b = image_data[ n_channels * (y * width + x) + 3];
		}
	} // 3 or 4 channel

	else if(n_channels == 1) // monochrome
	{
		// Copy the single channel to each of rgb, should still come out gray. Set fully opaque.
		r = image_data[ n_channels * (y * width + x) + 0];
		g = image_data[ n_channels * (y * width + x) + 0];
		b = image_data[ n_channels * (y * width + x) + 0];
	}

	return (Color) {r, g, b, a};
} // _get_color_at_pixel

void mesh_texture_populate_image_datas(fastObjMesh *mesh)
{
	struct fastObjImageDatas im_data;
	unsigned int current_kd_map;

	im_data.number_of_images = mesh->texture_count;


	// Allocate memory for our list of structures.
	im_data.image_contents = (struct fastObjImageContent*) malloc(mesh->texture_count * sizeof(struct fastObjImageContent));

	for(int i=0; i<mesh->material_count; ++i)
	{
		current_kd_map = mesh->materials[i].map_Kd;
		if(current_kd_map != 0)
		{
			im_data.image_contents[current_kd_map] = _read_image_to_image_content(mesh->textures[current_kd_map].path);
		}
		else
		{
			// TODO: Handle
		}
	}


	if(mesh->texture_count == 0)
	{
		fprintf(stderr, "mesh_texture: WARN, mesh texture count is zero.");
		return; 
	}



	for(int i=0; i<im_data.number_of_images; ++i)
	{
	}
	
	mesh->image_datas = im_data;
	return;
}


 
void mesh_texture_set_colors(fastObjMesh *mesh)
{
	unsigned int which_material; 
	char *texture_path; 
	Color color;
	unsigned int current_kd_map;
	float u, v;


	for(int i=0; (3 * i) < mesh->index_count; ++i)
	{
		which_material = mesh->face_materials[i];

		// Get the raw texcoords
		u = mesh->texcoords[2 * mesh->indices[3 * i].t];
		v = mesh->texcoords[(2 * mesh->indices[3 * i].t) + 1];

		// normalize them
		u = _normalize_coordinate(u);
		v = _normalize_coordinate(v);


		current_kd_map = mesh->materials[mesh->face_materials[i]].map_Kd;
		if(current_kd_map != 0)
		{
			struct fastObjImageContent *image_content = &mesh->image_datas.image_contents[current_kd_map];

			// Now grab and set the color
			color = _get_color_at_pixel(*image_content, u, v);

		}
		else{
			// Default will be pink.
			color = PINK;
		}


		// Get the pointer to the correct fastObjImageContent (for organization)
		mesh->face_colors[i] = color; 
		++ mesh->face_color_count;
	}
} // mesh_texture_set_colors

