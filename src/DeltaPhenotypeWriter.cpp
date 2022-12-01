#include "DeltaPhenotypeWriter.hpp"

#include "AbstractCellPopulation.hpp"
#include "DeltaLowPhenotypeProperty.hpp"
#include "DeltaHighPhenotypeProperty.hpp"


template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
DeltaPhenotypeWriter<ELEMENT_DIM, SPACE_DIM>::DeltaPhenotypeWriter()
    : AbstractCellWriter<ELEMENT_DIM, SPACE_DIM>("results.vizcellphenotype")
{
    this->mVtkCellDataName = "Delta Phenotype";
}

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
double DeltaPhenotypeWriter<ELEMENT_DIM, SPACE_DIM>::GetCellDataForVtkOutput(CellPtr pCell, AbstractCellPopulation<ELEMENT_DIM, SPACE_DIM>* pCellPopulation)
{   
    if(pCell->HasCellProperty<DeltaLowPhenotypeProperty>())
        return 1.0;
    if(pCell->HasCellProperty<DeltaHighPhenotypeProperty>())
        return 2.0;
    return 0.0;
}

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
void DeltaPhenotypeWriter<ELEMENT_DIM, SPACE_DIM>::VisitCell(CellPtr pCell, AbstractCellPopulation<ELEMENT_DIM, SPACE_DIM>* pCellPopulation)
{
    if(pCell->HasCellProperty<DeltaLowPhenotypeProperty>())
        *this->mpOutStream <<1<<" ";
    else if(pCell->HasCellProperty<DeltaHighPhenotypeProperty>())
         *this->mpOutStream <<2<<" ";
    else
         *this->mpOutStream <<0<<" ";
}

// Explicit instantiation
template class DeltaPhenotypeWriter<1,1>;
template class DeltaPhenotypeWriter<1,2>;
template class DeltaPhenotypeWriter<2,2>;
template class DeltaPhenotypeWriter<1,3>;
template class DeltaPhenotypeWriter<2,3>;
template class DeltaPhenotypeWriter<3,3>;
