/**
 *  @file   ExampleAlgorithms/ClearTransverseTrackHitsTool.h
 *
 *  @brief  Header file for the clear transverse track hit creation tool.
 *
 *  $Log: $
 */
#ifndef CLEAR_TRANSVERSE_TRACK_HITS_TOOL_H
#define CLEAR_TRANSVERSE_TRACK_HITS_TOOL_H 1

#include "ExampleAlgorithms/TransverseTrackHitsBaseTool.h"

namespace example_content
{

/**
 *  @brief  ClearTransverseTrackHitsTool class
 */
class ClearTransverseTrackHitsTool : public TransverseTrackHitsBaseTool
{
private:
    void GetTransverseTrackHit3D(const MatchedSlidingFitMap &matchedSlidingFitMap, ProtoHit &protoHit) const;
};

} // namespace example_content

#endif // #ifndef CLEAR_TRANSVERSE_TRACK_HITS_TOOL_H
