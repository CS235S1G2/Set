/***********************************************************************
* Header:
*    Set
* Summary:
*    This class contains the notion of a set: a container
*    that follows First In Last Out and expands as more items are put inside.
*
*    This will contain the class definition of:
*        Set         : A class that holds stuff
* Author
*    Nathan Bench, Jed Billman, Justin Chandler, Jeremy Chandler (Oh Yeah!)
************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>
#include <new>

/************************************************
 * SET
 * A class that holds stuff
 ***********************************************/
template <class T>
class Set
{
public:
   // default constructor : empty and kinda useless
   Set() : m_top(0), m_capacity(0), m_data(NULL) {}

   // copy constructor : copy it
   Set(const Set & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Set(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Set()        { if (m_capacity) delete [] m_data; }
   
   // is the container currently empty
   bool empty() const  { return m_top == 0;         }

   // remove all the items from the container
   void clear()        { m_top = 0;                 }

   // how many items can the set currently contain?
   int capacity() const { return m_capacity;             }
   
   // how many items are currently in the container?
   int size() const    { return m_top;              }

   // increase the capacity
   void increaseCapacity();

   // add an item to the container
   void insert(const T & t) throw (const char *);

   // Removes an item from the set
   void erase() throw (const char *);

   // Finds the item in the set
   T & find() throw (const char *);
   
   // union operator '||'
   Set<T> & operator || (const Set <T> & rhs);
   
   // insertion operator '&&'
   Set<T> & operator && (const Set <T> & rhs);

   //returns an iterator to the first element in the set
   int begin() throw (const char *);
   // returns an iterator referring to the first element in the set
   int end() throw (const char *);
   
   
private:
   T * m_data;          // dynamically allocated array of T
   int m_top;      // how many items are currently in the Set?
   int m_capacity;      // how many items can I put on the Set before full?
};


/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
{
   assert(rhs.m_capacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.m_capacity == 0)
   {
      m_capacity = m_top = 0;
      m_data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      m_data = new T[rhs.m_capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.m_top >= 0 && rhs.m_top <= rhs.m_capacity);
   m_capacity = rhs.m_capacity;
   m_top = rhs.m_top;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < m_top; i++)
      m_data[i] = rhs.m_data[i];

   // the rest needs to be filled with the default value for T
   for (int i = m_top; i < m_capacity; i++)
      m_data[i] = T();
}

/**********************************************
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Set <T> :: Set(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (m_capacity == 0)
   {
      this->m_capacity = this->m_top = 0;
      this->m_data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      m_data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->m_capacity = capacity;
   this->m_top = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < m_capacity; i++)
      m_data[i] = T();
}

/***************************************************
* STACK :: INCREASE CAPACITY
* Allocate memory for m_data
**************************************************/
template<class T>
void Set<T>::increaseCapacity()
{
	int newCap = m_capacity * 2;
   
	if (m_capacity == 0)
		newCap = 1;
   
	T *temp = new T[newCap];
	for (int i = 0; i < m_capacity; ++i)
	{
		temp[i] = m_data[i];
	}
   
	m_capacity = newCap;
	delete[] m_data;
	m_data = temp;
}

/***************************************************
* STACK :: PUSH
* Adds an item to the top of the set
**************************************************/
template<class T>
void Set<T>::push(const T & t) throw (const char *)
{
   // IF empty increase the capacity
	if (empty() || m_capacity <= m_top)
	{
		increaseCapacity();
	}
	m_data[m_top] = t;
	m_top++;
}

/***************************************************
* STACK :: POP
* Removes an item from the end of the set, and reduces size by one
**************************************************/
template<class T>
inline void Set<T>::pop() throw(const char *)
{
	if (empty())
		throw "ERROR: Unable to pop from an empty Set";
	m_top--;
}

/***************************************************
* STACK :: TOP
* Returns the item currently at the end of the set
**************************************************/
template<class T>
inline T & Set<T>::top() const throw(const char *)
{
	// if empty: throw Unable to reference the element from an empty Set
	if (empty() || (m_top < 0))
		throw "ERROR: Unable to reference the element from an empty Set";
	return m_data[m_top - 1];
}

/***************************************************
 * STACK :: =
 * Overload assignment operator
 **************************************************/
 template <class T>
Set<T> & Set <T> :: operator = (const Set <T> & rhs)
{
   // don't copy yourself
   if (this != &rhs)
   {
      // clean up m_data
      if (m_data)
         delete [] m_data;
      
      // assign each member variable to right-hand-side
      m_capacity = rhs.m_capacity;
      m_top = rhs.m_top;
      
      // allocate new array
      try
      {
         m_data = new T[m_capacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Set";
      }
      // copy over values from rhs
      for (int i = 0; i < rhs.m_top; i++)
      {
         m_data[i] = rhs.m_data[i];
      }
      
      return *this;
   }
}

#endif // STACK_H