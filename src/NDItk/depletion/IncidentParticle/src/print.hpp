/**
*   @brief Print the record (if it is not empty)
*
*   @param[in] iter           the current position in the output
 *  @param[in] indentLevel    an optional specification for which indentation level to start printing at
*/
template< typename OutputIterator >
void print( OutputIterator& iter, int indentLevel=0 ) const {

  if ( this->numberTargets() > 0 ) {

    auto indentPrefix = [](int n){ return std::string(2*n, ' '); };
  
    std::ostringstream buffer;
  
    buffer << indentPrefix(indentLevel) << this->keyword() << "\n";

    buffer << indentPrefix(indentLevel+1) << this->incidentIdentifier() << "\n";

    buffer << indentPrefix(indentLevel+1) << "num_targets\n";
    buffer << indentPrefix(indentLevel+2) << this->numberTargets() << "\n";
    
    for (const auto& entry : this->targets() ) {

      std::string tmp;
      auto tmp_output = std::back_inserter(tmp);
      entry.print( tmp_output, indentLevel+1 );
      buffer << tmp;
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  }
}
