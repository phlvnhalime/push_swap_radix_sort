/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_advanced.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 23:00:00 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/19 09:28:02 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	abs_i(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

static void	set_positions(t_stack *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		stack->pos = i;
		i++;
		stack = stack->next;
	}
}

static void	clear_keep(t_stack *a)
{
	while (a)
	{
		a->keep = false;
		a = a->next;
	}
}

/*
	Compute LIS on `index` (rank) in current stack order.
	Mark LIS nodes as keep=true (never pushed to B).
*/
static void	mark_lis_keep(t_stack *a)
{
	int		n;
	int		i;
	int		j;
	int		best_len;
	int		best_end;
	int		*lis_len;
	int		*lis_prev;
	t_stack	**nodes;

	clear_keep(a);
	n = count_elements(a);
	if (n <= 0)
		return ;
	nodes = (t_stack **)malloc(sizeof(t_stack *) * n);
	lis_len = (int *)malloc(sizeof(int) * n);
	lis_prev = (int *)malloc(sizeof(int) * n);
	if (!nodes || !lis_len || !lis_prev)
		exit(1);
	i = 0;
	/*
		nodes[0] = value 3 (index2)
		nodes[1] = value 1 (index0)
		nodes[2] = value 6 (index5)
		nodes[3] = value 2 (index1)
		nodes[4] = value 5 (index4)
		nodes[5] = value 4 (index3)
	*/
	while (a)
	{
		nodes[i++] = a;
		a = a->next;
	}
	i = 0;
	while (i < n)
	{
		lis_len[i] = 1;
		lis_prev[i] = -1;
		j = 0;
		while (j < i)
		{
			if (nodes[j]->index < nodes[i]->index && lis_len[j] + 1 > lis_len[i])
			{
				lis_len[i] = lis_len[j] + 1;
				lis_prev[i] = j;
			}
			j++;
		}
		i++;
	}
	best_len = 0;
	best_end = 0;
	i = 0;
	while (i < n)
	{
		if (lis_len[i] > best_len)
		{
			best_len = lis_len[i];
			best_end = i;
		}
		i++;
	}
	i = best_end;
	while (i != -1)
	{
		nodes[i]->keep = true;
		i = lis_prev[i];
	}
	free(nodes);
	free(lis_len);
	free(lis_prev);
}

/*
	Zone push strategy:
	- keep nodes stay in A
	- others go to B
	- if pushed element is > median => rb (send to bottom)
*/
static void	zone_push_to_b(t_stack **a, t_stack **b)
{
	int	size;
	int	median;
	int	i;

	size = count_elements(*a);
	median = size / 3;
	i = 0;
	while (i < size)
	{
		if ((*a)->keep)
			ra(a, false);
		else
		{
			pb(b, a, false);
			if (*b && (*b)->index > median)
				rb(b, false);
		}
		i++;
	}
}

static int	find_min_index_pos(t_stack *a)
{
	int		min_i;
	int		min_pos;
	t_stack	*cur;

	if (!a)
		return (0);
	set_positions(a);
	min_i = a->index;
	min_pos = a->pos;
	cur = a;
	while (cur)
	{
		if (cur->index < min_i)
		{
			min_i = cur->index;
			min_pos = cur->pos;
		}
		cur = cur->next;
	}
	return (min_pos);
}

static void	final_rotate_to_min(t_stack **a)
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

/*
	Target in A for node b:
	- smallest index in A that is > b->index
	- if none, wrap to smallest index in A
*/
static int	get_target_pos(t_stack *a, int b_index)
{
	t_stack	*cur;
	int		best_index;
	int		best_pos;
	int		min_index;
	int		min_pos;

	best_index = INT_MAX;
	best_pos = 0;
	min_index = INT_MAX;
	min_pos = 0;
	cur = a;
	while (cur)
	{
		if (cur->index < min_index)
		{
			min_index = cur->index;
			min_pos = cur->pos;
		}
		if (cur->index > b_index && cur->index < best_index)
		{
			best_index = cur->index;
			best_pos = cur->pos;
		}
		cur = cur->next;
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

/*
	Cost model maximizing rr/rrr:
	- same sign costs => can merge rotations => total = max(|a|,|b|)
	- different sign => total = |a| + |b|
	Tie-break: prefer larger common rotation part (more rr/rrr).
*/
static int	move_cost(t_stack *node)
{
	if ((node->cost_a >= 0 && node->cost_b >= 0)
		|| (node->cost_a <= 0 && node->cost_b <= 0))
	{
		if (abs_i(node->cost_a) > abs_i(node->cost_b))
			return (abs_i(node->cost_a));
		return (abs_i(node->cost_b));
	}
	return (abs_i(node->cost_a) + abs_i(node->cost_b));
}

static int	common_rot_part(t_stack *node)
{
	int	a;
	int	b;

	if (!((node->cost_a >= 0 && node->cost_b >= 0)
			|| (node->cost_a <= 0 && node->cost_b <= 0)))
		return (0);
	a = abs_i(node->cost_a);
	b = abs_i(node->cost_b);
	if (a < b)
		return (a);
	return (b);
}

static t_stack	*pick_cheapest(t_stack *b)
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

static void	rotate_a_cost(t_stack **a, int *cost)
{
	while (*cost > 0)
	{
		ra(a, false);
		(*cost)--;
	}
	while (*cost < 0)
	{
		rra(a, false);
		(*cost)++;
	}
}

static void	rotate_b_cost(t_stack **b, int *cost)
{
	while (*cost > 0)
	{
		rb(b, false);
		(*cost)--;
	}
	while (*cost < 0)
	{
		rrb(b, false);
		(*cost)++;
	}
}

static void	rotate_both_cost(t_stack **a, t_stack **b, int *ca, int *cb)
{
	while (*ca > 0 && *cb > 0)
	{
		rr(a, b, false);
		(*ca)--;
		(*cb)--;
	}
	while (*ca < 0 && *cb < 0)
	{
		rrr(a, b, false);
		(*ca)++;
		(*cb)++;
	}
}

static void	move_cheapest_to_a(t_stack **a, t_stack **b)
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

