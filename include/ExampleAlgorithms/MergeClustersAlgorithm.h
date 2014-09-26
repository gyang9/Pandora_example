/**
 *  @file   ExampleContent/include/ExampleAlgorithms/MergeClustersAlgorithm.h
 * 
 *  @brief  Header file for the merge clusters algorithm class.
 * 
 *  $Log: $
 */
#ifndef MERGE_CLUSTERS_ALGORITHM_H
#define MERGE_CLUSTERS_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  MergeClustersAlgorithm class
 */
class MergeClustersAlgorithm : public pandora::Algorithm
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

inline pandora::Algorithm *MergeClustersAlgorithm::Factory::CreateAlgorithm() const
{
    return new MergeClustersAlgorithm();
}

} // namespace example_content

#endif // #ifndef MERGE_CLUSTERS_ALGORITHM_H
