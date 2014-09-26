/**
 *  @file   ExampleContent/include/ExampleAlgorithms/CreateClustersAlgorithm.h
 * 
 *  @brief  Header file for the create clusters algorithm class.
 * 
 *  $Log: $
 */
#ifndef CREATE_CLUSTERS_ALGORITHM_H
#define CREATE_CLUSTERS_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  CreateClustersAlgorithm class
 */
class CreateClustersAlgorithm : public pandora::Algorithm
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

inline pandora::Algorithm *CreateClustersAlgorithm::Factory::CreateAlgorithm() const
{
    return new CreateClustersAlgorithm();
}

} // namespace example_content

#endif // #ifndef CREATE_CLUSTERS_ALGORITHM_H
