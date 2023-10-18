#include "so_long.h"

int	ft_c_iswall(char c)
{
	if (c == '1')
		return (0);
	return (-1);
}

char	ft_check_case(t_struct *data, t_case cell)
{
	char	c;

	c = '1';
	if (cell.direction == 0)
		c = data->map[cell.line - 1][cell.col];
	else if (cell.direction == 1)
		c = data->map[cell.line][cell.col + 1];
	else if (cell.direction == 2)
		c = data->map[cell.line + 1][cell.col];
	else if (cell.direction == 3)
		c = data->map[cell.line][cell.col - 1];
	else
		ft_putstr("WARNING CHECK CASE > 3!\n");
	return (c);
}

t_case	ft_get_case(t_case cell)
{
	if (cell.direction == 0)
		cell.line -= 1;
	else if (cell.direction == 1)
		cell.col += 1;
	else if (cell.direction == 2)
		cell.line += 1;
	else if (cell.direction == 3)
		cell.col -= 1;
	else
		ft_putstr("WARNING GET CASE > 3!\n");
	cell.direction = 0;
	return (cell);
}

int ft_check_chemin(t_struct *data, t_case cell)
{
	while (cell.direction <= 3)
	{
		if (data->map[cell.line][cell.col] == 'E')
			data->sortietrouve++;
		else if (data->map[cell.line][cell.col] == 'C')
			data->itemscount++;
		data->map[cell.line][cell.col] = '1';
		if (ft_c_iswall(ft_check_case(data, cell)) == 0)
			cell.direction++;
		else
		{
			ft_check_chemin(data, ft_get_case(cell));
		}
	}
	if (cell.direction > 3)
	{
		cell.direction = 0;
		return (-1);
	}
	return (0);
}
