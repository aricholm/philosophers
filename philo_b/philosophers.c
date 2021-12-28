/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:27:26 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/11 17:03:27 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philosopher(t_philosopher *philo)
{
	if (philo->id % 2)
		usleep(philo->setup->time_to_eat * 1000);
	while (!philo->game_over)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_join(philo->monitor, NULL);
	sem_close(philo->setup->s_kill);
	sem_close(philo->setup->s_write);
	sem_close(philo->setup->s_forks);
	if (philo->flag)
		sem_post(philo->setup->s_ready);
	sem_close(philo->setup->s_ready);
	return (NULL);
}

static void	init_philosopher(t_setup *setup, unsigned int id)
{
	t_philosopher	philo;

	philo.id = id;
	philo.setup = setup;
	philo.times_eaten = 0;
	philo.game_over = FALSE;
	philo.pid = getpid();
	philo.will_die = get_time() + setup->time_to_die;
	pthread_create(&philo.monitor, NULL, monitor_death, &philo);
	pthread_create(&philo.kill, NULL, monitor_kill, &philo);
	philosopher(&philo);
	pthread_join(philo.kill, NULL);
	exit(EXIT_SUCCESS);
}

static void	init_semaphore(t_setup *setup)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/ready");
	sem_unlink("/kill");
	setup->s_forks = sem_open("/forks", O_CREAT | O_EXCL,
			S_IRWXU, setup->max_philo);
	setup->s_write = sem_open("/write", O_CREAT | O_EXCL, S_IRWXU, 1);
	setup->s_ready = sem_open("/ready", O_CREAT | O_EXCL, S_IRWXU, 0);
	setup->s_kill = sem_open("/kill", O_CREAT | O_EXCL, S_IRWXU, 0);
	setup->start = get_time();
}

static void	initialize(t_setup *setup)
{
	size_t			i;
	pid_t			pid;

	init_semaphore(setup);
	i = 0;
	while (i < setup->max_philo)
	{
		pid = fork();
		setup->philo[i++] = pid;
		if (!pid)
			init_philosopher(setup, i);
	}
	if (pid)
	{	
		i = 0;
		while (i++ < setup->max_philo)
			sem_wait(setup->s_ready);
		i = 0;
		while (i++ < setup->max_philo)
		{
			sem_post(setup->s_forks);
			sem_post(setup->s_kill);
		}
	}
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
	shut_it_down(&setup);
	return (0);
}
