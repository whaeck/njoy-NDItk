/**
 *  @brief Write the record data
 *
 *  This assumes that the record is not empty.
 *
 *  @param[in] iter           the current position in the output
 *  @param[in] indent_level   an optional specification for which indentation level to start writing at
 */
template< typename OutputIterator >
void write( OutputIterator& iter, int indent_level=1 ) const {

  auto indent_prefix = [](int n){ return std::string(2*n, ' '); };

  std::ostringstream buffer;

  auto x = this->begin();
  buffer << indent_prefix(indent_level) << x[0] << '\n'
         << indent_prefix(indent_level) << x[1] << '\n';
  x += 2;

  auto lines = this->numberReactions();

  while ( lines-- ) {

    buffer << indent_prefix(indent_level) << x[0] << ' ' << x[1] << '\n';
    x += 2;
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
};
