/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 21:18:17 by alyasar           #+#    #+#             */
/*   Updated: 2022/06/18 15:20:02 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_error(char *str)
{
	printf("Error: %s\n", str);
	return (0);
}

static void	finish2(t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < gen->philo_count)
		pthread_mutex_destroy(&gen->fork[i].mutex);
	pthread_mutex_destroy(&gen->m_meal);
	pthread_mutex_destroy(&gen->m_write);
	pthread_mutex_destroy(&gen->m_dead);
	pthread_mutex_destroy(&gen->m_fork);
	pthread_mutex_destroy(&gen->m_win);
	pthread_mutex_destroy(&gen->m_t_eat);
	free(gen->philo);
	free(gen->fork);
}

static void	finish(t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < gen->philo_count)
		pthread_join(gen->philo[i].thread, NULL);
	finish2(gen);
}

int	main(int argc, char **argv)
{
	t_gen	gen;

	if (argc < 5 || argc > 6)
		return (print_error("Wrong number of arguments."));
	if (!initialize(&gen, argc, argv))
	{
		finish2(&gen);
		return (0);
	}
	threading(&gen);
	finish(&gen);
	return (0);
}
