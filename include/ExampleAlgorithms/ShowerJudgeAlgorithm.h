/**
 *  @file   ExampleAlgorithms/ShowerJudgeAlgorithm.h
 *
 *  @brief  Header file for the cluster merging algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_SHOWER_JUDGE_ALGORITHM_H
#define EXAMPLE_SHOWER_JUDGE_ALGORITHM_H 1

#include "Pandora/Algorithm.h"
#include "Pandora/AlgorithmTool.h"
#include "Pandora/AlgorithmHeaders.h"

#include <vector>

namespace example_content
{

/**
 *  @brief  ShowerJudgeAlgorithm class
 */
class ShowerJudgeAlgorithm : public pandora::Algorithm
{

public:

    ShowerJudgeAlgorithm();

    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };


private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    void GetPreprocessedListOfClusters(const pandora::ClusterList &unsortedList, pandora::ClusterVector &sortedVector) const;
    void PopulateInformation(pandora::ParticleFlowObject *pPfo, pandora::ClusterVector &clusterVector, pandora::ClusterVector &selectedClusterVector) const; // , pandora::CaloHitList &caloHitList) const;

    std::string m_inputClusterListName;
    std::string m_outputClusterListName;
    std::string m_outputClusterVectorName;
};

// -----------------------------------------------------------------------------

inline pandora::Algorithm *ShowerJudgeAlgorithm::Factory::CreateAlgorithm() const
{
    return new ShowerJudgeAlgorithm();
}

} // namespace example_content

#endif // #ifndef EXAMPLE_SHOWER_JUDGE_ALGORITHM_H
