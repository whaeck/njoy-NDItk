# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import CrossSection

class Test_NDItk_multigroup_CrossSection( unittest.TestCase ) :
    """Unit test for the CrossSection class."""

    chunk_values = [ 2, 0, 10.0000000000001, 20., 30., 40.12345678, 50., 60., 70. ]
    chunk_string = ( '    2 0\n'
                     '    10.0000000000001 20 30 40.12345678 50\n'
                     '    60 70\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 7, chunk.number_groups )
            self.assertEqual( 2, chunk.identifier )
            self.assertAlmostEqual( 0, chunk.qvalue )
            self.assertAlmostEqual( 10.0000000000001, chunk.cross_sections[0] )
            self.assertAlmostEqual( 20, chunk.cross_sections[1] )
            self.assertAlmostEqual( 30, chunk.cross_sections[2] )
            self.assertAlmostEqual( 40.12345678, chunk.cross_sections[3] )
            self.assertAlmostEqual( 50, chunk.cross_sections[4] )
            self.assertAlmostEqual( 60, chunk.cross_sections[5] )
            self.assertAlmostEqual( 70, chunk.cross_sections[6] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 9, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = CrossSection( reaction = 2, qvalue = 0.0,
                              values = [ 10.0000000000001, 20., 30., 40.12345678, 50., 60., 70. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
