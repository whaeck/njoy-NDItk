/**
 *  @brief Verify the multiplicity data values
 *
 *  The following verification tests are performed:
 *    - there are at least two values
 *    - the number of multiplicity values are more than zero
 *    - the number of multiplicity data match the declared length
 *
 *  @param[in] data    the data values in the cross section subrecord
 */
template < typename Range >
static void verify( const Range& data ) {

  if ( data.size() < 2 ) {

    Log::error( "Expected at least 2 data values consisting of a reaction product,\n"
                "and the number of reaction identifiers" );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }

  if ( data[1] < 0 ) {

    Log::error( "The number of reaction identifiers cannot be less than zero" );
    Log::info( "Found {} as the number of reaction identifiers", data[1] );
    throw std::exception();
  }

  if ( data.size() != 2 + 2 * data[1] ) {

    Log::error( "Expected at least {} data values consisting of a reactino product,\n"
                "the number of reaction identifiers (in this case equal to {}) followed\n"
                "by {} reaction identifier and multiplicity value pairs",
                2 + 2 * data[1], data[1], data[1] );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }
}
