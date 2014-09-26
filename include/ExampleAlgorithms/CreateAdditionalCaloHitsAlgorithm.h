/**
 *  @file   ExampleContent/include/ExampleAlgorithms/CreateAdditionalCaloHitsAlgorithm.h
 * 
 *  @brief  Header file for the create additional calo hits algorithm class.
 * 
 *  $Log: $
 */
#ifndef CREATE_ADDITIONAL_CALO_HITS_ALGORITHM_H
#define CREATE_ADDITIONAL_CALO_HITS_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  CreateAdditionalCaloHitsAlgorithm class
 */
class CreateAdditionalCaloHitsAlgorithm : public pandora::Algorithm
{
public:
    /**
     *  @brief  Factory class for instantiating algorithm
     */
    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };

private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    // Member variables here
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *CreateAdditionalCaloHitsAlgorithm::Factory::CreateAlgorithm() const
{
    return new CreateAdditionalCaloHitsAlgorithm();
}

} // namespace example_content

#endif // #ifndef CREATE_ADDITIONAL_CALO_HITS_ALGORITHM_H
