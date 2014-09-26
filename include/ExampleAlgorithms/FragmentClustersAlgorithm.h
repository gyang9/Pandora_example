/**
 *  @file   ExampleContent/include/ExampleAlgorithms/FragmentClustersAlgorithm.h
 * 
 *  @brief  Header file for the fragment clusters algorithm class.
 * 
 *  $Log: $
 */
#ifndef FRAGMENT_CLUSTERS_ALGORITHM_H
#define FRAGMENT_CLUSTERS_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  FragmentClustersAlgorithm class
 */
class FragmentClustersAlgorithm : public pandora::Algorithm
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

inline pandora::Algorithm *FragmentClustersAlgorithm::Factory::CreateAlgorithm() const
{
    return new FragmentClustersAlgorithm();
}

} // namespace example_content

#endif // #ifndef FRAGMENT_CLUSTERS_ALGORITHM_H
