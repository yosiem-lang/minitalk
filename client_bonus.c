/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:19:27 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/24 15:58:12 by mkazuhik         ###   ########.fr       */
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

void	sig_handler(int signo, siginfo_t *siginfo, void *oact)
{
	static int	send_byte;

	(void) siginfo;
	(void) oact;
	if (signo == SIGUSR2)
	{
		ft_putstr_fd ("\rSend byte :", STDOUT_FILENO);
		ft_putnbr_fd (++send_byte, STDOUT_FILENO);
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	act;

	if (argc != 3 || !arg1_checker(argv[1]))
	{
		ft_putstr_fd("Argument Error\n", STDOUT_FILENO);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || pid > PID_MAX)
		return (-1);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigemptyset (&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	transmitter(pid, argv[2]);
	return (0);
}
