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
	t_data	img;
	int		exit;
	int		x;
	int		y;
	int		size;		
}t_vars;

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

void	draw_square(t_data img, int x, int y, int size, int color)
{
	int	i;

	i = 0;
	while (x + i < x + size)
		cust_mlx_pixel_put(&img, x + i++, y, color);		
	i = 0;	
	while (y + i < y + size)
		cust_mlx_pixel_put(&img, x + size, y + i++, color);

	i = 0;
	while (x < x + size - i)
		cust_mlx_pixel_put(&img, x + size - i++, y + size, color);
	
	i = 0;
	while (y < y + size - i)
		cust_mlx_pixel_put(&img, x, y + size - i++, color);
	
}

int		key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{		
		close_win(vars);
		exit (0);
	}
	if (keycode == 65363)
	{	
		draw_square(vars->img, vars->x, vars->y, vars->size, 0x00000000);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);		
		vars->x += 10;		
	}
	if (keycode == 65362)
	{	
		draw_square(vars->img, vars->x, vars->y, vars->size, 0x00000000);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);		
		vars->y -= 10;		
	}
	if (keycode == 65364)
	{	
		draw_square(vars->img, vars->x, vars->y, vars->size, 0x00000000);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);		
		vars->y += 10;		
	}
	if (keycode == 65361)
	{	
		draw_square(vars->img, vars->x, vars->y, vars->size, 0x00000000);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);		
		vars->x -= 10;		
	}
	if (keycode == 65451)
	{	
		draw_square(vars->img, vars->x, vars->y, vars->size, 0x00000000);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);		
		vars->size += 20;		
	}
	if (keycode == 65453)
	{	
		draw_square(vars->img, vars->x, vars->y, vars->size, 0x00000000);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);		
		vars->size -= 20;		
	}
	draw_square(vars->img, vars->x, vars->y, vars->size, 0x00FFFF00);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);


	ft_printf("Key [%d] was pressed\n", keycode);
	return (0);
}



int	main(void)
{

	t_vars	vars;
	//void	*mlx;
	
	
	
	vars.exit = 0;
	vars.x = 200;
	vars.y = 200;
	vars.size = 50;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 600, "FCK THIS");
	//mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);
	
	vars.img.img = mlx_new_image(vars.mlx, 600,600);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	

	/*
	while (y < 10)
	{
		while (x < 20)
			draw_square(img, 5 + (50 * x++), 5 + (50 * y), 50, 0x00FFFF00);
		x = 0;	
		y++;
	}*/	
	mlx_key_hook(vars.win, key_hook, &vars);
	//mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	
	return (0);
}




/*	
	while (y < 200)
	{
		while (x < 1200)
		{			
			cust_mlx_pixel_put(&img, x, y, 0x00FF0000);
			
			x++;
			
		}
		x = 0;
		y++;
	}	
	
	while (y < 400)
	{
		while (x < 1200)
		{			
			cust_mlx_pixel_put(&img, x, y, 0xFFFFFFFF);
			x++;
			
		}
		x = 0;
		y++;
	}
	while (y < 600)
	{
		while (x < 1200)
		{			
			cust_mlx_pixel_put(&img, x, y, 0x00FF0000);
			x++;
			
		}
		x = 0;
		y++;
	}
*/
