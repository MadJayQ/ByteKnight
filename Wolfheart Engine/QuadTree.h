#pragma once
#include "EngineMath.h"
#include "AABB.h"

#include <memory>
#include <vector>

#define QT_CAPACITY 4

template<typename T>
class CQuadTreeNode
{
public:
	CQuadTreeNode<T>(CVector3 pos, T* data)
	{
		m_vecPosition = pos;
		m_pDataShared = std::shared_ptr<T>(data);
	}

	T* GetNodeData() { return m_pDataShared.get(); }
	CVector3 GetPosition() const { return m_vecPosition; }

private:
	std::shared_ptr<T> m_pDataShared;
	CVector3 m_vecPosition;
};

template<typename T>
class CQuadTree
{
public:
	CQuadTree<T>()
	{
		m_boundingBox = {};
		m_objects = std::vector<CQuadTreeNode<T>>();
	}
	CQuadTree<T>(AABB boundingBox) :
		m_boundingBox(boundingBox)
	{
		m_boundingBox = boundingBox;
		m_objects = std::vector<CQuadTreeNode<T>>();
	}

	~CQuadTree<T>()
	{
		m_pNorthEast.reset();
		m_pNorthWest.reset();
		m_pSouthEast.reset();
		m_pSouthWest.reset();
	}

	virtual bool Insert(CQuadTreeNode<T> node)
	{
		if (!m_boundingBox.Contains(node.GetPosition()))
		{
			//This object doesn't even exist in the quadtree's bounding rectangle
			return false;
		}
		if (m_objects.size() < QT_CAPACITY)
		{
			m_objects.push_back(node);
			return true;
		}
		if (!m_pNorthWest.get())
		{
			Split();
		}
		if (m_pNorthWest->Insert(node))
		{
			return true;
		}
		if (m_pNorthEast->Insert(node))
		{
			return true;
		}
		if (m_pSouthWest->Insert(node))
		{
			return true;
		}
		if (m_pSouthEast->Insert(node))
		{
			return true;
		}

		return false;
	}

	void Split()
	{
		CVector3 vecSize = CVector3(
			m_boundingBox.m_vecHalfSize._x,
			m_boundingBox.m_vecHalfSize._y,
			0.f
		);
		CVector3 vecCenter = CVector3(
			m_boundingBox.m_vecCenter._x - vecSize._x,
			m_boundingBox.m_vecCenter._y - vecSize._y,
			0.f
		);

		m_pNorthWest.reset(
			new CQuadTree<T>(AABB(
				vecCenter,
				vecSize
			))
		);

		vecCenter = CVector3(
			m_boundingBox.m_vecCenter._x + vecSize._x,
			m_boundingBox.m_vecCenter._y - vecSize._y,
			0.f
		);

		m_pNorthEast.reset(
			new CQuadTree<T>(AABB(
				vecCenter,
				vecSize
			))
		);

		vecCenter = CVector3(
			m_boundingBox.m_vecCenter._x - vecSize._x,
			m_boundingBox.m_vecCenter._y + vecSize._y,
			0.f
		);

		m_pSouthWest.reset(
			new CQuadTree<T>(AABB(
				vecCenter,
				vecSize
			))
		);

		vecCenter = CVector3(
			m_boundingBox.m_vecCenter._x + vecSize._x,
			m_boundingBox.m_vecCenter._y + vecSize._y,
			0.f
		);

		m_pSouthEast.reset(
			new CQuadTree<T>(AABB(
				vecCenter,
				vecSize
			))
		);
	}
	std::vector<CQuadTreeNode<T>> Query(AABB boundingRange)
	{
		std::vector<CQuadTreeNode<T>> retData;

		if (!m_boundingBox.Intersects(boundingRange))
		{
			return retData;
		}

		for (auto&& object : m_objects)
		{
			if (boundingRange.Contains(object.m_vecPosition))
			{
				retData.push_back(object);
			}
		}

		if (!m_pNorthWest.get())
		{
			return retData;
		}

		std::vector<CQuadTreeNode<T>> childrenNodes = m_pNorthWest->Query(boundingRange);
		retData.insert(retData.end(), childrenNodes.begin(), childrenNodes.end());

		childrenNodes = m_pNorthEast->Query(boundingRange);
		retData.insert(retData.end(), childrenNodes.begin(), childrenNodes.end());

		childrenNodes = m_pSouthWest->Query(boundingRange);
		retData.insert(retData.end(), childrenNodes.begin(), childrenNodes.end());

		childrenNodes = m_pSouthEast->Query(boundingRange);
		retData.insert(retData.end(), childrenNodes.begin(), childrenNodes.end());

		return retData;
	}
private:
	std::unique_ptr<CQuadTree<T>> m_pNorthWest;
	std::unique_ptr<CQuadTree<T>> m_pNorthEast;
	std::unique_ptr<CQuadTree<T>> m_pSouthWest;
	std::unique_ptr<CQuadTree<T>> m_pSouthEast;

	AABB m_boundingBox;
	std::vector<CQuadTreeNode<T>> m_objects;
};
