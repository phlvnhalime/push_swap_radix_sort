/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 01:26:17 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/17 20:03:27 by hpehliva         ###   ########.fr       */
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
    if(!(*str == '+' || *str == '-' || (*str >= '0' && *str <= '9')))
        return (1);
    if((*str == '+' || *str == '-') && !(str[1] >= '0' && str[1] <= '9'))
        return (1);
    while(*str)
    {
        if(!(*str >= '0' && *str <= '9'))
            return (1);
    }
    return (0);
}

int check_dub(t_stack *a, int size)
{
    while(a)
    {
        if(a->value == size)
            return (1);
    }
    return (0);
}

void add_to_stack(t_stack **stack, int size)
{
    t_stack *new_node;
    new_node = (t_stack *)malloc(sizeof(t_stack));
    new_node->value = size;
    new_node->next = NULL;
    if(!*stack)
    {
        *stack = new_node;
        return ;
    }
    new_node->next = *stack;
    *stack = new_node;
}

void handle_error()
{
    write(2, "Error: Invalid arguments\n", 25);
    exit(1);
}

long ft_atol(char *str)
{
    long num;
    int sign;
    int i;

    num = 0;
    sign = 1;
    i = 0;
    while(str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
        i++;
    if(str[i] == '+' || str[i] == '-')
    {
        if(str[i] == '-')
            sign = -1;
        i++;
    }
    while(str[i] && str[i] >= '0' && str[i] <= '9')
    {
        num = (num * 10) + (str[i] - '0');
        i++;
    }
    return (num * sign);
}

bool parse_and_init(t_stack **stack_a, int ac, char **av)
{
    int i;
    long num;

    i = 1;
    while(i < ac)
    {
        if(invalid_entries(av[i]))
            return (false);
        num = ft_atol(av[i]);
        if(num > INT_MAX || num < INT_MIN)
            return (false);
    }
    if(check_dub(*stack_a, (int)num))
        return (false);
    add_to_stack(stack_a, (int)num);
    i++;
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
    return (false);
}

int main(int ac, char **av)
{
    t_stack *stack_a;
    t_stack *stack_b;

    if(ac < 2)
        return (1);
    stack_a = NULL;
    stack_b = NULL;
    
    // Add conditions
    if(parse_and_init(&stack_a, ac, av) == false)
        handle_error();
    // check if the stack is ordered
    if(is_ordered(stack_a) == false)
        handle_error();

    // radix short algorithm
    radix_short(&stack_a, &stack_b);


    // free the stack
    free_stack(&stack_a);
    free_stack(&stack_b);

    return (0);
}