/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:36 by gudias            #+#    #+#             */
/*   Updated: 2022/06/10 16:39:52 by gudias           ###   ########.fr       */
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

void	free_all(pthread_mutex_t **forks_mutex, pthread_t **threads, t_philo **philos)
{
	free_philos(philos);
	free_threads(threads);
	free_forks_mutex(forks_mutex);
}

void	exit_error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}
