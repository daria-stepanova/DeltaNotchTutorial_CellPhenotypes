
#ifndef DELTAHIGHPHENOTYPEPROPERTY_HPP_
#define DELTAHIGHPHENOTYPEPROPERTY_HPP_

#include "AbstractCellProperty.hpp"

/**
 * Delta-high cell property.
 *
 * Each Cell owns a CellPropertyCollection, which may include a shared pointer
 * to an object of this type.
 *
 * The DeltaHighPhenotypeProperty object keeps track of the number of cells that have high Delta, as well
 * as what colour should be used by the visualizer to display cells that have high Delta.
 */

class DeltaHighPhenotypeProperty : public AbstractCellProperty
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
    DeltaHighPhenotypeProperty(unsigned colour=31);

    /**
     * Destructor.
     */
    virtual ~DeltaHighPhenotypeProperty();

    /**
     * @return #mColour.
     */
    unsigned GetColour() const;
};

#endif /* DELTAHIGHPHENOTYPEPROPERTY_HPP_ */
