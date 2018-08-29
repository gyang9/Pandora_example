/**
 *  @file   ExampleAlgorithms/MopUpBaseAlgorithm.h
 * 
 *  @brief  Header file for the mop up algorithm base class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_MOP_UP_BASE_ALGORITHM_H
#define EXAMPLE_MOP_UP_BASE_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  MopUpBaseAlgorithm class
 */
class MopUpBaseAlgorithm : public pandora::Algorithm
{
public:
    /**
     *  @brief  Find the name of the list hosting a specific object
     * 
     *  @param  pT the address of the object
     * 
     *  @return the name of the list
     */
    template <typename T>
    const std::string GetListName(const T *const pT) const;

protected:
    virtual pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    pandora::StringVector   m_daughterListNames;                ///< The list of potential daughter object list names
};

} // namespace example_content

#endif // #ifndef EXAMPLE_MOP_UP_BASE_ALGORITHM_H
