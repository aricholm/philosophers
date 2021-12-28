/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:29:50 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/11 16:48:34 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_kill(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) philosopher;
	sem_wait(philo->setup->s_kill);
	philo->game_over = TRUE;
	sem_post(philo->setup->s_forks);
	return (NULL);
}

void	*monitor_death(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) philosopher;
	philo->flag = TRUE;
	while (!philo->game_over)
	{
		if (get_time() > philo->will_die)
		{
			print_status(philo, DEAD);
		}
		if (philo->setup->times_to_eat && philo->flag
			&& philo->times_eaten == philo->setup->times_to_eat)
		{
			sem_post(philo->setup->s_ready);
			philo->flag = FALSE;
		}
		usleep(500);
	}
	return (NULL);
}

void	shut_it_down(t_setup *setup)
{
	unsigned int	i;

	i = 0;
	while (i < setup->max_philo)
		waitpid(setup->philo[i++], NULL, 0);
	sem_close(setup->s_kill);
	sem_close(setup->s_write);
	sem_close(setup->s_forks);
	sem_close(setup->s_ready);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/ready");
	sem_unlink("/kill");
	exit (EXIT_SUCCESS);
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
	unsigned int	i;

	if (!philo->game_over)
	{
		sem_wait(philo->setup->s_write);
		if (!philo->game_over)
			printf("%08ld: %ld %s\n", get_time() - philo->setup->start,
				philo->id, get_string(state));
		if (state == DEAD)
		{
			i = 0;
			philo->game_over = TRUE;
			while (i < philo->setup->max_philo)
			{
				sem_post(philo->setup->s_kill);
				i++;
			}
		}
		sem_post(philo->setup->s_write);
	}
}
