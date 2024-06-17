#pragma warning(disable : 4996)

#include <stdio.h>
#include <malloc.h>
#include "TourismRouterOrder.h"

const CITY city1 = SHA;
const CITY city2 = NKG;
const int NUM = 11;


//printf("%d\n", city2 - city1+1);

PRICEOFCITY priceTable[city2 - city1+1];  //11 city
const char* citiesname[NUM] = { "SHANGHAI", "BEIJING","SHENZHEN","GUANGZHOU","TIANJIN","CHONGQING","SUZHOU","CHENGDU","WUHAN","HANGZHOU","NANJING" };


void initCityPrice()
{
	printf("input city price:\n");
	for (CITY c = SHA; c <= NKG; c = (CITY)(c + 1))
	{
		//priceTable->city = c;
		priceTable[c].city = c;
		PRICE p;
	//	printf("input price:\n");
		scanf("%d", &p);
		//priceTable->price = p;
		priceTable[c].price = p;
	}
	
	printf("City Price is initialized!\n");
}

void printCity(CITY city)
{
	switch(city)
	{
		case SHA: printf("SHANGHAI"); break;
		case PEK: printf("BEIJING"); break;
		case SZX: printf("SHENZHEN"); break;
		case CAN: printf("GUANGZHOU"); break;
		case TSN: printf("TIANJIN"); break;
		case CKG: printf("CHONGQING"); break;
		case SZU: printf("SUZHOU"); break;
		case CTU: printf("CHENGDU"); break;
		case WUH: printf("WUHAN"); break;
		case HGH: printf("HANGZHOU"); break;
		case NKG: printf("NANJING"); break;
	}

}
/*
 * print price of City
*/
void printCityPrice()
{
	for (CITY c = SHA; c <= NKG; c = (CITY)(c + 1))
	{
		printf("The city is ");
		printCity(priceTable[c].city);
		printf("\n");
		printf("The price is %d\n", priceTable[c].price);
	}
}

ORDEROFCITY* makeCustomerOrder()
{
	int citycode;
	printf("Please choose your city where you want to go\n");
	printf("1-SHANGHAI, 2-BEIJING, 3-SHENZHEN, 4-GUANGZHOU, 5-TIANJIN, 6-CHONGQING, 7-SUZHOU, 8-CHENGDU, 9-WUHAN, 10-HANGZHOU, 11-NANJING\n");
	printf("Notice: 0-exit!\n");

	scanf("%d", &citycode);
	
	ORDEROFCITY* h = NULL, * t = NULL;
	ORDEROFCITY* p = NULL, *q = NULL;


	while (citycode != 0)
	{
		p=(ORDEROFCITY*)malloc(sizeof(ORDEROFCITY));
		
		switch (citycode)
		{
		case 1: p->pOfPriceOfCity = priceTable + 0; break;
		case 2: p->pOfPriceOfCity = priceTable + 1; break;
		case 3: p->pOfPriceOfCity = priceTable + 2; break;
		case 4: p->pOfPriceOfCity = priceTable + 3; break;
		case 5: p->pOfPriceOfCity = priceTable + 4; break;
		case 6: p->pOfPriceOfCity = priceTable + 5; break;
		case 7: p->pOfPriceOfCity = priceTable + 6; break;
		case 8: p->pOfPriceOfCity = priceTable + 7; break;
		case 9: p->pOfPriceOfCity = priceTable + 8; break;
		case 10: p->pOfPriceOfCity = priceTable + 9; break;
		case 11: p->pOfPriceOfCity = priceTable + 10; break;
		default: printf("Wrong input city!\n");
		}
		p->next = NULL;

		//insert into the tail of link list
		if (h == NULL)
		{
			h = p; t = p;
		}
		else
		{
			t->next = p;
			t = p;
		}
		scanf("%d", &citycode);
	}
	
	return h;
}

int printCustomerOrder(ORDEROFCITY* h)
{
	if (h == NULL)
	{
		printf("The router of your order is NULL!\n");
		return -1;
	}
	printf("The router of your order is\n");
	ORDEROFCITY* p = h;
	int sumPrice = 0;
	while (p != NULL)  //if need to handle the last Node, p!=NULL, if point to last Node, p->next!=NULL
	{
		int cPrice = p->pOfPriceOfCity->price;
		printCity(p->pOfPriceOfCity->city);
		printf(": %d\n", cPrice);
		sumPrice += cPrice;
		p = p->next;
	}
	printf("The total price of your order is %d\n", sumPrice);

	return 0;
}

int setCityPrice(int citycode, int price)
{
	if (citycode < 1 && citycode > 11)
		return -1;
	priceTable[citycode - 1].price = price;
	return 1;
}

ORDEROFCITY* freeCustomerOrder(ORDEROFCITY* h)
{
	printf("enter the free function!\n");
	printf("\n");

	ORDEROFCITY* p = NULL;
	while (h!= NULL)
	{
		p = h;
		h = h->next;
		printf("delete the city %s\n", citiesname[p->pOfPriceOfCity->city-SHA]);
		free(p);
	}
	return h;
}