/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:50:19 by gudias            #+#    #+#             */
/*   Updated: 2022/06/23 21:32:23 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_t	**create_threads(int nb, t_philo **philos)
{
	pthread_t	**threads;
	int			i;

	threads = malloc (sizeof (pthread_t *) * (nb + 1));
	if (!threads)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		threads[i] = malloc (sizeof (pthread_t));
		if (!threads[i])
		{
			free_threads(threads);
			return (NULL);
		}
		pthread_create(threads[i], NULL, &thread_philo_routine, philos[i]);
		i++;
	}
	threads[nb] = NULL;
	return (threads);
}

void	wait_all_threads(pthread_t **threads, pthread_t *thread_checker)
{
	int	i;

	i = 0;
	while (threads[i])
	{
		pthread_join(*(threads[i]), NULL);
		i++;
	}
	pthread_join(*thread_checker, NULL);
}
