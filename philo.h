/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:24 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/22 10:08:58 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philos
{
	pthread_t		phi_id;
	int				seat;
	long			last_eat;
	int				meals_eaten;
	int				checked;
}					t_philos;

typedef struct s_threads
{
	int				someone_died;
	int				numbers;
	int				time_die;
	int				eating;
	int				sleeping;
	int				must_eat;
	int				status;
	pthread_mutex_t	*forks;
	t_philos		*philos;
	long			start;
	pthread_mutex_t	printing;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	eating_count;
	pthread_mutex_t	death;
	int				even_odd;
	int				philosophers_done;

}					t_threads;

t_threads			*g_thread(void);
void				print_action(t_philos *philo, char *msg);
void				printnaam(t_philos *philos);
void				printfker(t_philos *philos);
void				take_the_forks(t_philos *philos);
long				get_time_ms(void);
void				*monitor(void *arg);
void				*routine(void *arg);
void				check_avs(char **av);
long				get_last_meal(int i);
int					check_the_philos(void);
void				unlock_forks(int right, int left);
void				lock_forks(int right, int left, t_philos *philos);
int					is_died(void);
void				use_usleep(long duration);
#endif