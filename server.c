/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ming <ming@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:14:22 by ming              #+#    #+#             */
/*   Updated: 2026/04/08 17:35:11 by ming             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

void	ft_putnbr_fd(int n, int fd)
{
	int		a;
	int		b;
	char	d;

	a = n % 10;
	b = n / 10;
	if (n < 0)
	{
		write(fd, "-", 1);
		a = -a;
		b = -b;
	}
	if (b > 9)
		ft_putnbr_fd(b, fd);
	else if (b <= 9 && b > 0)
	{
		b = b + '0';
		write(fd, &b, 1);
	}
	d = a + '0';
	write(fd, &d, 1);
}

void	receive(int sig)
{
	static int	bit;
	static char	current_c;

	if (sig == SIGUSR2)
		current_c = (current_c << 1) | 1;
	else if (sig == SIGUSR1)
		current_c = (current_c << 1);
	bit++;
	if (bit == 8)
	{
		write(1, &current_c, 1);
		if (current_c == '\0')
			write (1, "\n", 1);
		bit = 0;
		current_c = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	signal(SIGUSR1, receive);
	signal(SIGUSR2, receive);
	while (1)
		pause();
	return (0);
}
