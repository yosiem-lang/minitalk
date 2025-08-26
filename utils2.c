#include "minitalk.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	arg1_checker(char *str)
{
	size_t	i;
	size_t	digit_i;

	i = 0;
	digit_i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			digit_i++;
		i++;
	}
	if (digit_i == ft_strlen(str))
		return (1);
	return (0);
}
