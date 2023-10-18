#include "so_long.h"

int	ft_textures(t_vars	*vars)
{
	vars->exit = mlx_xpm_file_to_image(vars->mlx, "./texture/exit.xpm",
			&vars->img_width, &vars->img_height);
	vars->floor = mlx_xpm_file_to_image(vars->mlx, "./texture/floor.xpm",
			&vars->img_width, &vars->img_height);
	vars->wall = mlx_xpm_file_to_image(vars->mlx, "./texture/wall.xpm",
			&vars->img_width, &vars->img_height);
	vars->player = mlx_xpm_file_to_image(vars->mlx, "./texture/player.xpm",
			&vars->img_width, &vars->img_height);
	vars->item1 = mlx_xpm_file_to_image(vars->mlx, "./texture/item1.xpm",
			&vars->img_width, &vars->img_height);
	vars->item2 = mlx_xpm_file_to_image(vars->mlx, "./texture/item2.xpm",
			&vars->img_width, &vars->img_height);
	vars->item3 = mlx_xpm_file_to_image(vars->mlx, "./texture/item3.xpm",
			&vars->img_width, &vars->img_height);
	vars->item4 = mlx_xpm_file_to_image(vars->mlx, "./texture/item4.xpm",
			&vars->img_width, &vars->img_height);
	if (vars->exit == NULL || vars->floor == NULL || vars->wall == NULL
		|| vars->player == NULL || vars->item1 == NULL || vars->item2 == NULL
		|| vars->item3 == NULL || vars->item4 == NULL)
		ft_close(vars);
	return (0);
}

void	ft_check_player(t_vars *vars)
{
	static int	item = 0;

	if (vars->data.map[vars->y][vars->x] == 'C')
	{
		item++;
		vars->data.map[vars->y][vars->x] = '0';
	}
	if (vars->data.map[vars->y][vars->x] == 'E')
	{
		if (item == vars->data.item)
		{
			ft_putstr("YIPIEEE c'est la fin\n");
			ft_close(vars);
		}
	}
}

int	ft_item(t_vars	*vars, int i, int j, int count)
{
	if (count > 3)
		count = 0;
	if (count == 0)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->item1, j * 64, i * 64);
	else if (count == 1)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->item2, j * 64, i * 64);
	else if (count == 2)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->item3, j * 64, i * 64);
	else
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->item4, j * 64, i * 64);
	return (count + 1);
}

void	ft_draw(t_vars *vars, int i, int j, int a)
{
	if (a == 0)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->wall, j * 64, i * 64);
	else if (a == 1)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->exit, j * 64, i * 64);
	else
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->floor, j * 64, i * 64);
}

void	ft_map(t_struct *data, t_vars *vars)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (++i < data->line)
	{
		j = -1;
		while (++j < data->col - 1)
		{
			if (data->map[i][j] == '1')
				ft_draw(vars, i, j, 0);
			else if (data->map[i][j] == 'E')
				ft_draw(vars, i, j, 1);
			else if (data->map[i][j] == 'C')
			{
				count = ft_item(vars, i, j, count);
			}
			else
				ft_draw(vars, i, j, 2);
		}
	}
}
