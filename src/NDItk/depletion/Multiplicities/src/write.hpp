/**
 *  @brief Write the record data
 *
 *  This assumes that the record is not empty.
 *
 *  @param[in] iter   the current position in the output
 */
template< typename OutputIterator >
void write( OutputIterator& iter ) const {

  auto indentLevel  = 3;
  auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

  std::ostringstream buffer;

  auto x = this->begin();
  buffer << indentPrefix(indentLevel) << x[0] << '\n'
         << indentPrefix(indentLevel) << x[1] << '\n';
  x += 2;

  auto lines = this->numberReactions();

  while ( lines-- ) {

    buffer << indentPrefix(indentLevel) << x[0] << ' ' << x[1] << '\n';
    x += 2;
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
};
