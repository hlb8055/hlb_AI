#ifndef GRAPH_NODE_TYPES_H
#define GRAPH_NODE_TYPES_H
//-----------------------------------------------------------------------------
//
//  Name:   GraphNodeTypes.h
//
//
//  Desc:   Node classes to be used with graphs
//-----------------------------------------------------------------------------
#include <list>
#include "common/2D/Vector2D.h"




class GraphNode
{  
protected:
    //every node has an index. A valid index is >= 0
    int m_iIndex;

public:
    GraphNode():m_iIndex(-1){}
    GraphNode(int idx):m_iIndex(idx){}

    virtual ~GraphNode(){}

    int getIndex()const{return m_iIndex;}
    void setIndex(int NewIndex){m_iIndex = NewIndex;}
};   


//-----------------------------------------------------------------------------
//
//  Graph node for use in creating a navigation graph.This node contains
//  the position of the node and a pointer to a BaseEntity... useful
//  if you want your nodes to represent health packs, gold mines and the like
//-----------------------------------------------------------------------------
template <class extra_info = void*>
class NavGraphNode : public GraphNode
{
protected:
    //the node's position
    Vector2D m_vPosition;

    //often you will require a navgraph node to contain additional information.
    //For example a node might represent a pickup such as armor in which
    //case m_ExtraInfo could be an enumerated value denoting the pickup type,
    //thereby enabling a search algorithm to search a graph for specific items.
    //Going one step further, m_ExtraInfo could be a pointer to the instance of
    //the item type the node is twinned with. This would allow a search algorithm
    //to test the status of the pickup during the search. 
    extra_info m_ExtraInfo;

public:
    //ctors
    NavGraphNode():m_ExtraInfo(extra_info()){}

    NavGraphNode(int idx, Vector2D pos):GraphNode(idx),
                                                                     m_vPosition(pos),
                                                                     m_ExtraInfo(extra_info())
    {
    }

    virtual ~NavGraphNode(){}

    Vector2D getPos()const{return m_vPosition;}
    void setPos(Vector2D NewPosition){m_vPosition = NewPosition;}

    extra_info getExtraInfo()const{return m_ExtraInfo;}
    void setExtraInfo(extra_info info){m_ExtraInfo = info;}
};


#endif
