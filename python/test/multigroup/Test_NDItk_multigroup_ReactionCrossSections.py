# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import ReactionCrossSections
from NDItk.multigroup import CrossSection

class Test_NDItk_multigroup_ReactionCrossSections( unittest.TestCase ) :
    """Unit test for the ReactionCrossSections class."""

    chunk_values = [ 2, 0.,
                     10., 20., 30., 40., 50., 60., 70.,
                     16, 1.1234567,
                     1., 2., 3., 4., 5., 6., 7. ]
    chunk_string = ( 'sig_reac\n'
                     '    2 0\n'
                     '    10 20 30 40 50\n'
                     '    60 70\n'
                     '    16 1.1234567\n'
                     '    1 2 3 4 5\n'
                     '    6 7\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.number_reactions )
            self.assertEqual( 7, chunk.number_groups )

            self.assertEqual( True, chunk.has_reaction( 2 ) )
            self.assertEqual( True, chunk.has_reaction( 16 ) )
            self.assertEqual( False, chunk.has_reaction( 102 ) )

            self.assertEqual( 2, chunk.reactions[0].identifier )
            self.assertAlmostEqual( 0.0, chunk.reactions[0].qvalue )
            self.assertAlmostEqual( 10.0, chunk.reactions[0].cross_sections[0] )
            self.assertAlmostEqual( 20.0, chunk.reactions[0].cross_sections[1] )
            self.assertAlmostEqual( 30.0, chunk.reactions[0].cross_sections[2] )
            self.assertAlmostEqual( 40.0, chunk.reactions[0].cross_sections[3] )
            self.assertAlmostEqual( 50.0, chunk.reactions[0].cross_sections[4] )
            self.assertAlmostEqual( 60.0, chunk.reactions[0].cross_sections[5] )
            self.assertAlmostEqual( 70.0, chunk.reactions[0].cross_sections[6] )

            self.assertEqual( 16, chunk.reactions[1].identifier )
            self.assertAlmostEqual( 1.1234567, chunk.reactions[1].qvalue )
            self.assertAlmostEqual( 1.0, chunk.reactions[1].cross_sections[0] )
            self.assertAlmostEqual( 2.0, chunk.reactions[1].cross_sections[1] )
            self.assertAlmostEqual( 3.0, chunk.reactions[1].cross_sections[2] )
            self.assertAlmostEqual( 4.0, chunk.reactions[1].cross_sections[3] )
            self.assertAlmostEqual( 5.0, chunk.reactions[1].cross_sections[4] )
            self.assertAlmostEqual( 6.0, chunk.reactions[1].cross_sections[5] )
            self.assertAlmostEqual( 7.0, chunk.reactions[1].cross_sections[6] )

            xs = chunk.reaction( 2 )
            self.assertEqual( 2, xs.identifier )
            self.assertAlmostEqual( 0.0, xs.qvalue )
            self.assertAlmostEqual( 10.0, xs.cross_sections[0] )
            self.assertAlmostEqual( 20.0, xs.cross_sections[1] )
            self.assertAlmostEqual( 30.0, xs.cross_sections[2] )
            self.assertAlmostEqual( 40.0, xs.cross_sections[3] )
            self.assertAlmostEqual( 50.0, xs.cross_sections[4] )
            self.assertAlmostEqual( 60.0, xs.cross_sections[5] )
            self.assertAlmostEqual( 70.0, xs.cross_sections[6] )

            xs = chunk.reaction( 16 )
            self.assertEqual( 16, xs.identifier )
            self.assertAlmostEqual( 1.1234567, xs.qvalue )
            self.assertAlmostEqual( 1.0, xs.cross_sections[0] )
            self.assertAlmostEqual( 2.0, xs.cross_sections[1] )
            self.assertAlmostEqual( 3.0, xs.cross_sections[2] )
            self.assertAlmostEqual( 4.0, xs.cross_sections[3] )
            self.assertAlmostEqual( 5.0, xs.cross_sections[4] )
            self.assertAlmostEqual( 6.0, xs.cross_sections[5] )
            self.assertAlmostEqual( 7.0, xs.cross_sections[6] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'sig_reac', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 18, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = ReactionCrossSections( 
                  xs = [ CrossSection( 2, 0., [ 10., 20., 30., 40., 50., 60., 70. ] ), 
                         CrossSection( 16, 1.1234567, [ 1., 2., 3., 4., 5., 6., 7. ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ReactionCrossSections.from_string( self.chunk_string, 2, 7 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()

