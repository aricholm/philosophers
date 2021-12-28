/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:37:35 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/11 16:53:47 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_wait(t_philosopher *philo, unsigned int msec)
{
	unsigned long int	time;

	time = get_time();
	while (!philo->game_over)
	{
		if (get_time() > time + msec)
			return ;
		usleep(500);
	}
}

void	philo_think(t_philosopher *philo)
{
	print_status(philo, THINK);
}

void	philo_sleep(t_philosopher *philo)
{
	print_status(philo, SLEEP);
	philo_wait(philo, philo->setup->time_to_sleep);
}

void	philo_eat(t_philosopher *philo)
{
	sem_wait(philo->setup->s_forks);
	print_status(philo, FORK);
	sem_wait(philo->setup->s_forks);
	print_status(philo, FORK);
	print_status(philo, EAT);
	philo->times_eaten++;
	philo->will_die = get_time() + philo->setup->time_to_die;
	philo_wait(philo, philo->setup->time_to_eat);
	sem_post(philo->setup->s_forks);
	sem_post(philo->setup->s_forks);
}
