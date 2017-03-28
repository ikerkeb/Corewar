/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_cycles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewallner <ewallner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:16:11 by ewallner          #+#    #+#             */
/*   Updated: 2017/03/24 17:24:26 by nsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void ft_new_cycle(t_env *e, int *end)
{
	if(e->lives == 0)
		*end = 1;
	if(e->lives < NBR_LIVE)
		e->check += 1;
	if(e->check == MAX_CHECKS || e->lives >= NBR_LIVE)
	{
		e->cycles_to_die -= CYCLE_DELTA;
		if(e->cycles_to_die < 0)
			e->cycles_to_die = 0;
		e->lives = 0;
		e->check = 0;
	}
	e->lives = 0;
	e->cycle = 0;
}

void ft_adjust_cycle_macro(t_env *e, t_cursor *cursor, int *end)
{
	if(e->cycle == e->cycles_to_die)
		ft_new_cycle(e, end);
	else
		e->cycle += 1;
	cursor = cursor->next;
	ft_print_arena(e);
}

void ft_cycle_end_and_execute(t_env *e, t_cursor *cursor)
{
	void (*func_ptr[17])(t_env *e, t_cursor *cursor) =
	{ft_live, ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or,
	ft_xor, ft_zjmp, ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi,
	ft_lfork, ft_aff};

	if(cursor->cycle == 0)
	{
		if(ft_check_args(*e, *cursor))
			(*func_ptr[e->a[cursor->index].hex])(e, cursor);
		else
			ft_update_cursor(e, cursor, 1);
		cursor->running = 0;
	}
	else
		cursor->cycle -= 1;
}
