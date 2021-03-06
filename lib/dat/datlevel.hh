/*
 * Copyright (C) 2013-2014 Dmitry Marakasov
 *
 * This file is part of openstrike.
 *
 * openstrike is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * openstrike is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with openstrike.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DATLEVEL_HH
#define DATLEVEL_HH

#include <vector>
#include <list>
#include <map>
#include <functional>

#include <dat/buffer.hh>

class MemRange;

class DatLevel {
public:
	struct BuildingInstance {
		unsigned short type;
		unsigned short x;
		unsigned short y;
		signed short sprite_x;
		signed short sprite_y;

		unsigned short dead_type;
		signed short dead_sprite_x;
		signed short dead_sprite_y;

		BuildingInstance() : dead_type(0) {
		}
	};

	struct BuildingType {
		struct BBox {
			signed short x1, y1;
			signed short x2, y2;
			signed short z1, z2;
		};

		unsigned short width;
		unsigned short height;

		unsigned short health;

		std::string resource_name;

		std::vector<unsigned short> blocks;
		std::vector<BBox> bboxes;
	};

	struct UnitInstance {
		unsigned short x;
		unsigned short y;
		signed short z;
	};

	typedef std::function<void(const BuildingInstance&)> BuildingInstanceProcessor;
	typedef std::function<void(unsigned short, const BuildingType&)> BuildingTypeProcessor;

	typedef std::function<void(const UnitInstance&)> UnitInstanceProcessor;

protected:
	const static std::map<unsigned short, std::string> gfx_resources_;

protected:
	std::list<BuildingInstance> building_instances_;
	std::map<unsigned int, BuildingType> building_types_;
	std::list<UnitInstance> unit_instances_;

public:
	DatLevel(const MemRange& leveldata, const MemRange& thingsdata, int width_blocks, int height_blocks);

	void ForeachBuildingInstance(const BuildingInstanceProcessor& fn) const;
	void ForeachBuildingType(const BuildingTypeProcessor& fn) const;

	void ForeachUnitInstance(const UnitInstanceProcessor& fn) const;

	const BuildingType& GetBuildingType(unsigned short type) const;
};

#endif // DATLEVEL_HH
