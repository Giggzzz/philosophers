/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:50:19 by gudias            #+#    #+#             */
/*   Updated: 2022/06/25 03:49:08 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_process(t_philo **philos)
{
	int			i;

	i = 0;
	while (philos[i])
	{
		philos[i]->pid = fork();
		if (philos[i]->pid == -1)
			return (0);
		if (philos[i]->pid == 0)
		{
			philo_routine(philos[i]);
			exit (1);
		}
		i++;
	}
	return (1);
}

void	wait_all_process(t_philo **philos)
{
	int	i;
	
	i = 0;
	while (philos[i])
	{
		waitpid(philos[i]->pid, NULL, 0);
		i++;
	}
}

void	kill_all_process(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		kill(philos[i]->pid, SIGTERM);
		i++;
	}
}
