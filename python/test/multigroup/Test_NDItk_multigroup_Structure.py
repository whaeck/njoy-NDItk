# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import Structure

class Test_NDItk_multigroup_Structure( unittest.TestCase ) :
    """Unit test for the Structure class."""

    chunk_values = [ 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 ]
    chunk_string = ( 'e_bounds\n'
                     '    20 18 16 14 10\n'
                     '    5 1 1e-11\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 7, chunk.number_groups )
            self.assertAlmostEqual(    20, chunk.boundaries[0] )
            self.assertAlmostEqual(    18, chunk.boundaries[1] )
            self.assertAlmostEqual(    16, chunk.boundaries[2] )
            self.assertAlmostEqual(    14, chunk.boundaries[3] )
            self.assertAlmostEqual(    10, chunk.boundaries[4] )
            self.assertAlmostEqual(     5, chunk.boundaries[5] )
            self.assertAlmostEqual(     1, chunk.boundaries[6] )
            self.assertAlmostEqual( 1e-11, chunk.boundaries[7] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 8, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = Structure( weights = [ 20., 18., 16., 14., 10., 5, 1, 1e-11 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
