/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:25:03 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/19 14:25:03 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/push_swap.h"

/*
	This function check these parameters and initialize the stack
	1-) change the arguments to integers
	2-) check for those who exceed their integer limit
	3-) check the dublicates
	4-) if there is mistakes, returns with error message
	5-) constructs stack a with valid arguments.
*/

int	invalid_entries(char *str)
{
	int	i;

	if (!str || !str[0])
		return (1);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	check_dub(t_stack *a, int value)
{
	while (a)
	{
		if (a->value == value)
			return (1);
		a = a->next;
	}
	return (0);
}

void	add_to_stack(t_stack **stack, int value)
{
	t_stack	*new_node;
	t_stack	*tail;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		exit(1);
	new_node->value = value;
	new_node->index = -1;
	new_node->keep = false;
	new_node->pos = 0;
	new_node->target_pos = 0;
	new_node->cost_a = 0;
	new_node->cost_b = 0;
	new_node->before = NULL;
	new_node->next = NULL;
	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	tail = get_tail_node(*stack);
	tail->next = new_node;
	new_node->before = tail;
}

void	handle_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

bool	is_ordered(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

