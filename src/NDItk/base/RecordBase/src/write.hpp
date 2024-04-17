
 void write( std::ostream& out ) {

  out << this->keyword() ;

  for( unsigned int i = 0; i < this->data().size(); ++i ) {

    out << " " << this->data()[i];
    if ( ( i + 1) % 6 == 0 ) {

      out << std::endl;
    }
  }

  if ( this->data().size() % 6 != 0 ) {

    out << std::endl;
  }
}
