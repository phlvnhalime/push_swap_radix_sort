#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
    int value;
    struct s_stack *next;
    struct s_stack *before;
} t_stack;

// Utils functions
t_stack	*get_tail_node(t_stack *stack);
int		count_nodes(t_stack *stack);

// Push operators
void pa(t_stack **a, t_stack **b, bool check);
void pb(t_stack **b, t_stack **a, bool check);
void rra(t_stack **a, bool check);
void rrb(t_stack **b, bool check);
void rrr(t_stack **a, t_stack **b, bool check);
void sa(t_stack **a, bool check);
void sb(t_stack **b, bool check);
void ss(t_stack **a, t_stack **b, bool check);



#endif