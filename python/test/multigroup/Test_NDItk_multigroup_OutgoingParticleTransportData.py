# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import OutgoingParticleTransportData

class Test_NDItk_multigroup_OutgoingParticleTransportData( unittest.TestCase ) :
    """Unit test for the OutgoingParticleTransportData class."""

    chunk_values = [ 0, 1001 ]
    chunk_string = ( 'sec_part_zaids\n'
                     '    92000 92235.proton\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.number_outgoing_particles )
            self.assertAlmostEqual( "92000", chunk.values[0] )
            self.assertAlmostEqual( "92235.proton", chunk.values[1] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'sec_part_zaids', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 2, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = OutgoingParticleTransportData( values = [ '92000', '92235.proton' ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = OutgoingParticleTransportData.from_string( self.chunk_string, 2 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
