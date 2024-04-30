# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import AverageFissionEnergyRelease

class Test_NDItk_multigroup_AverageFissionEnergyRelease( unittest.TestCase ) :
    """Unit test for the AverageFissionEnergyRelease class."""

    chunk_values = [ 181.238898, 202.827, 6.5, 7.281253, 169.13, 4.827645 ]
    chunk_string = ( 'fiss_q\n'
                     '    181.238898 202.827 6.5 7.281253 169.13\n'
                     '    4.827645\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 181.238898, chunk.prompt_energy_release )
            self.assertAlmostEqual(    202.827, chunk.total_energy_release )
            self.assertAlmostEqual(        6.5, chunk.delayed_betas )
            self.assertAlmostEqual(   7.281253, chunk.prompt_gammas )
            self.assertAlmostEqual(     169.13, chunk.fission_fragments )
            self.assertAlmostEqual(   4.827645, chunk.prompt_neutrons )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'fiss_q', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 6, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = AverageFissionEnergyRelease(  total = 202.827, prompt = 181.238898, neutrons = 4.827645,
                                              gammas = 7.281253, betas = 6.5, fragments = 169.13 )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = AverageFissionEnergyRelease.from_string( self.chunk_string )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
