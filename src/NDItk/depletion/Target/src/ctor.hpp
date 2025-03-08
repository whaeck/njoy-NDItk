/**
 *  @brief Default constructor
 */
Target():
  Record( base::Keyword( "target" ) ), 
  identifier_(),
  products_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] identifier   target particle identifier
 *  @param[in] products     vector of depletion products
 */
Target( int identifier, std::vector< Product > products ):
  Record( base::Keyword( "target" ) ), 
  identifier_( identifier ),
  products_( std::move(products) ) {

    verify( this->products() );
  }
