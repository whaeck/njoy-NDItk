# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import EnergyGroupStructure

class Test_NDItk_multigroup_EnergyGroupStructure( unittest.TestCase ) :
    """Unit test for the EnergyGroupStructure class."""

    chunk_values = [ 20, 18, 16, 14, 10, 5, 1, 1e-11 ]
    chunk_string = ( 'e_bounds\n'
                     '    20 18 16 14 10\n'
                     '    5 1 1e-11\n' )

    chunk_outgoing_values = [ 20, 10, 1e-11 ]
    chunk_outgoing_string = ( 'e_bounds_1001\n'
                              '    20 10 1e-11\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 7, chunk.number_groups )
            self.assertAlmostEqual(    20, chunk.boundaries[0] )
            self.assertAlmostEqual(    18, chunk.boundaries[1] )
            self.assertAlmostEqual(    16, chunk.boundaries[2] )
            self.assertAlmostEqual(    14, chunk.boundaries[3] )
            self.assertAlmostEqual(    10, chunk.boundaries[4] )
            self.assertAlmostEqual(     5, chunk.boundaries[5] )
            self.assertAlmostEqual(     1, chunk.boundaries[6] )
            self.assertAlmostEqual( 1e-11, chunk.boundaries[7] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'e_bounds', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 8, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        def verify_outgoing_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.number_groups )
            self.assertAlmostEqual(    20, chunk.boundaries[0] )
            self.assertAlmostEqual(    10, chunk.boundaries[1] )
            self.assertAlmostEqual( 1e-11, chunk.boundaries[2] )

            self.assertEqual( self.chunk_outgoing_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'e_bounds_1001', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 3, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_outgoing_values[index], values[index] )

        # the data is given explicitly
        chunk = EnergyGroupStructure( boundaries = [ 20., 18., 16., 14., 10., 5, 1, 1e-11 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = EnergyGroupStructure.from_string( self.chunk_string, 8 )

        verify_chunk( self, chunk )

        # the data is given explicitly for an outgoing particle
        chunk = EnergyGroupStructure( particle = 1001, boundaries = [ 20., 10., 1e-11 ] )

        verify_outgoing_chunk( self, chunk )

        # the data is read from a string for an outgoing particle
        chunk = EnergyGroupStructure.from_string( self.chunk_outgoing_string, 3 )

        verify_outgoing_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
