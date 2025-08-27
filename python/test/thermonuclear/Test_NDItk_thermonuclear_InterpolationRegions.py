# standard imports
import unittest

# third party imports

# local imports
from NDItk.thermonuclear import InterpolationRegions

class Test_NDItk_thermonuclear_InterpolationRegions( unittest.TestCase ) :
    """Unit test for the InterpolationRegions class."""

    chunk_values = [ 3,1, 6,2, 9,3, 12,4, 15,5 ]

    chunk_string = ( '  5\n'
                     '  3  1\n' 
                     '  6  2\n' 
                     '  9  3\n' 
                     '  12  4\n' 
                     '  15  5\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 5, chunk.number_interpolation_regions )
            self.assertEqual( 3,  chunk.boundaries[0] )
            self.assertEqual( 6,  chunk.boundaries[1] )
            self.assertEqual( 9,  chunk.boundaries[2] )
            self.assertEqual( 12, chunk.boundaries[3] )
            self.assertEqual( 15, chunk.boundaries[4] )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.interpolants[1] )
            self.assertEqual( 3, chunk.interpolants[2] )
            self.assertEqual( 4, chunk.interpolants[3] )
            self.assertEqual( 5, chunk.interpolants[4] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 10, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = InterpolationRegions( endIndices  = [ 3, 6, 9, 12, 15 ], 
                                      interpTypes = [ 1, 2, 3,  4,  5 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
