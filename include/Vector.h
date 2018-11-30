#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <cstring>
#include <algorithm>

#define START_ID 0
#define MIN_SIZE 8
namespace aisdi
{

template <typename Type>
class Vector
{

public:
	using difference_type = std::ptrdiff_t;
	using size_type = std::size_t;
	using value_type = Type;
	using pointer = Type*;
	using reference = Type&;
	using const_pointer = const Type*;
	using const_reference = const Type&;

	class ConstIterator;
	class Iterator;
	using iterator = Iterator;
	using const_iterator = ConstIterator;

private:
	size_type capacity;
	pointer tab;
	size_type size;      


    void changeTab(int d, int s, bool ext)
		 {
    
      if(ext) 
			{
				capacity*=extensionMul();
			}
      
      pointer newtab = new value_type[capacity];
      // destination, source
			memcpy ( newtab +d , tab +s, getSize() * sizeof( value_type ) );

			delete[] tab;
			tab = newtab;
    
    }

    double extensionMul() 
		{

    if(capacity <= 100)
		{
      return 4;
    }
    if(capacity <= 1000) 
		{
      return 3;
    }
    if(capacity <= 10000)
		{
      return 2;
    }
    if(capacity <=100000) 
		{
      return 1.5;
    }
    return 1.2;
  }
public:
	Vector( )
		: capacity( MIN_SIZE ), size( 0 )
	{
      tab = new value_type [MIN_SIZE];
	}

	Vector( std::initializer_list<Type> l )
		: size( 0 )
	{
		capacity = l.size();
		tab = new value_type[capacity];

		for( auto element : l )
		{
			append( element );
		}
	}

	Vector( const Vector& other )
		: capacity( other.capacity ),  size( other.size )
	{
		tab = new value_type[capacity];
		memcpy ( tab , other.tab, getSize() * sizeof( value_type ) );
	}

	Vector( Vector&& other )
		: capacity( ( other.capacity ) ), size( ( other.size ) )
	{
		  if( this == &other )
      {
            return;
      }
		
		tab = other.tab;
		other.tab = nullptr;
		
	}

	~Vector()
	{
		delete[] tab;
	}

	Vector& operator=( const Vector& other )
	{
		if( this == &other ) 
		{
			return *this;
		}
			
		capacity = other.capacity;
		size = other.size;

		delete [] tab;
		tab = new value_type[capacity];
		memcpy ( tab , other.tab, getSize() * sizeof( value_type ) );

		return *this;
	}

	Vector& operator=( Vector&& other )
	{
		if( this == &other )
		{
			return *this;
		}
			
		size = other.size;
		capacity = other.capacity;
		

		delete [] tab;
		tab = other.tab;
		other.tab = nullptr;

		return *this;
	}

	bool isEmpty() const
	{
		return !getSize();
	}


	size_type getSize() const
	{
		return size;
	}

	void append( const Type& item )
	{
		
		if( size == capacity )
		{
		  changeTab(0,0,true);			
		}
	    tab[size] = item;
        ++size;
	}

	void prepend( const Type& item )
	{
        changeTab(1,0, size == capacity);
      
		tab[START_ID] = item;
        ++size;
	}

	void insert( const const_iterator& insertPosition, const Type& item )
	{
		if( insertPosition == end() )
		{
			append( item );
			return;
		}

		if( insertPosition == begin() )
		{
			prepend( item );
			return;
		}

		size++;

		for ( auto i = end() - 1 ; i != insertPosition ; i -- )
		{
			*i = std::move( *( i - 1 ) );
		}

		*iterator( insertPosition ) = item;

		if( size == capacity )
		{
			changeTab(0,0,true);
		}
	}

	Type popFirst()
	{
		if( isEmpty() )
		{
			throw std::logic_error( "cannot pop" );
		}

        value_type result = tab[START_ID];
        --size;
        changeTab(0,1,false);
		return result;
	}

	Type popLast()
	{
		if( isEmpty() )
		{
			throw std::logic_error( "cannot pop" );
		}
        --size;
		return tab[size];
	}

	void erase( const const_iterator& possition )
	{
		if( possition == end() )
		{
			throw std::out_of_range( "Eraseing vector end" );
		}
		else if( possition == begin() )
		{
			popFirst();
		}
		else if( possition == --end() )
		{
			popLast();
		}
		else
		{
       erase(possition, possition+1);
		}

	}

	void erase( const const_iterator& firstIncluded, const const_iterator& lastExcluded )
	{
		if( firstIncluded == lastExcluded ) {
				return;
		}
			

		auto to = iterator( firstIncluded );

		for ( auto from = iterator( lastExcluded ); from != end(); ++from )
		{
			*to = *from;
			++to;
		}

		size_type diff = 0;

		for( auto it = firstIncluded; it != lastExcluded; ++it )
		{
			diff++;
		}

		size -= diff;
	}

	iterator begin()
	{
		return iterator( cbegin() );
	}

	iterator end()
	{
		return iterator( cend() );
	}

	const_iterator cbegin() const
	{
		return ConstIterator(  &tab[START_ID], this );
	}

	const_iterator cend() const
	{
		return ConstIterator(  &tab[size], this );
	}

	const_iterator begin() const
	{
		return cbegin();
	}

	const_iterator end() const
	{
		return cend();
	}

};


template <typename Type>
class Vector<Type>::ConstIterator
{

  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Vector::value_type;
  using difference_type = typename Vector::difference_type;
  using pointer = typename Vector::const_pointer;
  using reference = typename Vector::const_reference;

private:
  pointer elementPointer;
  const Vector *vect;
public:
  explicit ConstIterator(pointer elementPointer, const Vector* vect):
      elementPointer(elementPointer), vect(vect)
  {}

  reference operator*() const
  {
    if( *this == vect->end() )
		{
			throw std::out_of_range( "Cannot get value" );
		}

    return *elementPointer;
  }

  ConstIterator& operator++()
  {
    if( *this == vect->end() )
		{
			throw std::out_of_range( "Cannot increment more" );
		}

    ++elementPointer;
    return *this;
  }

  ConstIterator operator++(int)
  {
    auto result = *this;
		++*this;
		return result;
  }

  ConstIterator& operator--()
  {
    if( *this == vect->begin())
    {
      throw std::out_of_range( "Cannot decrement more!" );
    }

    --elementPointer;
		return *this;	
  }

  ConstIterator operator--( int )
	{
		auto it = *this;
		--*this;
		return it;
	}

  ConstIterator operator+(difference_type d) const
  {
    auto it = *this;

		while( d-- ) {
			it++;
		}
		return it;
  }

  ConstIterator operator-(difference_type d) const
  {
    auto it = *this;

		while( d-- ) {
			it--;
		}
		return it;
  }

  bool operator==(const ConstIterator& other) const
  {
    return elementPointer == other.elementPointer;
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(elementPointer == other.elementPointer);
  }
};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
  using pointer = typename Vector::pointer;
  using reference = typename Vector::reference;

  explicit Iterator()
  {}

  Iterator(const ConstIterator& other)
    : ConstIterator(other)
  {}

  Iterator& operator++()
  {
    ConstIterator::operator++();
    return *this;
  }

  Iterator operator++(int)
  {
    auto result = *this;
    ConstIterator::operator++();
    return result;
  }

  Iterator& operator--()
  {
    ConstIterator::operator--();
    return *this;
  }

  Iterator operator--(int)
  {
    auto result = *this;
    ConstIterator::operator--();
    return result;
  }

  Iterator operator+(difference_type d) const
  {
    return ConstIterator::operator+(d);
  }

  Iterator operator-(difference_type d) const
  {
    return ConstIterator::operator-(d);
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif // AISDI_LINEAR_VECTOR_H