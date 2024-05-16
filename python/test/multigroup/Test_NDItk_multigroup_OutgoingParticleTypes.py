# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import OutgoingParticleTypes

class Test_NDItk_multigroup_OutgoingParticleTypes( unittest.TestCase ) :
    """Unit test for the OutgoingParticleTypes class."""

    chunk_values = [ 0, 1001 ]
    chunk_string = ( 'sec_part_types\n'
                     '    0 1001\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.number_outgoing_particles )
            self.assertAlmostEqual(    0, chunk.values[0] )
            self.assertAlmostEqual( 1001, chunk.values[1] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'sec_part_types', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 2, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = OutgoingParticleTypes( values = [ 0, 1001 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = OutgoingParticleTypes.from_string( self.chunk_string, 2 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
