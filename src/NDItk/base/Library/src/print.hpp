/**
*   @brief Print the header and each table in the library
*
*   @param[in] iter     the current position in the output
*/
template< typename OutputIterator >
void print( OutputIterator& iter ) const {

  std::ostringstream buffer;

  buffer << this->header();

  for (const auto& entry : this->tables() ) {

    std::string tmp;
    auto tmp_output = std::back_inserter(tmp);
    entry.print( tmp_output );
    buffer << "\n" << tmp;
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
}
