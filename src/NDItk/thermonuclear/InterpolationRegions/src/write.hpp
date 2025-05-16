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

  std::ostringstream buffer;

  buffer << indentPrefix(indentLevel) << this->numberRegions() << "\n";

  for (int i=0; i < this->numberRegions(); ++i) {

    buffer << indentPrefix(indentLevel) << this->regionEndIndex(i)+1 
           << indentPrefix(indentLevel) << this->regionInterpolationType(i) << "\n";
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
};
