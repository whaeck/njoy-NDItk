# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import CrossSection

class Test_NDItk_multigroup_CrossSection( unittest.TestCase ) :
    """Unit test for the CrossSection class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 7, chunk.number_groups )
            self.assertEqual( 2, chunk.identifier )
            self.assertAlmostEqual( 0, chunk.qvalue )
            self.assertAlmostEqual( 10, chunk.cross_sections[0] )
            self.assertAlmostEqual( 20, chunk.cross_sections[1] )
            self.assertAlmostEqual( 30, chunk.cross_sections[2] )
            self.assertAlmostEqual( 40, chunk.cross_sections[3] )
            self.assertAlmostEqual( 50, chunk.cross_sections[4] )
            self.assertAlmostEqual( 60, chunk.cross_sections[5] )
            self.assertAlmostEqual( 70, chunk.cross_sections[6] )

        # the data is given explicitly
        chunk = CrossSection( reaction = 2, qvalue = 0.0,
                              values = [ 10., 20., 30., 40., 50., 60., 70. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
