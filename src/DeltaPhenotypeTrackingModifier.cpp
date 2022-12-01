
#include "DeltaPhenotypeTrackingModifier.hpp"

#include "SmartPointers.hpp"
#include "CellPropertyRegistry.hpp"
#include "DeltaHighPhenotypeProperty.hpp"
#include "DeltaLowPhenotypeProperty.hpp"

#include "DifferentiatedCellProliferativeType.hpp"
#include "StemCellProliferativeType.hpp"


template<unsigned DIM>
DeltaPhenotypeTrackingModifier<DIM>::DeltaPhenotypeTrackingModifier()
    : AbstractCellBasedSimulationModifier<DIM>()
{
}

template<unsigned DIM>
DeltaPhenotypeTrackingModifier<DIM>::~DeltaPhenotypeTrackingModifier()
{
}

template<unsigned DIM>
void DeltaPhenotypeTrackingModifier<DIM>::UpdateAtEndOfTimeStep(AbstractCellPopulation<DIM,DIM>& rCellPopulation)
{
    UpdateCellData(rCellPopulation);
}

template<unsigned DIM>
void DeltaPhenotypeTrackingModifier<DIM>::SetupSolve(AbstractCellPopulation<DIM,DIM>& rCellPopulation, std::string outputDirectory)
{
    /*
     * We must update CellData in SetupSolve(), otherwise it will not have been
     * fully initialised by the time we enter the main time loop.
     */
    UpdateCellData(rCellPopulation);
}

template<unsigned DIM>
void DeltaPhenotypeTrackingModifier<DIM>::UpdateCellData(AbstractCellPopulation<DIM,DIM>& rCellPopulation)
{
    // Make sure the cell population is updated
    rCellPopulation.Update();

    MAKE_PTR(DeltaHighPhenotypeProperty, p_dhigh);
    MAKE_PTR(DeltaLowPhenotypeProperty, p_dlow);
    

    for (typename AbstractCellPopulation<DIM>::Iterator cell_iter = rCellPopulation.Begin();
         cell_iter != rCellPopulation.End();
         ++cell_iter)
    {
        
        double this_delta = cell_iter->GetCellData()->GetItem("delta");

        if(this_delta>0.6)
        {
            if(cell_iter->template HasCellProperty<DeltaLowPhenotypeProperty>())
                cell_iter->template RemoveCellProperty<DeltaLowPhenotypeProperty>();
            if(!(cell_iter->template HasCellProperty<DeltaHighPhenotypeProperty>()))
                cell_iter->template AddCellProperty(p_dhigh); //StemCellProliferativeType
            cell_iter->template SetCellProliferativeType(CellPropertyRegistry::Instance()->Get<StemCellProliferativeType>());
            cell_iter->InitialiseCellCycleModel();
        }
        else // < 0.6
        {
            if(cell_iter->template HasCellProperty<DeltaHighPhenotypeProperty>())
                cell_iter->template RemoveCellProperty<DeltaHighPhenotypeProperty>();
            // if Delta < 0.6, the cell stops dividing 
            cell_iter->template SetCellProliferativeType(CellPropertyRegistry::Instance()->Get<DifferentiatedCellProliferativeType>());
            cell_iter->InitialiseCellCycleModel();

            if(this_delta<0.2)  // >0.6
            {
                if(!(cell_iter->template HasCellProperty<DeltaLowPhenotypeProperty>()))
                    cell_iter->template AddCellProperty(p_dlow);
            }
            else    // [0.2, 0.6]
            {   // in this case, i.e. delta in [0.2, 0.6] we remove all labels. i.e. cell has neither Delta-high nor Delta-low phenotype
                if(cell_iter->template HasCellProperty<DeltaLowPhenotypeProperty>())
                    cell_iter->template RemoveCellProperty<DeltaLowPhenotypeProperty>();
            }
        }
    }

}

template<unsigned DIM>
void DeltaPhenotypeTrackingModifier<DIM>::OutputSimulationModifierParameters(out_stream& rParamsFile)
{
    // No parameters to output, so just call method on direct parent class
    AbstractCellBasedSimulationModifier<DIM>::OutputSimulationModifierParameters(rParamsFile);
}

// Explicit instantiation
template class DeltaPhenotypeTrackingModifier<1>;
template class DeltaPhenotypeTrackingModifier<2>;
template class DeltaPhenotypeTrackingModifier<3>;
