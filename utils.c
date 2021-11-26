/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:29:50 by aricholm          #+#    #+#             */
/*   Updated: 2021/11/19 17:11:52 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	shut_it_down(t_setup *setup)
{
	t_philosopher	*tmp;
	t_philosopher	*kill;

	tmp = setup->last;
	while (tmp)
	{
		kill = tmp;
		tmp = tmp->next;
		pthread_mutex_destroy(&kill->m_fork);
		free (kill);
	}
	pthread_mutex_destrox(&setup->m_write);
}

unsigned long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static char	*get_string(t_state state)
{
	if (state == EAT)
		return ("is eating");
	if (state == SLEEP)
		return ("is sleeping");
	if (state == THINK)
		return ("is thinking");
	if (state == DEAD)
		return ("died");
	if (state == FORK)
		return ("has taken a fork");
	if (state == WIN)
		return ("ate everything");
	return (NULL);
}

void	print_status(t_philosopher *philo, t_state state)
{
	pthread_mutex_lock(philo->setup->m_write);
	printf("%ld: %ld %s\n", get_time() - philo->setup->start,
		philo->id, get_string(state));
	pthread_mutex_unlock(philo->setup->m_write);
}
