/**
 *  @file   ExampleContent/include/ExampleAlgorithms/ReconfigureClustersAlgorithm.h
 * 
 *  @brief  Header file for the reconfigure clusters algorithm class.
 * 
 *  $Log: $
 */
#ifndef RECONFIGURE_CLUSTERS_ALGORITHM_H
#define RECONFIGURE_CLUSTERS_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  ReconfigureClustersAlgorithm class
 */
class ReconfigureClustersAlgorithm : public pandora::Algorithm
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

inline pandora::Algorithm *ReconfigureClustersAlgorithm::Factory::CreateAlgorithm() const
{
    return new ReconfigureClustersAlgorithm();
}

} // namespace example_content

#endif // #ifndef RECONFIGURE_CLUSTERS_ALGORITHM_H
