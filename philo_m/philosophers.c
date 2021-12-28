/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:27:26 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/11 16:26:16 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philosopher(void *philosopher)
{
	t_setup			*setup;
	t_philosopher	*philo;

	philo = (t_philosopher *) philosopher;
	setup = philo->setup;
	pthread_mutex_lock(&setup->m_ready);
	pthread_mutex_unlock(&setup->m_ready);
	if (philo->id % 2)
		usleep(philo->setup->time_to_eat * 1000);
	while (!setup->game_over)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

static void	init_philosopher(t_setup *setup)
{
	t_philosopher	*philo;
	static size_t	id = 0;

	philo = malloc(sizeof (t_philosopher));
	if (!philo)
	{
		shut_it_down(setup);
		exit(EXIT_FAILURE);
	}
	id++;
	philo->next = setup->last;
	setup->last = philo;
	philo->id = id;
	philo->times_eaten = 0;
	philo->setup = setup;
	pthread_mutex_init(&philo->m_fork, NULL);
	pthread_create(&philo->thread, NULL, philosopher, philo);
	philo->will_die = get_time() + setup->time_to_die;
}

static void	initialize(t_setup *setup)
{
	size_t			i;

	setup->game_over = FALSE;
	setup->start = get_time();
	setup->last = NULL;
	pthread_mutex_init(&setup->m_write, NULL);
	pthread_mutex_init(&setup->m_ready, NULL);
	pthread_mutex_lock(&setup->m_ready);
	i = 0;
	while (i < setup->max_philo)
	{
		init_philosopher(setup);
		i++;
	}
	link_first_to_last(setup);
	pthread_mutex_unlock(&setup->m_ready);
}

int	main(int argc, const char *argv[])
{
	t_setup		setup;

	if ((argc < 5 || argc > 6) || get_data(&setup, argc, argv))
	{
		printf("Usage:\n./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	initialize(&setup);
	monitor_death(&setup);
	shut_it_down(&setup);
	return (0);
}
