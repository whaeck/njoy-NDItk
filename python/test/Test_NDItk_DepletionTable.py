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

            # verify content - metadata
            metadata = chunk.metadata
            self.assertEqual( 'nosub010.zpd', metadata.zaid )
            self.assertEqual( 'this is some information for the table', metadata.information )
            self.assertEqual( 'e66_618_chain', metadata.library_name )
            self.assertEqual( '12/22/2011', metadata.source_date )
            self.assertEqual( '08/07/2013', metadata.processing_date )

            # verify content - incident particle records
            

        # the data is given explicitly
        chunk = MultigroupTable( 
            zaid = 'nosub010.zpd', 
            libname = 'e66_618_chain',
            information = 'this is some information for the table', 
            source = '12/22/2011',
            process = '08/07/2013', 
        )

        verify_chunk( self, chunk )

        # the data is read from a file
        chunk.to_file( 'test.txt' )
        chunk = DepletionTable.from_file( 'test.txt' )
        verify_chunk( self, chunk )
        os.remove( 'test.txt' )

if __name__ == '__main__' :

    unittest.main()
