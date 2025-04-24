  // Default constructor
  Library() = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] tables  a vector of NDI tables
   */
  Library( std::string header, std::vector<Table> tables ) 
  : header_( std::move(header) ), tables_( std::move( tables ) ) {}