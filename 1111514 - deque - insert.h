#ifndef DEQUE_H
#define DEQUE_H

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
   using size_type = typename MyDeque::size_type;

public:
   using value_type = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer = typename MyDeque::const_pointer;
   using reference = const value_type &;

   // construct with null pointer
   DequeConstIterator()
      : myOff( 0 ),
        myCont( nullptr )
   {
   }

   // construct with offset off in *pDeque
   DequeConstIterator( size_type off, const MyDeque *pDeque )
      : myOff( off ),
        myCont( pDeque )
   {
   }

   DequeConstIterator( const DequeConstIterator &right ) // copy constructor
      : myOff( right.myOff ),
        myCont( right.myCont )
   {
   }

   ~DequeConstIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const DequeConstIterator& operator=( const DequeConstIterator &right )
   {
      if( &right != this ) // avoid self-assignment
      {
         myCont = right.myCont;
         myOff = right.myOff;
      }
      return *this; // enables x = y = z, for example
   }

   reference operator*() const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

//      size_type block = myOff % ( dequeSize * myCont->mapSize ) / dequeSize;
      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % dequeSize;
      return myCont->map[ block ][ off ];
   }

   pointer operator->() const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % dequeSize;
      return &myCont->map[ block ][ off ];
   }
/*
   pointer operator->() const
   {
      return &( operator*() );
   }
*/
   DequeConstIterator& operator++() // preincrement
   {
      ++myOff;
      return *this;
   }

   DequeConstIterator operator++( int ) // postincrement
   {
      DequeConstIterator tmp = *this;
      ++*this;
      return tmp;
   }

   DequeConstIterator& operator--() // predecrement
   {
      --myOff;
      return *this;
   }

   DequeConstIterator operator--( int ) // postdecrement
   {
      DequeConstIterator tmp = *this;
      --*this;
      return tmp;
   }

   // increment by integer
   DequeConstIterator& operator+=( const difference_type off )
   {
      myOff += off;
      return *this;
   }

   // return this + integer
   DequeConstIterator operator+( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   // return this - integer
   DequeConstIterator operator-( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp -= off;
   }

   // return difference of iterators
   difference_type operator-( const DequeConstIterator &right ) const
   {
      return ( static_cast< difference_type >( this->myOff - right.myOff ) );
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return *( *this + off );
   }

   // test for iterator equality
   bool operator==( const DequeConstIterator &right ) const
   {
      return this->myCont == right.myCont && this->myOff == right.myOff;
   }

   // test for iterator inequality
   bool operator!=( const DequeConstIterator &right ) const
   {
      return !( *this == right );
   }

   // test if this < right
   bool operator<( const DequeConstIterator &right ) const
   {
      return this->myOff < right.myOff;
   }

   // test if this > right
   bool operator>( const DequeConstIterator &right ) const
   {
      return right < *this;
   }

   // test if this <= right
   bool operator<=( const DequeConstIterator &right ) const
   {
      return !( right < *this );
   }

   // test if this >= right
   bool operator>=( const DequeConstIterator &right ) const
   {
      return !( *this < right );
   }

   const MyDeque *myCont; // keep a pointer to deque
   size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
   using size_type = typename MyDeque::size_type;
   using MyBase = DequeConstIterator< MyDeque >;

public:
   using value_type = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer = typename MyDeque::pointer;
   using reference = value_type &;

   using MyBase::MyBase;

   DequeIterator() // construct with null deque pointer
   {
   }

   DequeIterator( size_type off, const MyDeque *pDeque )
      : MyBase( off, pDeque ) // construct with offset off in *pDeque
   {
   }

   reference operator*() const // return designated object
   {
      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const // return pointer to class object
   {
      return const_cast< pointer >( MyBase::operator->() );
//      return &( operator*() );
   }

   DequeIterator& operator++() // preincrement
   {
      MyBase::operator++();
      return *this;
   }

   DequeIterator operator++( int ) // postincrement
   {
      DequeIterator tmp = *this;
      MyBase::operator++();
      return tmp;
   }

   DequeIterator& operator--() // predecrement
   {
      MyBase::operator--();
      return *this;
   }

   DequeIterator operator--( int ) // postdecrement
   {
      DequeIterator tmp = *this;
      MyBase::operator--();
      return tmp;
   }

   // increment by integer
   DequeIterator& operator+=( const difference_type off )
   {
      MyBase::operator+=( off );
      return *this;
   }

   // return this + integer
   DequeIterator operator+( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeIterator& operator-=( const difference_type off )
   {
      MyBase::operator-=( off );
      return *this;
   }

   using MyBase::operator-; // return difference of iterators

   // return this - integer
   DequeIterator operator-( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp -= off;
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return const_cast< reference >( MyBase::operator[]( off ) );
   }
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;
   using MapPtr = Ty **;

   DequeVal() // initialize values
      : map(),
        mapSize( 0 ),
        myOff( 0 ),
        mySize( 0 )
   {
   }

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

      return off % ( dequeSize * mapSize ) / dequeSize;
//      return ( off / dequeSize ) & ( mapSize - 1 );
   }

   MapPtr map;        // pointer to array of pointers to blocks
   size_type mapSize; // size of map array, zero or 2^N
   size_type myOff;   // offset of initial element
   size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
   using MapPtr = Ty **;
   using ScaryVal = DequeVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = DequeIterator< ScaryVal >;
   using const_iterator = DequeConstIterator< ScaryVal >;

   // construct empty deque
   deque()
      : myData()
   {
   }

   // destroy the deque
   ~deque()
   {
      clear();
   }

   // return iterator for beginning of mutable sequence
   iterator begin()
   {
      return iterator( myData.myOff, &myData );
   }

   // return iterator for beginning of nonmutable sequence
   const_iterator begin() const
   {
      return const_iterator( myData.myOff, &myData );
   }

   // return iterator for end of mutable sequence
   iterator end()
   {
      return iterator( myData.myOff + myData.mySize, &myData );
   }

   // return iterator for end of nonmutable sequence
   const_iterator end() const
   {
      return const_iterator( myData.myOff + myData.mySize, &myData );
   }

   iterator makeIter( const_iterator where ) const
   {
      return iterator( where.myOff, &myData );
   }

   // return length of sequence
   size_type size() const
   {
      return myData.mySize;
   }

   // test if sequence is empty
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // insert val at where
   iterator insert( const_iterator where, const value_type &val )
   {
      size_type dequeSize = compDequeSize(); // elements per block (a power of 2)
      size_type off = static_cast< size_type >( where - begin() );

      /*
      cout << "original deque:";
      for (size_type i = myData.myOff; i < myData.myOff+myData.mySize; i++) {
          size_type k=0;
          size_type j=0;
          k = i / dequeSize;
          j = i % dequeSize;
          if (k >= myData.mapSize)
              k %= myData.mapSize;
          cout << myData.map[k][j];
      }
      cout << endl;
      cout << "insert position:" << off << endl;
      cout << "insert value:" << val << endl;*/

      if( myData.mySize == 0 )
      {
         if( myData.mapSize == 0 )
         {
            myData.map = new value_type * [ 8 ]();
            myData.mapSize = 8;
         }
         myData.myOff = dequeSize * myData.mapSize - 1;
         size_type where_row = (myData.myOff + off ) / dequeSize;
         size_type where_col = (myData.myOff + off ) % dequeSize;
         if (where_row >= myData.mapSize)
             where_row %= myData.mapSize;
         if (myData.map[where_row] == nullptr)
             myData.map[where_row] = new value_type[dequeSize];
         myData.map[where_row][where_col] = val;
      }
      else
      {
         // all elements before where move forward
          if (off <= myData.mySize / 2)
          {
              if (myData.myOff % dequeSize == 0 &&
                  myData.mapSize <= (myData.mySize + dequeSize) / dequeSize) {
                  //cout << "++++++++++++++++++++++++++++++++++++++++++++" << endl;
                  doubleMapSize();
              }
              size_type row;
              size_type col;
              size_type front_row;
              size_type front_col;
              //cout << "off: " << off << endl;
              //cout << "myOff: " << myData.myOff << endl;
              if (off == 0) {//insert begin()
                  row = (myData.myOff) / dequeSize;
                  col = (myData.myOff) % dequeSize;
                  if (row >= myData.mapSize)
                      row %= myData.mapSize;
                  if (col < 1) {
                      front_col = dequeSize - 1;
                      if (row < 1) {
                          front_row = myData.mapSize - 1;
                      }
                      else {
                          front_row = row - 1;
                      }
                  }
                  else {
                      front_row = row;
                      front_col = col - 1;
                  }
                  if (myData.map[front_row] == nullptr)
                      myData.map[front_row] = new value_type[dequeSize];
                  myData.map[front_row][front_col] = val;
                  if (myData.myOff < 1) {
                      myData.myOff = dequeSize * myData.mapSize - 1;
                  }
                  else {
                      --myData.myOff;
                  }
              }
              else {
                  //cout << "myoff: " << myData.myOff%(myData.mapSize*dequeSize) << endl;
                  //cout << myData.myOff << "~" << myData.myOff + off << endl;
                  //cout << "off: " << off << endl;
                  for (size_type i = myData.myOff; i < myData.myOff + off ; i++) {
                      row = i / dequeSize;
                      col = i % dequeSize;
                      if (row >= myData.mapSize)
                          row %= myData.mapSize;
                      if (col < 1) {
                          front_col = dequeSize - 1;
                          if (row < 1) {
                              front_row = myData.mapSize - 1;
                          }
                          else {
                              front_row = row - 1;
                          }
                      }
                      else {
                          front_row = row;
                          front_col = col - 1;
                      }
                      if (myData.map[front_row] == nullptr)
                          myData.map[front_row] = new value_type[dequeSize];
                      myData.map[front_row][front_col] = myData.map[row][col];
                  }
                  if (myData.myOff < 1) {
                      myData.myOff = dequeSize * myData.mapSize - 1;
                  }
                  else {
                      --myData.myOff;
                  }
                  size_type target_row = (myData.myOff + off ) / dequeSize;
                  if (target_row >= myData.mapSize)
                      target_row %= myData.mapSize;
                  myData.map[target_row][(myData.myOff + off ) % dequeSize] = val;
                  //cout << "row = " << target_row << endl;
                  //cout << "col= " << (myData.myOff + off) % dequeSize << endl;
              }
              
              //cout << "insert off: " << ((target_row)*dequeSize) + ((myData.myOff + off) % dequeSize) - myData.myOff << endl;
              //cout << "myoff: " << myData.myOff << endl;
              //cout << "mapsize: " << myData.mapSize << endl;
              //cout << "dequesize: " << dequeSize << endl;
            
          }
         else  // all elements after (and at) where move backward
         {
             if ((myData.myOff + myData.mySize) % dequeSize == 0 &&
                 myData.mapSize <= (myData.mySize + dequeSize) / dequeSize) {
                 //cout << "+++++++++++++++++++++++++++++" << endl;
                 doubleMapSize();
             }
            size_type row;
            size_type col;
            size_type back_row;
            size_type back_col;
            //cout << "before myoff: " << myData.myOff << endl;
            //cout << myData.myOff + myData.mySize - 1 << "~" << myData.myOff + off << endl;
            
            if (off==myData.mySize) {
                row = (myData.myOff + off) / dequeSize;
                if (row >= myData.mapSize)
                    row %= myData.mapSize;
                if (myData.map[row] == nullptr)
                    myData.map[row] = new value_type[dequeSize];
                myData.map[row][(myData.myOff + off) % dequeSize] = val;
                if (myData.myOff >= dequeSize * myData.mapSize)
                    myData.myOff %= dequeSize * myData.mapSize;
               
            }
            else {
                for (size_type i = myData.myOff + myData.mySize - 1 ; i >= myData.myOff + off ; i--) {
                    row = i / dequeSize;
                    col = i % dequeSize;
                    //cout << row << "and" << col << endl;
                    if (row >= myData.mapSize)
                        row %= myData.mapSize;
                    if (col >= dequeSize - 1) {
                        back_col = 0;
                        if (row >= myData.mapSize - 1) {
                            back_row = 0;
                        }
                        else
                            back_row = row + 1;
                    }
                    else {
                        back_col = col + 1;
                        back_row = row;
                    }
                    if (myData.map[back_row] == nullptr)
                        myData.map[back_row] = new value_type[dequeSize];
                    myData.map[back_row][back_col] = myData.map[row][col];
                }
                size_type target_row = (myData.myOff + off ) / dequeSize;
                if (target_row >= myData.mapSize)
                    target_row %= myData.mapSize;
                myData.map[target_row][(myData.myOff + off ) % dequeSize] = val;
            }
            //cout << 2 << endl;
               
            //cout << "myoff: "<<myData.myOff << endl;
            //cout << "mapsize: " << myData.mapSize << endl;
            //cout << "dequeSIze: " << dequeSize << endl;
        
            //cout << "insert off: " << ((target_row)*dequeSize) + ((myData.myOff + off) % dequeSize) - myData.myOff << endl;
          
            }
      }
      if (myData.myOff >= dequeSize * myData.mapSize)
          myData.myOff %= dequeSize * myData.mapSize;
      //cout << "myoff: " << myData.myOff << endl;
      ++myData.mySize;

      /*
      cout << "insert deque:";
      for (size_type i = myData.myOff; i < myData.myOff + myData.mySize; i++) {
          size_type k = 0;
          size_type j = 0;
          k = i / dequeSize;
          j = i % dequeSize;
          if (k >= myData.mapSize)
              k %= myData.mapSize;
          cout << myData.map[k][j];
      }
      cout << endl;*/
      return begin() + static_cast< difference_type >( off );
   }

   // erase all
   void clear()
   {
      if( myData.mapSize > 0 )
      {
         for( size_type i = 0; i < myData.mapSize; i++ )
            if( myData.map[ i ] != nullptr )
               delete[] myData.map[ i ];
         delete[] myData.map;

         myData.mapSize = 0;
         myData.mySize = 0;
         myData.myOff = 0;
         myData.map = nullptr;
      }
   }

private:

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return myData.getBlock( off );
//      return ( ( myData.off / compDequeSize() ) & ( myData.mapSize - 1 ) );
   }

   void doubleMapSize()
   {
      if( myData.mapSize > 0 )
      {
         size_type oldMapSize = myData.mapSize;
         size_type dequeSize = compDequeSize();
         myData.mapSize *= 2;
         value_type **newMap = new value_type * [ myData.mapSize ]();
         for (size_type i = 0; i < myData.mapSize; i++) {
             newMap[i] = new value_type[dequeSize];
         }
         for (size_type i = myData.myOff; i < myData.myOff+myData.mySize; i++) {
             size_type row = i / dequeSize;
             size_type new_row = i / dequeSize;
             if (row >= oldMapSize) {
                 row %= oldMapSize;
             }
             newMap[new_row][i % dequeSize] = myData.map[row][i % dequeSize];
         }

         delete[] myData.map;

         myData.map = newMap;
      }
   }

   size_type compDequeSize()
   {
      return sizeof( value_type ) <= 1 ? 16 : sizeof( value_type ) <= 2 ? 8 :
             sizeof( value_type ) <= 4 ?  4 : sizeof( value_type ) <= 8 ? 2 : 1;
   }

   ScaryVal myData;
};

#endif