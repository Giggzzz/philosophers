/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:01:46 by gudias            #+#    #+#             */
/*   Updated: 2022/06/04 04:56:56 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef	struct s_params
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
	int	min_turns;
}	t_params;

typedef	struct s_philo
{
	int	id;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	t_params	*params;
}	t_philo;

int	check_args(int argc, char **argv);
void	init_params(t_params *params, char **argv);

void	init_forks(int nb_forks);

int	ft_atoi(char *str);

#endif
