#include "so_long.h"

int ft_check_elem(t_struct *data, int i)
{
    int j;

    j = 0;
    while (j < data->col - 1)
    {
        if (ft_caravalide(data->map[i][j]) == -1)
                return (-1);
        if (data->map[i][j] == 'E')
            data->exit++;
        if (data->map[i][j] == 'C')
            data->item++;
        if (data->map[i][j] == 'P')
        {
            data->pos_col = j;
            data->pos_line = i;
            data->start++;
        }
        j++;
    }
    return (0);
}

