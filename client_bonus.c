/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvictor- <jvictor-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 01:17:29 by jvictor-          #+#    #+#             */
/*   Updated: 2022/04/17 03:48:33 by jvictor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_bit_send;

void	confirm_handler(int sig)
{
	if (sig == SIGUSR2)
		g_bit_send = 1;
	else
		write(1, "\nMESSAGE SENT SUCESSFULLY\n\n", 28);
	(void)sig;
}

void	send_signal(int bit, int pid)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			write(1, "Problem sending the signal!\n", 29);
			exit(1);
		}
	}
	if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			write(1, "Problem sending the signal!\n", 29);
			exit(1);
		}
	}
	while (g_bit_send == 0)
		;
	g_bit_send = 0;
}

void	convert(int c, int pid)
{
	t_byte_struct	byte_char;

	*(unsigned char *)&byte_char = (unsigned char)c;
	send_signal(byte_char.b1, pid);
	send_signal(byte_char.b2, pid);
	send_signal(byte_char.b3, pid);
	send_signal(byte_char.b4, pid);
	send_signal(byte_char.b5, pid);
	send_signal(byte_char.b6, pid);
	send_signal(byte_char.b7, pid);
	send_signal(byte_char.b8, pid);
}

void	send_zero(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		send_signal(0, pid);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int					i;
	int					pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_usage();
		exit(1);
	}
	pid = ft_atoi(*(argv + 1));
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = confirm_handler;
	if (sigaction(SIGUSR2, &sa, NULL))
		exit(1);
	if (sigaction(SIGUSR1, &sa, NULL))
		exit(1);
	i = 0;
	while (argv[2][i])
	{
		convert((int)argv[2][i], pid);
		i++;
	}
	send_zero(pid);
	return (0);
}
