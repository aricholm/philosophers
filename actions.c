/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:37:35 by aricholm          #+#    #+#             */
/*   Updated: 2021/11/22 12:55:08 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_think(t_philosopher *philo)
{
	print_status(philo, EAT);
	usleep(philo->setup->time_to_eat);
}

void	philo_sleep(t_philosopher *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->setup->time_to_sleep);
}

void	philo_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->m_fork);
	philo->fork = FALSE;
	pthread_mutex_lock(philo->next->m_fork);
	philo->next->m_fork = FALSE;
	
}