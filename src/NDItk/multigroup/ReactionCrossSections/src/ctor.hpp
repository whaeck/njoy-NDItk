private:

/**
 *  @brief Private intermediate constructor
 */
ReactionCrossSections( std::vector< CrossSection >&& xs,
                       std::size_t reactions, std::size_t groups ) :
    RealListRecord( base::Keyword( "sig_reac" ), generateData( std::move( xs ) ) ),
    reactions_( reactions ), groups_( groups ) {

  this->generateBlocks();
}

public:

/**
 *  @brief Default constructor
 */
ReactionCrossSections() : RealListRecord( base::Keyword( "sig_reac" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
ReactionCrossSections( std::vector< CrossSection > xs ) :
    ReactionCrossSections( std::move( xs ), xs.size(),
                           xs.size() == 0 ? 0 : xs.front().numberGroups() ) {}

/**
 *  @brief Copy constructor
 */
ReactionCrossSections( const ReactionCrossSections& base ) :
    RealListRecord( base ), reactions_( base.reactions_ ), groups_( base.groups_ ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor
 */
ReactionCrossSections( ReactionCrossSections&& base ) :
    RealListRecord( std::move( base ) ), reactions_( base.reactions_ ), groups_( base.groups_ ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment
 */
ReactionCrossSections& operator=( const ReactionCrossSections& base ) {

  new (this) ReactionCrossSections( base );
  return *this;
}

/**
 *  @brief Move assignment
 */
ReactionCrossSections& operator=( ReactionCrossSections&& base ) {

  new (this) ReactionCrossSections( std::move( base ) );
  return *this;
}
