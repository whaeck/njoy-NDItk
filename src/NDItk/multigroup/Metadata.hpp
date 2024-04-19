#ifndef NJOY_NDITK_MULTIGROUP_METADATA
#define NJOY_NDITK_MULTIGROUP_METADATA

// system includes

// other includes
#include "NDItk/base/SingleIntegerRecord.hpp"
#include "NDItk/base/SingleRealRecord.hpp"
#include "NDItk/base/SingleStringRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief Metadata associated to a neutron NDI file
 */
class Metadata {

  /* fields */
  base::SingleStringRecord zaid_;
  base::SingleStringRecord library_name_;
  base::SingleStringRecord source_date_;
  base::SingleStringRecord process_date_;
  base::SingleRealRecord awr_;
  base::SingleRealRecord atomic_weight_;
  base::SingleRealRecord temperature_;
  base::SingleRealRecord dilution_;
  base::SingleIntegerRecord groups_;
  base::SingleIntegerRecord upscatter_;
  base::SingleIntegerRecord downscatter_;
  base::SingleIntegerRecord legendre_order_;
  base::SingleIntegerRecord reactions_;

  template < typename Record, typename Iterator >
  static void readRecord( Record& record, Iterator& iter, const Iterator& end ) {

    if ( record.content().has_value() ) {

      throw std::runtime_error( "Duplicate keyword" );
    }
    record.read( iter, end );
  }

public:

  Metadata() : zaid_( "zaid" ), library_name_( "library_name" ), source_date_( "date_source" ),
               process_date_( "date_processed" ), awr_( "awr" ), atomic_weight_( "at_wgt" ),
               temperature_( "temp" ), dilution_( "sig_0" ), groups_( "num_grps" ),
               upscatter_( "up_grps" ), downscatter_( "down_grps" ),
               legendre_order_( "pn_order" ), reactions_( "num_reac" ) {}

  Metadata( std::string zaid, std::string libname, std::string source, std::string process,
            double awr, double weight, double temperature, double dilution,
            unsigned int groups, unsigned int upscatter, unsigned int downscatter,
            unsigned int order, unsigned int reactions ) :
      zaid_( "zaid", std::move( zaid ) ), library_name_( "library_name", std::move( libname ) ),
      source_date_( "date_source", std::move( source ) ),
      process_date_( "date_processed", std::move( process ) ),
      awr_( "awr", awr ), atomic_weight_( "at_wgt", weight ), temperature_( "temp", temperature ),
      dilution_( "sig_0", dilution ), groups_( "num_grps", groups ),
      upscatter_( "up_grps", upscatter ), downscatter_( "down_grps", downscatter ),
      legendre_order_( "pn_order", order ), reactions_( "num_reac", reactions ) {}

  bool isMetadataKey( const std::string& keyword ) const {

    return ( keyword == "zaid" ) || ( keyword == "library_name" ) || ( keyword == "date_source" ) ||
           ( keyword == "date_processed" ) || ( keyword == "awr" ) || ( keyword == "at_wgt" ) ||
           ( keyword == "temp" ) || ( keyword == "sig_0" ) || ( keyword == "num_grps" ) ||
           ( keyword == "up_grps" ) || ( keyword == "down_grps" ) || ( keyword == "pn_order" ) ||
           ( keyword == "num_reac" );
  }

  decltype(auto) zaid() const { return this->zaid_.content(); }
  decltype(auto) libraryName() const { return this->library_name_.content(); }
  decltype(auto) sourceData() const { return this->source_date_.content(); }
  decltype(auto) processDate() const { return this->process_date_.content(); }
  decltype(auto) atomicWeightRatio() const { return this->awr_.content(); }
  decltype(auto) atomicWeight() const { return this->atomic_weight_.content(); }
  decltype(auto) temperature() const { return this->temperature_.content(); }
  decltype(auto) dilution() const { return this->dilution_.content(); }
  decltype(auto) numberGroups() const { return this->groups_.content(); }
  decltype(auto) numberUpscatterGroups() const { return this->upscatter_.content(); }
  decltype(auto) numberDownscatterGroups() const { return this->downscatter_.content(); }
  decltype(auto) legendreOrder() const { return this->legendre_order_.content(); }
  decltype(auto) numberReactions() const { return this->reactions_.content(); }

  /**
   *  @brief Read the metadata record content
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( const std::string& keyword, Iterator& iter, const Iterator& end ) {

    if      ( keyword == this->zaid_.keyword() )           { readRecord( this->zaid_, iter, end ); }
    else if ( keyword == this->library_name_.keyword() )   { readRecord( this->library_name_, iter, end ); }
    else if ( keyword == this->source_date_.keyword() )    { readRecord( this->source_date_, iter, end ); }
    else if ( keyword == this->process_date_.keyword() )   { readRecord( this->process_date_, iter, end ); }
    else if ( keyword == this->awr_.keyword() )            { readRecord( this->awr_, iter, end ); }
    else if ( keyword == this->atomic_weight_.keyword() )  { readRecord( this->atomic_weight_, iter, end ); }
    else if ( keyword == this->temperature_.keyword() )    { readRecord( this->temperature_, iter, end ); }
    else if ( keyword == this->dilution_.keyword() )       { readRecord( this->dilution_, iter, end ); }
    else if ( keyword == this->groups_.keyword() )         { readRecord( this->groups_, iter, end ); }
    else if ( keyword == this->upscatter_.keyword() )      { readRecord( this->upscatter_, iter, end ); }
    else if ( keyword == this->downscatter_.keyword() )    { readRecord( this->downscatter_, iter, end ); }
    else if ( keyword == this->legendre_order_.keyword() ) { readRecord( this->legendre_order_, iter, end ); }
    else if ( keyword == this->reactions_.keyword() )      { readRecord( this->reactions_, iter, end ); }
    else {

      throw std::runtime_error( "Unknown keyword" );
    }
  };

  /**
   *  @brief Print the metadata
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->zaid_.print( iter );
    this->library_name_.print( iter );
    this->source_date_.print( iter );
    this->process_date_.print( iter );
    this->awr_.print( iter );
    this->atomic_weight_.print( iter );
    this->temperature_.print( iter );
    this->dilution_.print( iter );
    this->groups_.print( iter );
    this->upscatter_.print( iter );
    this->downscatter_.print( iter );
    this->legendre_order_.print( iter );
    this->reactions_.print( iter );
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
