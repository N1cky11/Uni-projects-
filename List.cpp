#include <iostream>
#include <new>

template <typename type> class List
{
  private :

  class Node {
    public:
    Node* next=nullptr ;
    Node* prev=nullptr ;
    type value=0 ;

    Node(type v) : next(nullptr),prev(nullptr),value(v) {}
    Node() : next(nullptr),prev(nullptr),value(0) {}
  };

  Node* head=nullptr ;
  Node* tail=nullptr ;
  size_t elCount=0 ;

  public :

    List() ;
    List(const List& object) ;
   ~List() ;

   template <typename T>
   friend std::ostream& operator<<(std::ostream& os,const List<T>& obj)  ;
   List& operator=(const List &obj) ;

   Node* alloc(const type& value) ;
   void PushBack(const type value) ;
   void PushFront(const type value) ;
   void Clear() ;
   void PopBack() ;
   void PopFront() ;
};

template <typename type>
List<type>::List() : head(new Node() ),tail(new Node() ),elCount(0)
{
  head->next=tail ;
  tail->prev=head ;

  tail->next=nullptr ;
  head->prev=nullptr ;
}

template <typename type>
List<type>::List(const List<type> &obj)
{
  head=new Node() ;
  tail=new Node() ;
  elCount=0 ;

  for(typename List<type>::Node* temp=obj.head->next ; temp!=obj.tail ; temp=temp->next ) PushBack(temp->value) ;
}

template <typename type>
List<type>::~List()
  {
    Clear()  ;

    delete head ;
    delete tail ;

    head=nullptr ;
    tail=nullptr ;

  }

template <typename type>
List<type>& List<type>::operator=(const List<type>& obj)
{
  Clear() ;

  for(typename List<type>::Node* temp=obj.head->next ; temp!=obj.tail ; temp=temp->next ) PushBack(temp->value) ;
  return *this ;
}

template <typename type>
std::ostream& operator<<(std::ostream& os,const List<type>& obj)
{
  for(typename List<type>::Node* temp=obj.head->next ; temp!=obj.tail ; temp=temp->next) os << temp->value <<" " ;
  os << "\n" ;
  return os ;
}

template <typename type>
typename List<type>::Node* List<type>::alloc(const type& value)
{
   try {
      Node* created=new Node(value) ;
      return created ;
    } catch(const std::bad_alloc& ex) {
        std::cerr << "Memory allocation failed:" << ex.what() << "\n" ;
        return nullptr ;
      }
}

template<typename type>
void List<type>::PushBack(const type value)
  {
    Node* created=alloc(value) ;
    if(created==nullptr) return ;

    if(elCount==0) {
      head->next=created ;
      tail->prev=created ;

      created->next=tail ;
      created->prev=head ;

    }
    else {
      Node* temp=tail->prev ;

      temp->next=created ;
      tail->prev=created ;

      created->next=tail ;
      created->prev=temp ;
    }

    elCount++ ;
  }

template <typename type>
void List<type>::PushFront(const type value)
  {
     Node* created=alloc(value) ;
     if(created==nullptr) return ;

     if(elCount==0) {
      created->next=tail ;
      created->prev=head ;

      head->next=created ;
      tail->prev=created ;

    }
     else {
       Node* temp=head->next ;

       created->prev=head ;
       created->next=temp ;

       temp->prev=created ;
       head->next=created ;

     }

      elCount++ ;
  }


template <typename type>
void List<type>::Clear() {

     while(elCount!=0) {
	 PopFront() ;
     }

     head->next=tail ;
     tail->prev=head ;
}

template <typename type>
void List<type>::PopBack()
{
   try {
      if(elCount==0){
      throw std::runtime_error("No elements to delete") ;
      }

     Node* toDelete=tail->prev ;
     Node* temp=toDelete->prev  ;

     temp->next=tail ;
     tail->prev=temp ;

     delete toDelete ;
     elCount-- ;
   } catch(const std::exception &ex) {
     std::cerr << ex.what() << "\n" ;
    }

}

template <typename type>
void List<type>::PopFront()
  {
    try {
      if(elCount==0){
      throw std::runtime_error("No elements to delete") ;
      }

     Node* toDelete=head->next ;
     Node* temp=toDelete->next ;

     temp->prev=head ;
     head->next=temp ;

     delete toDelete ;
     elCount-- ;
    }catch(const std::exception &ex) {
      std::cerr << ex.what() << "\n" ;
    }


  }


int main()
{
 /* List<int> li ;
  for(int i=-4 ; i<0 ; i++) li.PushFront(i) ;
  for(int i=7 ; i<9 ; i++ ) li.PushBack(i) ;
  std::cout<<li ;
  li.PopFront() ;
  std::cout<<li ;
  li.PopBack() ;
  std::cout<<li ;
  List<int> j(li) ;
  std::cout<<j ;
  List<int> k ;
  k.PopFront() ;
  k.PushBack(11) ;
  k.PushBack(12) ;
   k.PushBack(14) ;
   k.PopFront() ;
   std::cout << k ;
   k.PopFront() ;
   std::cout << k ;
   k.PopFront() ;
   std::cout << k ;
   k.PopFront() ;
  std :: cout << k ; */


  return 1;
}
