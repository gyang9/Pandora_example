/**
 *  @file   ExampleContent/include/ExampleAlgorithms/DeleteClustersAlgorithm.h
 * 
 *  @brief  Header file for the delete clusters algorithm class.
 * 
 *  $Log: $
 */
#ifndef DELETE_CLUSTERS_ALGORITHM_H
#define DELETE_CLUSTERS_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  DeleteClustersAlgorithm class
 */
class DeleteClustersAlgorithm : public pandora::Algorithm
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

inline pandora::Algorithm *DeleteClustersAlgorithm::Factory::CreateAlgorithm() const
{
    return new DeleteClustersAlgorithm();
}

} // namespace example_content

#endif // #ifndef DELETE_CLUSTERS_ALGORITHM_H
