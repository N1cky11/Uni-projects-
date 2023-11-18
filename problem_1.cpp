#include <iostream>
#include <vector>
#include <array>
#include <deque>

using std::cout ;

void print(const int* begin_,const int* end_ ,const char ch=' ')
{
 for(auto ptr=begin_ ; ptr!=end_ ; ptr++) cout<<*ptr<<ch ;
 cout<<*end_<<"\n" ;
}

int main()
{
  std::vector<int> c={11,12,15,18} ;
  //std::array<int,4> c={11,12,15,18} ;
  //std::deque<int> c={11,12,15,18} ;
  auto first_=&(*c.begin()) ;
  auto last_=&(*(c.end()-1)) ;
  print(first_,last_) ;
  return 1 ;
}
