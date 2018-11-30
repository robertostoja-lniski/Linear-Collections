#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iostream>
namespace aisdi
{

template <typename Type>
class LinkedList
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

	void sentInit() {
		Node* hSent = new Node(0);
		headSent = hSent;

		headSent -> prevNode = headSent;
		headSent -> nextNode = headSent;
	}
	struct Node
	{
		value_type value;
		Node* prevNode;
		Node* nextNode;

		
		Node( value_type value, Node* prevNode = nullptr, 
			  Node* nextNode = nullptr ):
			value( value ), prevNode( prevNode ), nextNode( nextNode )
		{}
	};

	size_type size;
	Node* headSent;

public:

	LinkedList(bool toMove): 
		size( 0 ), headSent( nullptr )
	{
			sentInit();
		
	}
	LinkedList():
		size( 0 ), headSent( nullptr )
	{
		sentInit();
	
	}

	LinkedList( std::initializer_list<Type> l ):
		LinkedList()
	{

		for( auto it : l )
		{
			append( it );
		}
	}

	LinkedList( const LinkedList& other ):
		LinkedList(false)
	{
		
		*this = other;
	}

	LinkedList( LinkedList&& other ):
		LinkedList()
	{
		*this = std::move( other );
	}
	
	~LinkedList()
	{
		if(headSent != nullptr)
		erase( begin(), end() );

		delete headSent;
	}

	LinkedList& operator=( const LinkedList& other )
	{
		if ( this == &other )
			return *this;

		erase( begin(), end() );

		for( auto it : other )
		{
			append( it );
		}

		return *this;
	}

	LinkedList& operator=( LinkedList&& other )
	{

		if ( this == &other )
			return *this;
		erase( begin(), end() );
		
		headSent = other.headSent;
		other.headSent = nullptr;

		size = other.size;
		other.size = 0;

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
		insert( cend(), item);	
	}

	void prepend( const Type& item )
	{
	    insert( cbegin(), item);
	}

	void insert( const const_iterator& insertPosition, const Type& item )
	{
	   Node* afterNew = insertPosition.nodePointer;
	   Node* beforeNew = insertPosition.nodePointer->prevNode;

	   Node* newNode = new Node( item );

	   newNode -> prevNode = beforeNew;
	   beforeNew -> nextNode = newNode;

	   newNode -> nextNode = afterNew;
	   afterNew -> prevNode = newNode;

	   size++;
	}

	Type popFirst()
	{
		if( isEmpty() )
		{
			throw std::out_of_range( "Poping empty list." );
		}

		Node* toPop = headSent -> nextNode;
		value_type result = toPop -> value;
		
		erase(  const_iterator( toPop, headSent ) );
		return result;
	}

	Type popLast()
	{
		if( isEmpty() )
		{
			throw std::out_of_range( "Poping empty list." );
		}

		Node* toPop = headSent -> prevNode;
		value_type result = toPop -> value;
		
		erase(  const_iterator( toPop, headSent ) );
		return result;
	}

	void erase( const const_iterator& possition )
	{
		if( possition == end() )
		{
			throw std::out_of_range( "All erased, cannot more." );
		}
		
		Node* beforeErase = possition.nodePointer -> prevNode;
		Node* afterErase = possition.nodePointer -> nextNode;

		beforeErase -> nextNode = afterErase;
		afterErase -> prevNode = beforeErase;

		Node* toDelete = possition.nodePointer;
		delete toDelete;

		size--;
			
	}

	void erase( const const_iterator& firstIncluded, const const_iterator& lastExcluded )
	{
		for ( iterator it = firstIncluded; it != lastExcluded; it++ )
		{
			erase(it);
		}
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
		return ConstIterator(  headSent->nextNode, headSent );
	}

	const_iterator cend() const
	{
		return ConstIterator( headSent, headSent );
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
class LinkedList<Type>::ConstIterator
{
private:
	friend class LinkedList;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = typename LinkedList::value_type;
	using difference_type = typename LinkedList::difference_type;
	using pointer = typename LinkedList::const_pointer;
	using reference = typename LinkedList::const_reference;

private:
	Node* nodePointer;
	Node* headSent;

public:

	explicit ConstIterator( Node* nodePointer, Node* headSent ):
		nodePointer( nodePointer ), headSent( headSent )
	{}

	reference operator*() const
	{
		if(nodePointer == headSent) {
			throw std::out_of_range( "Cannot get *tailSent value" );
		}
		
		return nodePointer -> value;
	}

	ConstIterator& operator++()
	{	

		if( nodePointer == headSent ) {
			throw std::out_of_range( "Cannot Increment outside the list" );
		}

		nodePointer = nodePointer -> nextNode;
		return *this;
	}

	ConstIterator operator++( int )
	{
		
		auto result = *this;
		++*this;
		return result;
	}

	ConstIterator& operator--()
	{
		if( nodePointer -> prevNode == headSent)
			throw std::out_of_range( "Cannot decrement tailSent!" );


		nodePointer = nodePointer -> prevNode;
		
		return *this;	
	}

	ConstIterator operator--( int )
	{
		auto it = *this;
		--*this;
		return it;
	}

	ConstIterator operator+( difference_type d ) const
	{
		auto it = *this;

		while( d-- ) {
			it++;
		}
		return it;
	}

	ConstIterator operator-( difference_type d ) const
	{
		auto it = *this;

		while( d-- ) {
			it--;
		}
		return it;
	}

	bool operator==( const ConstIterator& other ) const
	{
		return nodePointer == other.nodePointer;	
	}

	bool operator!=( const ConstIterator& other ) const
	{
		return !(nodePointer == other.nodePointer);
	}
};

template <typename Type>
class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
{
public:
	using pointer = typename LinkedList::pointer;
	using reference = typename LinkedList::reference;

	explicit Iterator()
	{}

	Iterator( const ConstIterator& other )
		: ConstIterator( other )
	{}

	Iterator& operator++()
	{
		ConstIterator::operator++();
		return *this;
	}

	Iterator operator++( int )
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

	Iterator operator--( int )
	{
		auto result = *this;
		ConstIterator::operator--();
		return result;
	}

	Iterator operator+( difference_type d ) const
	{
		return ConstIterator::operator+( d );
	}

	Iterator operator-( difference_type d ) const
	{
		return ConstIterator::operator-( d );
	}

	reference operator*() const
	{
		// ugly cast, yet reduces code duplication.
		return const_cast<reference>( ConstIterator::operator*() );
	}
};

}

#endif // AISDI_LINEAR_LINKEDLIST_H