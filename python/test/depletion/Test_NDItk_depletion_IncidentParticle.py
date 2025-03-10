# standard imports
import unittest

# third party imports

# local imports
from NDItk.depletion import Multiplicities
from NDItk.depletion import Product
from NDItk.depletion import Target
from NDItk.depletion import IncidentParticle

class Test_NDItk_depletion_IncidentParticle( unittest.TestCase ) :
    """Unit test for the IncidentParticle class."""

    chunk_string = (
        "inc_part\n"
        "  1\n"
#       "\n"
        "  num_targets\n"
        "    2\n"
#       "\n"
        "  target\n"
        "    1001\n"
        "    num_products\n"
        "      1\n"
        "    product\n"
        "      1002\n"
        "      1\n"
        "      102 1\n"
#       "\n"
        "  target\n"
        "    1002\n"
        "    num_products\n"
        "      2\n"
        "    product\n"
        "      1001\n"
        "      1\n"
        "      16 1\n"
        "    product\n"
        "      1003\n"
        "      1\n"
        "      102 1\n"
    )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.incident_identifier )
            self.assertEqual( 2, chunk.number_targets )

            self.assertEqual( "target", chunk.targets[0].keyword )
            self.assertEqual(     1001, chunk.targets[0].target_identifier)
            self.assertEqual(        1, chunk.targets[0].number_products)
            self.assertEqual(     1002, chunk.targets[0].products[0].reaction_product)
            self.assertEqual(        1, chunk.targets[0].products[0].number_reactions)
            self.assertEqual(      102, chunk.targets[0].products[0].reaction_identifiers[0])
            self.assertEqual(        1, chunk.targets[0].products[0].multiplicities[0])

            self.assertEqual( "target", chunk.targets[1].keyword )
            self.assertEqual(     1002, chunk.targets[1].target_identifier)
            self.assertEqual(        2, chunk.targets[1].number_products)
            self.assertEqual(     1001, chunk.targets[1].products[0].reaction_product)
            self.assertEqual(        1, chunk.targets[1].products[0].number_reactions)
            self.assertEqual(       16, chunk.targets[1].products[0].reaction_identifiers[0])
            self.assertEqual(        1, chunk.targets[1].products[0].multiplicities[0])
            self.assertEqual(     1003, chunk.targets[1].products[1].reaction_product)
            self.assertEqual(        1, chunk.targets[1].products[1].number_reactions)
            self.assertEqual(      102, chunk.targets[1].products[1].reaction_identifiers[0])
            self.assertEqual(        1, chunk.targets[1].products[1].multiplicities[0])

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'inc_part', chunk.keyword )

        # the data is given explicitly
        chunk = IncidentParticle(
            identifier=1,
            targets=[Target(identifier=1001, products=[Product(Multiplicities(product=1002, reactions=[102], multiplicities=[1]))]),
                     Target(identifier=1002, products=[Product(Multiplicities(product=1001, reactions=[16],  multiplicities=[1])),
                                                       Product(Multiplicities(product=1003, reactions=[102], multiplicities=[1]))])]
        )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
