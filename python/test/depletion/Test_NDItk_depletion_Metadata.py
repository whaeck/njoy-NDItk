# standard imports
import unittest

# third party imports

# local imports
from NDItk.depletion import Metadata

class Test_NDItk_depletion_Metadata( unittest.TestCase ) :
    """Unit test for the depletion Metadata class."""

    chunk_string = ( 
        'zaid\n'
        '    nosub010.zpd\n'
        'info\n'
        '    this is some information for the table\n' 
        'library_name\n'
        '    e66_618_chain\n'
        'date_source\n'
        '    12/22/2011\n'
        'date_processed\n'
        '    08/07/2013\n'
        'num_inc_parts\n'
        '    1\n' 
    )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 'nosub010.zpd', chunk.zaid )
            self.assertEqual( 'e66_618_chain', chunk.library_name )
            self.assertEqual( '08/07/2013', chunk.processing_date )
            self.assertEqual( 1, chunk.number_incident_particles )
            self.assertEqual( "this is some information for the table", chunk.information )
            self.assertEqual( '12/22/2011', chunk.source_date )

            self.assertEqual( self.chunk_string, chunk.to_string() )

        # the data is given explicitly
        chunk = Metadata( 
            zaid = 'nosub010.zpd', 
            libname = 'e66_618_chain', 
            process = '08/07/2013', 
            incident = 1,
            information = "this is some information for the table",
            source = '12/22/2011'
        )
        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
