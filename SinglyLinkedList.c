#include <stdio.h>
#include <stdlib.h>

// Define the Singly Linked List Structure

typedef struct node {
	int			data;
	struct node	*next_link;
} node;

// Colors for printf
void red ();
void green ();
void reset ();

//* ALL THE FOLLOWING FUNCTIONS ARE EXPLAINED BELOW THE MAIN FUNCTION 

void	add_to_beg(node **head, int data);
void	add_to_end(node **head, int data);
void	add_to_mid(node **head, int position, int data);
void	del_beg(node **head);
void	del_end(node **head);
void	del_if(node **head, int data_ref);
void	print_list(node *list);
int		list_len (node *list);
void	clear_list (node **head);

int	main (void)
{
	// Create list
	node	*head;
	int		list_size;

	// Initialize List
	head = NULL;

	// Function to add node to BEGGINING of the list //* Time Complexity : O(1)
	add_to_beg(&head, 75);

	// Function to add node to the MIDLE of the list //* Time Complexity : O(n)
	add_to_mid(&head, 3, 150);

	// Function to add node to END of the list //* Time Complexity : O(n)
	add_to_end(&head, 100);


	// Function to print list before deletion //* Time Complexity : O(n)
	green ();
	list_size = list_len(head);
	printf("List before deleting nodes:\n");
	printf("\tSize: %i\n", list_size);
	printf("\tList:\n");
	print_list(head);

	// Function to delete node from BEGGINING of the list //* Time Complexity : O(1)
	del_beg(&head);

	// Function to delete node IF DATA MATCHES DATA_REF from the list //* Time Complexity : O(n)
	del_if(&head, 150);

	// Function to delete node from END of the list //* Time Complexity : O(n)
	del_end(&head);

	// Function to print list after deletion //* Time Complexity : O(n)
	red();
	list_size = list_len(head);
	printf("List after deleting nodes:\n");
	printf("\tSize: %i\n", list_size);
	printf("\tList:\n");
	print_list(head);

	// Function to clear the list //* Time Complexity : O(n)
	clear_list(&head);

	// Function to print list after clearing the list //* Time Complexity : O(n)
	red();
	list_size = list_len(head);
	printf("List after clearing the list:\n");
	printf("\tSize: %i\n", list_size);
	printf("\tList:\n");
	print_list(head);

}

int		list_len (node *list)
{
	node	*iter; // Pointer to iterate the list
	int		counter; // Pointer to keep track of number of elements in the list

	iter = list; // Assign out iterator to the head / beggining of the list
	counter = 0;
	while (iter != NULL) // Till we reach the end of the list
	{
		// Go through every single node of the list and increment the counter
		counter++;
		iter = iter -> next_link;
	}
	return (counter); // Return the size of the list
}

void	print_list(node *list)
{
	node	*iter; // Pointer to iterate the list

	iter = list; // Assign out iterator to the head / beggining of the list
	while (iter != NULL) // Till we reach the end of the list
	{
		printf ("\t%i\n", iter -> data); // Print data from current node
		iter = iter -> next_link; // Go to the next node
	}
}

void	add_to_beg(node **head, int data)
{
	node	*new; 

	new = (node *)malloc(sizeof(node)); // Allocate memory for new node 
	if (!new) // Always use protection!
		return ;
	new -> data = data; // Assign the data value to the node
	new -> next_link = *head; // Point to the previous 1st node of the list
	*head = new; // Assign the Head / Root / Beggining to the new node
}

void	add_to_end(node **head, int data)
{
	node	*new;
	node	*tmp;

	new = (node *)malloc(sizeof(node)); // Allocate memory for new node 
	if (!new) // Always use protection!
		return ;
	new -> data = data; // Assign the data value to the node
	new -> next_link = NULL; // Assign the link of the new node to NULL because this will be the last node of the list.
	if (*head == NULL) // If the list was empty, then simply set the beggining to be our new node
		*head = new;
	else // If the list was not empty
	{
		tmp = *head; // Assign a temporary variable (Works as iterator) to the beggining of the list
		while (tmp -> next_link != NULL) // Travel to the last node of the list AND STAY AT THE LAST NODE
			tmp = tmp -> next_link;
		// This loop will end when our last node link is point to null.
		tmp -> next_link = new; // We can safely assign our last node link which was point to NULL, to the new node
	}
}

void	add_to_mid(node **head, int position, int data)
{
	node	*previous; // We're going to use this variable to keep track of the node before the insertion
	node	*next; // We're going to use this variable to keep track of the node after the insertion
	node	*new;
	int		i; // We're using i to know how many postions we are advancing 

	if (position > (list_len(*head) + 1) || position <= 0) // Protect for non valid position
	{
		printf ("You didn't insert a valid position for your add_to_mid() function.\n");
		return ;
	}
	if (position == (list_len(*head) + 1)) // If the position is the size of the list + 1 it means that the user is trying to inser a node at the end of the list so we can just use our previous function
		add_to_end(head, data);
	else if (position == 1) // If the position is the first position it means that the user is trying to inser a node at the beggining of the list so we can just use our previous function
		add_to_beg(head, data);
	else // Position valid for mid list insertion
	{
		new = (node *)malloc(sizeof(node)); // Allocate memory for new node 
		if (!new) // Always use Protection!
			return ;
		new -> data = data; // Assign the data value to the node
		previous = *head; // First We're using this as an iterator
		i = 0;
		while (i++ < (position - 2)) // Go to the node before the insertion
			previous = previous -> next_link;
		next = previous -> next_link; // Keep track of the address of the node that will stay after the insertion 
		previous -> next_link = new; // Safely assign the previous node link to the new node
		new -> next_link = next; // Assign the new node link to the address of the next node (that we saved 2 lines before)
	}
}

void	del_beg(node **head)
{
	node	*tmp;

	if (head == NULL || *head == NULL) // If list is empty then there's nothing to do here
		return;
	tmp = *head; // Save the current first of the list on a temporary variable (to safely free later)
	*head = tmp -> next_link; // Assign the new beggining of the list to the 2nd node of the list
	tmp -> next_link = NULL; // Assign the link of the node that will be freed to NULL (just to be more explicit)
	free (tmp); // Free the old 1st node of the list
	tmp = NULL; // Assign temp to NULL because we're good citizens
}

void	del_end(node **head)
{
	node	*current;
	node	*previous;

	// Three case scenario 
	//* 1 the list is empty
	if (head == NULL || *head == NULL) // If list is empty then there's nothing to do here
		return;
	//*2  The list only has 1 node
	previous = *head;
	if (previous -> next_link == NULL) // If the list only has one node, we can just free that node and initialize our head / root / beggining of the list to NULL
	{
		free (previous); // Free the node
		*head = NULL; // Initialize list to NULL
	}
	//* The list has more than 1 node
	while (previous -> next_link != NULL) // Travel through the list until we make the deletion
	{
		current = previous -> next_link; // Save the current node, which will be the one after the previous :o
		if (current -> next_link == NULL) // If the current node it's the last node
		{
			free (current); // Free the last node
			current = NULL; //  Assign current to NULL because we're good citizens
			previous -> next_link = NULL; // Set the 2nd to last node link to NULL (Now it will be the last node)
		}
		else
			previous = previous -> next_link; // Keep iterating through the list
	}
}

void	del_if(node **head, int data_ref)
{
	node	*previous; // To keep track of the previous node before deletion
	node	*current; // To keep track of the node that will be deleted

	if (head == NULL || *head ==  NULL) // If list is empty then there's nothing to do here
		return ;
	
	previous = *head;
	if ((previous -> next_link == NULL) && (previous -> data == data_ref)) // Check if the list only has 1 node
	{
		free (previous); // free the first node
		*head = NULL; // Initialize head to NULL
		return ; // Return
	}
	if (previous -> data == data_ref)
	{
		del_beg(head);
		return ;
	}
	while (previous -> next_link != NULL) // Keep track of the previous node & Iterate and stay in the last node because inside the loop I always use current to check if there's a node after the previous
	{
		current = previous -> next_link; // Keep track of the current node
		if (current -> data == data_ref) // If the data from the current node matches the data_ref 
		{
			previous -> next_link = current -> next_link; // Assign the link of the previous link to the next link of the current node
			free(current); // Now we can safely free the current node
			current = NULL; //  Assign current to NULL because we're good citizens
		}
		else
			previous = previous -> next_link; // Keep iterating through the list
	}
}

void	clear_list (node **head)
{
	node	*iter; // Using it to iterate through the list
	node	*next; // Using it to keep track of the next node

	if (head == NULL || *head == NULL) // Check if there's anything to clear
		return ;
	iter = *head; // Assign the iterator to the beggining of the list
	while (iter != NULL) // Loop till the end of the list
	{
		next = iter -> next_link; // Keep track of the next node, this is crucial because without this if we free'd the node, we'd lose track of the rest of out list
		free (iter); // Free the current node
		iter = next; // Go to the next node using the previous saved address
	}
	*head = NULL; // Set the list head to NULL after clearing it
}

// Printf Colours
void red () {
  printf("\033[1;31m");
}

void green () {   
  printf("\033[0;32m");
}

void reset () {
  printf("\033[0m");
}

