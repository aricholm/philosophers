/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:27:49 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/10 23:57:08 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define _DEFAULT_SOURCE 1
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h> 
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_bool{FALSE, TRUE}	t_bool;
typedef enum e_state{EAT, SLEEP, THINK, FORK, WIN, DEAD}	t_state;

typedef struct s_queue{
	unsigned int	philosopher;
	struct s_queue	*next;
}	t_queue;

typedef struct s_philosopher{
	size_t					id;
	pid_t					pid;
	pthread_t				monitor;
	pthread_t				kill;
	unsigned int			times_eaten;
	unsigned long int		will_die;
	struct s_setup			*setup;
	volatile t_bool			game_over;
	t_bool					flag;
}	t_philosopher;

typedef struct s_setup{
	unsigned int		max_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		times_to_eat;
	unsigned long int	start;
	pid_t				philo[200];
	sem_t				*s_forks;
	sem_t				*s_write;
	sem_t				*s_ready;
	sem_t				*s_kill;
}	t_setup;

int					get_data(t_setup *setup, int argc, const char *argv[]);
unsigned long int	get_time(void);
void				print_status(t_philosopher *philo, t_state state);
void				philo_think(t_philosopher *philo);
void				philo_sleep(t_philosopher *philo);
void				philo_eat(t_philosopher *philo);
void				shut_it_down(t_setup *setup);
void				*monitor_death(void *philosopher);
void				*monitor_kill(void *philosopher);
#endif
