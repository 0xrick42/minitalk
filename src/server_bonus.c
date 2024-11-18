/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:37:29 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/18 20:37:31 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_bonus.h"

void	handle_signal(int signal, siginfo_t *client_info, void *context)
{
	static int	bit_count;
	static int	current_char;

	(void)context;
	if (signal == SIGUSR1)
		current_char |= (0x01 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == 0)
		{
			kill(client_info->si_pid, SIGUSR2);
			ft_printf("\n");
		}
		else
		{
			ft_printf("%c", current_char);
		}
		bit_count = 0;
		current_char = 0;
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	signal_handler;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: Server takes no arguments\n");
		return (1);
	}
	server_pid = getpid();
	ft_printf("Server PID: %d\n", server_pid);
	ft_printf("Waiting for messages...\n");
	signal_handler.sa_sigaction = handle_signal;
	signal_handler.sa_flags = SA_SIGINFO;
	sigemptyset(&signal_handler.sa_mask);
	sigaction(SIGUSR1, &signal_handler, NULL);
	sigaction(SIGUSR2, &signal_handler, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
