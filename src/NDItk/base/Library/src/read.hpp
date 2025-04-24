/**
 *  @brief Read the header (if present) and all tables in the library
 *
 *  @param[in] iter   the current position in the input
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end ) {

  // read until start of first table as signified by the 'zaid' keyword
  Iterator headerStart = iter;

  std::string tableStartKeyword = "zaid";

  std::string keyword;
  while ( ( keyword != tableStartKeyword ) and ( iter != end ) ) {

    keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );
  }

  // 'undo' the last word ("zaid") read by disco 
  iter = std::prev( iter, tableStartKeyword.length() );

  // store all of the content before tables in a header string 
  this->header_ = std::string( headerStart, iter );
  this->header_.pop_back(); // header picks up an extra newline somehow? --> get rid of it

  // read the tables until the end
  while( iter != end ) {

    Table table; 
    table.read( iter, end );

    this->tables_.push_back( table );
  }   
}