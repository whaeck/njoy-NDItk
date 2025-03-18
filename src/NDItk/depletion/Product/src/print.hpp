/**
 *  @brief Print the record (if it is not empty)
 *
 *  @param[in] iter   the current position in the output
 */
template< typename OutputIterator >
void print( OutputIterator& iter ) const {

  if ( ! this->empty() ) {

    auto indentLevel  = 2;
    auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

    for ( auto c : indentPrefix(indentLevel) + this->keyword() + "\n" ) {
      *iter++ = c;
    }

    this->multiplicities_.print( iter );
  }
};
