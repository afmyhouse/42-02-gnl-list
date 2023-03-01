#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>

typedef struct s_node
{
	int data;
	struct s_node *next;
} t_node;

void	ft_lstadd_n(t_node **lst, t_node *new, int n)
{
	t_node *current;
	int i = 1;
	current = *lst;
	
	if ((n == 1) && lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
	else if ((n > 1) && lst && new)
	{
		while (current->next != NULL && ++i < n)
			current = current->next;
		new->next = current->next;
		current->next = new;
	}
	else if ((n == 0) && lst && new)
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
		new->next = NULL;
	}	
}

int main(void)
{
	int choice=1;
	int n = 0;
	t_node *head, *current, *new_node = NULL;

	while (choice < 5)
	{
		new_node = (t_node *)malloc(sizeof(t_node));
		new_node->data = 10 + choice++;
		new_node->next = NULL;
		if(head == NULL)
		{
			head = new_node;
			current = head;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}
	}

	printf("Printing list before front insertion:\n");
	current = head;
	while(current != NULL)
	{
		printf("%d\n", current->data);
		current = current->next;
	}
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->next = NULL;
	new_node->data = 1;
	ft_lstadd_n(&head, new_node, 1);

	printf("Printing list after front insertion:\n");
	current = head;
	while(current != NULL)
	{
		printf("%d\n", current->data);
		current = current->next;
	}

	while (1)
	{new_node = (t_node *)malloc(sizeof(t_node));
	new_node->next = NULL;
	printf("Enter the position to insert the new node 1 to Nth or 0 (last): ");
	scanf("%d", &n);
	new_node->data = n;
	ft_lstadd_n(&head, new_node, n);
	printf("Printing list after insertion at %dth position:\n", n);
	current = head;
	while(current != NULL)
	{
		printf("%d\n", current->data);
		current = current->next;
	}
	}
	return 0;
}
