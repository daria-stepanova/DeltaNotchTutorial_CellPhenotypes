
#include "DeltaHighPhenotypeProperty.hpp"

DeltaHighPhenotypeProperty::DeltaHighPhenotypeProperty(unsigned colour)
    : AbstractCellProperty(),
      mColour(colour)
{
}

DeltaHighPhenotypeProperty::~DeltaHighPhenotypeProperty()
{
}

unsigned DeltaHighPhenotypeProperty::GetColour() const
{
    return mColour;
}

