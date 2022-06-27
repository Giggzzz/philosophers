/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:01:46 by gudias            #+#    #+#             */
/*   Updated: 2022/06/27 17:35:57 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define MSG_FORK "\033[1;33mhas taken a fork\033[0m" 
# define MSG_EAT "\033[1;32mis eating\033[0m" 
# define MSG_SLEEP "\033[1;34mis sleeping\033[0m" 
# define MSG_THINK "\033[1;35mis thinking\033[0m" 
# define MSG_DIE "\033[1;31mdied\033[0m" 

typedef struct s_params
{
	int			nb_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_to_eat;
	long int	start_time;
	sem_t		*ended_sem;
	sem_t		*print_sem;
	sem_t		*forks_sem;
}	t_params;

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	long int	last_meal;
	sem_t		*last_meal_sem;
	int			meal_count;
	t_params	*params;
}	t_philo;

//init.c
int		init_params(t_params *params, int argc, char **argv);
t_philo	**create_philos(t_params *params);

//process.c
int		create_process(t_philo **philos);
void	wait_all_process(t_philo **philos);
void	kill_all_process(t_philo **philos);

//checker_thread.c
void	*thread_check_death(void *arg);
void	*thread_wait_end(void *arg);

//philo_routine.c
void	philo_routine(t_philo *philo);

//close.c
int		err_msg(char *str);
void	free_philos(t_philo **philos);
void	free_all(t_philo **philos);

//utils.c
void			print_msg(char *msg, t_params *params, int id);
long int		get_current_time(void);
void			tweaked_usleep(int ms_time);
int				is_number_pos(char *str);
int				ft_atoi(char *str);

#endif
