#include "so_long.h"

int	ft_close2(t_vars *vars)
{
	if (vars->mlx != NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (vars->data.map != NULL)
		ft_free(vars->data.map);
	exit (0);
	return (0);
}

int	ft_close(t_vars *vars)
{
	if (vars->exit != NULL)
		mlx_destroy_image(vars->mlx, vars->exit);
	if (vars->player != NULL)
		mlx_destroy_image(vars->mlx, vars->player);
	if (vars->wall != NULL)
		mlx_destroy_image(vars->mlx, vars->wall);
	if (vars->floor != NULL)
		mlx_destroy_image(vars->mlx, vars->floor);
	if (vars->item1 != NULL)
		mlx_destroy_image(vars->mlx, vars->item1);
	if (vars->item2 != NULL)
		mlx_destroy_image(vars->mlx, vars->item2);
	if (vars->item3 != NULL)
		mlx_destroy_image(vars->mlx, vars->item3);
	if (vars->item4 != NULL)
		mlx_destroy_image(vars->mlx, vars->item4);
	if (vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	return (ft_close2(vars), 0);
}

void	ft_input2(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		ft_close(vars);
	else if (keycode == 119 && vars->data.map[vars->y - 1][vars->x] != '1')
	{
		vars->y = vars->y - 1;
		vars->mov_count++;
	}
	else if (keycode == 115 && vars->data.map[vars->y + 1][vars->x] != '1')
	{
		vars->y = vars->y + 1;
		vars->mov_count++;
	}
	else if (keycode == 97 && vars->data.map[vars->y][vars->x - 1] != '1')
	{
		vars->x = vars->x - 1;
		vars->mov_count++;
	}
	else if (keycode == 100 && vars->data.map[vars->y][vars->x + 1] != '1')
	{
		vars->x = vars->x + 1;
		vars->mov_count++;
	}
}

int	ft_input(int keycode, t_vars *vars)
{
	int	xx;
	int	yy;

	xx = vars->x;
	yy = vars->y;
	ft_input2(keycode, vars);
	if (vars->x != xx || vars->y != yy)
	{
		ft_check_player(vars);
		ft_map(&vars->data, vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player,
			vars->x * 64, vars->y * 64);
		ft_putstr("nombre de deplacements: ");
		ft_putnbr(vars->mov_count);
		ft_putchar('\n');
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_struct	data;
	t_vars		vars;

	if (ac != 2)
		return (0);
	if (ft_verif(av, &data) == -1)
		return (-1);
	vars.x = data.pos_col;
	vars.y = data.pos_line;
	vars.mov_count = 0;
	ft_remplissage(av[1], &data);
	vars.data = data;
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (ft_free(vars.data.map), 0);
	vars.win = mlx_new_window(vars.mlx, (data.col - 1) * 64, (data.line) * 64,
			"SO_LONG");
	ft_textures(&vars);
	ft_map(&data, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.player,
		vars.x * 64, vars.y * 64);
	mlx_hook(vars.win, 2, 1L<<0, ft_input, &vars);
	mlx_hook(vars.win, 17, 0, ft_close, &vars);
	mlx_loop(vars.mlx);
}
