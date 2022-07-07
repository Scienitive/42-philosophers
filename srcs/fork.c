/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:18:20 by alyasar           #+#    #+#             */
/*   Updated: 2022/06/18 15:18:33 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->taken = 0;
	fork->taken_by = 0;
	pthread_mutex_unlock(&fork->mutex);
}

int	take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (!fork->taken)
	{
		write_status(philo->gen, philo->id, "has taken a fork.");
		fork->taken = 1;
		fork->taken_by = philo->id;
	}
	if (fork->taken_by == philo->id)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}
