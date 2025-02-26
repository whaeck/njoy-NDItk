/**
 *  @brief Print the record (if it is not empty)
 *
 *  @param[in] iter   the current position in the output
 */
template< typename OutputIterator >
void print( OutputIterator& iter, int indentLevel=2 ) const {

  if ( ! this->empty() ) {

    auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

    for ( auto c : indentPrefix(indentLevel) + this->keyword() + "\n" ) {
      *iter++ = c;
    }

    this->multiplicities_.print( iter, indentLevel+1 );

    std::ostringstream buffer;

/*
    buffer << indentPrefix(indentLevel) << this->key() << "\n";

    // write multiplicity subrecord to string, then insert into buffer
    std::string tmp;
    auto tmp_output = std::back_inserter(tmp);
    this->multiplicities_.print( tmp_output, indentLevel+1 );
    buffer << tmp;

    for ( auto c : buffer.str() ) { *iter++ = c; }
*/
  }
};
