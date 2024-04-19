SubListRecord() = default;

SubListRecord( const SubListRecord& base ) {

  *this = base;
}

SubListRecord( SubListRecord&& base ) {

  *this = std::move( base );
}

SubListRecord( const Iterator& begin, const Iterator& end ) :
  values_( std::nullopt ),
  begin_( begin ), end_( end ),
  length_( std::distance( begin, end ) ) {}

SubListRecord( std::vector< Type > values ) :
  values_( std::move( values ) ) {

  this->begin_ = this->values_->begin();
  this->end_ = this->values_->end();
  this->length_ = this->values_->size();
}

SubListRecord& operator=( const SubListRecord& right ) {

  this->values_ = right.values_;
  if ( this->owner() ) {

    this->begin_ = this->values_->begin();
    this->end_ = this->values_->end();
    this->length_ = this->values_->size();
  }
  else {

    this->begin_ = right.begin_;
    this->end_ = right.end_;
    this->length_ = right.length_;
  }
  return *this;
}

SubListRecord& operator=( SubListRecord&& right ) {

  this->values_ = std::move( right.values_ );
  if ( this->owner() ) {

    this->begin_ = this->values_->begin();
    this->end_ = this->values_->end();
    this->length_ = this->values_->size();
  }
  else {

    this->begin_ = right.begin_;
    this->end_ = right.end_;
    this->length_ = right.length_;
  }
  return *this;
}
