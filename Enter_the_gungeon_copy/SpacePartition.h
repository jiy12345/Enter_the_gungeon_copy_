#pragma once
#include "stdafx.h"
#include "ObjectManager.h"
#include "sizes.h"

enum class SP_TYPE
{
	T_QUADTREE,
	T_OCTREE,
	T_BSP,
};

#define DEPTH 5

template <size_t n> 
struct Node {
public:
	int						m_iDepth;
	nCube<n>				m_area;
	std::vector<int>		m_staticObjectList;
	std::unordered_set<int> m_dynamicObjectList;
};

template <size_t n>
class SpacePartition: public JSingleton<SpacePartition<n>>
{
	friend class JSingleton<SpacePartition<n>>;
private:
	const int m_iArraySize = ((1 << ((DEPTH)*n)) - 1) / ((1 << n) - 1);
public:
	Node<n> nodeList[((1 << ((DEPTH)*n)) - 1) / ((1 << n) - 1)];
public:
	int					LeftMostChild(int iDepth, int iNodeNum);
	int					getLeftMostNode(int iDepth);
	int					getRightMostNode(int iDepth);
	void				Buildtree(int iDepth, int iNodeNum);
	int					FindNode(int iNodeNum, nCube<n> &ObjectArea);
	std::vector<int>	FindCollisionSearchNode(int iNodeNum, nCube<n> &ObjectArea);
public:
	void	Init();
private:
	const int delta[3][8] = { {0, 1, 0, 1, 0, 1, 0, 1 },
					{0, 0, 1, 1, 0, 0, 1, 1 },
					{0, 0, 0, 0, 1, 1, 1, 1 }
	};
private:
	SpacePartition<n>() {};
	~SpacePartition<n>() = default;
	SpacePartition<n>(const SpacePartition<n>&) = delete;
	SpacePartition<n>& operator=(const SpacePartition<n>&) = delete;
};

#define I_SP2D SpacePartition<2>::GetInstance()
#define I_SP3D SpacePartition<3>::GetInstance()

template<size_t n>
inline int SpacePartition<n>::LeftMostChild(int iDepth, int iNodeNum)
{
	if (iNodeNum == 0) return 1;
	int iLeftMostNode = getLeftMostNode(iDepth);
	int iNextLayerLeftMostNode = getLeftMostNode(iDepth + 1);
	int r = 1 << n;
	return iNextLayerLeftMostNode + (iNodeNum - iLeftMostNode) * r;
}

template<size_t n>
inline int SpacePartition<n>::getLeftMostNode(int iDepth)
{
	int r = 1 << n;
	return ((1 << ((iDepth - 1) * n)) - 1) / (r - 1);
}

template<size_t n>
inline int SpacePartition<n>::getRightMostNode(int iDepth)
{
	int r = 1 << n;
	return ((1 << (iDepth * n)) - 1) / (r - 1) - 1;
}

template<size_t n>
inline void SpacePartition<n>::Buildtree(int iDepth, int iNodeNum)
{
	if (iDepth >= DEPTH) return;
    int leftMostChild = LeftMostChild(iDepth, iNodeNum);
    JVector<n> pos;
    JVector<n> size = nodeList[iNodeNum].m_area.m_vSize / 2;
    int childNum = 1 << n;
    for (int iCurChildNode = leftMostChild; iCurChildNode < leftMostChild + childNum; iCurChildNode++) {
        for (int j = 0; j < n; j++) {
            pos[j] = nodeList[iNodeNum].m_area.m_vLeftTop[j] + delta[j][iCurChildNode - leftMostChild] * size[j];
        }
		nodeList[iCurChildNode].m_area.Set(pos, size);
		nodeList[iCurChildNode].m_iDepth = iDepth;
		Buildtree(iDepth + 1, iCurChildNode);
    }
}

template<size_t n>
inline int SpacePartition<n>::FindNode(int iNodeNum, nCube<n> &ObjectArea)
{
	std::queue<int> bfs_queue;
	int curNode = iNodeNum;
	int childNum = 1 << n;
	do {
		int leftMostChild = LeftMostChild(nodeList[curNode].m_iDepth, curNode);
		// if (leftMostChild >= m_iArraySize) continue;
		for (int iCurChildNode = leftMostChild; iCurChildNode < leftMostChild + childNum; iCurChildNode++) {
			if (leftMostChild >= m_iArraySize) continue;

			nCube<n> curNodeArea = nodeList[iCurChildNode].m_area;
			if (JCollision<n>::CubeToCube(ObjectArea, curNodeArea) == CollisionType::C_B_IN_A) {
				bfs_queue.push(iCurChildNode);
				break;
			}
		}
		if (bfs_queue.empty()) break;
		curNode = bfs_queue.front();
		bfs_queue.pop();
	} while (curNode);
	return curNode;
}

template<size_t n>
inline std::vector<int> SpacePartition<n>::FindCollisionSearchNode(int iNodeNum, nCube<n>& ObjectArea)
{
	std::queue<int> bfs_queue;
	std::vector<int> nodeToSearch;
	int curNode = iNodeNum;
	int childNum = 1 << n;
	do {
		int leftMostChild = LeftMostChild(nodeList[curNode].m_iDepth, curNode);
		for (int iCurChildNode = leftMostChild; iCurChildNode < leftMostChild + childNum; iCurChildNode++) {
			if (leftMostChild >= m_iArraySize) continue;

			nCube<n> curNodeArea = nodeList[iCurChildNode].m_area;
			if (JCollision<n>::CubeToCube(ObjectArea, curNodeArea) != CollisionType::C_OUT) {
				bfs_queue.push(iCurChildNode);
				nodeToSearch.push_back(iCurChildNode);
			}
		}
		if (bfs_queue.empty()) break;
		curNode = bfs_queue.front();
		bfs_queue.pop();
	} while (curNode);
	return nodeToSearch;
}

template<size_t n>
inline void SpacePartition<n>::Init()
{
	JVector<n> pos;
	JVector<n> size;

	for (int i = 0; i < n; i++) {
		pos[i] = 0;
		size[i] = MAP_SIZE_X;
	}

	nodeList[0].m_area.Set(pos, size);
	nodeList[0].m_iDepth = 0;
}