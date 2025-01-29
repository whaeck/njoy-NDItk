# standard imports
import unittest

# third party imports

# local imports
from NDItk.depletion import Product

class Test_NDItk_depletion_Product( unittest.TestCase ) :
    """Unit test for the Product class."""

    chunk_values = [ 1001, 5, 28, 1, 45, 1, 103, 1, 111, 2, 112, 1 ]
    chunk_string = ( '    1001\n'
                     '    5\n'
                     '    28 1\n'
                     '    45 1\n'
                     '    103 1\n'
                     '    111 2\n'
                     '    112 1\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 5, chunk.number_reactions )
            self.assertEqual( 5, len( chunk.reaction_identifiers ) )
            self.assertEqual( 5, len( chunk.multiplicities ) )
            self.assertEqual( 1001, chunk.reaction_product )
            self.assertEqual( 28,  chunk.reaction_identifiers[0] )
            self.assertEqual( 45,  chunk.reaction_identifiers[1] )
            self.assertEqual( 103, chunk.reaction_identifiers[2] )
            self.assertEqual( 111, chunk.reaction_identifiers[3] )
            self.assertEqual( 112, chunk.reaction_identifiers[4] )
            self.assertEqual( 1, chunk.multiplicities[0] )
            self.assertEqual( 1, chunk.multiplicities[1] )
            self.assertEqual( 1, chunk.multiplicities[2] )
            self.assertEqual( 2, chunk.multiplicities[3] )
            self.assertEqual( 1, chunk.multiplicities[4] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 12, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = Product( product = 1001, reactions = [ 28, 45, 103, 111, 112 ],
                                multiplicities = [ 1, 1, 1, 2, 1 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
