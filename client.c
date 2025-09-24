/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:20:04 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/24 15:58:02 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	transmitter(pid_t pid, const char *message)
{
	int	i;

	i = 0;
	while (*message)
	{
		i = 0;
		while (i < 8)
		{
			if (*message & (0x01 << i))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			i++;
		}
		message++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3 || !arg1_checker(argv[1]))
	{
		ft_putstr_fd("Argument Error\n", STDOUT_FILENO);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || pid > PID_MAX)
		return (-1);
	transmitter(pid, argv[2]);
	return (0);
}
