/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:51:24 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/27 20:31:34 by yaaitmou         ###   ########.fr       */
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
    pthread_mutex_t fork;
    int     seat;
    int time_to_die;
    int time_to_sleep;
    int time_to_eat;
}            t_philos;

typedef struct s_status
{
    int status;
    t_philos *original;
    t_philos *philos;
}	           t_status;
# endif