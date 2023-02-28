#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>

struct node
{
	int data;
	struct node *next;
};
int main(int argc, char const *argv[])
{
	/* code */
	int choice=1;
	struct node *head = NULL;
	struct node *current = NULL;
	struct node *new_node = NULL;
	//new_node = (struct node *)malloc(sizeof(struct node));
	while (choice)
	{
		printf("Enter 1 to add data, 0 to exit:");
		scanf("%d", &choice);
		if (choice == 1)
		{
			new_node = (struct node *)malloc(sizeof(struct node));
			printf("Enter data:");
			scanf("%d", &new_node->data);
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
	}
	current = head;
	while(current != NULL)
	{
		printf("%d", current->data);
		current = current->next;
	}
	return 0;
}
