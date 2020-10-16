#ifndef BLOCKID_HPP_INCLUDED
#define BLOCKID_HPP_INCLUDED

enum class BlockID
{
	Air = -1,
	Grass = 0,
	Dirt = 1,
	Stone = 2
};

struct cmpBlockID {
	bool operator()(const BlockID& a, const BlockID& b) const {
		return static_cast<int>(a) < static_cast<int>(b);
	}
};

#endif // BLOCKID_HPP_INCLUDED
