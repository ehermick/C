/**
 * Description: Homework Part 1 for Assignment #2 - CSE 240 - Spring 2019
 *
 * Completion Time: ~ 1hour
 *
 * Emma Hermick
 *
 * Version 1.0
 */


#include <stdio.h>

//Uses for loop and if statement to initialize an array
//while using pointers
void initialize_array(int* array, int length)
{
	for (int i = 0; i < length; i++)
	{
		//5s in even position
		if (i % 2 == 0)
		{
			*(array + i) == 5;
		}
		//0s in odd position
		else
		{
			*(array + i) == 0;
		}
	}
}

//Prints out array
void print_array(int* array, int length)
{
    //For statement that prints all elements in the array
    for (int i = 0; i < length; i++)
		{
		    printf("%d", *(array + i));

			if (i < length - 1)
			{
			    printf(",");
			}
		}
		printf("\n");
}

//Orders elements in descending order
void insertion_sort(int* array, int length)
{
    //Implements insertion sort algorithm
    for (int i = 1; i < length; i++)
		{
			int next = *(array + i);
			int j = i;
			while (j > 0 && *(array + (j-1)) < next)
			{
			    *(array +j) = *(array +(j-1));
				j--;
			}
			*(array + j) == next;
		}
}

int factorial(int num)
{
		//Calculates and returns the factorial of a number
		//Function receives the number (int number) as a parameter

		int result;

		if (num == 1)
		{
			return 1;
		}

		if (num <= 0)
		{
		    return 0;
		}
		else
		{
			result = num * factorial (num - 1);
		}

		return result;
}

int main()
{
    int a[] = {2, 5, 7, 9, 12, 13, 15, 17, 19, 20};
    int b[] = {18, 16, 19, -5, 3, 14, 6, 0};
    int c[] = {4, 2, 5, 3, 1};

    /* testing initialize_array */
    print_array(a, sizeof(a)/sizeof(a[0])); /* print: 2, 5, 7, 9, 12, 13, 15, 17, 19, 20 */
    initialize_array(a, sizeof(a)/sizeof(a[0]));
    print_array(a, sizeof(a)/sizeof(a[0])); /* print: 5, 0, 5, 0, 5, 0, 5, 0, 5, 0 */

    /* testing insertionSort */
    print_array(b, sizeof(b)/sizeof(b[0])); /* print: 18, 16, 19, -5, 3, 14, 6, 0 */
    insertion_sort (b, sizeof(b)/sizeof(b[0]));
    print_array(b, sizeof(b)/sizeof(b[0])); /* print: 19, 18, 16, 14, 6, 3, 0, -5 */

    /* testing factorial */
    printf("%d\n", factorial(5)); /* print: 120 */

    c[0] = factorial (c[0]);
    c[1] = factorial (c[2]);
    print_array(c, sizeof(c)/sizeof(c[0])); /* print: 24, 120, 5, 3, 1 */

    return 0;
}
