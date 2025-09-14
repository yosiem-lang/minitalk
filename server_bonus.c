/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:20:19 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/08/06 18:20:47 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receiver(int signo, siginfo_t *siginfo, void *oact)
{
	static int		bit_i;
	static char		received_char;
	static pid_t	client_pid;

	(void) oact;
	if (!client_pid || client_pid != siginfo->si_pid)
		client_pid = siginfo->si_pid;
	if (signo == SIGUSR1)
		received_char |= (0x01 << bit_i);
	if (bit_i == 7)
	{
		write(STDOUT_FILENO, &received_char, 1);
		bit_i = 0;
		received_char = 0x00;
		kill(client_pid, SIGUSR2);
	}
	else
	{
		bit_i++;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	act;

	pid = getpid();
	ft_putstr_fd("[PID] ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	act.sa_sigaction = receiver;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
