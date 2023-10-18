#include "so_long.h"


int	ft_remplissage(char *str, t_struct *data)
{
	int	i;
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	data->map = malloc(sizeof(char *) * (data->line + 1));
	if (data->map == NULL)
		return (close(fd), -1);
	while (i < data->line)
	{
		data->map[i] = malloc(sizeof(char) * (data->col + 1));
		if (data->map[i] == NULL)
			return (close(fd), -1);
		read(fd, data->map[i], data->col + 1);
		data->map[i][data->col - 1] = '\0';
		i++;
	}
	data->map[i] = malloc(sizeof(char) * (data->line));
	if (data->map[i] == NULL)
		return (close(fd), -1);
	data->map[i][0] = '\0';
	return (close(fd), 0);
}

int	ft_size_line(char *str, t_struct *data)
{
	int		fd;
	char	buffer[1];
	int		colcount;

	data->line = 1;
	colcount = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (read(fd, buffer, 1) != 0)
	{
		colcount++;
		if (buffer[0] == '\n')
		{
			if (colcount != data->col + 1)
				return (data->line = -1, close(fd), -1);
			colcount = 0;
			data->line++;
		}
	}
	if (buffer[0] == '\n')
		data->line--;
	return (close(fd), data->line);
}

int	ft_size_col(char *str, t_struct *data)
{
	int		fd;
	char	buffer[1];
	int		byte;

	buffer[0] = 0;
	data->col = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (buffer[0] != '\n')
	{
		byte = read(fd, buffer, 1);
		if (byte == -1)
			return (close(fd), -1);
		if (buffer[0] == '\n')
			break ;
		data->col++;
	}
	return (close(fd), data->col);
}


int	ft_verifichier(char *str)
{
	int			fd;
	int			i;
	int			j;
	static char	ber[4] = ".ber";

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	i = ft_strlen(str);
	if (i < 4)
		return (-1);
	i = i - 4;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ber[j])
			return (-1);
		i++;
		j++;
	}
	return (0);
}

int	ft_verif2(t_struct *data)
{
	t_case	cell;

	cell.line = data->pos_line;
	cell.col = data->pos_col;
	cell.direction = 0;
	data->sortietrouve = 0;
	data->itemscount = 0;
	ft_check_chemin(data, cell);
	if (data->sortietrouve != 1 || data->itemscount != data->item)
		return (-1);
	ft_free(data->map);
	return (0);
}

int	ft_verif(char **av, t_struct *data)
{
	if (ft_verifichier(av[1]) == -1)
		return (ft_putstr("Error\nLe fichier n'est pas valide\n"), -1);
	ft_size_col(av[1], data);
	ft_size_line(av[1], data);
	if (data->col < 3 || data->line < 3)
		return (ft_putstr("Error\nLa map est trop petite ou grande\n"), -1);
	if (ft_remplissage(av[1], data) == -1)
		return (ft_putstr("Error\nProbleme de malloc OU pas reussi a OPEN!\n")
			, -1);
	if (ft_check_wall1(data) == -1)
		return (ft_putstr("Error\nMur pas valide\n"), ft_free(data->map), -1);
	if (ft_check_map(data) == -1)
		return (ft_putstr("ERROR\n,Map pas bonne\n"), ft_free(data->map), -1);
	if (ft_verif2(data) == -1)
		return (ft_free(data->map), ft_putstr("Error\nPas de chemin valide\n")
			, -1);
	return (0);
}
