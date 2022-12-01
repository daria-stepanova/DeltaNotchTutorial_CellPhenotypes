
#ifndef DELTAPHENOTYPEWRITER_HPP_
#define DELTAPHENOTYPEWRITER_HPP_

#include "AbstractCellWriter.hpp"

/**
 * A class written using the visitor pattern for writing Delta cell phenotype to file.
 *
 * The output file is called results.vizcelltypes by default. If VTK is switched on,
 * then the writer also specifies the VTK output for each cell, which is stored in
 * the VTK cell data "Cell types" by default.
 */
template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
class DeltaPhenotypeWriter : public AbstractCellWriter<ELEMENT_DIM, SPACE_DIM>
{

public:

    /**
     * Default constructor.
     */
    DeltaPhenotypeWriter();

    /**
     * Overridden GetCellDataForVtkOutput() method.
     *
     * Get a double associated with a cell. This method reduces duplication
     * of code between the methods VisitCell() and AddVtkData().
     *
     * @param pCell a cell
     * @param pCellPopulation a pointer to the cell population owning the cell
     *
     * @return data associated with the cell
     */
    double GetCellDataForVtkOutput(CellPtr pCell, AbstractCellPopulation<ELEMENT_DIM, SPACE_DIM>* pCellPopulation);

    /**
     * Overridden VisitCell() method.
     *
     * Visit a cell and write its proliferative type, as given by this property's member mColour.
     *
     * Outputs a line of space-separated values of the form:
     * ...[cell proliferative type] ...
     *
     * Note that if the cell is undergoing apoptosis (i.e. has the property ApoptoticCellProperty),
     * then the hard-coded value 6 is written. If instead the cell is labelled (i.e. has the property
     * CellLabel), then this property's member mColour is instead written. Lastly, if the cell
     * has a mutation state other than WildTypeCellMutationState, then this property's member
     * mColour is instead written.
     *
     * This is appended to the output written by AbstractCellBasedWriter, which is a single
     * value [present simulation time], followed by a tab.
     *
     * @param pCell a cell
     * @param pCellPopulation a pointer to the cell population owning the cell
     */
    virtual void VisitCell(CellPtr pCell, AbstractCellPopulation<ELEMENT_DIM, SPACE_DIM>* pCellPopulation);
};

#endif /* DELTAPHENOTYPEWRITER_HPP_ */