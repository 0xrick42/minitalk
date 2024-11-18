/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:37:35 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/18 20:37:36 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	handle_signal(int signal)
{
	static int	bit_count;
	static int	current_char;

	if (signal == SIGUSR1)
		current_char |= (0x01 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		ft_printf("%c", current_char);
		bit_count = 0;
		current_char = 0;
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: Server takes no arguments\n");
		return (1);
	}
	server_pid = getpid();
	ft_printf("Server PID: %d\n", server_pid);
	while (1)
	{
		signal(SIGUSR1, handle_signal);
		signal(SIGUSR2, handle_signal);
		pause();
	}
	return (0);
}
