  /**
   *  @brief Read the record data
   *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input
 *  @param[in,out] reactions   the number of reactions
 *  @param[in,out] groups      the number of groups
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t reactions, std::size_t groups ) {

    // read in the data
    this->reactions_ = reactions;
    this->groups_ = groups;
    base::RealListRecord::read( iter, end, reactions * ( 2 + groups ) );
    this->generateBlocks();

    // verify
    verify( this->reactions() );
  };
