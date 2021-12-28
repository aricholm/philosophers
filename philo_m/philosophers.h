/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:27:49 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/03 19:36:53 by aricholm         ###   ########.fr       */
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

typedef enum e_bool{FALSE, TRUE}	t_bool;
typedef enum e_state{EAT, SLEEP, THINK, FORK, WIN, DEAD}	t_state;

typedef struct s_queue{
	unsigned int	philosopher;
	struct s_queue	*next;
}	t_queue;

typedef struct s_philosopher{
	size_t					id;
	pthread_t				thread;
	unsigned int			times_eaten;
	unsigned long int		will_die;
	struct s_setup			*setup;
	struct s_philosopher	*next;
	pthread_mutex_t			m_fork;
}	t_philosopher;

typedef struct s_setup{
	unsigned int		max_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		times_to_eat;
	unsigned long int	start;
	t_philosopher		*last;
	pthread_mutex_t		m_write;
	pthread_mutex_t		m_ready;
	volatile t_bool		game_over;
}	t_setup;

int					get_data(t_setup *setup, int argc, const char *argv[]);
unsigned long int	get_time(void);
void				link_first_to_last(t_setup *setup);
void				print_status(t_philosopher *philo, t_state state);
void				philo_think(t_philosopher *philo);
void				philo_sleep(t_philosopher *philo);
void				philo_eat(t_philosopher *philo);
void				shut_it_down(t_setup *setup);
void				monitor_death(t_setup *setup);
#endif
