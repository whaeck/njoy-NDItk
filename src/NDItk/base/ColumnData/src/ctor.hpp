/**
 *  @brief Default constructor
 */
ColumnData() = default;

/**
 *  @brief Constructor
 *
 *  @param[in] data     the data to be interpreted as columns
 */
ColumnData( std::vector<T> data ) :
  Parent( std::move(data) ) {

  verify( this->values() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the column data 
 *  @param[in] end      the end iterator of the column data
 */
ColumnData( Iterator begin, Iterator end ) :
  Parent( begin, end ) {

  verify( this->values() );
}
