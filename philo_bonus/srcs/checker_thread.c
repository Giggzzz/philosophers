/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:11:59 by gudias            #+#    #+#             */
/*   Updated: 2022/06/25 03:33:02 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_philo_dead(t_philo *philo)
{
	long int	timestamp;

	timestamp = get_current_time() - philo->params->start_time;
	if (philo->last_meal + philo->params->time_to_die < timestamp)
		return (1);
	return (0);
}

static int	check_all_ate(t_philo **philos)
{
	int	i;

	if ((*philos)->params->meals_to_eat <= 0)
		return (0);
	i = 0;
	while (philos[i])
	{
		if (philos[i]->meal_count < philos[i]->params->meals_to_eat)
			return (0);
		i++;
	}
	kill_all_process(philos);
	return (1);
}

static int	check_someone_died(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (is_philo_dead(philos[i]))
		{
			printf("%d lastmeal: %ld\n", i+1, philos[i]->last_meal);
			kill_all_process(philos);
			tweaked_usleep(1);
			print_msg(MSG_DIE, philos[i]->params, philos[i]->id);
			return (1);
		}	
		i++;
	}
	return (0);
}

void	*thread_check_death(void *arg)
{
	t_philo		**philos;
	long int	time;

	philos = (t_philo **) arg;
	while (1)
	{
		time = get_current_time();
		if (check_someone_died(philos))
			return (NULL);
		if (check_all_ate(philos))
			return (NULL);
		while (get_current_time() == time)
			usleep(100);
	}
	return (NULL);
}
