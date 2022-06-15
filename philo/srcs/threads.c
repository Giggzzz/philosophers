/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:50:19 by gudias            #+#    #+#             */
/*   Updated: 2022/06/15 15:44:29 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(char *msg, t_params *params, int id)
{
	long int	timestamp;

	timestamp = get_current_time() - params->start_time;
	//pthread_mutex_lock(&(params->print_lock));
	printf("%ld\tms\t%d %s\n", timestamp, id, msg);
	//pthread_mutex_unlock(&(params->print_lock));
}

int	is_dead(t_philo *philo)
{
	long int	timestamp;

	timestamp = get_current_time() - philo->params->start_time;
	if (philo->last_meal + philo->params->time_to_die <= timestamp)
		return (1);
	return (0);
}

void	*thread_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;	
	while (1)
	{
		pthread_mutex_lock(philo->fork1);
		print_msg(MSG_FORK, philo->params, philo->id);

		
		if (is_dead(philo))
			break ;
		
		pthread_mutex_lock(philo->fork2);
		print_msg(MSG_FORK, philo->params, philo->id);

		if (is_dead(philo))
			break ;

		print_msg(MSG_EAT, philo->params, philo->id);
		philo->last_meal = get_current_time() - philo->params->start_time;
		usleep(philo->params->time_to_eat * 1000);	
	
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		philo->meal_count++;	
		if (is_dead(philo))
			break ;
	
		print_msg(MSG_SLEEP, philo->params, philo->id);
		usleep(philo->params->time_to_sleep * 1000);
		
		if (is_dead(philo))
			break ;

		print_msg(MSG_THINK, philo->params, philo->id);
		
	}
	print_msg(MSG_DIE, philo->params, philo->id);
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
