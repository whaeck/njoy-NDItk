# standard imports
import unittest

# third party imports

# local imports
from NDItk import MultigroupTable
from NDItk.multigroup import AverageFissionEnergyRelease
from NDItk.multigroup import EnergyGroupStructure
from NDItk.multigroup import FluxWeights
from NDItk.multigroup import ReactionCrossSections
from NDItk.multigroup import CrossSection

class Test_NDItk_MultigroupTable( unittest.TestCase ) :
    """Unit test for the MultigroupTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content - metadata
            metadata = chunk.metadata
            self.assertEqual( '92235.711nm', metadata.zaid )
            self.assertEqual( 'mendf71x', metadata.library_name )
            self.assertEqual( '12/22/2011', metadata.source_date )
            self.assertEqual( '08/07/2013', metadata.process_date )
            self.assertAlmostEqual( 233.0248, metadata.atomic_weight_ratio )
            self.assertAlmostEqual( 235.043937521619, metadata.atomic_weight )
            self.assertAlmostEqual( 2.53e-8, metadata.temperature )
            self.assertAlmostEqual( 1e+10, metadata.dilution )
            self.assertEqual( 7, metadata.number_groups )
            self.assertEqual( 2, metadata.number_reactions )

            # verify content - energy boundaries
            structure = chunk.structure
            self.assertEqual( 7, structure.number_groups )
            self.assertAlmostEqual(    20, structure.boundaries[0] )
            self.assertAlmostEqual(    18, structure.boundaries[1] )
            self.assertAlmostEqual(    16, structure.boundaries[2] )
            self.assertAlmostEqual(    14, structure.boundaries[3] )
            self.assertAlmostEqual(    10, structure.boundaries[4] )
            self.assertAlmostEqual(     5, structure.boundaries[5] )
            self.assertAlmostEqual(     1, structure.boundaries[6] )
            self.assertAlmostEqual( 1e-11, structure.boundaries[7] )

            # verify content - flux weights
            flux = chunk.flux
            self.assertEqual( 7, flux.number_groups )
            self.assertAlmostEqual( 0.10, flux.weights[0] )
            self.assertAlmostEqual( 0.20, flux.weights[1] )
            self.assertAlmostEqual( 0.25, flux.weights[2] )
            self.assertAlmostEqual( 0.05, flux.weights[3] )
            self.assertAlmostEqual( 0.15, flux.weights[4] )
            self.assertAlmostEqual( 0.04, flux.weights[5] )
            self.assertAlmostEqual( 0.06, flux.weights[6] )

            # verify content - reaction cross sections
            reactions = chunk.reaction_cross_sections
            self.assertEqual( 2, reactions.number_reactions )
            self.assertEqual( 7, reactions.number_groups )
            self.assertEqual( True, reactions.has_reaction( 2 ) )
            self.assertEqual( True, reactions.has_reaction( 16 ) )
            self.assertEqual( False, reactions.has_reaction( 102 ) )
            self.assertEqual( 2, reactions.reactions[0].identifier )
            self.assertAlmostEqual( 0.0, reactions.reactions[0].qvalue )
            self.assertAlmostEqual( 10.0, reactions.reactions[0].cross_sections[0] )
            self.assertAlmostEqual( 20.0, reactions.reactions[0].cross_sections[1] )
            self.assertAlmostEqual( 30.0, reactions.reactions[0].cross_sections[2] )
            self.assertAlmostEqual( 40.0, reactions.reactions[0].cross_sections[3] )
            self.assertAlmostEqual( 50.0, reactions.reactions[0].cross_sections[4] )
            self.assertAlmostEqual( 60.0, reactions.reactions[0].cross_sections[5] )
            self.assertAlmostEqual( 70.0, reactions.reactions[0].cross_sections[6] )

            self.assertEqual( 16, reactions.reactions[1].identifier )
            self.assertAlmostEqual( 1.1234567, reactions.reactions[1].qvalue )
            self.assertAlmostEqual( 1.0, reactions.reactions[1].cross_sections[0] )
            self.assertAlmostEqual( 2.0, reactions.reactions[1].cross_sections[1] )
            self.assertAlmostEqual( 3.0, reactions.reactions[1].cross_sections[2] )
            self.assertAlmostEqual( 4.0, reactions.reactions[1].cross_sections[3] )
            self.assertAlmostEqual( 5.0, reactions.reactions[1].cross_sections[4] )
            self.assertAlmostEqual( 6.0, reactions.reactions[1].cross_sections[5] )
            self.assertAlmostEqual( 7.0, reactions.reactions[1].cross_sections[6] )

            xs = reactions.reaction( 2 )
            self.assertEqual( 2, xs.identifier )
            self.assertAlmostEqual( 0.0, xs.qvalue )
            self.assertAlmostEqual( 10.0, xs.cross_sections[0] )
            self.assertAlmostEqual( 20.0, xs.cross_sections[1] )
            self.assertAlmostEqual( 30.0, xs.cross_sections[2] )
            self.assertAlmostEqual( 40.0, xs.cross_sections[3] )
            self.assertAlmostEqual( 50.0, xs.cross_sections[4] )
            self.assertAlmostEqual( 60.0, xs.cross_sections[5] )
            self.assertAlmostEqual( 70.0, xs.cross_sections[6] )

            xs = reactions.reaction( 16 )
            self.assertEqual( 16, xs.identifier )
            self.assertAlmostEqual( 1.1234567, xs.qvalue )
            self.assertAlmostEqual( 1.0, xs.cross_sections[0] )
            self.assertAlmostEqual( 2.0, xs.cross_sections[1] )
            self.assertAlmostEqual( 3.0, xs.cross_sections[2] )
            self.assertAlmostEqual( 4.0, xs.cross_sections[3] )
            self.assertAlmostEqual( 5.0, xs.cross_sections[4] )
            self.assertAlmostEqual( 6.0, xs.cross_sections[5] )
            self.assertAlmostEqual( 7.0, xs.cross_sections[6] )

            # verify content - average fission energy release
            release = chunk.average_fission_energy_release
            self.assertAlmostEqual( 181.238898, release.prompt_energy_release )
            self.assertAlmostEqual(    202.827, release.total_energy_release )
            self.assertAlmostEqual(        6.5, release.delayed_betas )
            self.assertAlmostEqual(   7.281253, release.prompt_gammas )
            self.assertAlmostEqual(     169.13, release.fission_fragments )
            self.assertAlmostEqual(   4.827645, release.prompt_neutrons )

        # the data is given explicitly
        chunk = MultigroupTable( zaid = '92235.711nm', libname = 'mendf71x', source = '12/22/2011',
                                 process = '08/07/2013', awr = 233.0248, weight = 235.043937521619,
                                 temperature = 2.53e-8, dilution = 1e+10,
                                 structure = EnergyGroupStructure( [ 20., 18., 16., 14., 10., 5, 1, 1e-11 ] ),
                                 outgoing = [],
                                 flux = FluxWeights( [ 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 ] ),
                                 xs = ReactionCrossSections(
                                          xs = [ CrossSection( 2, 0., [ 10., 20., 30., 40., 50., 60., 70. ] ),
                                                 CrossSection( 16, 1.1234567, [ 1., 2., 3., 4., 5., 6., 7. ] ) ] ),
                                 release = AverageFissionEnergyRelease( 202.827, 181.238898, 4.827645,
                                                                        7.281253, 6.5, 169.13 ) )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
