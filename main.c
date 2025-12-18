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

#include "push_swap.h"


/*
    This function check these parameters and initialize the stack
    1-) change the arguments to integers
    2-) check for those who exceed their integer limit
    3-) check the dublicates
    4-) if there is mistakes, returns with error message
    5-) constructs stack a with valid arguments.
*/

int invalid_entries(char *str)
{
    int i;

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

int check_dub(t_stack *a, int value)
{
    while(a)
    {
        if(a->value == value)
            return (1);
        a = a->next;
    }
    return (0);
}

void add_to_stack(t_stack **stack, int value)
{
    t_stack *new_node;
    t_stack *tail;

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

void handle_error()
{
    write(2, "Error: Invalid arguments\n", 25);
    exit(1);
}

long	ft_atol(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

bool parse_and_init(t_stack **stack_a, int ac, char **av)
{
    int i;
    int j;
    long num;
    char **parts;

    i = 1;
    while(i < ac)
    {
        parts = NULL;
        if (!av[i] || !av[i][0])
            return (false);
        parts = ft_split(av[i], ' ');
        if (!parts || !parts[0])
        {
            ft_free_split(parts);
            return (false);
        }
        j = 0;
        while (parts[j])
        {
            if(invalid_entries(parts[j]))
            {
                ft_free_split(parts);
                return (false);
            }
            num = ft_atol(parts[j]);
            if(num > INT_MAX || num < INT_MIN)
            {
                ft_free_split(parts);
                return (false);
            }
            if(check_dub(*stack_a, (int)num))
            {
                ft_free_split(parts);
                return (false);
            }
            add_to_stack(stack_a, (int)num);
            j++;
        }
        ft_free_split(parts);
        i++;
    }
    return (true);
}

bool is_ordered(t_stack *stack)
{
    while(stack && stack->next)
    {
        if(stack->value > stack->next->value)
            return (false);
        stack = stack->next;
    }
    return (true);
}

int main(int ac, char **av)
{
    t_stack *stack_a;
    t_stack *stack_b;
    int     size;

    if(ac < 2)
        return (1);
    stack_a = NULL;
    stack_b = NULL;
    
    // Add conditions
    if(parse_and_init(&stack_a, ac, av) == false)
        handle_error();
    // check if the stack is ordered
    if(is_ordered(stack_a))
    {
        free_stack(&stack_a);
        free_stack(&stack_b);
        return (0);
    }

    size = count_nodes(stack_a);
    if (size <= 5)
        small_sort(&stack_a, &stack_b);
    else
        sorting_advanced(&stack_a, &stack_b);


    // free the stack
    free_stack(&stack_a);
    free_stack(&stack_b);

    return (0);
}