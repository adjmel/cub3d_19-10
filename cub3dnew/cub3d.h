#ifndef CUB3D_H

# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx_linux/mlx_int.h"
# include "mlx_linux/mlx.h"
# include <fcntl.h>
# include <string.h>
# include <X11/Xlib.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

#define MAX_LINE_LENGTH 204//1024 // longueur maximale d'une ligne (a ajuster mais les lignes sont courtes donc ca va)
#define MAX_MAP_SIZE_X 24 // Ajustez selon besoin
#define MAX_MAP_SIZE_Y 24

typedef struct s_parsing
{
	/*texte du fichier .cub*/
	char **text_file;

	/*valeurs rgb du sol et plafond*/
	int floor_value_1;
	int floor_value_2;
	int floor_value_3;
	int sky_value_1;
	int sky_value_2;
	int sky_value_3;

	/*valeurs pour la resolution*/
	int r_value_x;
	int r_value_y;

	/*valeurs pour les textures*/
	char *no_texture_value;
    char *so_texture_value;
    char *we_texture_value;
    char *ea_texture_value;
    char *s_texture_value;

	/*map*/
	char **map;
	char **copied_map;
	int map_height;

	/*position x et y du player*/
	//int

	/*distances horizontale et verticale*/
	//float;

	/*direction dans laquelle il regarde en radiant*/
	//float;

}			t_parsing;


typedef struct s_data
{
	t_parsing   parsing;
	//char **text_file;

}			t_data;

/*enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_BUTTONPRESS = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};*/

/*PARSING*/
int check_no_wall();
int map_closed();
int map_less_3_lines();
int check_nbr_player();
int correct_number(char **text_file);

void    init_textures(t_parsing *parsing);
int parsing(char *file_cub3d_name);
int parsing_rgbs();
int parsing_resolution();
int parsing_textures();
int check_map_prefixes();
int parsing_cub3d(char **text_file, t_parsing *parsing);
int put_text_struct();
int put_map_in_struct(t_parsing *parsing);

/*EXECUTION*/


#endif