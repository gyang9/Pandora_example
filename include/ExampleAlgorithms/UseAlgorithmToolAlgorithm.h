/**
 *  @file   ExampleContent/include/ExampleAlgorithms/UseAlgorithmToolAlgorithm.h
 * 
 *  @brief  Header file for the use algorithm tool algorithm class.
 * 
 *  $Log: $
 */
#ifndef USE_ALGORITHM_TOOL_ALGORITHM_H
#define USE_ALGORITHM_TOOL_ALGORITHM_H 1

#include "Pandora/Algorithm.h"
#include "Pandora/AlgorithmTool.h"

namespace example_content
{

class IExampleAlgorithmTool;

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  UseAlgorithmToolAlgorithm class
 */
class UseAlgorithmToolAlgorithm : public pandora::Algorithm
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

    typedef std::vector<IExampleAlgorithmTool*> AlgorithmToolList;  ///< The algorithm tool list typedef
    AlgorithmToolList   m_algorithmToolList;                        ///< The algorithm tool list

    // Further member variables here
};

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  IExampleAlgorithmTool class
 */
class IExampleAlgorithmTool : public pandora::AlgorithmTool
{
public:
    /**
     *  @brief  Use the example algorithm tool functionality
     *
     *  @param  pAlgorithm address of the calling algorithm
     */
    virtual pandora::StatusCode ExampleToolFunctionality(const UseAlgorithmToolAlgorithm *const pAlgorithm) = 0;
};

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *UseAlgorithmToolAlgorithm::Factory::CreateAlgorithm() const
{
    return new UseAlgorithmToolAlgorithm();
}

} // namespace example_content

#endif // #ifndef USE_ALGORITHM_TOOL_ALGORITHM_H
