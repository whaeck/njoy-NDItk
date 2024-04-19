#ifndef NJOY_NDITK_MULTIGROUP_REACTIONCROSSSECTIONS
#define NJOY_NDITK_MULTIGROUP_REACTIONCROSSSECTIONS

// system includes
#include <algorithm>
#include <iostream>

// other includes
#include "NDItk/base/RealListRecord.hpp"
#include "NDItk/multigroup/CrossSection.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A reaction cross section record
 */
class ReactionCrossSections : protected base::RealListRecord {

  /* fields */
  std::vector< CrossSection > xs_;
  std::size_t groups_;
  std::size_t reactions_;

  /* auxiliary functions */

  void generateBlocks() {

    if ( this->hasContent() ) {

      this->xs_.clear();
      for ( unsigned int index = 0; index < this->numberReactions(); ++index ) {

        const auto left = this->content()->begin() + index * ( 2 + this->numberGroups() );
        const auto right = left + 2 + this->numberGroups();
        this->xs_.emplace_back( left, right );
      }
    }
  }

  static std::vector< double > generateData( std::vector< CrossSection > xs ) {

    std::vector< double > data;
    data.reserve( xs.size() * ( 2 + xs.front().numberGroups() ) );
    for ( auto&& entry : xs ) {

      data.insert( data.end(), entry.begin(), entry.end() );
    }
    return data;
  }

  ReactionCrossSections( std::vector< CrossSection >&& xs,
                         std::size_t reactions, std::size_t groups ) :
      RealListRecord( "sig_reac", generateData( std::move( xs ) ) ),
      reactions_( reactions ), groups_( groups ) {

    this->generateBlocks();
  }

public:

  ReactionCrossSections() : RealListRecord( "sig_reac" ) {}

  ReactionCrossSections( std::vector< CrossSection > xs ) :
      ReactionCrossSections( std::move( xs ), xs.size(), xs.front().numberGroups() ) {}

  ReactionCrossSections( const ReactionCrossSections& base ) :
    RealListRecord( base ), reactions_( base.reactions_ ), groups_( base.groups_ ) {

    this->generateBlocks();
  }

  ReactionCrossSections( ReactionCrossSections&& base ) :
    RealListRecord( std::move( base ) ), reactions_( base.reactions_ ), groups_( base.groups_ ) {

    this->generateBlocks();
  }

  ReactionCrossSections& operator=( const ReactionCrossSections& base ) {

    new (this) ReactionCrossSections( base );
    return *this;
  }

  ReactionCrossSections& operator=( ReactionCrossSections&& base ) {

    new (this) ReactionCrossSections( std::move( base ) );
    return *this;
  }

  using base::RealListRecord::keyword;

  decltype(auto) data() const { return this->content(); }

  /**
   *  @brief Return the number of groups
   */
  std::size_t numberGroups() const {

      return this->groups_;
  }

  /**
   *  @brief Return the number of reactions
   */
  std::size_t numberReactions() const {

    return this->reactions_;
  }

  /**
   *  @brief Return the cross section for all reactions
   */
  const std::vector< CrossSection >& reactions() const {

    return this->xs_;
  }

  using base::RealListRecord::hasContent;

  /**
   *  @brief Verify whether or not a given reaction is present
   *
   *  @param[in] reaction   the reaction to look for
   */
  bool hasReaction( int reaction ) const {

    auto iter = std::find_if( this->reactions().begin(), this->reactions().end(),
                              [reaction] ( const auto& entry ) {

                                return entry.reaction() == reaction; } );
    return iter != this->reactions().end();
  }

  /**
   *  @brief Return the cross section for a given reaction
   *
   *  @param[in] reaction   the reaction to look for
   */
  const CrossSection& crossSection( int reaction ) const {

    auto iter = std::find_if( this->reactions().begin(), this->reactions().end(),
                              [reaction] ( const auto& entry ) {

                                return entry.reaction() == reaction; } );
    if ( iter != this->reactions().end() ){

      return *iter;
    }
    else {

      throw std::runtime_error( "reaction not defined" );
    }
  }

  /**
   *  @brief Read the record content
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t reactions, std::size_t groups ) {

    this->reactions_ = reactions;
    this->groups_ = groups;
    base::RealListRecord::read( iter, end, reactions * ( 2 + groups ) );
    this->generateBlocks();
  };

  /**
   *  @brief Print the record (if it has content)
   *
   *  Printing the data contained in the record is delegated to the
   *  derived class which knows how to format the data.
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    if ( this->content().has_value() ) {

      for ( auto c : this->keyword() ) { *iter++ = c; }
      *iter++ = '\n';
      for ( const auto& entry : this->xs_ ) {

        entry.print( iter );
      }
    }
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
