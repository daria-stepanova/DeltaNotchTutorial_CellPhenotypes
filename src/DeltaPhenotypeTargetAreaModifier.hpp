
#ifndef DELTAPHENOTYPETARGETAREAMODIFIER_HPP_
#define DELTAPHENOTYPETARGETAREAMODIFIER_HPP_

#include "AbstractTargetAreaModifier.hpp"

// consider that Delta-high cells and Delta-low cells have different target areas
// cells which are neither Delta-high nor Delta low have another target area
 
template<unsigned DIM>
class DeltaPhenotypeTargetAreaModifier : public AbstractTargetAreaModifier<DIM>
{
    /**
     * The duration that a cell's target area to increase from 0.5*mReferenceTargetArea
     * to mReferenceTargetArea at the start of its cell cycle. Defaults to DOUBLE_UNSET.
     * If this variable is set using SetGrowthDuration(), then it is used regardless of
     * whether a phase-based cell-cycle model is used.
     */
    double mGrowthDuration;

    double mDeltaHighPhenotypeTargetAreaCoefficient;
    double mDeltaLowPhenotypeTargetAreaCoefficient;
    double mTransientPhenotypeTargetAreaCoefficient;

public:

    /**
     * Default constructor.
     */
    DeltaPhenotypeTargetAreaModifier();

    /**
     * Destructor.
     */
    virtual ~DeltaPhenotypeTargetAreaModifier();

    /**
     * Overridden UpdateTargetAreaOfCell() method.
     *
     * @param pCell pointer to the cell
     */
    virtual void UpdateTargetAreaOfCell(const CellPtr pCell);

    /**
     * @return #mGrowthDuration
     */
    double GetGrowthDuration();

    /**
     * Set #mGrowthDuration.
     *
     * @param growthDuration the new value of #mGrowthDuration
     */
    void SetGrowthDuration(double growthDuration);

    /**
     * @return #mDeltaHighPhenotypeTargetAreaCoefficient
     */
    double GetDeltaHighPhenotypeTargetAreaCoefficient();

    /**
     * Set #mDeltaHighPhenotypeTargetAreaCoefficient.
     *
     * @param deltaHighPhenotypeTargetAreaCoefficient the new value of #mDeltaHighPhenotypeTargetAreaCoefficient
     */
    void SetDeltaHighPhenotypeTargetAreaCoefficient(double deltaHighPhenotypeTargetAreaCoefficient);

    /**
     * @return #mDeltaLowPhenotypeTargetAreaCoefficient
     */
    double GetDeltaLowPhenotypeTargetAreaCoefficient();

    /**
     * Set #mDeltaLowPhenotypeTargetAreaCoefficient.
     *
     * @param deltaLowPhenotypeTargetAreaCoefficient the new value of #mDeltaLowPhenotypeTargetAreaCoefficient
     */
    void SetDeltaLowPhenotypeTargetAreaCoefficient(double deltaLowPhenotypeTargetAreaCoefficient);

/**
     * @return #mTransientPhenotypeTargetAreaCoefficient
     */
    double GetTransientPhenotypeTargetAreaCoefficient();

    /**
     * Set #mTransientPhenotypeTargetAreaCoefficient.
     *
     * @param transientPhenotypeTargetAreaCoefficient the new value of #mTransientPhenotypeTargetAreaCoefficient
     */
    void SetTransientPhenotypeTargetAreaCoefficient(double transientPhenotypeTargetAreaCoefficient);

    /**
     * Overridden OutputSimulationModifierParameters() method.
     * Output any simulation modifier parameters to file.
     *
     * @param rParamsFile the file stream to which the parameters are output
     */
    void OutputSimulationModifierParameters(out_stream& rParamsFile);
};

#endif /*DELTAPHENOTYPETARGETAREAMODIFIER_HPP_*/
