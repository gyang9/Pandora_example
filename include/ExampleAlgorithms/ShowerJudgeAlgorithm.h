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

    void GetPreprocessedListOfClusters(pandora::ClusterVector &unsortedVector, pandora::ClusterVector &sortedVector) const;
    void PopulateInformation(pandora::ClusterVector &sortedVector, std::pair<int, double> showerInfo) const;

    std::string m_inputClusterListName;
};

// -----------------------------------------------------------------------------

inline pandora::Algorithm *ShowerJudgeAlgorithm::Factory::CreateAlgorithm() const
{
    return new ShowerJudgeAlgorithm();
}

} // namespace example_content

#endif // #ifndef EXAMPLE_SHOWER_JUDGE_ALGORITHM_H
