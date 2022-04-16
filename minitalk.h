/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvictor- <jvictor-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:10:53 by jvictor-          #+#    #+#             */
/*   Updated: 2022/04/16 05:00:52 by jvictor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct byte
{
	unsigned char	b1:1;
	unsigned char	b2:1;
	unsigned char	b3:1;
	unsigned char	b4:1;
	unsigned char	b5:1;
	unsigned char	b6:1;
	unsigned char	b7:1;
	unsigned char	b8:1;
}	t_byte_struct;

void	set_bit(t_byte_struct *c, int i, int bit);
void	check_end_of_string(unsigned char *c);
void	signal_handler(int num, siginfo_t *info, void *ctx);
void	confirm_handler(int sig);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	send_signal(int bit, int pid);
void	convert(int c, int pid);
void	send_zero(int pid);
void	ft_putnbr_fd(int n, int fd);

#endif