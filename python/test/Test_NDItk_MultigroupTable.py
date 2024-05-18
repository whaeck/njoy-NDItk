# standard imports
import unittest

# third party imports

# local imports
from NDItk import MultigroupTable
from NDItk.multigroup import AverageFissionEnergyRelease
from NDItk.multigroup import EnergyGroupStructure
from NDItk.multigroup import FluxWeights
from NDItk.multigroup import TotalCrossSection
from NDItk.multigroup import ReactionCrossSections
from NDItk.multigroup import CrossSection
from NDItk.multigroup import Velocities
from NDItk.multigroup import HeatingNumbers
from NDItk.multigroup import Kerma
from NDItk.multigroup import OutgoingParticleTypes
from NDItk.multigroup import OutgoingParticleTransportData
from NDItk.multigroup import LegendreMoment
from NDItk.multigroup import ScatteringMatrix

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
            self.assertEqual( 3, metadata.number_outgoing_groups( 0 ) )
            self.assertEqual( 2, metadata.number_outgoing_groups( 1001 ) )
            self.assertEqual( 2, metadata.number_reactions )

            # verify content - primary energy boundaries
            structure = chunk.primary_group_boundaries
            self.assertEqual( 7, structure.number_groups )
            self.assertAlmostEqual(    20, structure.values[0] )
            self.assertAlmostEqual(    18.123456789, structure.values[1] )
            self.assertAlmostEqual(    16.0000000000001, structure.values[2] )
            self.assertAlmostEqual(    14, structure.values[3] )
            self.assertAlmostEqual(    10, structure.values[4] )
            self.assertAlmostEqual(     5, structure.values[5] )
            self.assertAlmostEqual(     1, structure.values[6] )
            self.assertAlmostEqual( 1e-11, structure.values[7] )

            # verify content - velocities
            velocities = chunk.velocities
            self.assertEqual( 7, velocities.number_groups )
            self.assertAlmostEqual( 2.10, velocities.values[0] )
            self.assertAlmostEqual( 2.20, velocities.values[1] )
            self.assertAlmostEqual( 2.25, velocities.values[2] )
            self.assertAlmostEqual( 2.05, velocities.values[3] )
            self.assertAlmostEqual( 2.15, velocities.values[4] )
            self.assertAlmostEqual( 2.04, velocities.values[5] )
            self.assertAlmostEqual( 2.06, velocities.values[6] )

            # verify content - flux weights
            flux = chunk.flux_weights
            self.assertEqual( 7, flux.number_groups )
            self.assertAlmostEqual( 0.10, flux.values[0] )
            self.assertAlmostEqual( 0.20, flux.values[1] )
            self.assertAlmostEqual( 0.25, flux.values[2] )
            self.assertAlmostEqual( 0.05, flux.values[3] )
            self.assertAlmostEqual( 0.15, flux.values[4] )
            self.assertAlmostEqual( 0.04, flux.values[5] )
            self.assertAlmostEqual( 0.06, flux.values[6] )

            # verify content - total cross section
            total = chunk.total_cross_section
            self.assertEqual( 7, total.number_groups )
            self.assertAlmostEqual( 1.10, total.values[0] )
            self.assertAlmostEqual( 1.20, total.values[1] )
            self.assertAlmostEqual( 1.25, total.values[2] )
            self.assertAlmostEqual( 1.05, total.values[3] )
            self.assertAlmostEqual( 1.15, total.values[4] )
            self.assertAlmostEqual( 1.04, total.values[5] )
            self.assertAlmostEqual( 1.06, total.values[6] )

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

            # verify content - primary heating numbers
            heating = chunk.primary_heating_numbers
            self.assertEqual( 7, heating.number_groups )
            self.assertAlmostEqual( 11, heating.values[0] )
            self.assertAlmostEqual( 22, heating.values[1] )
            self.assertAlmostEqual( 33, heating.values[2] )
            self.assertAlmostEqual( 44, heating.values[3] )
            self.assertAlmostEqual( 55, heating.values[4] )
            self.assertAlmostEqual( 66, heating.values[5] )
            self.assertAlmostEqual( 77, heating.values[6] )

            # verify content - outgoing particle types
            types = chunk.outgoing_particle_types
            self.assertEqual( 2, types.number_outgoing_particles )
            self.assertEqual(    0, types.values[0] )
            self.assertEqual( 1001, types.values[1] )

            # verify content - outgoing particle transport data
            transport = chunk.outgoing_particle_transport_data
            self.assertEqual( 2, transport.number_outgoing_particles )
            self.assertEqual( '92000', transport.values[0] )
            self.assertEqual( '92235.proton', transport.values[1] )

            # verify content - primary kerma
            kerma = chunk.primary_kerma
            self.assertEqual( 7, kerma.number_groups )
            self.assertAlmostEqual( 110, kerma.values[0] )
            self.assertAlmostEqual( 220, kerma.values[1] )
            self.assertAlmostEqual( 330, kerma.values[2] )
            self.assertAlmostEqual( 440, kerma.values[3] )
            self.assertAlmostEqual( 550, kerma.values[4] )
            self.assertAlmostEqual( 660, kerma.values[5] )
            self.assertAlmostEqual( 770, kerma.values[6] )

            # verify content - outgoing energy boundaries: 0
            structure = chunk.outgoing_group_boundaries( 0 )
            self.assertEqual( 3, structure.number_groups )
            self.assertAlmostEqual(    20, structure.values[0] )
            self.assertAlmostEqual(    10, structure.values[1] )
            self.assertAlmostEqual(     5, structure.values[2] )
            self.assertAlmostEqual( 1e-11, structure.values[3] )

            # verify content - outgoing energy boundaries: 1001
            structure = chunk.outgoing_group_boundaries( 1001 )
            self.assertEqual( 2, structure.number_groups )
            self.assertAlmostEqual(    20, structure.values[0] )
            self.assertAlmostEqual(    10, structure.values[1] )
            self.assertAlmostEqual( 1e-11, structure.values[2] )

            # verify content - outgoing heating numbers: 0
            heating = chunk.outgoing_heating_numbers( 0 )
            self.assertEqual( 3, heating.number_groups )
            self.assertAlmostEqual( 21  , heating.values[0] )
            self.assertAlmostEqual( 11  , heating.values[1] )
            self.assertAlmostEqual(  5.1, heating.values[2] )

            # verify content - outgoing heating numbers: 1001
            heating = chunk.outgoing_heating_numbers( 1001 )
            self.assertEqual( 2, heating.number_groups )
            self.assertAlmostEqual( 25, heating.values[0] )
            self.assertAlmostEqual( 15, heating.values[1] )

            # verify content - outgoing kerma: 0
            kerma = chunk.outgoing_kerma( 0 )
            self.assertEqual( 3, kerma.number_groups )
            self.assertAlmostEqual( 210, kerma.values[0] )
            self.assertAlmostEqual( 110, kerma.values[1] )
            self.assertAlmostEqual(  51, kerma.values[2] )

            # verify content - outgoing kerma: 1001
            kerma = chunk.outgoing_kerma( 1001 )
            self.assertEqual( 2, kerma.number_groups )
            self.assertAlmostEqual( 250, kerma.values[0] )
            self.assertAlmostEqual( 150, kerma.values[1] )

        # the data is given explicitly
        chunk = MultigroupTable( zaid = '92235.711nm', libname = 'mendf71x', source = '12/22/2011',
                                 process = '08/07/2013', awr = 233.0248, weight = 235.043937521619,
                                 temperature = 2.53e-8, dilution = 1e+10,
                                 structure = EnergyGroupStructure( [ 20., 18.123456789, 16.0000000000001, 14., 10., 5, 1, 1e-11 ] ),
                                 velocities = Velocities( [ 2.1, 2.2, 2.25, 2.05, 2.15, 2.04, 2.06 ] ),
                                 flux = FluxWeights( [ 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 ] ),
                                 total = TotalCrossSection( [ 1.1, 1.2, 1.25, 1.05, 1.15, 1.04, 1.06 ] ),
                                 xs = ReactionCrossSections(
                                          xs = [ CrossSection( 2, 0., [ 10., 20., 30., 40., 50., 60., 70. ] ),
                                                 CrossSection( 16, 1.1234567, [ 1., 2., 3., 4., 5., 6., 7. ] ) ] ),
                                 scattering = ScatteringMatrix(
                                     [ LegendreMoment( 0, [ 1, 0, 0, 0, 0, 0, 0,
                                                            0, 1, 0, 0, 0, 0, 0,
                                                            0, 0, 1, 0, 0, 0, 0,
                                                            0, 0, 0, 1, 0, 0, 0,
                                                            0, 0, 0, 0, 1, 0, 0,
                                                            0, 0, 0, 0, 0, 1, 0,
                                                            0, 0, 0, 0, 0, 0, 1 ], 7 ),
                                       LegendreMoment( 1, [ 0, 0, 0, 0, 0, 0, 1,
                                                             0, 0, 0, 0, 0, 1, 0,
                                                             0, 0, 0, 0, 1, 0, 0,
                                                             0, 0, 0, 1, 0, 0, 0,
                                                             0, 0, 1, 0, 0, 0, 0,
                                                             0, 1, 0, 0, 0, 0, 0,
                                                             1, 0, 0, 0, 0, 0, 0 ], 7 ) ] ),
                                 release = AverageFissionEnergyRelease( 202.827, 181.238898, 4.827645,
                                                                        7.281253, 6.5, 169.13 ),
                                 primary_heating = HeatingNumbers( [ 11., 22., 33., 44., 55., 66., 77. ] ),
                                 primary_kerma = Kerma( [ 110., 220., 330., 440., 550., 660., 770. ] ),
                                 types = OutgoingParticleTypes( [ 0, 1001 ] ),
                                 transport = OutgoingParticleTransportData( [ "92000", "92235.proton" ] ),
                                 outgoing = [ EnergyGroupStructure( 0, [ 20., 10., 5, 1e-11 ] ),
                                              EnergyGroupStructure( 1001, [ 20., 10., 1e-11 ] ) ],
                                 outgoing_heating = [ HeatingNumbers( 0, [ 21., 11., 5.1 ] ),
                                                      HeatingNumbers( 1001, [ 25., 15. ] ) ],
                                 outgoing_kerma = [ Kerma( 0, [ 210., 110., 51. ] ),
                                                    Kerma( 1001, [ 250., 150. ] ) ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
