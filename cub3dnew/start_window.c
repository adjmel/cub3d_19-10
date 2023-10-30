#include "cub3d.h"

float pi = 3.14159265358979323846;

int    drawPlayer(t_data *s);

float degToRad(int a) { return a*pi/180.0;}

int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

int closer(t_data *s)
{
    mlx_destroy_window(s->mlx, s->win);
    exit(0);
}

int	key_event(int button, t_data *s)
{
    (void)s;
	if (button == 65307)
		closer(s);
    // if (button == 65361) { s->parsing.player_direction+=5; s->parsing.player_direction=FixAng(s->parsing.player_direction); s->parsing.player_dx=cos(degToRad(s->parsing.player_direction)); s->parsing.player_dy=-sin(degToRad(s->parsing.player_direction));}
    // if (button == 65363) { s->parsing.player_direction-=5; s->parsing.player_direction=FixAng(s->parsing.player_direction); s->parsing.player_dx=cos(degToRad(s->parsing.player_direction)); s->parsing.player_dy=-sin(degToRad(s->parsing.player_direction));} 
    if (button == 65361) { s->parsing.player_direction -= 0.1 ; s->parsing.player_dx = cos(s->parsing.player_direction) * 5; s->parsing.player_dy = sin(s->parsing.player_direction) * 5;}
    if (button == 65363) { s->parsing.player_direction += 0.1 ; s->parsing.player_dx = cos(s->parsing.player_direction) * 5; s->parsing.player_dy = sin(s->parsing.player_direction) * 5;}
    if (button == 65362) { s->parsing.player_x += s->parsing.player_dx * 5; s->parsing.player_y += s->parsing.player_dy * 5;}
    if (button == 65364) { s->parsing.player_y -= s->parsing.player_dy * 5; s->parsing.player_x -= s->parsing.player_dx * 5;}
    drawPlayer(s);
    return (0);
}

int drawMap2d(t_data *s)
{
    int x = 0;
    int y = 0;
    int mapX = 8;
    int mapY = 8;
    int color;
    int xo;
    int yo;
    // mlx_clear_window(s->mlx, s->win);

    while(y < mapY)
    {
        while(x < mapX)
        {
            if(map[y*mapX+x]==1){ color = 0x288BA8;} else{ color = 0xFFFFFF;}
            xo = x * 64; yo = y * 64;
            while (xo < (x * 64) + 64)
            {
                while (yo < (y * 64) + 64)
                {
                    mlx_pixel_put(s->mlx, s->win, xo, yo, color);
                    yo++;
                }
                yo = y * 64;
                xo++;
            }
            x++;
        }
        x = 0;
        y++;
    }

    return (0);
}

int    drawPlayer(t_data *s)
{
    int i;
    int j;
    int x;
    int y;

    // mlx_clear_window(s->mlx, s->win);
    drawMap2d(s);
    i = 0;
    j = 0;
    x = s->parsing.player_x / 2;
    y = s->parsing.player_y / 2;
    while (i < 10)
    {
        while (j < 10)
        {
            mlx_pixel_put(s->mlx, s->win, x + i, y + j, 0x00FF0000);
            j++;
        }
        j = 0;
        i++;
    }

    i = 0;
    while (i < 30)
    {
        mlx_pixel_put(s->mlx, s->win, x + (s->parsing.player_dx * i), y + (s->parsing.player_dy * i), 0x00FF0000);
        i++;
    }
    
    
    return (0);
}

int init_window(t_data s)
{
    s.mlx = mlx_init();
    // printf("r x = %d\n r y =%d\n", s.parsing.r_value_x, s.parsing.r_value_y);
    mlx_get_screen_size(s.mlx, &s.parsing.r_value_x, &s.parsing.r_value_y);
    s.win= mlx_new_window(s.mlx, s.parsing.r_value_x, s.parsing.r_value_y, "cub3d");
    s.parsing.player_x = 100;
    s.parsing.player_y = 100;
    s.parsing.player_direction = 0;
    s.parsing.player_dx = cos(degToRad(s.parsing.player_direction));
    s.parsing.player_dy = sin(degToRad(s.parsing.player_direction));
    mlx_hook(s.win, 2, 1L << 0, key_event, &s);
	mlx_hook(s.win, 17, 0, closer, &s);
    drawPlayer(&s);
    // mlx_loop_hook(s.mlx, drawMap2d, &s);
    mlx_loop(s.mlx);
    return (0);
}