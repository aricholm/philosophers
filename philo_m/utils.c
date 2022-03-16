/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:29:50 by aricholm          #+#    #+#             */
/*   Updated: 2022/03/16 17:03:38 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	link_first_to_last(t_setup *setup)
{
	t_philosopher	*tmp;

	tmp = setup->last;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = setup->last;
}

void	shut_it_down(t_setup *setup)
{
	t_philosopher	*tmp;
	t_philosopher	*kill;

	tmp = setup->last->next;
	pthread_join(setup->last->thread, NULL);
	while (tmp != setup->last)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
	tmp = tmp->next;
	pthread_mutex_destroy(&setup->last->m_fork);
	free (setup->last);
	while (tmp != setup->last)
	{
		kill = tmp;
		tmp = tmp->next;
		pthread_mutex_destroy(&kill->m_fork);
		free (kill);
	}
	pthread_mutex_destroy(&setup->m_write);
	pthread_mutex_destroy(&setup->m_check);
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
	pthread_mutex_lock(&philo->setup->m_write);
	if (!is_gameover(philo->setup))
		printf("%08ld: %ld %s\n", get_time() - philo->setup->start,
			philo->id, get_string(state));
	if (state == DEAD)
	{
		pthread_mutex_lock(&philo->setup->m_check);
		philo->setup->game_over = TRUE;
		pthread_mutex_unlock(&philo->setup->m_check);
	}
	pthread_mutex_unlock(&philo->setup->m_write);
}
