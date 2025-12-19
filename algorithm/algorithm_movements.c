/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_movements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:13:18 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/19 11:14:59 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/push_swap.h"


t_stack	*pick_cheapest(t_stack *b)
{
	t_stack	*best;
	int		best_cost;
	int		best_common;
	int		c;
	int		common;

	best = b;
	best_cost = move_cost(b);
	best_common = common_rot_part(b);
	while (b)
	{
		c = move_cost(b);
		common = common_rot_part(b);
		if (c < best_cost || (c == best_cost && common > best_common))
		{
			best = b;
			best_cost = c;
			best_common = common;
		}
		b = b->next;
	}
	return (best);
}

void	move_cheapest_to_a(t_stack **a, t_stack **b)
{
	t_stack	*best;
	int		ca;
	int		cb;

	best = pick_cheapest(*b);
	ca = best->cost_a;
	cb = best->cost_b;
	rotate_both_cost(a, b, &ca, &cb);
	rotate_a_cost(a, &ca);
	rotate_b_cost(b, &cb);
	pa(a, b, false);
}

void	final_rotate_to_min(t_stack **a)
{
	int	len;
	int	pos;

	len = count_elements(*a);
	if (len <= 1)
		return ;
	pos = find_min_index_pos(*a);
	if (pos <= len / 2)
	{
		while (pos-- > 0)
			ra(a, false);
	}
	else
	{
		while (pos++ < len)
			rra(a, false);
	}
}