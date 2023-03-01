#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>

typedef struct s_node
{
	int data;
	struct s_node *next;
} t_node;

void	ft_lstadd_front(t_node **lst, t_node *new)
{
	if (lst && new)
	{
//		(*new).next = *lst;
		new->next = *lst;
		*lst = new;
	}
}

int main(void)
{
	/* code */
	/*struct node
	{
		int data;
		struct node *next;
	};*/
	int choice=1;
	t_node *head = NULL;
	t_node *current = NULL;
	t_node *new_node = NULL;
	//new_node = (struct node *)malloc(sizeof(struct node));
	while (choice < 5)
	{
		new_node = (t_node *)malloc(sizeof(t_node));
		new_node->data = choice++;
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
	new_node->data = 555;
	ft_lstadd_front(&head, new_node);

	printf("Printing list after front insertion:\n");
	current = head;
	while(current != NULL)
	{
		printf("%d\n", current->data);
		current = current->next;
	}

	return 0;
}
