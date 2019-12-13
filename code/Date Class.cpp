#include "date.hpp"

void Date::setDate(int year, int month, int day){
    year_ = year;
    month_ = month;
    day_ = day;
}

int Date::daysOfMonth(int year, int month) const{
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(year %4 ==0 && year%100 !=0 || year %400 == 0 )
	{
		days[1] = 29;
	}
return days[month - 1];
}

int Date::year() const{
    return year_;
}

int Date::month() const{
    return month_;
}

int Date::day() const{
    return day_;
}

void Date::increment(){
    if(day_ == daysOfMonth(year_, month_))
    {
    	if(month_ == 12)
    	{
    		year_++;
    		month_ = 1;
    		day_ = 1;
    	}
    	else
    	{
    		month_++;
    	    day_ = 1;
    	}
    	
    }
    else
    {
    	day_++;
    }

}    

void Date::decrement(){ 
    if(day_ == 1)
    {
    	if(month_ == 1)
    	{
    		year_--;
    		month_ = 12;
		}
		else
		{
			month_--;
		}
		day_ = daysOfMonth(year_, month_);
	}
	else
	{
		day_ -= 1;
	}
	 
}
