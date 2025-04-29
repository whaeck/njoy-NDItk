# standard imports
import unittest

# third party imports

# local imports
from NDItk.dosimetry import Metadata

class Test_NDItk_dosimetry_Metadata( unittest.TestCase ) :
    """Unit test for the Metadata class."""

    chunk_string = ( 'zaid\n'
                     '    92235.000nd\n'
                     'library_name\n'
                     '    testing\n'
                     'date_source\n'
                     '    12/22/2011\n'
                     'date_processed\n'
                     '    08/07/2013\n'
                     'awr\n'
                     '    233.0248\n'
                     'at_wgt\n'
                     '    235.043937521619\n'
                     'temp\n'
                     '    2.53e-08\n'
                     'sig_0\n'
                     '    10000000000\n'
                     'num_grps\n'
                     '    618\n'
                     'num_reac\n'
                     '    7\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( '92235.000nd', chunk.zaid )
            self.assertEqual( 'testing', chunk.library_name )
            self.assertEqual( '12/22/2011', chunk.source_date )
            self.assertEqual( '08/07/2013', chunk.processing_date )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertAlmostEqual( 235.043937521619, chunk.atomic_weight )
            self.assertAlmostEqual( 2.53e-8, chunk.temperature )
            self.assertAlmostEqual( 1e+10, chunk.dilution )
            self.assertEqual( 618, chunk.number_groups )
            self.assertEqual(   7, chunk.number_reactions )
            self.assertEqual( None, chunk.number_upscatter_groups )
            self.assertEqual( None, chunk.number_downscatter_groups )

            self.assertEqual( self.chunk_string, chunk.to_string() )

        # the data is given explicitly
        chunk = Metadata( zaid = '92235.000nd', libname = 'testing', source = '12/22/2011',
                          process = '08/07/2013', awr = 233.0248, weight = 235.043937521619,
                          temperature = 2.53e-8, dilution = 1e+10, groups = 618,
                          reactions = 7 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
