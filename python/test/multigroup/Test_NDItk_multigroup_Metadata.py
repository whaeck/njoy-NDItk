# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import Metadata

class Test_NDItk_multigroup_Metadata( unittest.TestCase ) :
    """Unit test for the Metadata class."""

    chunk_string = ( 'zaid\n'
                     '    92235.711nm\n'
                     'library_name\n'
                     '    mendf71x\n'
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
                     '    7\n'
                     'pn_order\n'
                     '    5\n'
                     'num_sec_parts\n'
                     '    2\n'
                     'num_grps_0\n'
                     '    30\n'
                     'num_grps_1001\n'
                     '    250\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( '92235.711nm', chunk.zaid )
            self.assertEqual( 'mendf71x', chunk.library_name )
            self.assertEqual( '12/22/2011', chunk.source_date )
            self.assertEqual( '08/07/2013', chunk.processing_date )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertAlmostEqual( 235.043937521619, chunk.atomic_weight )
            self.assertAlmostEqual( 2.53e-8, chunk.temperature )
            self.assertAlmostEqual( 1e+10, chunk.dilution )
            self.assertEqual( 618, chunk.number_groups )
            self.assertEqual(  30, chunk.number_outgoing_groups( 0 ) )
            self.assertEqual( 250, chunk.number_outgoing_groups( 1001 ) )
            self.assertEqual(   7, chunk.number_reactions )
            self.assertEqual(   5, chunk.number_legendre_moments )
            self.assertEqual( None, chunk.number_upscatter_groups )
            self.assertEqual( None, chunk.number_downscatter_groups )

            self.assertEqual( self.chunk_string, chunk.to_string() )

        # the data is given explicitly
        chunk = Metadata( zaid = '92235.711nm', libname = 'mendf71x', source = '12/22/2011',
                          process = '08/07/2013', awr = 233.0248, weight = 235.043937521619,
                          temperature = 2.53e-8, dilution = 1e+10, groups = 618,
                          outgoing = { 0 : 30, 1001 : 250 }, reactions = 7, legendre = 5 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
