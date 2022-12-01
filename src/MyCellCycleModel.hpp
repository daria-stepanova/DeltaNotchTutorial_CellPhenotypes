#ifndef MYCELLCYCLEMODEL_HPP_
#define MYCELLCYCLEMODEL_HPP_

#include "AbstractSimpleGenerationalCellCycleModel.hpp"
#include "StemCellProliferativeType.hpp"
#include "TransitCellProliferativeType.hpp"
#include "DifferentiatedCellProliferativeType.hpp"

class MyCellCycleModel : public AbstractSimpleGenerationalCellCycleModel
{
private:
    void SetG1Duration()
    {
        assert(mpCell != NULL);

        double uniform_random_number = RandomNumberGenerator::Instance()->ranf();

        if (mpCell->GetCellProliferativeType()->IsType<StemCellProliferativeType>())
        {
            mG1Duration = -log(uniform_random_number) * GetStemCellG1Duration();
        }
        else if (mpCell->GetCellProliferativeType()->IsType<TransitCellProliferativeType>())
        {
            mG1Duration = -log(uniform_random_number) * GetTransitCellG1Duration();
        }
        else if (mpCell->GetCellProliferativeType()->IsType<DifferentiatedCellProliferativeType>())
        {
            mG1Duration = DBL_MAX;
        }
        else
        {
            NEVER_REACHED;
        }
    }

    void InitialiseDaughterCell()
    {
        double uniform_random_number = RandomNumberGenerator::Instance()->ranf();
        if (uniform_random_number < 0.75)
        {
            boost::shared_ptr<AbstractCellProperty> p_diff_type = mpCell->rGetCellPropertyCollection().GetCellPropertyRegistry()->Get<DifferentiatedCellProliferativeType>();
            mpCell->SetCellProliferativeType(p_diff_type);
        }
        else
        {
            boost::shared_ptr<AbstractCellProperty> p_stem_type = mpCell->rGetCellPropertyCollection().GetCellPropertyRegistry()->Get<StemCellProliferativeType>();
            mpCell->SetCellProliferativeType(p_stem_type);
        }

        AbstractSimplePhaseBasedCellCycleModel::InitialiseDaughterCell();
    }

public:
    MyCellCycleModel()
    {
    }

    AbstractCellCycleModel *CreateCellCycleModel()
    {
        MyCellCycleModel *p_model = new MyCellCycleModel();

        p_model->SetBirthTime(mBirthTime);
        p_model->SetMinimumGapDuration(mMinimumGapDuration);
        p_model->SetStemCellG1Duration(mStemCellG1Duration);
        p_model->SetTransitCellG1Duration(mTransitCellG1Duration);
        p_model->SetSDuration(mSDuration);
        p_model->SetG2Duration(mG2Duration);
        p_model->SetMDuration(mMDuration);
        p_model->SetGeneration(mGeneration);
        p_model->SetMaxTransitGenerations(mMaxTransitGenerations);

        return p_model;
    }
    
};

#endif // MYCELLCYCLEMODEL_HPP_
