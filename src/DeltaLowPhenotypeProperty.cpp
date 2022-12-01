#include "DeltaLowPhenotypeProperty.hpp"

DeltaLowPhenotypeProperty::DeltaLowPhenotypeProperty(unsigned colour)
    : AbstractCellProperty(),
      mColour(colour)
{
}

DeltaLowPhenotypeProperty::~DeltaLowPhenotypeProperty()
{
}

unsigned DeltaLowPhenotypeProperty::GetColour() const
{
    return mColour;
}
