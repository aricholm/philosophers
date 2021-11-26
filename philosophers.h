/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:27:49 by aricholm          #+#    #+#             */
/*   Updated: 2021/11/22 12:42:05 by aricholm         ###   ########.fr       */
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
typedef enum e_state{STANDBY, EAT, SLEEP, THINK, FORK, WIN, DEAD}	t_state;

typedef struct s_queue{
	unsigned int	philosopher;
	struct s_queue	*next;
}	t_queue;

typedef struct s_philosopher{
	size_t					id;
	pthread_t				thread;
	t_state					state;
	unsigned int			times_eaten;
	struct s_setup			*setup;
	struct s_philosopher	*next;
	pthread_mutex_t			m_fork;
	t_bool					fork;
}	t_philosopher;

typedef struct s_setup{
	unsigned int		max_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		times_to_eat;
	t_queue				*next;
	unsigned long int	start;
	t_philosopher		*last;
	pthread_mutex_t		*m_write;
	t_bool				ready;
}	t_setup;

unsigned long int	get_time(void);
void				print_status(t_philosopher *philo, t_state state);
#endif
