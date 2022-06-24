/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:36 by gudias            #+#    #+#             */
/*   Updated: 2022/06/24 19:01:38 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philos(t_philo **philos)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (philos[i])
	{
		pthread_mutex_destroy(&(philos[i]->last_meal_lock));
		free(philos[i]);
		philos[i] = NULL;
		i++;
	}
	free(philos);
	philos = NULL;
}

void	free_threads(pthread_t **threads)
{
	int	i;

	if (!threads)
		return ;
	i = 0;
	while (threads[i])
	{
		free(threads[i]);
		threads[i] = NULL;
		i++;
	}
	free(threads);
	threads = NULL;
}

void	free_forks_mutex(pthread_mutex_t **forks_mutex)
{
	int	i;

	if (!forks_mutex)
		return ;
	i = 0;
	while (forks_mutex[i])
	{
		pthread_mutex_destroy(forks_mutex[i]);
		free (forks_mutex[i]);
		forks_mutex[i] = NULL;
		i++;
	}
	free(forks_mutex);
	forks_mutex = NULL;
}

void	free_all(pthread_mutex_t **frks, pthread_t **thrds, t_philo **phls)
{
	free_philos(phls);
	free_threads(thrds);
	free_forks_mutex(frks);
}

int	err_msg(char *str)
{
	printf("Error: %s\n", str);
	return (1);
}
