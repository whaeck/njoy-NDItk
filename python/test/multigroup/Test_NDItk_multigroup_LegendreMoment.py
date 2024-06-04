# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import LegendreMoment

class Test_NDItk_multigroup_LegendreMoment( unittest.TestCase ) :
    """Unit test for the LegendreMoment class."""

    chunk_values = [ 2, 1.,  2.,  3., 4.,  5.,  6., 7.,  8.,  9., 10., 11., 12. ]
    chunk_string = ( '    2\n'
                     '    1 2 3 4 5\n'
                     '    6 7 8 9 10\n'
                     '    11 12\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.order )
            self.assertEqual( 4, chunk.number_primary_groups )
            self.assertEqual( 3, chunk.number_outgoing_groups )
            self.assertAlmostEqual(  1, chunk.matrix[0][0] )
            self.assertAlmostEqual(  2, chunk.matrix[0][1] )
            self.assertAlmostEqual(  3, chunk.matrix[0][2] )
            self.assertAlmostEqual(  4, chunk.matrix[1][0] )
            self.assertAlmostEqual(  5, chunk.matrix[1][1] )
            self.assertAlmostEqual(  6, chunk.matrix[1][2] )
            self.assertAlmostEqual(  7, chunk.matrix[2][0] )
            self.assertAlmostEqual(  8, chunk.matrix[2][1] )
            self.assertAlmostEqual(  9, chunk.matrix[2][2] )
            self.assertAlmostEqual( 10, chunk.matrix[3][0] )
            self.assertAlmostEqual( 11, chunk.matrix[3][1] )
            self.assertAlmostEqual( 12, chunk.matrix[3][2] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 13, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = LegendreMoment( order = 2,
                                values = [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 ],
                                incident = 4, outgoing = 3 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
