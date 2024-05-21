/**
 *  @brief Write the record content
 *
 *  This assumes that the record is not empty.
 *
 *  @param[in] iter   the current position in the output
 */
template< typename OutputIterator >
void write( OutputIterator& iter ) const {

  std::ostringstream buffer;

  auto full = this->data().size() / 5;
  auto partial = this->data().size() - full * 5;
  auto x = this->data().begin();

  while ( full-- ) {

    buffer << "    " << x[0];
    buffer << ' ' << x[1];
    buffer << ' ' << x[2];
    buffer << ' ' << x[3];
    buffer << ' ' << x[4] << '\n';
    x += 5;
  }

  if ( partial ) {

    buffer << "   ";
    while ( partial-- ) {

      buffer << ' ' << *x;
      ++x;
    }
     buffer << '\n';
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
};
