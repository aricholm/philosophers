/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:27:26 by aricholm          #+#    #+#             */
/*   Updated: 2022/03/16 14:35:56 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philosopher(void *philosopher)
{
	t_setup			*setup;
	t_philosopher	*philo;

	philo = (t_philosopher *) philosopher;
	setup = philo->setup;
	if (philo->id % 2)
		usleep(philo->setup->time_to_eat * 1000);
	while (!is_gameover(setup))
	{
		philo_eat(philo);
		print_status(philo, SLEEP);
		usleep(philo->setup->time_to_sleep * 1000);
		print_status(philo, THINK);
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
	pthread_mutex_lock(&setup->m_check);
	philo->will_die = get_time() + setup->time_to_die;
	pthread_mutex_unlock(&setup->m_check);
}

static void	initialize(t_setup *setup)
{
	size_t			i;

	setup->start = get_time();
	setup->last = NULL;
	pthread_mutex_init(&setup->m_write, NULL);
	pthread_mutex_init(&setup->m_check, NULL);
	setup->game_over = FALSE;
	i = 0;
	while (i < setup->max_philo)
	{
		init_philosopher(setup);
		i++;
	}
	link_first_to_last(setup);
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
