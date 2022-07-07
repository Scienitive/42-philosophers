/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 21:12:29 by alyasar           #+#    #+#             */
/*   Updated: 2022/06/18 15:26:34 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					taken;
	int					taken_by;
}						t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					times_eat;
	int					left;
	int					right;
	long int			last_meal;
	struct s_gen		*gen;
}						t_philo;

typedef struct s_gen
{
	int					philo_count;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					max_eat;
	int					died;
	int					win;
	long int			start_time;
	pthread_mutex_t		m_meal;
	pthread_mutex_t		m_dead;
	pthread_mutex_t		m_win;
	pthread_mutex_t		m_write;
	pthread_mutex_t		m_fork;
	pthread_mutex_t		m_t_eat;
	t_philo				*philo;
	t_fork				*fork;
}						t_gen;

int			ft_atoi(const char *str);
int			print_error(char *str);
int			initialize(t_gen *gen, int argc, char **argv);
void		write_status(t_gen *gen, int id, char *str);
long int	get_real_time(void);
void		smart_sleep(long int time, t_gen *gen);
void		threading(t_gen *gen);
int			check_died(t_gen *gen);
int			check_win(t_gen *gen);
int			is_reached_max_eat(t_philo *philo);
void		*thread(void *input);
void		*thread_1(void *input);
void		release_fork(t_fork *fork);
int			take_fork(t_philo *philo, t_fork *fork);

#endif