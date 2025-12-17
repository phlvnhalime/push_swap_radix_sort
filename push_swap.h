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
    int index;
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
void ra(t_stack **a, bool check);
void rb(t_stack **b, bool check);
void rr(t_stack **a, t_stack **b, bool check);

// Radix short algorithm
void radix_short(t_stack **a, t_stack **b);
void assign_indicators(t_stack **a);
t_stack *find_smallest_element(t_stack *a);

// Parse and initialize and error handling
bool parse_and_init(t_stack **stack_a, int ac, char **av);
int invalid_entries(char *str);
bool is_ordered(t_stack *stack);
int check_dub(t_stack *a, int size);
void add_to_stack(t_stack **stack, int size);
void handle_error();

// Utils functions
long ft_atol(char *str);
void free_stack(t_stack **stack);



#endif