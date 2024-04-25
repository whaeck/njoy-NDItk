  /**
   *  @brief Read the record data
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t reactions, std::size_t groups ) {

    this->reactions_ = reactions;
    this->groups_ = groups;
    base::RealListRecord::read( iter, end, reactions * ( 2 + groups ) );
    this->generateBlocks();
  };
