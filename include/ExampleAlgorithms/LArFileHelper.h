/**
 *  @file   ExampleAlgorithms/LArFileHelper.h
 *
 *  @brief  Header file for the file helper class
 *
 *  $Log: $
 */
#ifndef EXAMPLE_FILE_HELPER_H
#define EXAMPLE_FILE_HELPER_H 1

#include <string>

namespace example_content
{

/**
 *  @brief  LArFileHelper class
 */
class LArFileHelper
{
public:
    /**
     *  @brief  Find the fully-qualified file name by searching through a list of delimiter-separated paths in a named environment
     *          variable. The fully-qualified file name will be provided for the first instance of the file name encountered.
     *
     *  @param  unqualifiedFileName the unqualified file name
     *  @param  environmentVariable the name of the environment variable specifying a list of delimiter-separated paths
     *  @param  delimiter the specified delimiter
     *
     *  @return the fully-qualified name if found, else a StatusCode exception will be raised
     */
    static std::string FindFileInPath(const std::string &unqualifiedFileName, const std::string &environmentVariable, const std::string &delimiter = ":");
};

} // namespace example_content

#endif // #ifndef EXAMPLE_FILE_HELPER_H