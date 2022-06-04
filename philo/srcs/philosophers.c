/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:00:50 by gudias            #+#    #+#             */
/*   Updated: 2022/06/04 05:12:22 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

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
	printf("%d ttd\n", philo->params->time_to_die);	
	printf("%d tte\n", philo->params->time_to_eat);	
	printf("%d tts\n", philo->params->time_to_sleep);	
	usleep(10000);
	printf("%d finished eating\n", philo->id);	

	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	return (NULL);
}

int	main (int argc, char **argv)
{
	t_params	params;

	if (!check_args(argc, argv))
		return (1);

	init_params(&params, argv);
	
	//init_forks(atoi(argv[1])); //init_mutex
	//init_philos(argv); //init_threads

	//INIT MUTEX (forks)
	pthread_mutex_t	fork0 = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t	fork1 = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t	fork2 = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t	fork3 = PTHREAD_MUTEX_INITIALIZER;
	
	//THREADS
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;
	pthread_t	t4;
	
	//INIT T_PHILO(id, fork1, fork2)
	t_philo		philo1;
	t_philo		philo2;
	t_philo		philo3;
	t_philo		philo4;

	philo1.fork1 = &fork0;
	philo1.id = 1;
	philo1.params = &params;
	philo1.fork2 = &fork1;
	philo2.fork1 = &fork1;
	philo2.id = 2;
	philo2.params = &params;
	philo2.fork2 = &fork2;
	philo3.fork1 = &fork2;
	philo3.id = 3;
	philo3.params = &params;
	philo3.fork2 = &fork3;
	philo4.fork1 = &fork3;
	philo4.id = 4;
	philo4.params = &params;
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
