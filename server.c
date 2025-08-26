#include "minitalk.h"

void	receiver(int signo, siginfo_t *siginfo, void *oact)
{
	static int	bit_i;
	static char	received_char;

	(void) oact;
	(void) siginfo;
	if (!(signo == SIGUSR1 || signo == SIGUSR2))
		ft_putstr_fd("Signal error\n", STDOUT_FILENO);
	if (signo == SIGUSR1)
		received_char |= (0x01 << bit_i);
	if (bit_i == 7)
	{
		write(STDOUT_FILENO, &received_char, 1);
		bit_i = 0;
		received_char = 0x00;
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