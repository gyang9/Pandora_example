/**
 *  @file   ExampleAlgorithms/LArObjectHelper.h
 *
 *  @brief  Header file for the object helper class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_OBJECT_HELPER_H
#define EXAMPLE_OBJECT_HELPER_H 1

#include "Objects/Cluster.h"

namespace example_content
{

/**
 *  @brief  LArObjectHelper class
 */
class LArObjectHelper
{
public:
    /**
     *  @brief  TypeAdaptor
     */
    class TypeAdaptor
    {
    public:
        /**
         *  @brief  Get the associated position
         *
         *  @param  t the input object
         *
         *  @return the associated position
         */
        template<typename T>
        static pandora::CartesianVector GetPosition(const T &t);

        /**
         *  @brief  Get the associated calo hit, or nullptr if none
         *
         *  @param  t the input object
         *
         *  @return the associated calo hit, or nullptr if none
         */
        template<typename T>
        static const pandora::CaloHit *GetCaloHit(const T &t);
    };
};

} // namespace example_content

#endif // #ifndef EXAMPLE_OBJECT_HELPER_H
