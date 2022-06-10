/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:50:19 by gudias            #+#    #+#             */
/*   Updated: 2022/06/10 19:38:59 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thread_philo_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	//printf("[%d] %d arrives and wait for fork\n", get_current_time(), philo->id);
	

	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(philo->fork2);

	printf("[%d] %d starts to eat\n", get_current_time(), philo->id);
	usleep(philo->params->time_to_eat);
	printf("[%d] %d finished eating\n", get_current_time(), philo->id);

	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);


	printf("[%d] %d starts to sleep\n", get_current_time(), philo->id);
	usleep(philo->params->time_to_sleep);

	printf("[%d] %d dies\n", get_current_time(), philo->id);
	return (NULL);
}

void	wait_all_threads(int nb, pthread_t **threads)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_join(*(threads[i]), NULL);
		i++;
	}
}
