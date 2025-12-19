/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 01:26:17 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/17 22:08:42 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/push_swap.h"

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size;

	if (ac < 2)
		return (1);
	stack_a = NULL;
	stack_b = NULL;
	if (parse_and_init(&stack_a, ac, av) == false)
		handle_error();
	if (is_ordered(stack_a))
	{
		free_stack(&stack_a);
		free_stack(&stack_b);
		return (0);
	}
	size = count_elements(stack_a);
	if (size <= 5)
		small_sort(&stack_a, &stack_b);
	else
		sorting_advanced(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
