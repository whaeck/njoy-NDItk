/**
*   @brief Print the record 
*
*   @param[in] iter     the current position in the output
*/
template< typename OutputIterator >
void print( OutputIterator& iter ) const {

  auto indentLevel  = 1;
  auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

  std::ostringstream buffer;

  buffer << indentPrefix(indentLevel) << this->keyword() << "\n";

  buffer << indentPrefix(indentLevel+1) << this->targetIdentifier() << "\n";

  buffer << indentPrefix(indentLevel+1) << "num_products\n";
  buffer << indentPrefix(indentLevel+2) << this->numberProducts() << "\n";
  
  for (const auto& entry : this->products() ) {

    std::string tmp;
    auto tmp_output = std::back_inserter(tmp);
    entry.print( tmp_output );
    buffer << tmp;
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
}
