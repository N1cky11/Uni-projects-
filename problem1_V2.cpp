#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>

using std::cout ;
template <typename type>
void print(const type &container,const char=' ')
{
 for(auto it=container.begin() ; it!=container.end() ; it++ )
    cout <<*it << " " ;
 cout<<"\n" ;
}

int main()
{
  //std::vector<int> c={11,12,15,18} ;
  //std::array<int,4> c={11,12,15,18} ;
  //std::deque<int> c={11,12,15,18} ;
   std::list<int> c={11,12,15,18} ;
   print(c) ;
  return 1 ;
}
