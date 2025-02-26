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
 *  @param[in] target_identifier
 *  @param[in] products
 */
Target( int target_identifier, std::vector< Product > products ):
  Record( base::Keyword( "target" ) ), 
  identifier_( target_identifier ),
  products_( std::move(products) ) {}
