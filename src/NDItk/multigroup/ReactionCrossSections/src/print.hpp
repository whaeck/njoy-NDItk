/**
 *  @brief Print the record (if it is not empty)
 *
 *  @param[in] iter   the current position in the output
 */
template< typename OutputIterator >
void print( OutputIterator& iter ) const {

  if ( ! this->empty() ) {

    for ( auto c : this->keyword() ) { *iter++ = c; }
    *iter++ = '\n';
    for ( const auto& entry : this->xs_ ) {

      entry.print( iter );
    }
  }
};
