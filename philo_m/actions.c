/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:37:35 by aricholm          #+#    #+#             */
/*   Updated: 2022/03/16 16:58:17 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	is_gameover(t_setup *setup)
{
	t_bool	over;

	pthread_mutex_lock(&setup->m_check);
	over = setup->game_over;
	pthread_mutex_unlock(&setup->m_check);
	return (over);
}

static unsigned long	get_willdie(t_philosopher *philo)
{
	unsigned long	willdie;

	pthread_mutex_lock(&philo->setup->m_check);
	willdie = philo->will_die;
	pthread_mutex_unlock(&philo->setup->m_check);
	return (willdie);
}

static unsigned int	get_timeseaten(t_philosopher *philo)
{
	unsigned int	timeseaten;

	pthread_mutex_lock(&philo->setup->m_check);
	timeseaten = philo->times_eaten;
	pthread_mutex_unlock(&philo->setup->m_check);
	return (timeseaten);
}

void	monitor_death(t_setup *setup)
{
	t_philosopher	*philo;
	t_bool			well_fed;

	philo = setup->last;
	well_fed = FALSE;
	while (!is_gameover(setup))
	{
		if (philo == setup->last && setup->times_to_eat)
			well_fed = TRUE;
		if (get_time() > get_willdie(philo))
		{
			print_status(philo, DEAD);
			return ;
		}
		if (get_timeseaten(philo) < setup->times_to_eat)
			well_fed = FALSE;
		philo = philo->next;
		if (philo == setup->last && well_fed)
		{
			pthread_mutex_lock(&setup->m_check);
			setup->game_over = TRUE;
			pthread_mutex_unlock(&setup->m_check);
			return ;
		}
	}
}

void	philo_eat(t_philosopher *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = &philo->m_fork;
	second = &philo->next->m_fork;
	if (philo->id % 2)
	{
		second = &philo->m_fork;
		first = &philo->next->m_fork;
	}
	pthread_mutex_lock(first);
	print_status(philo, FORK);
	pthread_mutex_lock(second);
	print_status(philo, FORK);
	print_status(philo, EAT);
	pthread_mutex_lock(&philo->setup->m_check);
	philo->times_eaten++;
	philo->will_die = get_time() + philo->setup->time_to_die;
	pthread_mutex_unlock(&philo->setup->m_check);
	usleep(philo->setup->time_to_eat * 1000);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}
