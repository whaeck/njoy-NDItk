#ifndef NJOY_NDITK_MULTIGROUP
#define NJOY_NDITK_MULTIGROUP

// system includes

// other includes
#include "NDItk/multigroup/Metadata.hpp"
#include "NDItk/multigroup/Structure.hpp"
#include "NDItk/multigroup/FluxWeights.hpp"
#include "NDItk/multigroup/ReactionCrossSections.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A multigroup NDI table
 */
class MultigroupTable {

  /* fields */
  multigroup::Metadata metadata_;
  multigroup::Structure structure_;
  multigroup::FluxWeights weights_;
  multigroup::ReactionCrossSections xs_;

  template < typename Record, typename Iterator, typename... Arguments >
  static void readRecord( Record& record, Iterator& iter, const Iterator& end,
                          Arguments... arguments ) {

    if ( record.hasContent() ) {

      throw std::runtime_error( "Duplicate keyword" );
    }
    record.read( iter, end, arguments... );
  }

public:

  MultigroupTable() : metadata_(), structure_(), weights_(), xs_() {}

  const multigroup::Metadata& metadata() const { return this->metadata_; }
  const multigroup::Structure& structure() const { return this->structure_; }
  const multigroup::FluxWeights& flux() const { return this->weights_; }
  const multigroup::ReactionCrossSections& crossSections() const { return this->xs_; }

  /**
   *  @brief Print the NDI table
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->metadata_.print( iter );
    this->structure_.print( iter );
    this->weights_.print( iter );
    this->xs_.print( iter );
    *iter++ = 'e';
    *iter++ = 'n';
    *iter++ = 'd';
    *iter++ = '\n';
  };

  /**
   *  @brief Read the table content
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    std::string keyword;
    while ( ( keyword != "end" ) && ( iter != end ) ) {

      keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );

      if ( this->metadata_.isMetadataKey( keyword ) ) {

        this->metadata_.read( keyword, iter, end );
      }
      else if ( keyword == this->structure_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->structure_, iter, end, this->metadata_.numberGroups().value() + 1 );
        }
        else {

          throw std::runtime_error( "Required metadata is missing" );
        }
      }
      else if ( keyword == this->weights_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->weights_, iter, end, this->metadata_.numberGroups().value() + 1 );
        }
        else {

          throw std::runtime_error( "Required metadata is missing" );
        }
      }
      else if ( keyword == this->xs_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() && this->metadata_.numberReactions().has_value() ) {

          readRecord( this->xs_, iter, end, this->metadata_.numberReactions().value(), this->metadata_.numberGroups().value() );
        }
        else {

          throw std::runtime_error( "Required metadata is missing" );
        }
      }
      else {

        if ( keyword != "end" ) {

          throw std::runtime_error( std::string( "Unknown keyword: " ) + keyword );
        }
      }

      while ( std::isspace( *iter ) && iter != end ) {

        ++iter;
      }
    }
  };
};

} // NDItk namespace
} // njoy namespace

#endif
