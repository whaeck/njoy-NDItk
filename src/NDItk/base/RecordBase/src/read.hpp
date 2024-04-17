
template < typename Iterator >
static std:: vector< double >
read( const std::string& keyword, Iterator& iter, const Iterator& end, std::size_t size ) {

  using namespace njoy::tools::disco;

  std::vector< double > data;
  data.reserve(size);

  std::string key = FreeFormatCharacter::read< std::string >( iter, end );
  if ( key != keyword ) {

    throw std::runtime_error( "Error! Unexpected keyword." );
  }

  for( unsigned int i = 0; i < size; ++i ) {

    data.push_back( FreeFormatReal::read< double >( iter, end ) );
  }

  return data;
}
