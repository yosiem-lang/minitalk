#include "minitalk.h"

int	ft_atoi(const char *nptr)
{
	const char	*s;
	long		out;
	int			neg;

	s = nptr;
	out = 0;
	neg = 0;
	while (*s == '\t' || *s == '\n' || *s == '\v' || \
	*s == '\f' || *s == '\r' || *s == ' ')
		s++;
	if (*s == '-')
	{
		neg = 1;
		s++;
	}
	else if (*s == '+')
		s++;
	while ((*s >= '0' && *s <= '9') && *s != '\0')
	{
		out *= 10;
		out += *s++ - '0';
	}
	if (neg)
		return (-out);
	return (out);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
	{
		write (fd, "\0", 1);
		return ;
	}
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd ('-', fd);
		ft_putnbr_fd (-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd (n / 10, fd);
		ft_putnbr_fd (n % 10, fd);
	}
	else
	{
		ft_putchar_fd (n + '0', fd);
	}
}
