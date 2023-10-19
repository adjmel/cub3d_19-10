#include "cub3d.h"

void	clean_exit(int exit_code, t_data *vars)
{
	if (!vars)
		exit(exit_code);
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars->mlx_win && vars->mlx)
		mlx_destroy_window(vars->mlx, vars->mlx_win);
	if (vars->mlx)
	{
		mlx_loop_end(vars->mlx);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	free(vars);
	exit(EXIT_SUCCESS);
}

int	mouse_click(t_data *vars)
{
	clean_exit(1, vars);
	exit(1);
}

int	close_win(int keycode, t_data *vars)
{
	if (keycode == 65307)
	{
		clean_exit(1, vars);
		exit(1);
	}
	return (0);
}

t_data	*init_window(void)
{
	t_data	*vars;
	int col = 0;

	vars = (t_data *)malloc(sizeof(t_data));
	if (!vars)
		exit(1);
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		free(vars);
		exit(1);
	}
	vars->mlx_win = mlx_new_window(vars->mlx, 800, 600, "Cub3d");
	vars->img = mlx_new_image(vars->mlx, 800, 600);
	
	while (col < WINDOW_WIDTH)
	{
		double wall_distance = 10.0; // Exemple : distance arbitraire de 10 unités mais utiliser le raycasting pour caclculer la bonne taille des murs
		int wall_height = (int)(WINDOW_HEIGHT / wall_distance);
		int row = 0;
		while (row < WINDOW_HEIGHT)
		{
			int color;
			if (row < WINDOW_HEIGHT / 2 - wall_height / 2)
			{
				color = 0x0000FF; // Couleur du sol
			}
			else if (row < WINDOW_HEIGHT / 2 + wall_height / 2)
			{
				color = 0x9B9CBC; // Couleur du mur
			}
			else
			{
				color = 0x37C719; // Couleur du plafond
			}
			mlx_pixel_put(vars->mlx, vars->mlx_win, col, row, color);
			
			row++;
		}
		col++;
	}
	if (!vars->mlx_win || !vars->img)
		clean_exit(1, vars);
	return (vars);
}


void	set_init()
{
	t_data	*vars;

	vars = init_window();
	//set_values_julia(av, vars);
	mlx_hook(vars->mlx_win, 2, 1L << 0, close_win, vars);
	mlx_hook(vars->mlx_win, 17, 0L, mouse_click, vars);
	//mlx_mouse_hook(vars->mlx_win, mouse_hook_julia, vars);
	//draw_fractal_julia(50, vars);
	mlx_loop(vars->mlx);
}
