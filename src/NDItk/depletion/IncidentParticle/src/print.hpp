/**
*   @brief Print the record (if it is not empty)
*
*   @param[in] iter           the current position in the output
*/
template< typename OutputIterator >
void print( OutputIterator& iter ) const {

  if ( this->numberTargets() > 0 ) {

    auto indentLevel  = 0;
    auto indentPrefix = [](int n){ return std::string(2*n, ' '); };
  
    std::ostringstream buffer;
  
    buffer << indentPrefix(indentLevel) << this->keyword() << "\n";

    buffer << indentPrefix(indentLevel+1) << this->incidentIdentifier() << "\n";

    buffer << indentPrefix(indentLevel+1) << "num_targets\n";
    buffer << indentPrefix(indentLevel+2) << this->numberTargets() << "\n";
    
    for (const auto& entry : this->targets() ) {

      std::string tmp;
      auto tmp_output = std::back_inserter(tmp);
      entry.print( tmp_output );
      buffer << tmp;
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  }
}
