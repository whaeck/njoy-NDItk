/**
*   @brief Print the record (if it is not empty)
*
*   @param[in] iter           the current position in the output
 *  @param[in] indent_level   an optional specification for which indentation level to start printing at
*/
template< typename OutputIterator >
void print( OutputIterator& iter, int indent_level=0 ) const {

  if ( this->numberProducts() > 0 ) {

    auto indent_prefix = [](int n){ return std::string(2*n, ' '); };
  
    std::ostringstream buffer;
  
    buffer << indent_prefix(indent_level) << this->keyword() << "\n";

    buffer << indent_prefix(indent_level+1) << this->targetIdentifier() << "\n";

    buffer << indent_prefix(indent_level+1) << "num_products\n";

    buffer << indent_prefix(indent_level+2) << this->numberProducts() << "\n";
    
    for (const auto& entry : this->products() ) {

      buffer << indent_prefix(indent_level+1) << "product\n";

      std::string tmp;
      auto tmp_output = std::back_inserter(tmp);
      entry.print( tmp_output, indent_level+2 );
      buffer << tmp;
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  }
}
