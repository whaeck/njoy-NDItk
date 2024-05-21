/**
 *  @brief Read the record data
 *
 *  This function overrides the base record read() function to enable
 *  verification of the read data.
 *
 *  @param[in,out] iter     an iterator to the current position in the input
 *  @param[in,out] end      an iterator to the end of the input
 *  @param[in,out] groups   the number of weight values to be read
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end, std::size_t groups ) {

  base::RealListRecord::read( iter, end, groups );
  verify( this->weights() );
};
