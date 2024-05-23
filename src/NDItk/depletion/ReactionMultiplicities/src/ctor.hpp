private:

/**
 *  @brief Private intermediate constructor
 */
ReactionMultiplicities( std::vector< Multiplicities >&& multiplicities,
                        std::size_t reactions ) :
    IntegerListRecord( base::Keyword( "rprod" ), generateData( std::move( multiplicities ) ) ),
    reactions_( reactions ) {

  this->generateBlocks();
}

public:

/**
 *  @brief Default constructor
 */
ReactionMultiplicities() : IntegerListRecord( base::Keyword( "rprod" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
ReactionMultiplicities( std::vector< Multiplicities > multiplicities ) :
    ReactionMultiplicities( std::move( multiplicities ), multiplicities.size() ) {}

/**
 *  @brief Copy constructor
 */
ReactionMultiplicities( const ReactionMultiplicities& base ) :
    IntegerListRecord( base ), reactions_( base.reactions_ ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor
 */
ReactionMultiplicities( ReactionMultiplicities&& base ) :
    IntegerListRecord( std::move( base ) ), reactions_( base.reactions_ ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment
 */
ReactionMultiplicities& operator=( const ReactionMultiplicities& base ) {

  new (this) ReactionMultiplicities( base );
  return *this;
}

/**
 *  @brief Move assignment
 */
ReactionMultiplicities& operator=( ReactionMultiplicities&& base ) {

  new (this) ReactionMultiplicities( std::move( base ) );
  return *this;
}
