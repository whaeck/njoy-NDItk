/**
 *  @brief Constructor
 *
 *  @param data   the data of the record
 */
RecordBase( std::vector< double > data ) : data_( std::move( data ) ) {}

/**
 *  @brief Constructor
 *
 *  @param in   the input stream
 */
template < typename Iterator >
RecordBase( const std::string& key, Iterator& iter, const Iterator& end, std::size_t size ) :
  RecordBase( Derived::read( key, iter, end, size ) ) {}