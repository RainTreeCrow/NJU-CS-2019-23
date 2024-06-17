//#pragma once
#ifndef _TOURISMROUTERORDER_H
#define _TOURISMROUTERORDER_H
/* CITY     CODE                PRICE
 * SHA      SHANGHAI       12
 * PEK      BEIJING             10
 * SZX      SHENZHEN       15 
 * CAN     GUANGZHOU   9
 * TSN      TIANJIN            5
 * CKG      CHONGQING   4  
 * SZU      SUZHOU           7
 * CTU      CHENGDU        3
 * WUH    WUHAN            5 
 * HGH      HANGZHOU    8
 * NKG      NANJING         6
 *
*/
enum CITY {SHA, PEK, SZX, CAN, TSN, CKG, SZU, CTU, WUH, HGH, NKG};

typedef int PRICE;

struct PRICEOFCITY
{
    CITY city;
    PRICE price;      //thousand yuan
};

struct ORDEROFCITY
{
    PRICEOFCITY* pOfPriceOfCity;
    ORDEROFCITY* next;
};

//const CITY city1 = SHA;
//const CITY city2 = NKG;

//printf("%d\n", city2 - city1+1);

//PRICEOFCITY priceTable[city2 - city1 + 1];  //11 city

void initCityPrice();
void printCity(CITY city);
void printCityPrice();

ORDEROFCITY* makeCustomerOrder();
int printCustomerOrder(ORDEROFCITY* h);

int setCityPrice(int citycode, int price);

ORDEROFCITY* freeCustomerOrder(ORDEROFCITY* h);


#endif // !_TOURISMROUTERORDER_H