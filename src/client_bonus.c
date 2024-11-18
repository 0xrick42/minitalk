/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:37:21 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/18 20:37:23 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_bonus.h"

void	handle_confirmation(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("Message received successfully!\n");
}

static int	ft_atoi(const char *str)
{
	int					index;
	int					sign;
	unsigned long int	number;

	index = 0;
	sign = 1;
	number = 0;
	while (str[index] == 32 || (str[index] >= 9 && str[index] <= 13))
		index++;
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	else if (str[index] == '+')
		index++;
	while (str[index] >= '0' && str[index] <= '9')
	{
		number = number * 10 + (str[index] - '0');
		index++;
	}
	return (number * sign);
}

void	send_char(int server_pid, char character)
{
	int	bit_position;

	bit_position = 0;
	while (bit_position < 8)
	{
		if ((character & (0x01 << bit_position)))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(500);
		bit_position++;
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;
	int	message_index;

	if (argc != 3)
	{
		ft_printf("Error: Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR2, handle_confirmation);
	message_index = 0;
	while (argv[2][message_index] != '\0')
	{
		send_char(server_pid, argv[2][message_index]);
		message_index++;
	}
	send_char(server_pid, '\0');
	pause();
	return (0);
}
