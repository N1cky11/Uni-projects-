#include <iostream>
#include <tuple>
#include <cmath>

  using std::ostream ;
  using std::istream ;
  using std::tuple ;

class Date
{

  private:

  int day=0 ;
  int month=0 ;
  int year=0 ;
  //std::map<int,int> month_days={ {1,31},{2,28},{3,31},{4,30},{5,31},{6,30},{7,31},{8,31},{9,30},{10,31},{11,30},{12,31} } ;

  public:

  Date(int day,int month,int year) ;
  Date(int day) ;
  Date()=default ;

  tuple<int,int,int> adjust(int day,int month,int year) ;

   ostream& operator<<(ostream& os) ;
   istream& operator>>(istream& os) ;
   Date& operator+(Date &obj) ;
   Date& operator-(Date &obj);
   Date& operator+=(int days) ;

};

 ostream& Date::operator<<(ostream& os)
{
  os << day << "." << month << "." << year <<"\n" ;
  return os ;
}

Date::Date(int day,int month,int year)
{
  auto res=adjust(day,month,year) ;
  std::tie(this->day,this->month,this->year)=res ;
}

tuple<int,int,int> Date::adjust(int day,int month,int year)
{
   if(abs(day)>30 || day<0)
   {
     month+=day/30 ;
     day%=30 ;

     if(day<0)
     {
      month-=1 ;
      day=30-day ;
     }
   }

  if(abs(month>12) || month<0)
    {
     year+=month/12 ;
     month%=12 ;
       if(month<0)
        {
          year-=1 ;
          month=12-month ;
        }
     }

  return std::make_tuple(day,month,year) ;
}

Date& Date::operator+(Date &obj)
{
  int sum_days=this->day+obj.day ;
  int sum_month=this->month+obj.month ;
  int sum_years=this->year+obj.year ;

  std::tie(sum_days,sum_month,sum_years)=adjust(sum_days,sum_month,sum_years) ;
  return *this;
}

int main()
{
  Date today(34,11,2023) ;
  today<<std::cout ;
}
