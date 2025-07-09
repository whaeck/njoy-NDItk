/**
 *  @brief Write the record data
 *
 *  This assumes that the record is not empty.
 *
 *  @param[in] iter   the current position in the output
 */
template< typename OutputIterator >
void print( OutputIterator& iter ) const {

  auto indentLevel  = 1;
  auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

  std::ostringstream buffer;

  buffer << indentPrefix(indentLevel) << this->numberInterpolationRegions() << "\n";

  for (int i=0; i < this->numberInterpolationRegions(); ++i) {

    buffer << indentPrefix(indentLevel) << this->boundaries()[i] 
           << indentPrefix(indentLevel) << this->interpolants()[i] << "\n";
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
};
