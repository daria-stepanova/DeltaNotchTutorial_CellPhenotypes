
#include "DeltaPhenotypeTargetAreaModifier.hpp"
#include "AbstractPhaseBasedCellCycleModel.hpp"
#include "ApoptoticCellProperty.hpp"
#include "DeltaHighPhenotypeProperty.hpp"
#include "DeltaLowPhenotypeProperty.hpp"

template<unsigned DIM>
DeltaPhenotypeTargetAreaModifier<DIM>::DeltaPhenotypeTargetAreaModifier()
    : AbstractTargetAreaModifier<DIM>(),
      mGrowthDuration(DOUBLE_UNSET),
      mDeltaHighPhenotypeTargetAreaCoefficient(1.0),
      mDeltaLowPhenotypeTargetAreaCoefficient(1.0),
      mTransientPhenotypeTargetAreaCoefficient(1.0)
{
}

template<unsigned DIM>
DeltaPhenotypeTargetAreaModifier<DIM>::~DeltaPhenotypeTargetAreaModifier()
{
}

template<unsigned DIM>
void DeltaPhenotypeTargetAreaModifier<DIM>::UpdateTargetAreaOfCell(CellPtr pCell)
{
    // Get target area A of a healthy cell in S, G2 or M phase
    double cell_target_area = this->mReferenceTargetArea;

    //This is the only bit I change for Delta phenotypes
    if(pCell->HasCellProperty<DeltaLowPhenotypeProperty>())
    {
        cell_target_area *=mDeltaLowPhenotypeTargetAreaCoefficient;
    }
    else if(pCell->HasCellProperty<DeltaHighPhenotypeProperty>())
    {
        cell_target_area *=mDeltaHighPhenotypeTargetAreaCoefficient;
    }
    else
    //if(!((pCell->HasCellProperty<PanethCellProperty>())||(pCell->HasCellProperty<StemCellProperty>())))
    {
        cell_target_area *=mTransientPhenotypeTargetAreaCoefficient;
    }
    // end of changes

    double growth_duration = mGrowthDuration;
    if (growth_duration == DOUBLE_UNSET)
    {
        if (dynamic_cast<AbstractPhaseBasedCellCycleModel*>(pCell->GetCellCycleModel()) == nullptr)
        {
            EXCEPTION("If SetGrowthDuration() has not been called, a subclass of AbstractPhaseBasedCellCycleModel must be used");
        }
        AbstractPhaseBasedCellCycleModel* p_model = static_cast<AbstractPhaseBasedCellCycleModel*>(pCell->GetCellCycleModel());

        growth_duration = p_model->GetG1Duration();

        // If the cell is differentiated then its G1 duration is infinite
        if (growth_duration == DBL_MAX)
        {
            // This is just for fixed cell-cycle models, need to work out how to find the g1 duration
            growth_duration = p_model->GetTransitCellG1Duration();
        }
    }

    if (pCell->HasCellProperty<ApoptoticCellProperty>())
    {
        // Age of cell when apoptosis begins
        if (pCell->GetStartOfApoptosisTime() - pCell->GetBirthTime() < growth_duration)
        {
            cell_target_area *= 0.5*(1 + (pCell->GetStartOfApoptosisTime() - pCell->GetBirthTime())/growth_duration);
        }

        // The target area of an apoptotic cell decreases linearly to zero
        double time_spent_apoptotic = SimulationTime::Instance()->GetTime() - pCell->GetStartOfApoptosisTime();

        cell_target_area *= 1.0 - 0.5/(pCell->GetApoptosisTime())*time_spent_apoptotic;
        if (cell_target_area < 0)
        {
            cell_target_area = 0;
        }
    }
    else
    {
        double cell_age = pCell->GetAge();

        // The target area of a proliferating cell increases linearly from A/2 to A over the course of the prescribed duration
        if (cell_age < growth_duration)
        {
            cell_target_area *= 0.5*(1 + cell_age/growth_duration);
        }
        else
        {
            /**
             * At division, daughter cells inherit the cell data array from the mother cell.
             * Here, we assign the target area that we want daughter cells to have to cells
             * that we know to divide in this time step.
             *
             * \todo This is a little hack that we might want to clean up in the future.
             */
            if (pCell->ReadyToDivide())
            {
                cell_target_area *= 0.5;//*this->mReferenceTargetArea;
            }
        }
    }

    // Set cell data
    pCell->GetCellData()->SetItem("target area", cell_target_area);
}

template<unsigned DIM>
double DeltaPhenotypeTargetAreaModifier<DIM>::GetGrowthDuration()
{
    return mGrowthDuration;
}

template<unsigned DIM>
void DeltaPhenotypeTargetAreaModifier<DIM>::SetGrowthDuration(double growthDuration)
{
    assert(growthDuration >= 0.0);
    mGrowthDuration = growthDuration;
}

template<unsigned DIM> double DeltaPhenotypeTargetAreaModifier<DIM>::GetDeltaHighPhenotypeTargetAreaCoefficient()
{
    return mDeltaHighPhenotypeTargetAreaCoefficient;
}

template<unsigned DIM> void DeltaPhenotypeTargetAreaModifier<DIM>::SetDeltaHighPhenotypeTargetAreaCoefficient(double deltaHighPhenotypeTargetAreaCoefficient)
{
    assert(deltaHighPhenotypeTargetAreaCoefficient >= 0.0);
    mDeltaHighPhenotypeTargetAreaCoefficient = deltaHighPhenotypeTargetAreaCoefficient;
}

template<unsigned DIM> double DeltaPhenotypeTargetAreaModifier<DIM>::GetDeltaLowPhenotypeTargetAreaCoefficient()
{
    return mDeltaLowPhenotypeTargetAreaCoefficient;
}

template<unsigned DIM> void DeltaPhenotypeTargetAreaModifier<DIM>::SetDeltaLowPhenotypeTargetAreaCoefficient(double deltaLowPhenotypeTargetAreaCoefficient)
{
    assert(deltaLowPhenotypeTargetAreaCoefficient >= 0.0);
    mDeltaLowPhenotypeTargetAreaCoefficient = deltaLowPhenotypeTargetAreaCoefficient;
}

template<unsigned DIM> double DeltaPhenotypeTargetAreaModifier<DIM>::GetTransientPhenotypeTargetAreaCoefficient()
{
    return mTransientPhenotypeTargetAreaCoefficient;
}

template<unsigned DIM> void DeltaPhenotypeTargetAreaModifier<DIM>::SetTransientPhenotypeTargetAreaCoefficient(double transientPhenotypeTargetAreaCoefficient)
{
    assert(transientPhenotypeTargetAreaCoefficient >= 0.0);
    mTransientPhenotypeTargetAreaCoefficient = transientPhenotypeTargetAreaCoefficient;
}

template<unsigned DIM>
void DeltaPhenotypeTargetAreaModifier<DIM>::OutputSimulationModifierParameters(out_stream& rParamsFile)
{
    *rParamsFile << "\t\t\t<GrowthDuration>" << mGrowthDuration << "</GrowthDuration>\n";
    *rParamsFile << "\t\t\t<DeltaHighPhenotypeTargetAreaCoefficient>" << mDeltaHighPhenotypeTargetAreaCoefficient << "</DeltaHighPhenotypeTargetAreaCoefficient>\n";
    *rParamsFile << "\t\t\t<DeltaLowPhenotypeTargetAreaCoefficient>" << mDeltaLowPhenotypeTargetAreaCoefficient << "</DeltaLowPhenotypeTargetAreaCoefficient>\n";
    *rParamsFile << "\t\t\t<TransientPhenotypeTargetAreaCoefficient>" << mTransientPhenotypeTargetAreaCoefficient << "</TransientPhenotypeTargetAreaCoefficient>\n";

    // Next, call method on direct parent class
    AbstractTargetAreaModifier<DIM>::OutputSimulationModifierParameters(rParamsFile);
}

// Explicit instantiation
template class DeltaPhenotypeTargetAreaModifier<1>;
template class DeltaPhenotypeTargetAreaModifier<2>;
template class DeltaPhenotypeTargetAreaModifier<3>;
