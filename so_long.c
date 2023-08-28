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
	int		**map;
	int		x;
	int		y;
	int		moves;
	int		collect;
	int		exit;
	int		player;		
}t_vars;

typedef	struct s_map
{
	int		**map;	
}t_map;


int	close_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

void	cust_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int		key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{		
		close_win(vars);
		exit (0);
	}
	//ft_printf("Player position before move [%d][%d], value of array = %d \n", vars->x, vars->y,vars->map[vars->y][vars->x]);
	
	if (keycode == 65363)
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
	if (keycode == 65362)
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
	if (keycode == 65364)
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
	if (keycode == 65361)
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

	if (((vars->map)[vars->y][vars->x]) == 3)
				vars->collect--;
	if (vars->map[vars->y][vars->x] == 4 && vars->collect == 0)
	{
		ft_printf("YOU WON THE GAME - CONGRATULATIONS\n");
		close_win(vars);
		exit (0);
	}
	if (vars->map[vars->y][vars->x] == 4)
		ft_printf("YOU NEED TO COLLECT ALL COLLECTIBLES BEFORE HEADING TO EXIT - %d COLLECTIBLES REMAINING\n", vars->collect);
	else
		vars->map[vars->y][vars->x] = 2;	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_pl.img,vars->x*32,vars->y*32);
	//ft_printf("Player position after move [%d][%d] value of array = %d\n", vars->x, vars->y,vars->map[vars->y][vars->x]);
	ft_printf("Count of collectibles = [%d]\n", vars->collect);
	ft_printf("Count of moves = [%d]\n\n", vars->moves);
	//ft_printf("Key [%d] was pressed\n\n", keycode);
	
	/*int	i = 0;
	int j = 0;

	while (j < 5)
	{
		while (i < 13)
		{
			ft_printf("%d", vars->map[j][i]);			
			i++;
		}
		ft_printf("\n");
		i = 0;
		j++;
	}*/
	return (0);
}



int	main(void)
{

	t_vars	vars;
	
	char	*path0 = "./graphic/00_ground.xpm";
	char	*path1 = "./graphic/01_wall.xpm";
	char	*path2 = "./graphic/02_player.xpm";
	char	*path3 = "./graphic/03_collect.xpm";
	char	*path4 = "./graphic/04_exit.xpm";
	char	*mappath = "./maps/map9.ber";
	int		width;
	int		height;
	size_t	line_cnt;
	size_t	str_cnt;
	size_t	lgnth;

	line_cnt = 0;
	lgnth = 0;

	vars.moves = 0;
	vars.collect = 0;
	vars.exit = 0;
	vars.player = 0;

	char	*toprint;
	char 	*toprint2;
	
	
	int fd = open(mappath, O_RDONLY | O_CREAT);
		
	while ((toprint = get_next_line(fd)) != NULL )
	{
		line_cnt++;		
		lgnth = ft_strlen(toprint) - 1;
		free(toprint);
	}


	close(fd);
	free(toprint);
	vars.map = malloc(sizeof(int **) * line_cnt);
	line_cnt = 0;
	str_cnt = 0;
	int fd2 = open(mappath, O_RDONLY | O_CREAT);
	while ((toprint2 = get_next_line(fd2)) != NULL )
	{		
		vars.map[line_cnt] = malloc(sizeof(int *) * lgnth);
		while (str_cnt < lgnth)
		{			
			if (toprint2[str_cnt] == '0')
				vars.map[line_cnt][str_cnt] = 0;
			if (toprint2[str_cnt] == '1')
				vars.map[line_cnt][str_cnt] = 1;
			if (toprint2[str_cnt] == 'P')
			{
				vars.map[line_cnt][str_cnt] = 2;
				vars.player++;
			}
			if (toprint2[str_cnt] == 'C')
			{				
				vars.map[line_cnt][str_cnt] = 3;
				vars.collect++;
			}
			if (toprint2[str_cnt] == 'E')
			{
				vars.map[line_cnt][str_cnt] = 4;			
				vars.exit++;
			}
			str_cnt++;			
		}
		free(toprint2);
		str_cnt = 0;
		line_cnt++;
	}	
	ft_printf("line count = %d\n", line_cnt);
	str_cnt = lgnth;
	ft_printf("str count = %d\n", str_cnt);
	ft_printf("%d\n", vars.map[2][0]);
	close(fd2);	
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 32*str_cnt, 32*line_cnt, "42_SO_LONG");
	vars.img_gr.img = mlx_xpm_file_to_image(vars.mlx, path0, &width, &height);
	vars.img_wa.img = mlx_xpm_file_to_image(vars.mlx, path1, &width, &height);
	vars.img_pl.img = mlx_xpm_file_to_image(vars.mlx, path2, &width, &height);
	vars.img_co.img = mlx_xpm_file_to_image(vars.mlx, path3, &width, &height);
	vars.img_ex.img = mlx_xpm_file_to_image(vars.mlx, path4, &width, &height);

	size_t i = 0;
	size_t j = 0;

	while (j < line_cnt)
	{
		while (i < str_cnt)
		{
			if (vars.map[j][i] == 0)	
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img_gr.img, i*32, j*32);
			if (vars.map[j][i] == 1)	
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img_wa.img, i*32, j*32);
			if (vars.map[j][i] == 2)	
			{
				vars.x = i;
				vars.y = j;
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img_pl.img, i*32, j*32);
				printf("Player starting position by map generation [%d][%d]\n\n", vars.x, vars.y);
			}
			if (vars.map[j][i] == 3)
			{				
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img_co.img, i*32, j*32);
			}
			if (vars.map[j][i] == 4)	
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img_ex.img, i*32, j*32);	
			i++;
		}
		i = 0;
		j++;
	}
	ft_printf("Count of collectibles = [%d]\n\n", vars.collect);	
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	
	return (0);
}