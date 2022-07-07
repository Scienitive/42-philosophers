/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 21:54:12 by alyasar           #+#    #+#             */
/*   Updated: 2022/06/18 23:19:38 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	win_checker(t_gen *gen)
{
	int	i;

	i = 0;
	while (gen->max_eat != -1 && i < gen->philo_count
		&& is_reached_max_eat(&gen->philo[i]))
		i++;
	if (i == gen->philo_count)
	{
		pthread_mutex_lock(&gen->m_win);
		gen->win = 1;
		pthread_mutex_unlock(&gen->m_win);
		pthread_mutex_lock(&gen->m_write);
		printf("Each philosopher ate at least %d time(s).\n", gen->max_eat);
		pthread_mutex_unlock(&gen->m_write);
	}
}

static void	death_checker(t_gen *gen)
{
	int	i;

	while (!check_win(gen))
	{
		i = -1;
		while (++i < gen->philo_count && !check_died(gen))
		{
			pthread_mutex_lock(&gen->m_meal);
			if (get_real_time() - gen->philo[i].last_meal > gen->die_time)
			{
				pthread_mutex_lock(&gen->m_dead);
				gen->died = 1;
				pthread_mutex_unlock(&gen->m_dead);
				pthread_mutex_lock(&gen->m_write);
				printf("%ld %d %s\n", get_real_time() - gen->start_time,
					gen->philo[i].id, "died.");
				pthread_mutex_unlock(&gen->m_write);
			}
			pthread_mutex_unlock(&gen->m_meal);
			usleep(200);
		}
		if (check_died(gen))
			break ;
		win_checker(gen);
	}
}

void	threading(t_gen *gen)
{
	int		i;
	void	*func;

	i = -1;
	if (gen->philo_count == 1)
		func = thread_1;
	else
		func = thread;
	gen->start_time = get_real_time();
	while (++i < gen->philo_count)
	{
		gen->philo[i].last_meal = gen->start_time;
		pthread_create(&gen->philo[i].thread, NULL, func, &gen->philo[i]);
	}
	if (func == thread)
		death_checker(gen);
}
