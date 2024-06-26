#include <std_include.hpp>
#include "comworld.hpp"

namespace zonetool::iw7
{
	ComWorld* com_world::parse(const std::string& name, zone_memory* mem)
	{
		const auto path = name + ".commap"s;

		assetmanager::reader read(mem);
		if (!read.open(path))
		{
			return nullptr;
		}

		ZONETOOL_INFO("Parsing commap \"%s\"...", name.data());

		ComWorld* asset = read.read_single<ComWorld>();
		asset->name = read.read_string();

		asset->primaryLights = read.read_array<ComPrimaryLight>();
		for (unsigned int i = 0; i < asset->primaryLightCount; i++)
		{
			asset->primaryLights[i].defName = read.read_string();
		}
		asset->primaryLightEnvs = read.read_array<ComPrimaryLightEnv>();

		asset->changeListInfo.userName = read.read_string();

		asset->umbraGateNames = mem->allocate<const char*>(asset->numUmbraGates);
		for (unsigned int i = 0; i < asset->numUmbraGates; i++)
		{
			asset->umbraGateNames[i] = read.read_string();
		}

		read.close();

		return asset;
	}

	void com_world::init(const std::string& name, zone_memory* mem)
	{
		this->name_ = name;
		this->asset_ = this->parse(name, mem);

		if (!this->asset_)
		{
			ZONETOOL_FATAL("Could not parse commap \"%s\"", name.data());
		}
	}

	void com_world::prepare(zone_buffer* buf, zone_memory* mem)
	{
	}

	void com_world::load_depending(zone_base* zone)
	{
		auto asset = this->asset_;

		for (unsigned int i = 0; i < asset->primaryLightCount; i++)
		{
			if (asset->primaryLights[i].defName)
			{
				zone->add_asset_of_type(ASSET_TYPE_LIGHT_DEF, asset->primaryLights[i].defName);
			}
		}
	}

	std::string com_world::name()
	{
		return this->name_;
	}

	std::int32_t com_world::type()
	{
		return ASSET_TYPE_COMWORLD;
	}

	void com_world::write(zone_base* zone, zone_buffer* buf)
	{
		auto* data = this->asset_;
		auto* dest = buf->write(data);

		buf->push_stream(XFILE_BLOCK_VIRTUAL);

		dest->name = buf->write_str(this->name());

		if (data->primaryLights)
		{
			buf->align(7);
			auto* primary_light = buf->write(data->primaryLights, data->primaryLightCount);

			for (unsigned int i = 0; i < data->primaryLightCount; i++)
			{
				if (data->primaryLights[i].defName)
				{
					primary_light[i].defName = buf->write_str(data->primaryLights[i].defName);
				}
			}

			buf->clear_pointer(&dest->primaryLights);
		}

		if (data->primaryLightEnvs)
		{
			buf->align(3);
			buf->write(data->primaryLightEnvs, data->primaryLightEnvCount);
			buf->clear_pointer(&dest->primaryLightEnvs);
		}

		if (data->changeListInfo.userName)
		{
			dest->changeListInfo.userName = buf->write_str(data->changeListInfo.userName);
		}

		if (data->umbraGateNames)
		{
			buf->align(7);
			dest->umbraGateNames = buf->write(data->umbraGateNames, data->numUmbraGates);

			for (unsigned int i = 0; i < data->numUmbraGates; i++)
			{
				dest->umbraGateNames[i] = buf->write_str(data->umbraGateNames[i]);
			}

			buf->clear_pointer(&dest->umbraGateNames);
		}
		

		buf->pop_stream();
	}

	void com_world::dump(ComWorld* asset)
	{
		const auto path = asset->name + ".commap"s;

		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}

		write.dump_single(asset);
		write.dump_string(asset->name);

		write.dump_array(asset->primaryLights, asset->primaryLightCount);
		for (unsigned int i = 0; i < asset->primaryLightCount; i++)
		{
			write.dump_string(asset->primaryLights[i].defName);
		}
		write.dump_array(asset->primaryLightEnvs, asset->primaryLightEnvCount);

		write.dump_string(asset->changeListInfo.userName);

		for (unsigned int i = 0; i < asset->numUmbraGates; i++)
		{
			write.dump_string(asset->umbraGateNames[i]);
		}

		write.close();
	}
}