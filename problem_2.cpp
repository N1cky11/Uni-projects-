#include <iostream>
#include <unordered_map>
#include <string>

using std::string ;
bool func(string letter,string paper)
{
  std::unordered_map<char,int> ch ;
  for(const auto &x : letter) ch[x]++ ;
  for(const auto &x : paper)
  {
    auto found=ch.find(x) ;
    if(found!=ch.end() ) found->second-- ;
  }
  for(const auto &x : ch) if(x.second>0) return false ;
  return true ;
}
int main()
{
  string s1="daafaac" ;
  string s2="abaaadfdaaacfdac"  ;
  if(func(s1,s2)==true) std::cout<<"true" ;
  else std::cout<<"false" ;
  return 0 ;
}
