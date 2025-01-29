/**
 *  @brief Verify the production/depletion chain product data values
 *
 *  The following verification tests are performed:
 *    - there are at least two values
 *    - the specified number of reaction identifiers and multiplicity values are present
 *
 *  @param[in] data    the data values in the cross section subrecord
 */
template < typename Range >
static void verify( const Range& data ) {

  if ( data.size() < 2 ) {

    Log::error( "Expected at least 2 data values consisting of a product identifier,\n"
                "and the number of reactions" );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }

  if ( data.size() != 2 + 2 * data[1] ) {

    Log::error( "Expected at least {} data values consisting of a product identifier,\n"
                "the number of reactions (in this case equal to {}) followed\n"
                "by {} reaction identifier and multiplicity value pairs",
                2 + 2 * data[1], data[1], data[1] );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }
}
