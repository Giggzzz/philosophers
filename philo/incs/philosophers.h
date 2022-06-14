/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:01:46 by gudias            #+#    #+#             */
/*   Updated: 2022/06/14 18:42:32 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define MSG_FORK "\033[1;33mhas taken a fork\033[0m" 
# define MSG_FORK2 "\033[1;35mhas taken a fork\033[0m" 
# define MSG_EAT "\033[1;32mis eating\033[0m" 
# define MSG_SLEEP "\033[1;34mis sleeping\033[0m" 
# define MSG_DIE "\033[1;31mdied\033[0m" 
	
	
typedef	struct s_params
{
	int		nb_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		min_turns;
	long int	start_time;
	pthread_mutex_t	print_lock;
}	t_params;

typedef	struct s_philo
{
	int	id;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	t_params	*params;
}	t_philo;

//init
int		check_args(int argc, char **argv);
void		init_params(t_params *params, char **argv);
pthread_mutex_t	**init_mutex_forks(int nb_forks);
t_philo		**init_philos(t_params *params, pthread_mutex_t **forks_mutex);
pthread_t	**init_threads(int nb, t_philo **philos);

//threads
void	*thread_philo_func(void *arg);
void	wait_all_threads(int nb, pthread_t **threads);
void	print_msg(char *msg, t_params *params, int id);

//time
long int		get_current_time(void);

//close
void	free_forks_mutex(pthread_mutex_t **forks_mutex);
void	free_philos(t_philo **philos);
void	free_threads(pthread_t **threads);
void	free_all(pthread_mutex_t **forks_mutex, pthread_t **threads, t_philo **philos);
void	exit_error_msg(char *msg);

//utils
int	err_msg(char *str);
int	is_number_pos(char *str);
int	ft_atoi(char *str);

#endif
