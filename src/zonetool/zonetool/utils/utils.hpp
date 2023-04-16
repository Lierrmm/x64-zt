#pragma once

#include "memory.hpp"

#include "io/filesystem.hpp"
#include "io/assetmanager.hpp"

#include "csv.hpp"

#include "shader.hpp"
#include "game/mode.hpp"
#include "game/shared.hpp"

#include "interfaces/zonebuffer.hpp"
#include "interfaces/zone.hpp"
#include "interfaces/asset.hpp"

#include <utils/memory.hpp>

#define JSON_DIAGNOSTICS 1
#include "json.hpp"
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

namespace nlohmann
{
	static inline std::vector<std::uint8_t> get_object_bytes(json object)
	{
		if (!object.is_object())
		{
			throw (detail::concat("type must be object, but is ", object.type_name()));
		}
		auto bytes = object["bytes"];
		if (bytes.is_null())
		{
			throw ("object doesn't have \"bytes\" field");
		}
		std::vector<std::uint8_t> m_bytes(bytes.size());
		for (auto i = 0; i < bytes.size(); i++)
		{
			auto byte = bytes[i].get<std::uint8_t>();
			m_bytes[i] = byte;
		}
		return m_bytes;
	}
}

#define MAX_ZONE_SIZE (1024ull * 1024ull * 1024ull) * 2ull
#define MAX_MEM_SIZE (1024ull * 1024ull * 1024ull) * 2ull

#define ZONETOOL_INFO(__FMT__,...) \
	printf("[ INFO ][ " __FUNCTION__ " ]: " __FMT__ "\n", __VA_ARGS__)

#define ZONETOOL_ERROR(__FMT__,...) \
	printf("[ ERROR ][ " __FUNCTION__ " ]: " __FMT__ "\n", __VA_ARGS__)

#define ZONETOOL_FATAL(__FMT__,...) \
	printf("[ FATAL ][ " __FUNCTION__ " ]: " __FMT__ "\n", __VA_ARGS__); \
	MessageBoxA(nullptr, &utils::string::va("Oops! An unexpected error occured. Error was: \n" __FMT__ "\n\nZoneTool must be restarted to resolve the error. Last error code reported by windows: 0x%08X (%u)", __VA_ARGS__, GetLastError(), GetLastError())[0], nullptr, MB_ICONERROR); \
	std::quick_exit(EXIT_FAILURE)

#define ZONETOOL_WARNING(__FMT__,...) \
	printf("[ WARNING ][ " __FUNCTION__ " ]: " __FMT__ "\n", __VA_ARGS__)


#define ASSET_TEMPLATE typename S, std::int32_t Type, typename H, typename E
#define REGISTER_TEMPLATED_ASSET(__name__, __struct__, __type__) using __name__ = zonetool::__name__<__struct__, __type__, XAssetHeader, XAssetEntry>

#include "assets/rawfile.hpp"

namespace zonetool
{
	struct zonetool_globals_t
	{
		bool verify;
		bool dump;
		game::game_mode target_game;
		filesystem::file csv_file;
	};
}