# standard imports
import unittest

# third party imports

# local imports
from NDItk.thermonuclear import Temperatures

class Test_NDItk_thermonuclear_Temperatures( unittest.TestCase ) :
    """Unit test for the Temperatures class."""

    chunk_values = [ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7 ]
    chunk_string = ( 'temps\n'
                     '    0.1 0.2 0.3 0.4 0.5\n'
                     '    0.6 0.7\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 7, chunk.number_temperatures )
            self.assertAlmostEqual( 0.1, chunk.values[0] )
            self.assertAlmostEqual( 0.2, chunk.values[1] )
            self.assertAlmostEqual( 0.3, chunk.values[2] )
            self.assertAlmostEqual( 0.4, chunk.values[3] )
            self.assertAlmostEqual( 0.5, chunk.values[4] )
            self.assertAlmostEqual( 0.6, chunk.values[5] )
            self.assertAlmostEqual( 0.7, chunk.values[6] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'temps', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 7, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = Temperatures( values = [ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Temperatures.from_string( self.chunk_string, 7 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
