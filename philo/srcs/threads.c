/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:50:19 by gudias            #+#    #+#             */
/*   Updated: 2022/06/21 17:05:49 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(char *msg, t_params *params, int id)
{
	long int	timestamp;

	timestamp = get_current_time() - params->start_time;
	//pthread_mutex_lock(&(params->print_lock));
	printf("%ld\t%d %s\n", timestamp, id, msg);
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

void	*thread_check_death(void *arg)
{
	t_philo	**philos;
	int		i;

	philos = (t_philo **) arg;
	while (1)
	{
		i = 0;
		while (philos[i])
		{
			if (is_dead(philos[i]))
			{	
				philos[i]->params->sim_finished = 1; //mutex ?
				print_msg(MSG_DIE, philos[i]->params, philos[i]->id);
				return (NULL);
			}	
			i++;
		}
	}
	return (NULL);
}

void	*thread_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;	
	while (!philo->params->sim_finished)
	{
		pthread_mutex_lock(philo->fork1);
		if (philo->params->sim_finished)
			break ;
		print_msg(MSG_FORK, philo->params, philo->id);

		
		
		pthread_mutex_lock(philo->fork2);
		if (philo->params->sim_finished)
			break ;
		print_msg(MSG_FORK, philo->params, philo->id);

		
		print_msg(MSG_EAT, philo->params, philo->id);
		philo->last_meal = get_current_time() - philo->params->start_time;
		tweaked_usleep(philo->params->time_to_eat);	
	
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		philo->meal_count++;	
		
		if (philo->params->sim_finished)
			break ;
	
		print_msg(MSG_SLEEP, philo->params, philo->id);
		tweaked_usleep(philo->params->time_to_sleep);
		
		if (philo->params->sim_finished)
			break ;
		print_msg(MSG_THINK, philo->params, philo->id);
		
	}
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
