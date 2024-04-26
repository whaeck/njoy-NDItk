# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import FluxWeights

class Test_NDItk_multigroup_FluxWeights( unittest.TestCase ) :
    """Unit test for the FluxWeights class."""

    chunk_values = [ 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 ]
    chunk_string = ( 'wgts\n'
                     '    0.1 0.2 0.25 0.05 0.15\n'
                     '    0.04 0.06\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 7, chunk.number_groups )
            self.assertAlmostEqual( 0.10, chunk.weights[0] )
            self.assertAlmostEqual( 0.20, chunk.weights[1] )
            self.assertAlmostEqual( 0.25, chunk.weights[2] )
            self.assertAlmostEqual( 0.05, chunk.weights[3] )
            self.assertAlmostEqual( 0.15, chunk.weights[4] )
            self.assertAlmostEqual( 0.04, chunk.weights[5] )
            self.assertAlmostEqual( 0.06, chunk.weights[6] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 7, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = FluxWeights( weights = [ 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
