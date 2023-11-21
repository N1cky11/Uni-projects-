#include <iostream>
#include <tuple>
#include <cmath>

  using std::ostream ;
  using std::istream ;
  using std::tuple ;

class Except
{
  private:
    std::string error_m ;

  public:
    Except(const std::string &message) : error_m(message) {}
    const std::string& what() const {return error_m ; }
    void handle(int& num1,int& num2,int& num3)
    {
      num1=0 ;
      num2=0 ;
      num3=0 ;
    }
};


class Date
{

  private:

  int day=0 ;
  int month=0 ;
  int year=0 ;

  public:

   Date(int day,int month,int year) ;
   Date(int day) ;
   Date(const Date &obj) ;
   Date()=default ;
   ~Date() ;

   tuple<int,int,int> adjust(int day,int month,int year) ;

   friend ostream& operator<<(ostream& os,const Date &obj) ;
   friend istream& operator>>(istream& os,const Date &obj) ;

   Date operator+(const Date &obj) ;
   Date operator-(const Date &obj);
   Date& operator+=(const Date &obj) ;
   Date& operator+=(int days) ;
   Date& operator=(const Date &obj) ;
};

Date::~Date()
{
  std::cout << "running destructor" << "\n" ;
}
Date::Date(const Date &obj)
  {
    day=obj.day ;
    month=obj.month ;
    year=obj.year ;
  }

Date& Date::operator=(const Date &obj)
   {
      day=obj.day ;
      month=obj.month ;
      year=obj.year ;
      return *this ;
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
      day=30-abs(day) ;
     }
   }

  if(abs(month)>12 || month<0)
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

  Date::Date(int day,int month,int year)
{
  try
  {
        if(day>30 || day<0 || month>12 || month<0) throw Except("Invalid input") ;
        else
         {
            this->day=day ;
            this->month=month ;
            this->year=year ;
         }
  }
    catch(Except &ex)
    {
       std::cerr << "Error:" << ex.what() << "\n" << "All values set to default \n" ;
       ex.handle(this->day,this->month,this->year) ;
    }
}

 Date::Date(int d)
 {
     d-=(d/(365*4) ) ;

     year=d/365 ;
     d-=year*365 ;
     month=d/30 ;
     day=d%30 ;
 }

ostream& operator<<(ostream& os,const Date &obj)
    {
      if(obj.year>0 && obj.month>0 && obj.day>0) os << obj.day << "." << obj.month << "." << obj.year <<"\n" ;
      else os << abs(obj.day)<< "." << abs(obj.month)<< "." << abs(obj.year)<<" BCE\n" ;
      return os ;
    }

istream& operator>>(istream& is,const Date &obj)
    {
      int d,m,y ;
      is>>d>>m>>y ;

      Date(d,m,y) ;

      return is ;
    }

Date Date::operator+(const Date &obj)
{
  int temp1,temp2,temp3 ;
  std::tie(temp1,temp2,temp3)=adjust(this->day+obj.day,this->month+obj.month,this->year+obj.year) ;

  Date temp(temp1,temp2,temp3) ;

  return temp;
}

Date Date::operator-(const Date &obj)
{
  int temp1,temp2,temp3 ;
  std::tie(temp1,temp2,temp3)=adjust(this->day+obj.day,this->month+obj.month,this->year+obj.year) ;

  Date temp(temp1,temp2,temp3) ;

  return temp;
}

Date& Date::operator+=(const Date &obj)
{
  *this=*this+obj ;
  return *this ;
}

Date& Date::operator+=(int days)
{
  int temp1,temp2,temp3 ;
  std::tie(temp1,temp2,temp3)=adjust(day+days,month,year) ;

  day=temp1 ;
  month=temp2 ;
  year=temp3 ;

  return *this ;
}

int main()
{

  return 1 ;
}

