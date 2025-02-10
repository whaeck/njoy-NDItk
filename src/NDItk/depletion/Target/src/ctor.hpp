/**
 *  @brief Default constructor
 */
Target():
  Record( base::Keyword( "target" ) ), 
  target_identifier_(),
  products_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] target_identifier
 *  @param[in] products
 */
Target( unsigned int target_identifier, std::vector< Product > products ):
  Record( base::Keyword( "target" ) ), 
  target_identifier_( target_identifier ),
  products_( std::move(products) ) {}
