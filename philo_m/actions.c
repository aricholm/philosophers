/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:37:35 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/11 16:59:31 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor_death(t_setup *setup)
{
	t_philosopher	*philo;
	t_bool			well_fed;

	philo = setup->last;
	well_fed = FALSE;
	while (!setup->game_over)
	{
		if (philo == setup->last && setup->times_to_eat)
			well_fed = TRUE;
		if (get_time() > philo->will_die)
		{
			print_status(philo, DEAD);
			return ;
		}
		if (philo->times_eaten < setup->times_to_eat)
			well_fed = FALSE;
		philo = philo->next;
		if (philo == setup->last && well_fed)
		{
			setup->game_over = TRUE;
			return ;
		}
	}
}

void	philo_wait(t_setup *setup, unsigned int msec)
{
	unsigned long int	time;

	time = get_time();
	while (!setup->game_over)
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
	philo_wait(philo->setup, philo->setup->time_to_sleep);
}

void	philo_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->m_fork);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->next->m_fork);
	print_status(philo, FORK);
	print_status(philo, EAT);
	philo->times_eaten++;
	philo->will_die = get_time() + philo->setup->time_to_die;
	philo_wait(philo->setup, philo->setup->time_to_eat);
	pthread_mutex_unlock(&philo->next->m_fork);
	pthread_mutex_unlock(&philo->m_fork);
}
