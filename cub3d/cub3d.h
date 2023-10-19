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

#define MAX_LINE_LENGTH 1024 // longueur maximale d'une ligne (a ajuster mais les lignes sont courtes donc ca va)
#define MAX_MAP_SIZE_X 24 // Ajustez selon besoins
#define MAX_MAP_SIZE_Y 24

typedef struct s_data //strucure de mon acien fractol
{
	void		*img;
	char		*addr;
	int			color;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	double		tmp;
	long double	c_r;
	long double	c_i;

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

int open_file_cub(int ac, char **av);

/*EXECUTION*/

t_data		*init_window(void);
void		set_init();
int			close_win(int keycode, t_data *vars);
int			mouse_click(t_data *vars);

#endif