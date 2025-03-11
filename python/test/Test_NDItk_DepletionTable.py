# standard imports
import unittest
import os

# third party imports

# local imports
from NDItk import DepletionTable
from NDItk.depletion import Multiplicities
from NDItk.depletion import Product
from NDItk.depletion import Target
from NDItk.depletion import IncidentParticle

class Test_NDItk_DepletionTable( unittest.TestCase ) :
    """Unit test for the DepletionTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            self.assertEqual( 1, chunk.number_incident_particles )

            # verify content - metadata
            metadata = chunk.metadata
            self.assertEqual( 'nosub010.zpd', metadata.zaid )
            self.assertEqual( 'this is some information for the table', metadata.information )
            self.assertEqual( 'e66_618_chain', metadata.library_name )
            self.assertEqual( '02/01/2007', metadata.source_date )
            self.assertEqual( '02/01/2007', metadata.processing_date )

            # verify content - incident particle records
            incident0 = chunk.incident_particles[0]
            self.assertEqual( 1, chunk.incident_particle(1).incident_identifier )
            self.assertEqual( 1, incident0.incident_identifier )
            self.assertEqual( 2, incident0.number_targets )

            target0 = chunk.incident0.targets[0]
            self.assertEqual( "target", target0.keyword )
            self.assertEqual(     1001, target0.target_identifier)
            self.assertEqual(        1, target0.number_products)
            self.assertEqual(     1002, target0.products[0].reaction_product)
            self.assertEqual(        1, target0.products[0].number_reactions)
            self.assertEqual(      102, target0.products[0].reaction_identifiers[0])
            self.assertEqual(        1, target0.products[0].multiplicities[0])

            target1 = chunk.incident0.targets[1]
            self.assertEqual( "target", target1.keyword )
            self.assertEqual(     1002, target1.target_identifier)
            self.assertEqual(        2, target1.number_products)
            self.assertEqual(     1001, target1.products[0].reaction_product)
            self.assertEqual(        1, target1.products[0].number_reactions)
            self.assertEqual(       16, target1.products[0].reaction_identifiers[0])
            self.assertEqual(        1, target1.products[0].multiplicities[0])
            self.assertEqual(     1003, target1.products[1].reaction_product)
            self.assertEqual(        1, target1.products[1].number_reactions)
            self.assertEqual(      102, target1.products[1].reaction_identifiers[0])
            self.assertEqual(        1, target1.products[1].multiplicities[0])
            

        incident = IncidentParticle(
            identifier=1,
            targets=[Target(identifier=1001, products=[Product(Multiplicities(product=1002, reactions=[102], multiplicities=[1]))]),
                     Target(identifier=1002, products=[Product(Multiplicities(product=1001, reactions=[16],  multiplicities=[1])),
                                                       Product(Multiplicities(product=1003, reactions=[102], multiplicities=[1]))])]
        )

        # the data is given explicitly
        chunk = DepletionTable( 
            zaid = 'nosub010.zpd', 
            libname = 'e66_618_chain',
            information = 'this is some information for the table', 
            source = '02/01/2007',
            process = '02/01/2007', 
            incident = [incident]
        )
        verify_chunk( self, chunk )

        # the data is read from a file
        chunk.to_file( 'test.txt' )
        chunk = DepletionTable.from_file( 'test.txt' )
        verify_chunk( self, chunk )
        os.remove( 'test.txt' )

if __name__ == '__main__' :

    unittest.main()
