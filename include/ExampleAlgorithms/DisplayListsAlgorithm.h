/**
 *  @file   ExampleContent/include/ExampleAlgorithms/DisplayListsAlgorithm.h
 * 
 *  @brief  Header file for the display lists algorithm class.
 * 
 *  $Log: $
 */
#ifndef DISPLAY_LISTS_ALGORITHM_H
#define DISPLAY_LISTS_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  DisplayListsAlgorithm class
 */
class DisplayListsAlgorithm : public pandora::Algorithm
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

inline pandora::Algorithm *DisplayListsAlgorithm::Factory::CreateAlgorithm() const
{
    return new DisplayListsAlgorithm();
}

} // namespace example_content

#endif // #ifndef DISPLAY_LISTS_ALGORITHM_H
