/**
 *  @brief Generate the subrecords for this record
 */
void generateBlocks() {

  if ( ! this->empty() ) {

    this->xs_.clear();
    for ( unsigned int index = 0; index < this->numberReactions(); ++index ) {

      const auto left = this->values().begin() + index * ( 2 + this->numberGroups() );
      const auto right = left + 2 + this->numberGroups();
      this->xs_.emplace_back( left, right );
    }
  }
}
