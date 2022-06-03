/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:00:50 by gudias            #+#    #+#             */
/*   Updated: 2022/06/03 17:31:30 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	*thread_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;

	printf("%d arrives and start to wait\n", philo->id);
	usleep(2000);

	printf("%d wait for fork\n", philo->id);
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(philo->fork2);
	
	printf("%d start eating\n", philo->id);	
	usleep(10000);
	printf("%d finished eating\n", philo->id);	

	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	return (NULL);
}

int	main (int argc, char **argv)
{
	(void) argc;
	(void) argv;
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;
	pthread_t	t4;
	//int		*res;
	t_philo		philo1;
	t_philo		philo2;
	t_philo		philo3;
	t_philo		philo4;

	//INIT MUTEX (forks)
	pthread_mutex_t	fork0 = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t	fork1 = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t	fork2 = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t	fork3 = PTHREAD_MUTEX_INITIALIZER;

	//INIT T_PHILO(id, fork1, fork2)
	philo1.fork1 = &fork0;
	philo1.id = 1;
	philo1.fork2 = &fork1;
	philo2.fork1 = &fork1;
	philo2.id = 2;
	philo2.fork2 = &fork2;
	philo3.fork1 = &fork2;
	philo3.id = 3;
	philo3.fork2 = &fork3;
	philo4.fork1 = &fork3;
	philo4.id = 4;
	philo4.fork2 = &fork0;

	pthread_create(&t1, NULL, &thread_func, &philo1);
	pthread_create(&t2, NULL, &thread_func, &philo2);
	pthread_create(&t3, NULL, &thread_func, &philo3);
	pthread_create(&t4, NULL, &thread_func, &philo4);
	
	//wait
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	//printf("end: %d\n", arg);
	return (0);
}
