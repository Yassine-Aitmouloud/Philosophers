/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:24 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/06/17 15:47:50 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philos
{
    pthread_t phi_id;
    int     seat;
    long       last_eat;
}            t_philos;

typedef struct s_threads
{
    int someone_died;
    int numbers;
    int time_die;
    int eating;
    int sleeping;
    int status;
    pthread_mutex_t *forks;
    t_philos *original;
    t_philos *philos;
    long       start;
    pthread_mutex_t printing;
    pthread_mutex_t mute;
    pthread_mutex_t last_meal;
    pthread_mutex_t eating_mute;
    pthread_mutex_t try;
}	           t_threads;

t_threads	*g_thread(void);
void	print_action(t_philos *philo, char *msg);
void	printnaam(t_philos *philos);
void	printfker(t_philos *philos);
void	take_the_forks(t_philos *philos);
long	get_time_ms(void);
void	*monitor(void *arg);
void	*routine(void *arg);
void	setup_philos(pthread_t *mod);
# endif