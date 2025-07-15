/**
 *  @brief Write the record data
 *
 *  This assumes that the record is not empty.
 *
 *  @param[in] iter   the current position in the output
 */
template< typename OutputIterator >
void write( OutputIterator& iter ) const {

  auto indentLevel  = 1;
  auto indentPrefix = [](int n){ return std::string(2*n, ' '); };
  auto maskFirst    = [](int i){ return ( (i == 0) ? 1 : 0 );  };

  std::ostringstream buffer;
  buffer << std::setprecision(15);
         

  auto nrow = this->size() / this->numberColumns();

  for (int i=0; i < nrow; ++i) {

    for (int j=0; j < this->numberColumns(); ++j) {

      buffer << indentPrefix( (indentLevel-1)*maskFirst(i) + 1 ) 
             << this->value( i*this->numberColumns() + j );
    }

    buffer << "\n";
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
};
