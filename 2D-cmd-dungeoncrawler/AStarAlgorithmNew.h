#pragma once

#include "Vector2i.h"
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <functional>

/* 
	https://www.quora.com/How-can-I-declare-an-unordered-set-of-pair-of-int-int-in-C++11
	Functions copied from source and then rewritten.
*/
template <class T>
void hash_combine( std::size_t & seed, const T & v )
{
	std::hash<T> hasher;
	seed ^= hasher( v ) + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 );
}
namespace std
{
	template<>
	struct hash<Vector2i>
	{
		typedef Vector2i argument_type;
		typedef std::size_t result_type;
		result_type operator()( argument_type const& s ) const
		{
			size_t seed = 0;
			::hash_combine( seed, s.col );
			::hash_combine( seed, s.row );
			return seed;
		}
	};
}

template<typename T, typename Number = int>
struct ModifiedPriorityQueue
{
	std::priority_queue<std::pair<Number, T>, std::vector<std::pair<Number, T>>, std::greater<std::pair<Number, T>>> elements;

	bool Empty( )
	{
		return elements.empty( );
	}
	void Put( const T& item, const Number& priority )
	{
		elements.emplace( priority, item );
	}
	const T Get( )
	{
		const T itemBest = elements.top( ).second;
		elements.pop( );
		return itemBest;
	}
};

struct SquareGrid
{
	SquareGrid( const Vector2i& gridSize, const std::vector<Vector2i>& obstaclePositions );

	Vector2i gridSize;
	std::unordered_set<Vector2i> obstacles;
	static const std::array<Vector2i, 4> DIRS;

	bool InBounds( const Vector2i& position ) const;
	bool Passable( const Vector2i& position ) const;
	const std::vector<Vector2i> GetValidNeighbors( const Vector2i& position ) const;
};

int Heuristic( const Vector2i& a, const Vector2i& b );

std::vector<Vector2i> AStarAlgorithmNew( const Vector2i& positionStart, const Vector2i& positionFinish, const Vector2i& gridSize, const std::vector<Vector2i>& obstaclePositions );