/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:07:04 by jrosmari          #+#    #+#             */
/*   Updated: 2023/08/15 17:29:24 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "so_long.h"
#include "get_next_line/get_next_line.h"
#include <stdlib.h>

typedef struct s_data{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}t_data;

typedef struct s_vars{
	void	*mlx;
	void	*win;
	t_data	img_gr;
	t_data	img_wa;
	t_data	img_pl;
	t_data	img_co;
	t_data	img_ex;
	int	**map;
	int	x;
	int	y;
	int	moves;
	int	collect;
	int	exit;
	int	player;
	char	*path0;
	char	*path1;
	char	*path2;
	char	*path3;
	char	*path4;
	size_t	length;
	size_t	line_cnt;
	size_t	str_cnt;			
}t_vars;

int	close_win(t_vars *vars)
{
	if (vars->map[vars->y][vars->x] == 4 && vars->collect == 0)
	{
		ft_printf("\n//** You won this game - CONGRATULATIONS **\\\\\n");
		ft_printf("//** So Long, and Thanks for All the Fish **\\\\\n");
	}
	mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
}

void	move_right(t_vars *vars)
{
	if (((vars->map)[vars->y][(vars->x + 1)]) != 1)
	{
		if (((vars->map)[vars->y][(vars->x)]) != 4)
		{
			vars->map[vars->y][vars->x] = 0;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_gr.img, (vars->x)*32, (vars->y)*32);
		}
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ex.img, (vars->x)*32, (vars->y)*32);				
		vars->x += 1;
		vars->moves++;
	}
}

void	move_up(t_vars *vars)
{
	if (((vars->map)[vars->y - 1][(vars->x)]) != 1)
	{
		if (((vars->map)[vars->y][(vars->x)]) != 4)
		{
			vars->map[vars->y][vars->x] = 0;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_gr.img, (vars->x)*32, (vars->y)*32);
		}
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ex.img, (vars->x)*32, (vars->y)*32);
		vars->y -= 1;
		vars->moves++; 
	}	
}

void	move_down(t_vars *vars)
{
	if (((vars->map)[vars->y + 1][(vars->x)]) != 1)
	{
		if (((vars->map)[vars->y][(vars->x)]) != 4)
		{
			vars->map[vars->y][vars->x] = 0;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_gr.img, (vars->x)*32, (vars->y)*32);
		}
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ex.img, (vars->x)*32, (vars->y)*32);				
		vars->y += 1;
		vars->moves++;
	}
}

void	move_left(t_vars *vars)
{
	if (((vars->map)[vars->y][(vars->x - 1)]) != 1)
	{
		if (((vars->map)[vars->y][(vars->x)]) != 4)
		{
			vars->map[vars->y][vars->x] = 0;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_gr.img, (vars->x)*32, (vars->y)*32);
		}
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ex.img, (vars->x)*32, (vars->y)*32);			
		vars->x -= 1;
		vars->moves++;
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_win(vars);
	if (keycode == 65363)
		move_right(vars);
	if (keycode == 65362)
		move_up(vars);
	if (keycode == 65364)
		move_down(vars);
	if (keycode == 65361)
		move_left(vars);	
	if (((vars->map)[vars->y][vars->x]) == 3)
		vars->collect--;
	if (vars->map[vars->y][vars->x] == 4 && vars->collect == 0)
		close_win(vars);
	if (vars->map[vars->y][vars->x] == 4)
	{
		ft_printf("Stop cheating - you must collect or collectibles before heading to exit\n");
		ft_printf("There is still [%d] of remaining collectibles\n", vars->collect);
	}
	else
		vars->map[vars->y][vars->x] = 2;	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_pl.img,vars->x*32,vars->y*32);
	ft_printf("Current moves count = [%d]\n", vars->moves);	
	return (0);
}

void	vars_init(t_vars *vars)
{
	vars->line_cnt = 0;
	vars->moves = 0;
	vars->collect = 0;
	vars->exit = 0;
	vars->player = 0;
	vars->path0 = "./graphic/00_ground.xpm";
	vars->path1 = "./graphic/01_wall.xpm";
	vars->path2 = "./graphic/02_player.xpm";
	vars->path3 = "./graphic/03_collect.xpm";
	vars->path4 = "./graphic/04_exit.xpm";
	vars->length = 0;
}

void	finish(char	*error)
{
	ft_printf("Error\n");
	ft_printf("%s", error);	
	exit(0);
}

void	map_init(t_vars *vars, int fd, char *toprint, size_t lngh)
{
	while ((toprint = get_next_line(fd)) != NULL )
	{		
		vars->map[vars->line_cnt] = malloc(sizeof(int *) * lngh);
		while (vars->str_cnt < lngh)
		{			
			if (toprint[vars->str_cnt] == '0')
				vars->map[vars->line_cnt][vars->str_cnt] = 0;
			else if (toprint[vars->str_cnt] == '1')
				vars->map[vars->line_cnt][vars->str_cnt] = 1;
			else if (toprint[vars->str_cnt] == 'P' && vars->player++ >= 0)
				vars->map[vars->line_cnt][vars->str_cnt] = 2;
			else if (toprint[vars->str_cnt] == 'C' && vars->collect++ >= 0)
				vars->map[vars->line_cnt][vars->str_cnt] = 3;
			else if (toprint[vars->str_cnt] == 'E' && vars->exit++ >= 0)
				vars->map[vars->line_cnt][vars->str_cnt] = 4;
			else
				vars->map[vars->line_cnt][vars->str_cnt] = 5;			
			vars->str_cnt++;			
		}
		free(toprint);
		vars->str_cnt = 0;
		vars->line_cnt++;
	}
}

void	map_check(t_vars *vars)
{
	//int	i;
	//int	length;
	//int	line_cnt;

	//length = vars->str_cnt;
	//line_cnt = vars->line_cnt;
	//i = 0;
	if (vars->player != 1)
		finish("There can be only one player starting position in map\n");
	if (vars->exit != 1)
		finish("There can be only one exit in map\n");
	if (vars->collect < 1)
		finish("There must be at least one collectible\n");
	/*while (vars->map[0][i] < length)
	{
		ft_printf("%d", vars->map[0][i]);
		if (vars->map[0][i] != 1)
		{	
			
			finish("Wall is not intact around perimeter\n");
			
		}
		i++;
	}*/
}

void	map_prerender(t_vars *vars)
{
	int	width;
	int	height;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 32*vars->str_cnt, 32*vars->line_cnt, "42_SO_LONG");
	vars->img_gr.img = mlx_xpm_file_to_image(vars->mlx, vars->path0, &width, &height);
	vars->img_wa.img = mlx_xpm_file_to_image(vars->mlx, vars->path1, &width, &height);
	vars->img_pl.img = mlx_xpm_file_to_image(vars->mlx, vars->path2, &width, &height);
	vars->img_co.img = mlx_xpm_file_to_image(vars->mlx, vars->path3, &width, &height);
	vars->img_ex.img = mlx_xpm_file_to_image(vars->mlx, vars->path4, &width, &height);
}

void	map_render(t_vars *vars, size_t i, size_t j)
{
	while (j < vars->line_cnt)
	{
		while (i < vars->str_cnt)
		{
			if (vars->map[j][i] == 0)	
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img_gr.img, i*32, j*32);
			if (vars->map[j][i] == 1)	
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img_wa.img, i*32, j*32);
			if (vars->map[j][i] == 2)	
			{
				vars->x = i;
				vars->y = j;
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img_pl.img, i*32, j*32);
			}
			if (vars->map[j][i] == 3)	
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img_co.img, i*32, j*32);
			if (vars->map[j][i] == 4)	
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ex.img, i*32, j*32);
			if (vars->map[j][i] == 5)
				finish("Map is not rectangular or unsupported character in map\n");		
			i++;
		}
		i = 0;
		j++;
	}
}

int	main(void)
{
	t_vars	vars;
	char	*mappath = "./maps/map0.ber";	
	size_t	lngh;
	char	*toprint;
	int	fd;

	vars_init(&vars);
	lngh = 0;	
	fd = open(mappath, O_RDONLY | O_CREAT);		
	while ((toprint = get_next_line(fd)) != NULL )
	{
		lngh = ft_strlen(toprint) - 1;
		ft_printf("Line - %d\n", lngh);
		if (vars.length == 0)
			vars.length = lngh;				
		vars.line_cnt++;		
		if (vars.length != lngh)
			finish("Map is not rectangular\n");
		free(toprint);
	}
	close(fd);
	free(toprint);	
	vars.map = malloc(sizeof(int **) * vars.line_cnt);
	vars.line_cnt = 0;	
	vars.str_cnt = 0;	
	fd = open(mappath, O_RDONLY | O_CREAT);
	map_init(&vars, fd, toprint, lngh);			
	close(fd);
	vars.str_cnt = lngh;
	map_check(&vars);
	map_prerender(&vars);
	map_render(&vars, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);	
	return (0);
}