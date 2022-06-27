/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:50:19 by gudias            #+#    #+#             */
/*   Updated: 2022/06/27 12:04:49 by gudias           ###   ########.fr       */
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
			return (1);
		if (philos[i]->pid == 0)
		{
			philo_routine(philos[i]);
			exit (0);
		}
		i++;
	}
	return (0);
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
