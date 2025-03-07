/**
 *  @brief Default constructor
 */
Product() : 
    IntegerListRecord( base::Keyword( "product" ) ),
    multiplicities_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] multiplicities   a depletion::Multiplicities SubListRecord
 */
Product( Multiplicities multiplicities ) : 
    IntegerListRecord( base::Keyword( "product" ), 
                       generateData( std::move( multiplicities ) ) ),
    multiplicities_( this->begin(), this->end() ) {}

/**
 *  @brief Copy constructor
 */
Product( const Product& base ) : 
    IntegerListRecord( base ),
    multiplicities_( this->begin(), this->end() ) {}


/**
 *  @brief Move constructor
 */
Product( Product&& base ) : 
    IntegerListRecord( std::move( base ) ), 
    multiplicities_( this->begin(), this->end() ) {}


/**
 *  @brief Copy assignment
 */
Product& operator=( const Product& base ) {

  if ( this != &base ) {

    base::IntegerListRecord::operator=( base );
    this->multiplicities_ = Multiplicities( this->begin(), this->end() );
  }
  return *this;
}

/**
 *  @brief Move assignment
 */
Product& operator=( Product&& base ) {

  if ( this != &base ) {

    base::IntegerListRecord::operator=( std::move( base ) );
    this->multiplicities_ = Multiplicities( this->begin(), this->end() );
  }
  return *this;
}
