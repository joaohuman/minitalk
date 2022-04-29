/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvictor- <jvictor-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 04:02:02 by jvictor-          #+#    #+#             */
/*   Updated: 2022/04/29 20:49:03 by jvictor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	set_bit(t_byte_struct *c, int i, int bit)
{
	if (bit == 0)
		c->b1 = i;
	else if (bit == 1)
		c->b2 = i;
	else if (bit == 2)
		c->b3 = i;
	else if (bit == 3)
		c->b4 = i;
	else if (bit == 4)
		c->b5 = i;
	else if (bit == 5)
		c->b6 = i;
	else if (bit == 6)
		c->b7 = i;
	else if (bit == 7)
		c->b8 = i;
}

void	check_end_of_string(unsigned char *c, siginfo_t *info)
{
	if (*c == '\0')
	{
		write(1, "\n", 1);
		kill(info->si_pid, SIGUSR1);
	}
}

void	signal_handler(int num, siginfo_t *info, void *ctx)
{
	static t_byte_struct	c;
	static int				counter;

	if (num == SIGUSR1)
		set_bit(&c, 0, counter);
	else if (num == SIGUSR2)
		set_bit(&c, 1, counter);
	if (counter == 7)
	{
		counter = 0;
		write(1, (unsigned char *)&c, 1);
		check_end_of_string((unsigned char *)&c, info);
	}
	else
		counter++;
	if (kill(info->si_pid, SIGUSR2))
		exit (1);
	(void)ctx;
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			mask;

	ft_bzero(&sa, sizeof(struct sigaction));
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	sa.sa_mask = mask;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL))
		exit (1);
	if (sigaction(SIGUSR2, &sa, NULL))
		exit (1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
