# standard imports
import unittest

# third party imports

# local imports
from NDItk.depletion import Target
from NDItk.depletion import Multiplicities
from NDItk.depletion import Product

class Test_NDItk_depletion_Target( unittest.TestCase ) :
    """Unit test for the Target class."""

    chunk_string = (
         "  target\n"
         "    3006\n"
         "    num_products\n"
         "      6\n"
         "    product\n"
         "      1001\n"
         "      2\n"
         "      24 1\n"
         "      103 1\n"
         "    product\n"
         "      1002\n"
         "      1\n"
         "      32 1\n"
         "    product\n"
         "      1003\n"
         "      1\n"
         "      105 1\n"
         "    product\n"
         "      2004\n"
         "      3\n"
         "      24 1\n"
         "      32 1\n"
         "      105 1\n"
         "    product\n"
         "      2006\n"
         "      1\n"
         "      103 1\n"
         "    product\n"
         "      3007\n"
         "      1\n"
         "      102 1\n"
    )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3006, chunk.target_identifier )
            self.assertEqual(    6, chunk.number_products )

            self.assertEqual( 1001, chunk.products[0].reaction_product )
            self.assertEqual(    2, chunk.products[0].number_reactions )
            self.assertEqual(   24, chunk.products[0].reaction_identifiers[0] )
            self.assertEqual(  103, chunk.products[0].reaction_identifiers[1] )
            self.assertEqual(    1, chunk.products[0].multiplicities[0] )
            self.assertEqual(    1, chunk.products[0].multiplicities[1] )

            self.assertEqual( 1002, chunk.products[1].reaction_product )
            self.assertEqual(    1, chunk.products[1].number_reactions )
            self.assertEqual(   32, chunk.products[1].reaction_identifiers[0] )
            self.assertEqual(    1, chunk.products[1].multiplicities[0] )

            self.assertEqual( 1003, chunk.products[2].reaction_product )
            self.assertEqual(    1, chunk.products[2].number_reactions )
            self.assertEqual(  105, chunk.products[2].reaction_identifiers[0] )
            self.assertEqual(    1, chunk.products[2].multiplicities[0] )

            self.assertEqual( 2004, chunk.products[3].reaction_product )
            self.assertEqual(    3, chunk.products[3].number_reactions )
            self.assertEqual(   24, chunk.products[3].reaction_identifiers[0] )
            self.assertEqual(   32, chunk.products[3].reaction_identifiers[1] )
            self.assertEqual(  105, chunk.products[3].reaction_identifiers[2] )
            self.assertEqual(    1, chunk.products[3].multiplicities[0] )
            self.assertEqual(    1, chunk.products[3].multiplicities[1] )
            self.assertEqual(    1, chunk.products[3].multiplicities[2] )

            self.assertEqual( 2006, chunk.products[4].reaction_product )
            self.assertEqual(    1, chunk.products[4].number_reactions )
            self.assertEqual(  103, chunk.products[4].reaction_identifiers[0] )
            self.assertEqual(    1, chunk.products[4].multiplicities[0] )

            self.assertEqual( 3007, chunk.products[5].reaction_product )
            self.assertEqual(    1, chunk.products[5].number_reactions )
            self.assertEqual(  102, chunk.products[5].reaction_identifiers[0] )
            self.assertEqual(    1, chunk.products[5].multiplicities[0] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'target', chunk.keyword )

        # the data is given explicitly
        chunk = Target(
            identifier = 3006,
            products = [
                Product(Multiplicities( product = 1001, reactions = [ 24, 103 ], multiplicities = [ 1, 1 ] )),
                Product(Multiplicities( product = 1002, reactions = [ 32 ], multiplicities = [ 1 ] )),
                Product(Multiplicities( product = 1003, reactions = [ 105 ], multiplicities = [ 1 ] )),
                Product(Multiplicities( product = 2004, reactions = [ 24, 32, 105 ], multiplicities = [ 1, 1, 1 ] )),
                Product(Multiplicities( product = 2006, reactions = [ 103 ], multiplicities = [ 1 ] )),
                Product(Multiplicities( product = 3007, reactions = [ 102 ], multiplicities = [ 1 ] ))
            ]
        )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
