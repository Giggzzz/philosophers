/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:46:06 by gudias            #+#    #+#             */
/*   Updated: 2022/06/28 16:02:41 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->params->forks_sem);
	print_msg(MSG_FORK, philo->params, philo->id);
	sem_wait(philo->params->forks_sem);
	print_msg(MSG_FORK, philo->params, philo->id);
}

static void	take_lunch(t_philo *philo)
{
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_current_time() - philo->params->start_time;
	sem_post(philo->last_meal_sem);
	print_msg(MSG_EAT, philo->params, philo->id);
	tweaked_usleep(philo->params->time_to_eat);
	philo->meal_count++;
	sem_post(philo->params->forks_sem);
	sem_post(philo->params->forks_sem);
	if (philo->meal_count == philo->params->meals_to_eat)
		sem_post(philo->params->is_full_sem);
}

static void	have_a_good_night(t_philo *philo)
{
	print_msg(MSG_SLEEP, philo->params, philo->id);
	tweaked_usleep(philo->params->time_to_sleep);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	death_checker;

	pthread_create(&death_checker, NULL, &thread_check_death, philo);
	if (philo->id % 2 == 0)
		tweaked_usleep(philo->params->time_to_eat);
	while (1)
	{
		take_forks(philo);
		take_lunch(philo);
		have_a_good_night(philo);
		print_msg(MSG_THINK, philo->params, philo->id);
	}
}
