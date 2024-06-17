#include <stdio.h>
#include "TourismRouterOrder.h"


int main()
{
	//set table of city price
	initCityPrice();
	printf("\n\n\n");

	printCityPrice();
	printf("\n\n\n");

	//creat two customer order list head1, head2

	printf("******************************\n");
	printf("Welcome My Tourist!!\n");
	printf("******************************\n");
	printf("\n\n\n");


//	printf("Please choose your city where you want to go\n");
	ORDEROFCITY* head1 = NULL; 
	ORDEROFCITY* head2 = NULL;
	
	printf("Creat customer1 order list!\n");
	head1 = makeCustomerOrder();
	printf("\n\n\n");
	printf("Customer1:\n");
	printCustomerOrder(head1);

	printf("\n\n\n");
	printf("Creat customer2 order list!\n");
	head2 = makeCustomerOrder();
	printf("\n\n\n");
	printf("Customer2:\n");
	printCustomerOrder(head2);

	//reset the price of city to verify the soundness of data structure
	//set Nanjing city price from 6 to 8
	setCityPrice(11, 8);

	printf("\n\n\n");
	printf("After city price is adjusted!\n");
	printf("Customer1:\n");
	printCustomerOrder(head1);

	printf("\n\n\n");
	printf("Customer2:\n");
	printCustomerOrder(head2);
	
	printf("\n\n\n");
	head1 = freeCustomerOrder(head1);
	printf("\n\n\n");
	head2 = freeCustomerOrder(head2);

	printf("\n\n\n");
	if (head1 == NULL) printf("head1 order is totally deleted!\n");
	if (head2 == NULL) printf("head2 order is totally deleted!\n");



	return 0;
}