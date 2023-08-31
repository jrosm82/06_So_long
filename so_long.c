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
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
	int		**map2;
	int		x;
	int		y;
	int		moves;
	int		collect;
	int		exit;
	int		player;
	char	*path0;
	char	*path1;
	char	*path2;
	char	*path3;
	char	*path4;
	char	*mappath;
	size_t	length;
	size_t	line_cnt;
	size_t	str_cnt;
	int		path_exists;
	int		same_coll;
	size_t	lngh;	
}t_vars;

void	free_var(t_vars *vars, size_t i)
{
	while (i < vars->line_cnt)
		free(vars->map[i++]);
	i = 0;
	while (i < vars->line_cnt)
		free(vars->map2[i++]);
}

int	close_win(t_vars *vars)
{
	if (vars->map[vars->y][vars->x] == 4 && vars->collect == 0)
	{
		ft_printf("\n// You won this game - CONGRATULATIONS \\\\\n");
		ft_printf("// So Long, and Thanks for All the Fish \\\\\n");
	}
	ft_printf("\nYou exit the game\n\n");
	mlx_destroy_window(vars->mlx, vars->win);
	free_var(vars, 0);
	exit (0);
}

void	move_right(t_vars *vars)
{
	if (((vars->map)[vars->y][(vars->x + 1)]) != 1)
	{
		if (((vars->map)[vars->y][(vars->x)]) != 4)
		{
			vars->map[vars->y][vars->x] = 0;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_gr.img, \
			(vars->x) * 32, (vars->y) * 32);
		}
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ex.img, \
			(vars->x) * 32, (vars->y) * 32);
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
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_gr.img, \
			(vars->x) * 32, (vars->y) * 32);
		}
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ex.img, \
			(vars->x) * 32, (vars->y) * 32);
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
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_gr.img, \
			(vars->x) * 32, (vars->y) * 32);
		}
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ex.img, \
			(vars->x) * 32, (vars->y) * 32);
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
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_gr.img, \
			(vars->x) * 32, (vars->y) * 32);
		}
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ex.img, \
			(vars->x) * 32, (vars->y) * 32);
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
		ft_printf("Collect all collectibles before heading to exit\n");
		ft_printf("Still [%d] of remaining collectibles\n", vars->collect);
	}
	else
		vars->map[vars->y][vars->x] = 2;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_pl.img, \
	vars->x * 32, vars->y * 32);
	ft_printf("Current moves count = [%d]\n", vars->moves);
	return (0);
}

void	vars_init(t_vars *vars, char *argv)
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
	vars->mappath = argv;
	vars->length = 0;
	vars->path_exists = 0;
	vars->same_coll = 0;
	vars->lngh = 0;
}

void	finish(char	*error)
{
	ft_printf("Error\n");
	ft_printf("%s\n", error);
	exit(0);
}

void	map_init2(t_vars *vars, char *toprint)
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

void	map_init(t_vars *vars, int fd, char *toprint, size_t lngh)
{
	toprint = get_next_line(fd);
	while ((toprint) != NULL )
	{
		vars->map[vars->line_cnt] = malloc(sizeof(int *) * lngh);
		while (vars->str_cnt < lngh)
		{
			map_init2(vars, toprint);
		}
		free(toprint);
		vars->str_cnt = 0;
		vars->line_cnt++;
		toprint = get_next_line(fd);
	}
	free(toprint);
}

void	peri_check(t_vars *vars)
{
	size_t	i;

	i = 0;
	while (i < vars->str_cnt)
		if (vars->map[0][i++] != 1)
			finish("Wall is not intact around perimeter\n");
	i = 0;
	while (i < vars->line_cnt)
		if (vars->map[i++][0] != 1)
			finish("Wall is not intact around perimeter\n");
	i = vars->str_cnt - 1;
	while (i > 0)
		if (vars->map[vars->line_cnt - 1][i--] != 1)
			finish("Wall is not intact around perimeter\n");
	i = vars->line_cnt - 1;
	while (i > 0)
		if (vars->map[i--][vars->str_cnt - 1] != 1)
			finish("Wall is not intact around perimeter\n");
}

void	copy_map(t_vars *vars, size_t i, size_t j)
{
	vars->map2 = malloc(sizeof(int **) * vars->line_cnt);
	while (i < vars->line_cnt)
	{
		vars->map2[i] = malloc(sizeof(int *) * vars->str_cnt);
		i++;
	}
	i = 0;
	while (j < vars->line_cnt)
	{
		while (i < vars->str_cnt)
		{
			vars->map2[j][i] = vars->map[j][i];
			i++;
		}
		i = 0;
		j++;
	}
}

void	fill_check(t_vars *vars, int line, int column)
{
	if (vars->map2[line][column] == 3)
		vars->same_coll++;
	if (vars->map2[line][column] == 4)
		vars->path_exists = 1;
	vars->map2[line][column] = 1;
	if (vars->map2[line + 1][column] != 1)
		fill_check(vars, line + 1, column);
	if (vars->map2[line - 1][column] != 1)
		fill_check(vars, line - 1, column);
	if (vars->map2[line][column + 1] != 1)
		fill_check(vars, line, column + 1);
	if (vars->map2[line][column - 1] != 1)
		fill_check(vars, line, column - 1);
}

void	map_check(t_vars *vars)
{
	if (vars->player != 1)
		finish("There must be one player starting position tile(P) in map\n");
	if (vars->exit != 1)
		finish("There must be one exit tile(E) in provided map\n");
	if (vars->collect < 1)
		finish("There must be at least one(C) collectible in map\n");
	peri_check(vars);
	copy_map(vars, 0, 0);
	fill_check(vars, vars->y, vars->x);
	if (vars->path_exists == 0 || vars->collect != vars->same_coll)
		finish("No valid path to exit or collectible to finish the game");
}

void	map_prerender(t_vars *vars)
{
	int	width;
	int	height;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 32 * vars->str_cnt, \
	32 * vars->line_cnt, "42_SO_LONG");
	vars->img_gr.img = mlx_xpm_file_to_image(vars->mlx, \
	vars->path0, &width, &height);
	vars->img_wa.img = mlx_xpm_file_to_image(vars->mlx, \
	vars->path1, &width, &height);
	vars->img_pl.img = mlx_xpm_file_to_image(vars->mlx, \
	vars->path2, &width, &height);
	vars->img_co.img = mlx_xpm_file_to_image(vars->mlx, \
	vars->path3, &width, &height);
	vars->img_ex.img = mlx_xpm_file_to_image(vars->mlx, \
	vars->path4, &width, &height);
}

void	fuck_norminette(t_vars *vars, size_t i, size_t j)
{
	if (vars->map[j][i] == 0)
		mlx_put_image_to_window(vars->mlx, \
		vars->win, vars->img_gr.img, i * 32, j * 32);
	if (vars->map[j][i] == 1)
		mlx_put_image_to_window(vars->mlx, \
		vars->win, vars->img_wa.img, i * 32, j * 32);
	if (vars->map[j][i] == 2)
	{
		vars->x = i;
		vars->y = j;
		mlx_put_image_to_window(vars->mlx, \
		vars->win, vars->img_pl.img, i * 32, j * 32);
	}
	if (vars->map[j][i] == 3)
		mlx_put_image_to_window(vars->mlx, \
		vars->win, vars->img_co.img, i * 32, j * 32);
	if (vars->map[j][i] == 4)
		mlx_put_image_to_window(vars->mlx, \
		vars->win, vars->img_ex.img, i * 32, j * 32);
	if (vars->map[j][i] == 5)
		finish("Not rectangular or unsupp. character in map\n");
}

void	map_render(t_vars *vars, size_t i, size_t j)
{
	while (j < vars->line_cnt)
	{
		while (i < vars->str_cnt)
		{
			fuck_norminette(vars, i, j);
			i++;
		}
		i = 0;
		j++;
	}
}

void	line_read(t_vars *vars, int fd)
{
	char	*toprint;

	if (fd < 0)
		finish("Bad filename");
	toprint = get_next_line(fd);
	while ((toprint) != NULL )
	{
		vars->lngh = ft_strlen(toprint) - 1;
		if (vars->length == 0)
			vars->length = vars->lngh;
		vars->line_cnt++;
		if (vars->length != vars->lngh)
			finish("Map is not rectangular\n");
		free(toprint);
		toprint = get_next_line(fd);
	}
	free(toprint);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	char	*toprint;
	int		fd;

	toprint = NULL;
	if (argc < 2)
		finish("No map filename specified");
	vars_init(&vars, argv[1]);
	fd = open(vars.mappath, O_RDONLY);
	line_read(&vars, fd);
	close(fd);
	vars.map = malloc(sizeof(int **) * vars.line_cnt);
	vars.line_cnt = 0;
	vars.str_cnt = 0;
	fd = open(vars.mappath, O_RDONLY);
	map_init(&vars, fd, toprint, vars.lngh);
	close(fd);
	vars.str_cnt = vars.lngh;
	map_prerender(&vars);
	map_render(&vars, 0, 0);
	map_check(&vars);
	mlx_hook(vars.win, 17, 1L << 17, close_win, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
