/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 21:42:44 by alyasar           #+#    #+#             */
/*   Updated: 2022/06/18 23:20:19 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	write_status(t_gen *gen, int id, char *str)
{
	pthread_mutex_lock(&gen->m_write);
	if (!check_died(gen) && !check_win(gen))
		printf("%ld %d %s\n", get_real_time() - gen->start_time, id, str);
	pthread_mutex_unlock(&gen->m_write);
}

long int	get_real_time(void)
{
	struct timeval	time;
	long int		i;

	gettimeofday(&time, NULL);
	i = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (i);
}

void	smart_sleep(long int time, t_gen *gen)
{
	long int	i;

	i = get_real_time();
	while (get_real_time() - i < time)
	{
		if (check_died(gen) || check_win(gen))
			break ;
		usleep(100);
	}
}

int	check_died(t_gen *gen)
{
	pthread_mutex_lock(&gen->m_dead);
	if (gen->died)
	{
		pthread_mutex_unlock(&gen->m_dead);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&gen->m_dead);
		return (0);
	}
}

int	check_win(t_gen *gen)
{
	pthread_mutex_lock(&gen->m_win);
	if (gen->win)
	{
		pthread_mutex_unlock(&gen->m_win);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&gen->m_win);
		return (0);
	}
}
