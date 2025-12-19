/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_advanced.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 23:00:00 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/19 15:30:24 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/push_swap.h"

static void	target_conditions(t_stack *curr, int b_index, int *best_index,
		int *best_pos)
{
	if (curr->index > b_index && curr->index < *best_index)
	{
		*best_index = curr->index;
		*best_pos = curr->pos;
	}
}

/*
	Target in A for node b:
	- smallest index in A that is > b->index
	- if none, wrap to smallest index in A
*/
static int	get_target_pos(t_stack *a, int b_index)
{
	t_stack	*curr;
	int		best_index;
	int		best_pos;
	int		min_pos;
	int		min_index;

	best_index = INT_MAX;
	best_pos = 0;
	min_index = INT_MAX;
	min_pos = 0;
	curr = a;
	while (curr)
	{
		if (curr->index < min_index)
		{
			min_index = curr->index;
			min_pos = curr->pos;
		}
		target_conditions(curr, b_index, &best_index, &best_pos);
		curr = curr->next;
	}
	if (best_index != INT_MAX)
		return (best_pos);
	return (min_pos);
}

static void	set_targets_and_costs(t_stack *a, t_stack *b)
{
	int		len_a;
	int		len_b;
	t_stack	*cur_b;

	len_a = count_elements(a);
	len_b = count_elements(b);
	set_positions(a);
	set_positions(b);
	cur_b = b;
	while (cur_b)
	{
		cur_b->target_pos = get_target_pos(a, cur_b->index);
		if (cur_b->pos <= len_b / 2)
			cur_b->cost_b = cur_b->pos;
		else
			cur_b->cost_b = -(len_b - cur_b->pos);
		if (cur_b->target_pos <= len_a / 2)
			cur_b->cost_a = cur_b->target_pos;
		else
			cur_b->cost_a = -(len_a - cur_b->target_pos);
		cur_b = cur_b->next;
	}
}

void	sorting_advanced(t_stack **a, t_stack **b)
{
	if (!a || !*a)
		return ;
	assign_indicators(a);
	mark_lis_keep(*a);
	zone_push_to_b(a, b);
	while (*b)
	{
		set_targets_and_costs(*a, *b);
		move_cheapest_to_a(a, b);
	}
	final_rotate_to_min(a);
}
