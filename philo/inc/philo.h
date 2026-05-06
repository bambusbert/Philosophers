/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:24:40 by slambert          #+#    #+#             */
/*   Updated: 2026/05/06 19:12:03 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_shit_to_free
{
	void					*shit;
	struct s_shit_to_free	*next;
}							t_shit_to_free;

typedef struct s_god_struct
{
	t_shit_to_free			*shit_list;
	int						num_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						no_o_t_e_p_m_eat;
	long long				start_time;
	pthread_t				*threads;
	// pthread_mutex_t			shit_mutex;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			*forks;
}							t_god_struct;

// struct for singular philosopher
typedef struct s_single_philo
{
	t_god_struct			*p_god;
	int						status;
	int						id;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						no_o_t_e_p_m_eat;
	int						time_since_last_meal;
	pthread_mutex_t			*fork_left;
	pthread_mutex_t			*fork_right;
	// info on left and right fork
}							t_single_philo;

enum						e_philo_status
{
	NOT_INIT = 0,
	INIT,
	SLEEPING,
	THINKING,
	FORK_TAKEN,
	HUNGRY,
	EATING,
	DEAD
};

enum
{
	RET_OK = 0,
	ERROR_SOFT = -1,
	ERROR_HARD = -2
};

// debug.c
void						print_p_init(t_god_struct *p_init);
void						print_philo_forks(t_single_philo *philo);
void						say_hello(t_single_philo *philo);

// init.c
t_god_struct				*create_god_struct(char **argv);
t_single_philo				*init_philo_struct(t_god_struct *p_god, int i);
void						init_mutexes(t_god_struct *p_god);

// xyxyxyxyx
int							ft_atoi(char *arg);
void						*ft_calloc(size_t nmemb, size_t size);
long long					return_time_in_ms(void);
long long					return_delta_time(t_god_struct *p_god);

// threads.c
int							create_philo_threads(t_god_struct *p_god);
void						wait_for_philo_threads(t_god_struct *p_god);

// routine.c
void						*philo_routine(void *arg);

// print_slave.c
void						print_status_fork(t_god_struct *p_god,
								long long timestamp, int id);
void						print_status_eating(t_god_struct *p_god,
								long long timestamp, int id);
void						print_status_sleeping(t_god_struct *p_god,
								long long timestamp, int id);
void						print_status_thinking(t_god_struct *p_god,
								long long timestamp, int id);
void						print_status_died(t_god_struct *p_god,
								long long timestamp, int id);

// cleanup.c
void						cleanup_everything(t_god_struct *p_god);
int							add_to_shit_list(t_god_struct *p_god,
								t_shit_to_free **shit_list, void *elem);
void						destroy_mutexes(t_god_struct *p_god);

#endif