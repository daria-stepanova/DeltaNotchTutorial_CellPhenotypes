
#ifndef DELTALOWPHENOTYPEPROPERTY_HPP_
#define DELTALOWPHENOTYPEPROPERTY_HPP_

#include "AbstractCellProperty.hpp"
/**
 * Delta-low cell property.
 *
 * Each Cell owns a CellPropertyCollection, which may include a shared pointer
 * to an object of this type.
 *
 * The DeltaLowPhenotypeProperty object keeps track of the number of cells that have low Delta, as well
 * as what colour should be used by the visualizer to display cells that have low Delta.
 */

class DeltaLowPhenotypeProperty : public AbstractCellProperty
{
private:

    /**
     * Colour for use by visualizer.
     */
    unsigned mColour;

public:

    /**
     * Constructor.
     *
     * @param colour  what colour cells with this property should be in the visualizer (defaults to 6)
     */
    DeltaLowPhenotypeProperty(unsigned colour=32);

    /**
     * Destructor.
     */
    virtual ~DeltaLowPhenotypeProperty();

    /**
     * @return #mColour.
     */
    unsigned GetColour() const;
};

#endif /* DELTALOWPHENOTYPEPROPERTY_HPP_ */
