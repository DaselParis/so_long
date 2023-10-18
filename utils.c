#include "so_long.h"

int    ft_strlen(char *str)
{
    int    i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_putchar(char c)
{
    write (1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_putnbr(int nb)
{
	unsigned int	num;

	if (nb < 0)
	{
		num = -nb;
		ft_putchar('-');
	}
	else
		num = nb;
	if (num <= 9)
		ft_putchar(num + 48);
	else
	{
		ft_putnbr(num / 10);
		ft_putchar(num % 10 + 48);
	}
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i][0] != 0)
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}
