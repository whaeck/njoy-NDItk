Structure() : RealListRecord( "e_bounds" ) {}
Structure( unsigned int particle ) :
    RealListRecord( std::string( "e_bounds_" ) + std::to_string( particle ) ) {}

Structure( std::vector< double > boundaries ) :
    RealListRecord( "e_bounds", std::move( boundaries ) ) {}
Structure( unsigned int particle, std::vector< double > boundaries ) :
    RealListRecord( std::string( "e_bounds_" ) + std::to_string( particle ),
                    std::move( boundaries ) ) {}
