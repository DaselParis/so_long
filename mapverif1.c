#include "so_long.h"

int ft_caravalide(char c)
{
    if (c == '0' || c == 'E' || c == 'P' || c == '1' || c == 'C')
        return (0);
    return (-1);
}

int    ft_check_wall1(t_struct *data)
{
    int i;

    i = 0;
    while (i < data->col - 1)
    {
        if(data->map[0][i] != '1')
            return (-1);
        i++;
    }
    i = 0;
    while (i < data->line)
    {
        if(data->map[i][0] != '1')
            return (-1);
        i++;
    }
    return (ft_check_wall2(data));
}

int ft_check_wall2(t_struct *data)
{
    int i;

    i = 0;
    while (i < data->col - 1)
    {
        if (data->map[data->line - 1][i] != '1')
            return (-1);
        i++;
    }
    i = 0;
    while (i < data->line)
    {
        if (data->map[i][data->col - 2] != '1')
            return (-1);
        i++;
    }
    return (0);
}

int ft_check_map(t_struct *data)
{
    int i;

    i = 0;
    data->exit = 0;
    data->item = 0;
    data->start = 0;
    while (i < data->line)
    {
        if (ft_check_elem(data, i) == -1)
            return (-1);
        i++;
    }
    if (data->exit > 1 || data->start > 1)
        return (ft_putstr("Error\nLa map contient des doublons!\n"), -1);
    if (data->exit == 0 || data->start == 0)
        return (ft_putstr("Error\nPas de sortie ou/et d'Entree\n"), -1);
    if (data->item < 1)
        return (ft_putstr("Error\nLa map ne contient pas de collectibles!\n"), -1);
    return (0);
}

