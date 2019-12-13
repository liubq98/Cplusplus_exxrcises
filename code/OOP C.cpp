#include "date.h"
#include <stdlib.h>
#include <string.h>

Date* CreateDate(int year, int month, int day){
	Date *date = (Date*)malloc(sizeof(Date));
	SetDate(date, year, month, day);
return date;
}

void DestroyDate(Date** p){
	free(*p);
}

Date* CopyDate(const Date* date){
	Date* temp = (Date*)malloc(sizeof(Date));
	temp->year = date->year;
	temp->month = date->month;
	temp->day = date->day;
return temp;
}

int GetYear(const Date* date){
	return date->year;
}

int GetMonth(const Date* date){
	return date->month;
}

int GetDay(const Date* date){
	return date->day;
}

void SetYear(Date* date, int year){
	date->year = year;
}
void SetMonth(Date* date, int month){
	date->month = month;
}

void SetDay(Date* date, int day){
	date->day = day;
}

void SetDate(Date* date, int year, int month, int day){
	SetYear(date, year);
	SetMonth(date, month);
	SetDay(date, day);
}

char* GetDateString(const Date* date){
	char* str = (char*)malloc(sizeof(char) * 10 + 1);
	snprintf(str, sizeof(char)*10 + 1, "%04d-%02d-%02d", date->year, date->month, date->day);
return str;
}

void DestroyDateString(char** p){
	free(*p);
	*p = NULL;
}

void IncreaseDate(Date* date){
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(date->year %4 ==0 && date->year%100 !=0 || date->year %400 == 0 )
	{
		days[1] = 29;
	}
	int daysOfMonth = days[date->month - 1];
    if(date->day == daysOfMonth)
    {
    	if(date->month == 12)
    	{
    		date->year++;
    		date->month = 1;
    		date->day = 1;
    	}
    	else
    	{
    		date->month++;
    	    date->day = 1;
    	}
    	
    }
    else
    {
    	date->day++;
    }

}

void DecreaseDate(Date* date){
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(date->year %4 ==0 && date->year%100 !=0 || date->year %400 == 0 )
	{
		days[1] = 29;
	}
	int daysOfMonth = days[date->month - 1];
		
    if(date->day == 1)
    {
    	if(date->month == 1)
    	{
    		date->year--;
    		date->month = 12;
		}
		else
		{
			date->month--;
		}
		daysOfMonth = days[date->month - 1];
		date->day = daysOfMonth;
	}
	else
	{
		date->day -= 1;
	}
	 
}
