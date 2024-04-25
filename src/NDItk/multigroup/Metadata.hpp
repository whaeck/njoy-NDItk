#ifndef NJOY_NDITK_MULTIGROUP_METADATA
#define NJOY_NDITK_MULTIGROUP_METADATA

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/SingleIntegerRecord.hpp"
#include "NDItk/base/SingleRealRecord.hpp"
#include "NDItk/base/SingleStringRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief Metadata associated with a neutron NDI file
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
  base::SingleIntegerRecord reactions_;

  /* auxiliary functions */

  #include "NDItk/multigroup/Metadata/src/readRecord.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/Metadata/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return wether or not a given key corresponds to a metadata key
   */
  bool isMetadataKey( const std::string& keyword ) const {

    return ( keyword == "zaid" ) || ( keyword == "library_name" ) || ( keyword == "date_source" ) ||
           ( keyword == "date_processed" ) || ( keyword == "awr" ) || ( keyword == "at_wgt" ) ||
           ( keyword == "temp" ) || ( keyword == "sig_0" ) || ( keyword == "num_grps" ) ||
           ( keyword == "num_reac" );
  }

  /**
   *  @brief Return the zaid of the table
   */
  decltype(auto) zaid() const { return this->zaid_.data(); }

  /**
   *  @brief Return the library name
   */
  decltype(auto) libraryName() const { return this->library_name_.data(); }

  /**
   *  @brief Return the source date
   */
  decltype(auto) sourceData() const { return this->source_date_.data(); }

  /**
   *  @brief Return the processing date
   */
  decltype(auto) processDate() const { return this->process_date_.data(); }

  /**
   *  @brief Return the atomic weight ratio of the target (with respect
   *         to the neutron mass)
   */
  decltype(auto) atomicWeightRatio() const { return this->awr_.data(); }

  /**
   *  @brief Return the atomic weight of the target
   */
  decltype(auto) atomicWeight() const { return this->atomic_weight_.data(); }

  /**
   *  @brief Return the temperature of the target
   */
  decltype(auto) temperature() const { return this->temperature_.data(); }

  /**
   *  @brief Return the dilution (aka sigma0)
   */
  decltype(auto) dilution() const { return this->dilution_.data(); }

  /**
   *  @brief Return the number of groups in the primary group structure
   */
  decltype(auto) numberGroups() const { return this->groups_.data(); }

  /**
   *  @brief Return the number of reactions defined in the table
   */
  decltype(auto) numberReactions() const { return this->reactions_.data(); }

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
    else if ( keyword == this->reactions_.keyword() )      { readRecord( this->reactions_, iter, end ); }
    else {

      Log::error( "Record with keyword \'{}\' is not part of the "
                  "multigroup metadata", keyword );
      throw std::exception();
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
    this->reactions_.print( iter );
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
