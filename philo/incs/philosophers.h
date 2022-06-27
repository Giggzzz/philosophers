/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:01:46 by gudias            #+#    #+#             */
/*   Updated: 2022/06/27 11:45:09 by gudias           ###   ########.fr       */
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
# define MSG_EAT "\033[1;32mis eating\033[0m" 
# define MSG_SLEEP "\033[1;34mis sleeping\033[0m" 
# define MSG_THINK "\033[1;35mis thinking\033[0m" 
# define MSG_DIE "\033[1;31mdied\033[0m" 

typedef struct s_params
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	long int		start_time;
	int				ended;
	pthread_mutex_t	ended_lock;
	pthread_mutex_t	print_lock;
}	t_params;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	long int		last_meal;
	pthread_mutex_t	last_meal_lock;
	int				meal_count;
	t_params		*params;
}	t_philo;

//init.c
int				init_params(t_params *params, int argc, char **argv);
pthread_mutex_t	**init_mutex_forks(int nb_forks);
t_philo			**create_philos(t_params *params, pthread_mutex_t **forks);

//threads.c
pthread_t		**create_threads(int nb, t_philo **philos, pthread_t *t_check);
void			wait_all_threads(pthread_t **threads, pthread_t *thread_check);

//checker_thread.c
void			*thread_check_death(void *arg);

//philo_routine.c
void			*thread_philo_routine(void *arg);

//close.c
int				err_msg(char *str);
void			free_forks_mutex(pthread_mutex_t **forks_mutex);
void			free_philos(t_philo **philos);
void			free_threads(pthread_t **threads);
void			free_all(pthread_mutex_t **frks, pthread_t **th, t_philo **ph);

//utils.c
void			print_msg(char *msg, t_params *params, int id);
long int		get_current_time(void);
void			tweaked_usleep(int ms_time);
int				is_number_pos(char *str);
int				ft_atoi(char *str);

#endif
