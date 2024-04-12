/**
 *  @brief Constructor
 *
 *  @param data   the data of the record
 */
RecordBase( std::vector<double> data ):
  data_( std::move( data ) ) {}

  /**
 *  @brief Constructor
 *
 *  @param in   the input stream 
 */
RecordBase( std::istream& in , std::size_t size, const std::string& keyword):
  RecordBase(Derived::read(in, size, keyword)) {}