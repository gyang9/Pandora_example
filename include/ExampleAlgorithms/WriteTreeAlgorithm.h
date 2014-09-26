/**
 *  @file   ExampleContent/include/ExampleAlgorithms/WriteTreeAlgorithm.h
 * 
 *  @brief  Header file for the write tree algorithm class.
 * 
 *  $Log: $
 */
#ifndef WRITE_TREE_ALGORITHM_H
#define WRITE_TREE_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  WriteTreeAlgorithm class
 */
class WriteTreeAlgorithm : public pandora::Algorithm
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

inline pandora::Algorithm *WriteTreeAlgorithm::Factory::CreateAlgorithm() const
{
    return new WriteTreeAlgorithm();
}

} // namespace example_content

#endif // #ifndef WRITE_TREE_ALGORITHM_H
