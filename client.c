/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ming <ming@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:14:26 by ming              #+#    #+#             */
/*   Updated: 2026/04/08 17:56:03 by ming             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	i = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n);
}

void	encoder(char c, int pid)
{
	int		i;
	int		shifted_char;

	i = 7;
	while (i >= 0)
	{
		shifted_char = (c >> i) & 1;
		if (shifted_char == 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(1800);
		i--;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	i = 0;
	if (ac != 3)
	{
		write(2, "Wrong format\n", 13);
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		write (2, "Wrong PID!\n", 11);
		return (1);
	}
	while (av[2][i] != '\0')
	{
		encoder(av[2][i], pid);
		i++;
	}
	encoder('\0', pid);
	return (0);
}
