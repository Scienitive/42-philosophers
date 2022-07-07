/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:23:20 by alyasar           #+#    #+#             */
/*   Updated: 2022/06/18 23:21:11 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	eat(t_philo *philo)
{
	while (1)
	{
		if (take_fork(philo, &philo->gen->fork[philo->left]))
			break ;
		usleep(100);
	}
	while (1)
	{
		if (take_fork(philo, &philo->gen->fork[philo->right]))
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&philo->gen->m_meal);
	write_status(philo->gen, philo->id, "is eating.");
	philo->last_meal = get_real_time();
	pthread_mutex_unlock(&philo->gen->m_meal);
	smart_sleep(philo->gen->eat_time, philo->gen);
	pthread_mutex_lock(&philo->gen->m_t_eat);
	philo->times_eat++;
	pthread_mutex_unlock(&philo->gen->m_t_eat);
	release_fork(&philo->gen->fork[philo->left]);
	release_fork(&philo->gen->fork[philo->right]);
}

void	*thread(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (!check_died(philo->gen))
	{
		eat(philo);
		if (check_win(philo->gen))
			break ;
		write_status(philo->gen, philo->id, "is sleeping.");
		smart_sleep(philo->gen->sleep_time, philo->gen);
		write_status(philo->gen, philo->id, "is thinking.");
	}
	return (NULL);
}

void	*thread_1(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	write_status(philo->gen, philo->id, "has taken a fork.");
	usleep(philo->gen->die_time * 1000);
	write_status(philo->gen, philo->id, "died.");
	return (NULL);
}
