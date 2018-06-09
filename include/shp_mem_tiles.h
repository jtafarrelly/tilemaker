#ifndef _SHP_MEM_TILES
#define _SHP_MEM_TILES

#include "tile_data.h"

class ShpMemTiles : public TileDataSource
{
public:
	ShpMemTiles(uint baseZoom);

	virtual void MergeTileCoordsAtZoom(uint zoom, TileCoordinatesSet &dstCoords);

	virtual void MergeSingleTileDataAtZoom(TileCoordinates dstIndex, uint zoom, 
		std::vector<OutputObjectRef> &dstTile);

	// Find intersecting shapefile layer
	virtual std::vector<std::string> FindIntersecting(const std::string &layerName, Box &box);
	virtual bool Intersects(const std::string &layerName, Box &box);
	virtual void CreateNamedLayerIndex(const std::string &layerName);
	virtual void AddObjectedToIndex(const std::string &layerName, Box &box, bool hasName, const std::string &name);

	TileIndex tileIndex;
	std::vector<Geometry> cachedGeometries;					// prepared boost::geometry objects (from shapefiles)
	std::map<uint, std::string> cachedGeometryNames;			//  | optional names for each one
	std::map<std::string, RTree> indices;			// Spatial indices, boost::geometry::index objects for shapefile indices

private:
	std::vector<uint> findIntersectingGeometries(const std::string &layerName, Box &box);
	std::vector<uint> verifyIntersectResults(std::vector<IndexValue> &results, Point &p1, Point &p2);
	std::vector<std::string> namesOfGeometries(std::vector<uint> &ids);

	uint baseZoom;
};

#endif //_OSM_MEM_TILES

