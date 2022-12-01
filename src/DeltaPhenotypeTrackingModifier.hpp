
#ifndef DELTAPHENOTYPETRACKINGMODIFIER_HPP_
#define DELTAPHENOTYPETRACKINGMODIFIER_HPP_

#include "AbstractCellBasedSimulationModifier.hpp"

/**
 * A modifier class in which contact areas with Paneth and stem cells
 * are computed and stored in CellData.
 */
template<unsigned DIM>
class DeltaPhenotypeTrackingModifier : public AbstractCellBasedSimulationModifier<DIM,DIM>
{

public:

    /**
     * Default constructor.
     */
    DeltaPhenotypeTrackingModifier();

    /**
     * Destructor.
     */
    virtual ~DeltaPhenotypeTrackingModifier();

    /**
     * Overridden UpdateAtEndOfTimeStep() method.
     *
     * Specifies what to do in the simulation at the end of each time step.
     *
     * @param rCellPopulation reference to the cell population
     */
    virtual void UpdateAtEndOfTimeStep(AbstractCellPopulation<DIM,DIM>& rCellPopulation);

    /**
     * Overridden SetupSolve() method.
     *
     * Specifies what to do in the simulation before the start of the time loop.
     *
     * @param rCellPopulation reference to the cell population
     * @param outputDirectory the output directory, relative to where Chaste output is stored
     */
    virtual void SetupSolve(AbstractCellPopulation<DIM,DIM>& rCellPopulation, std::string outputDirectory);

    /**
     * Helper method to compute the mean level of Delta in each cell's neighbours and store these in the CellData.
     *
     * Note: If using a CaBasedCellPopulation, we assume a Moore neighbourhood and unit carrying capacity.
     * If a cell has no neighbours (such as an isolated cell in a CaBasedCellPopulation), we store the
     * value -1 in the CellData.
     *
     * @param rCellPopulation reference to the cell population
     */
    void UpdateCellData(AbstractCellPopulation<DIM,DIM>& rCellPopulation);

    /**
     * Overridden OutputSimulationModifierParameters() method.
     * Output any simulation modifier parameters to file.
     *
     * @param rParamsFile the file stream to which the parameters are output
     */
    void OutputSimulationModifierParameters(out_stream& rParamsFile);
};

#endif /*DELTAPHENOTYPETRACKINGMODIFIER_HPP_*/
