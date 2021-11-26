/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:27:26 by aricholm          #+#    #+#             */
/*   Updated: 2021/11/22 12:37:27 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philosopher(void *philosopher)
{
	t_setup			*setup;
	t_philosopher	*philo;

	philo = (t_philosopher *) philosopher;
	setup = philo->setup;
	while (!setup->ready)
		sleep (1);
	while (!setup->times_to_eat || philo->times_eaten != setup->times_to_eat)
	{
		philo_eat();
		philo_sleep();
		philo_think();
	}
}

static int	ph_atoi(const char *str)
{
	size_t	i;
	int		out;

	i = 0;
	out = 0;
	while (str[i])
		out = out * 10 + (str[i++] - '0');
	return (out);
}

static void	init_philosopher(t_setup *setup)
{
	t_philosopher	*philo;
	static size_t	id = 0;

	philo = malloc(sizeof (t_philosopher));
	if (!philosopher)
	{
		shut_it_down(setup);
		exit(EXIT_FAILURE);
	}
	id++;
	philo->next = setup->last;
	setup->last = philo;
	philo->id = id;
	philo->state = STANDBY;
	philo->times_eaten = 0;
	philo->setup = setup;
	pthread_mutex_init(&philo->m_fork, NULL);
	philo->fork = TRUE;
	pthread_create(&philo->thread, NULL, philosopher, philo);
}

static void	init_setup(t_setup *setup, const char *argv[])
{
	setup->time_to_die = ph_atoi(argv[2]);
	setup->time_to_eat = ph_atoi(argv[3]);
	setup->time_to_sleep = ph_atoi(argv[4]);
	if (argv[5])
		setup->times_to_eat = ph_atoi(argv[5]);
	else
		setup->times_to_eat = 0;
	setup->start = get_time();
	pthread_mutex_init(setup->m_write, NULL);
	setup->ready = FALSE;
}

int	main(int argc, const char *argv[])
{
	t_setup		setup;
	pthread_t	filo1;

	if (argc < 5 || argc > 6)
	{
		printf("Usage:\n./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	init_setup(&setup, argv);
	pthread_create(&filo1, NULL, philosopher, &setup);
	while (1)
		sleep(1);
	return (0);
}
