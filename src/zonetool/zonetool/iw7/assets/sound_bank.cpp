#include <std_include.hpp>
#include "sound_bank.hpp"

#include "../common/sound.hpp"

#include "utils/io.hpp"
#include "utils/bit_buffer.hpp"

namespace zonetool::iw7
{
	namespace ducks
	{
		bool parse_duck(const std::string& name, zone_memory* mem, SndDuck* asset);
	}

	namespace aliases
	{
		std::string LOAD_TYPES[] =
		{
			"loaded",
			"rev_vehicle",
			"hybrid_pcm",
			"streamed",
			"primed",
		};

		std::string LOOP_TYPES[] =
		{
			"nonlooping",
			"looping",
			"unused",
			"rlooping",
		};

		std::string MUSIC_CONTENT[] =
		{
			"none",
			"music",
			"licensed",
		};

		std::string GPAD_OUTPUT[] =
		{
			"none",
			"ifavailable",
			"controlleronly",
		};

		std::string SHAPES[] =
		{
			"disc",
			"donut",
			"donut_log_fast",
			"donut_log_slow",
			"donut_flat_ended",
			"donut_flat_middle",
		};

		std::string FULLDRYLEVEL[] =
		{
			"",
			"fulldrylevel"
		};

		std::string SND_ALIAS_FIELDS[] =
		{
			"Name",
			"SecondaryAliasName",
			"StopAliasName",
			"Subtitle",
			"File",
			"vol_min",
			"vol_max",
			"vol_mod",
			"pitch_min",
			"pitch_max",
			"donut_fadeend",
			"dist_min",
			"dist_max",
			"Velocity_Min",
			"channel",
			"type",
			"loop",
			"Probability",
			"volumefalloffcurve",
			"lpfcurve",
			"hpfcurve",
			"reverbsendcurve",
			"StartDelay",
			"SpeakerMap",
			"reverb",
			"reverb_multiplier",
			"far_reverb_multiplier",
			"lfe_percentage",
			"center_percentage",
			"envelop_min",
			"envelop_max",
			"envelop_percentage",
			"shape",
			"ignoreDistanceCheck",
			"occlusionshape",
			"dopplerpreset",
			"smartPanDistance2d",
			"smartPanDistance3d",
			"smartPanAttenuation2d",
			"stereoSpreadMinDist",
			"stereoSpreadMaxDist",
			"stereoSpreadMidPoint",
			"stereoSpreadMaxAngle",
			"contexttype",
			"contextvalue",
			"precached",
			"duck",
			"MusicContent",
			"GPadOutput",
			"ForceSubtitle",
			"masterPriority",
			"masterPercentage",
			"masterSlavePercentage",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".aliases.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_ALIAS_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write_alias(SndBank* asset, SndAlias* alias, csv_writer& writer)
		{
			writer.write_column(alias->aliasName ? alias->aliasName : "");
			writer.write_column(alias->secondaryAliasName ? alias->secondaryAliasName : "");
			writer.write_column(alias->stopAliasName ? alias->stopAliasName : "");
			writer.write_column(alias->subtitle ? alias->subtitle : "");
			writer.write_column(alias->assetFileName ? alias->assetFileName : "");
			writer.write_column(alias->volMin);
			writer.write_column(alias->volMax);
			writer.write_column(VOLMODS[alias->volModIndex]);
			writer.write_column(alias->pitchMin);
			writer.write_column(alias->pitchMax);
			writer.write_column(alias->donutFadeEnd);
			writer.write_column(alias->distMin);
			writer.write_column(alias->distMax);
			writer.write_column(alias->velocityMin);
			writer.write_column(ENTCHANNELS[alias->flags.channel]);
			writer.write_column(LOAD_TYPES[alias->flags.type]);
			writer.write_column(LOOP_TYPES[alias->flags.looping]);
			writer.write_column(alias->probability);
			writer.write_column(alias->volumeFalloffCurveIndex == 0xFF ? "" : vf_curves_s[alias->volumeFalloffCurveIndex]);
			writer.write_column(alias->lpfCurveIndex == 0xFF ? "" : lpf_curves_s[alias->lpfCurveIndex]);
			writer.write_column(alias->hpfCurveIndex == 0xFF ? "" : hpf_curves_s[alias->hpfCurveIndex]);
			writer.write_column(alias->reverbSendCurveIndex == 0xFF ? "" : rvb_curves_s[alias->reverbSendCurveIndex]);
			writer.write_column(alias->startDelay);
			writer.write_column(alias->speakerMapIndex == 0xFF ? "" : speaker_maps_s[alias->speakerMapIndex]);
			writer.write_column(FULLDRYLEVEL[alias->flags.reverb]);
			writer.write_column(alias->reverbMultiplier);
			writer.write_column(alias->farReverbMultiplier);
			writer.write_column(alias->lfePercentage);
			writer.write_column(alias->centerPercentage);
			writer.write_column(alias->envelopMin);
			writer.write_column(alias->envelopMax);
			writer.write_column(alias->envelopPercentage);
			writer.write_column(SHAPES[alias->flags.shape]);
			writer.write_column(FALSE_TRUE[alias->flags.ignoreDistanceCheck]);
			writer.write_column(alias->occlusionShapeIndex == 0xFF ? "" : occlusion_shapes_s[alias->occlusionShapeIndex]);
			writer.write_column(alias->dopplerPresetIndex == 0xFF ? "" : doppler_presets_s[alias->dopplerPresetIndex]);
			writer.write_column(alias->smartPanDistance2d);
			writer.write_column(alias->smartPanDistance3d);
			writer.write_column(alias->smartPanAttenuation2d);
			writer.write_column(alias->stereoSpreadMinDist);
			writer.write_column(alias->stereoSpreadMaxDist);
			writer.write_column(alias->stereoSpreadMidPoint);
			writer.write_column(alias->stereoSpreadMaxAngle);
			writer.write_column(get_hashed_string(alias->contextType));
			writer.write_column(get_hashed_string(alias->contextValue));
			writer.write_column(FALSE_TRUE[alias->flags.precached]);
			writer.write_column(duck_hash_lookup(asset, alias->duck));
			writer.write_column(MUSIC_CONTENT[alias->flags.MusicContent]);
			writer.write_column(GPAD_OUTPUT[alias->flags.GPadOutput]);
			writer.write_column(FALSE_TRUE[alias->flags.ForceSubtitle]);
			writer.write_column(alias->masterPriority);
			writer.write_column(alias->masterPercentage);
			writer.write_column(alias->slavePercentage);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->aliasCount; i++)
			{
				auto* alias_list = &asset->alias[i];

				for (auto j = 0; j < alias_list->count; j++)
				{
					write_alias(asset, &alias_list->head[j], writer);
				}
			}

			writer.save(get_path(asset));
		}

		void parse_file(SndBank* asset, const std::string& path, std::vector<SndAlias*>& aliases, std::set<std::string>& ducks, zone_memory* mem)
		{
			ZONETOOL_INFO("Parsing sound alias csv \"%s\"...", path.data());

			const auto parse_path = filesystem::get_file_path(path) + path;
			csv::parser parser(parse_path);

			const auto row_count = parser.get_num_rows();
			if (row_count <= 1) return; // has at least one entry

			const auto max_fields = parser.get_max_columns();
			if (max_fields != std::extent_v<decltype(SND_ALIAS_FIELDS)>)
			{
				ZONETOOL_ERROR("Failed to parse file %s, csv doesn't have correct field count.", path.data());
				return;
			}

			const auto rows = parser.get_rows();

			for (auto i = 1; i < row_count; i++)
			{
				if (rows[i]->num_fields != max_fields)
				{
					ZONETOOL_ERROR("Tried to parse invalid line %u in csv file %s", i, path.data());
					continue;
				}

				SndAlias* alias = mem->allocate<SndAlias>();

				auto field_idx = 0;
				const auto get = [&]()
				{
					return rows[i]->fields[field_idx++];
				};

				const auto get_string = [&]() -> const char*
				{
					auto str = get();
					if (*str)
					{
						return mem->duplicate_string(str);
					}
					return nullptr;
				};

				alias->aliasName = get_string();
				alias->id = snd_hash_name(alias->aliasName);

				if (!alias->aliasName || !*alias->aliasName)
				{
					ZONETOOL_WARNING("Parsed an empty alias name on line %d for file %s", i, path.data());
				}

				ZONETOOL_INFO("Parsing sound \"%s\"...", alias->aliasName);

				alias->secondaryAliasName = get_string();
				alias->secondaryId = snd_hash_name(alias->secondaryAliasName);

				alias->stopAliasName = get_string();
				alias->stopAliasID = snd_hash_name(alias->stopAliasName);

				alias->subtitle = get_string();

				alias->assetFileName = get_string();
				alias->assetId = snd_hash_name(alias->assetFileName);

				alias->sequence = 0;

				alias->volMin = get_value<float>(get());
				alias->volMax = get_value<float>(get());
				alias->volModIndex = get_value_index<int>(get(), VOLMODS, std::extent_v<decltype(VOLMODS)>);
				alias->pitchMin = get_value<float>(get());
				alias->pitchMax = get_value<float>(get());
				alias->donutFadeEnd = get_value<float>(get());
				alias->distMin = get_value<float>(get());
				alias->distMax = get_value<float>(get());
				alias->velocityMin = get_value<float>(get());
				alias->flags.channel = get_value_index<unsigned int>(get(), ENTCHANNELS, std::extent_v<decltype(ENTCHANNELS)>);
				alias->flags.type = get_value_index<unsigned int>(get(), LOAD_TYPES, std::extent_v<decltype(LOAD_TYPES)>);
				alias->flags.looping = get_value_index<unsigned int>(get(), LOOP_TYPES, std::extent_v<decltype(LOOP_TYPES)>);
				alias->probability = get_value<float>(get());
				alias->volumeFalloffCurveIndex = get_value_index<unsigned char>(get(), vf_curves_s, std::extent_v<decltype(vf_curves_s)>, 0xFF);
				alias->lpfCurveIndex = get_value_index<unsigned char>(get(), lpf_curves_s, std::extent_v<decltype(lpf_curves_s)>, 0xFF);
				alias->hpfCurveIndex = get_value_index<unsigned char>(get(), hpf_curves_s, std::extent_v<decltype(hpf_curves_s)>, 0xFF);
				alias->reverbSendCurveIndex = get_value_index<unsigned char>(get(), rvb_curves_s, std::extent_v<decltype(rvb_curves_s)>, 0xFF);
				alias->startDelay = get_value<int>(get());
				alias->speakerMapIndex = get_value_index<unsigned char>(get(), speaker_maps_s, std::extent_v<decltype(speaker_maps_s)>, 0xFF);
				alias->flags.reverb = get_value_index<unsigned int>(get(), FULLDRYLEVEL, std::extent_v<decltype(FULLDRYLEVEL)>);
				alias->reverbMultiplier = get_value<float>(get());
				alias->farReverbMultiplier = get_value<float>(get());
				alias->lfePercentage = get_value<float>(get());
				alias->centerPercentage = get_value<float>(get());
				alias->envelopMin = get_value<float>(get());
				alias->envelopMax = get_value<float>(get());
				alias->envelopPercentage = get_value<float>(get());
				alias->flags.shape = get_value_index<unsigned int>(get(), SHAPES, std::extent_v<decltype(SHAPES)>);
				alias->flags.ignoreDistanceCheck = get_value_index<unsigned int>(get(), FALSE_TRUE, std::extent_v<decltype(FALSE_TRUE)>);
				alias->occlusionShapeIndex = get_value_index<unsigned char>(get(), occlusion_shapes_s, std::extent_v<decltype(occlusion_shapes_s)>, 0xFF);
				alias->dopplerPresetIndex = get_value_index<unsigned char>(get(), doppler_presets_s, std::extent_v<decltype(doppler_presets_s)>, 0xFF);
				alias->smartPanDistance2d = get_value<float>(get());
				alias->smartPanDistance3d = get_value<float>(get());
				alias->smartPanAttenuation2d = get_value<float>(get());
				alias->stereoSpreadMinDist = get_value<float>(get());
				alias->stereoSpreadMaxDist = get_value<float>(get());
				alias->stereoSpreadMidPoint = get_value<float>(get());
				alias->stereoSpreadMaxAngle = get_value<int>(get());
				alias->contextType = snd_hash_name(get());
				alias->contextValue = snd_hash_name(get());
				alias->flags.precached = get_value_index<unsigned int>(get(), FALSE_TRUE, std::extent_v<decltype(FALSE_TRUE)>);

				auto duck = get_string();
				if (duck)
				{
					ducks.insert(duck);
					alias->duck = snd_hash_name(duck);
				}

				alias->flags.MusicContent = get_value_index<unsigned int>(get(), MUSIC_CONTENT, std::extent_v<decltype(MUSIC_CONTENT)>);
				alias->flags.GPadOutput = get_value_index<unsigned int>(get(), GPAD_OUTPUT, std::extent_v<decltype(GPAD_OUTPUT)>);
				alias->flags.ForceSubtitle = get_value_index<unsigned int>(get(), FALSE_TRUE, std::extent_v<decltype(FALSE_TRUE)>);
				alias->masterPriority = get_value<int>(get());
				alias->masterPercentage = get_value<float>(get());
				alias->slavePercentage = get_value<float>(get());

				aliases.push_back(alias);
			}
		}

		void parse(SndBank* asset, zone_memory* mem, ordered_json& paths)
		{
			if (!paths.is_array() || !paths.size()) return;

			std::vector<SndAlias*> aliases;
			std::set<std::string> ducks;

			for (size_t i = 0; i < paths.size(); i++)
			{
				const auto path = paths[i].get<std::string>();

				if (!filesystem::file(path).exists())
				{
					ZONETOOL_ERROR("Could not find file %s", path.data());
					continue;
				}

				parse_file(asset, path, aliases, ducks, mem);
			}

			// add ducks
			asset->duckCount = static_cast<unsigned int>(ducks.size()); // since ducks is a std::set it will have no duplicates
			asset->ducks = mem->allocate<SndDuck>(asset->duckCount);
			unsigned int duck_index = 0;
			for (auto& duck : ducks)
			{
				ducks::parse_duck(duck, mem, &asset->ducks[duck_index++]);
			}
			ducks.clear();

			// create temp alias list
			std::vector<SndAliasList> alias_list;
			alias_list.reserve(aliases.size());
			for (size_t i = 0; i < aliases.size(); i++)
			{
				SndAliasList list{};
				unsigned int alias_count = 1;
				list.aliasName = mem->duplicate_string(aliases[i]->aliasName);
				list.id = snd_hash_name(list.aliasName);
				list.head = aliases[i];
				while (i + 1 < aliases.size())
				{
					if (!strcmp(aliases[i]->aliasName, aliases[i + 1]->aliasName))
					{
						alias_count++;
						i++;
					}
					else
						break;
				}
				list.count = alias_count;
				list.sequence = 0;

				alias_list.push_back(list);
			}
			aliases.clear();

			if (alias_list.size() >= std::numeric_limits<unsigned short>::max())
			{
				ZONETOOL_FATAL("Zone has too many sound aliases! %d/%d", static_cast<unsigned int>(alias_list.size()), std::numeric_limits<unsigned short>::max() - 1);
			}

			// create final alias list
			asset->aliasCount = static_cast<unsigned int>(alias_list.size());
			asset->alias = mem->allocate<SndAliasList>(asset->aliasCount);
			for (auto i = 0u; i < asset->aliasCount; i++)
			{
				memcpy(asset->alias, &alias_list[i], sizeof(SndAliasList));
			}
			alias_list.clear();

			// create alias index list
			asset->aliasIndex = mem->allocate<SndIndexEntry>(asset->aliasCount);
			memset(asset->aliasIndex, 0xFF, sizeof(SndIndexEntry) * asset->aliasCount);

			const auto setAliasIndexList = std::make_unique<bool[]>(asset->aliasCount);

			for (unsigned short i = 0; i < asset->aliasCount; i++)
			{
				const auto idx = asset->alias[i].id % asset->aliasCount;
				if (asset->aliasIndex[idx].value == std::numeric_limits<unsigned short>::max())
				{
					asset->aliasIndex[idx].value = i;
					asset->aliasIndex[idx].next = std::numeric_limits<unsigned short>::max();
					setAliasIndexList[i] = true;
				}
			}

			for (unsigned short i = 0u; i < asset->aliasCount; i++)
			{
				if (setAliasIndexList[i])
					continue;

				unsigned short idx = static_cast<unsigned short>(asset->alias[i].id % asset->aliasCount);
				while (asset->aliasIndex[idx].next != std::numeric_limits<unsigned short>::max())
				{
					idx = asset->aliasIndex[idx].next;
				}

				unsigned short offset = 1u;
				auto freeIdx = std::numeric_limits<unsigned short>::max();
				while (true)
				{
					freeIdx = (idx + offset) % asset->aliasCount;
					if (asset->aliasIndex[freeIdx].value == std::numeric_limits<unsigned short>::max())
						break;

					freeIdx = (idx + static_cast<unsigned short>(asset->aliasCount) - offset) % static_cast<unsigned short>(asset->aliasCount);
					if (asset->aliasIndex[freeIdx].value == std::numeric_limits<unsigned short>::max())
						break;

					offset++;
					freeIdx = std::numeric_limits<unsigned short>::max();

					if (offset >= asset->aliasCount)
						break;
				}

				if (freeIdx == std::numeric_limits<unsigned short>::max())
				{
					ZONETOOL_FATAL("Unable to allocate sound bank alias index list");
				}

				asset->aliasIndex[idx].next = freeIdx;
				asset->aliasIndex[freeIdx].value = i;
				asset->aliasIndex[freeIdx].next = std::numeric_limits<unsigned short>::max();
				setAliasIndexList[i] = true;
			}
		}
	}

	namespace send_effect_params
	{
		std::string SND_SENDEFFECT_FIELDS[] =
		{
			"name",
			"smoothing",
			"earlyTime",
			"lateTime",
			"earlyGain",
			"lateGain",
			"lateGainProx",
			"returnGain",
			"earlyLpf",
			"lateLpf",
			"inputLpf",
			"dampLpf",
			"wallReflect",
			"dryGain",
			"earlySize",
			"lateSize",
			"diffusion",
			"rearLevel",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".sendEffectParams.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_SENDEFFECT_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(SndSendEffectParams* asset, csv_writer& writer)
		{
			writer.write_column(reinterpret_cast<const char*>(asset->name));
			writer.write_column(asset->smoothing);
			writer.write_column(asset->earlyTime);
			writer.write_column(asset->lateTime);
			writer.write_column(asset->earlyGain);
			writer.write_column(asset->lateGain);
			writer.write_column(asset->lateGainProx);
			writer.write_column(asset->returnGain);
			writer.write_column(asset->earlyLpf);
			writer.write_column(asset->lateLpf);
			writer.write_column(asset->inputLpf);
			writer.write_column(asset->dampLpf);
			writer.write_column(asset->wallReflect);
			writer.write_column(asset->dryGain);
			writer.write_column(asset->earlySize);
			writer.write_column(asset->lateSize);
			writer.write_column(asset->diffusion);
			writer.write_column(asset->rearLevel);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->sendEffectCount; i++)
			{
				write(&asset->sendEffects[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace adsr_settings
	{
		std::string SND_TAB_ADSR_FIELDS[] =
		{
			"ADSR_Name",
			"Att_Len",
			"Att_Curve",
			"Dec_Len",
			"Dec_Curve",
			"Rel_Len",
			"Rel_Curve",
			"Sus_Len",
			"Sus_Level",
		};

		std::string ADSRCURVES[] =
		{
			"linear",
			"log_fast",
			"log_slow",
			"flat_ended",
			"flat_middle",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".adsr.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_ADSR_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(ADSRSetting* asset, csv_writer& writer)
		{
			writer.write_column(asset->name);
			writer.write_column(asset->attackLength);
			writer.write_column(ADSRCURVES[asset->attackCurve]);
			writer.write_column(asset->decayLength);
			writer.write_column(ADSRCURVES[asset->decayCurve]);
			writer.write_column(asset->releaseLength);
			writer.write_column(ADSRCURVES[asset->releaseCurve]);
			writer.write_column(asset->sustainLevel);
			writer.write_column(asset->sustainLength);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.adsrCount; i++)
			{
				write(&asset->soundTable.adsrSettings[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace ambient_def
	{
		std::string SND_TAB_AMB_DEF_FIELDS[] =
		{
			"ambient_name",
			"Time_Min",
			"Time_Max",
			"EventIndex",
			"NumEvents",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".ambient.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_AMB_DEF_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(AmbientDef* asset, csv_writer& writer)
		{
			writer.write_column(asset->name);
			writer.write_column(asset->timeMin);
			writer.write_column(asset->timeMax);
			writer.write_column(asset->ambientEventIndex);
			writer.write_column(asset->numEvents);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.ambientDefCount; i++)
			{
				write(&asset->soundTable.ambientDefs[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace ambient_event
	{
		std::string SND_TAB_AMB_EVT_FIELDS[] =
		{
			"idString",
			"Weight",
			"ElementIndex",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".ambientEvent.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_AMB_EVT_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(AmbientEvent* asset, csv_writer& writer)
		{
			writer.write_column(asset->id);
			writer.write_column(asset->weight);
			writer.write_column(asset->ambientElementIndex);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.ambientEventCount; i++)
			{
				write(&asset->soundTable.ambientEvents[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace ambient_elem
	{
		std::string SND_TAB_AMB_ELEM_FIELDS[] =
		{
			"ambient_element",
			"Range_Min",
			"Range_Max",
			"Cone_Min",
			"Cone_Max",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".ambientElement.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_AMB_ELEM_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(AmbientElement* asset, csv_writer& writer)
		{
			writer.write_column(asset->id);
			writer.write_column(asset->rangeMin);
			writer.write_column(asset->rangeMax);
			writer.write_column(asset->coneMin);
			writer.write_column(asset->coneMax);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.ambientElementsCount; i++)
			{
				write(&asset->soundTable.ambientElements[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace filter
	{
		std::string SND_TAB_FILTER_FIELDS[] =
		{
			"idString",
			"Channel",
			"Band",
			"Type",
			"Freq",
			"Gain",
			"Q",
		};

		std::string snd_eqTypeStrings[] =
		{
			"lowpass",
			"highpass",
			"lowshelf",
			"highshelf",
			"bell",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".filters.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_FILTER_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(FilterDef* asset, csv_writer& writer)
		{
			writer.write_column(asset->id);
			writer.write_column(ENTCHANNELS[asset->entChannelIdx]);
			writer.write_column(asset->band);
			writer.write_column(snd_eqTypeStrings[asset->type]);
			writer.write_column(asset->freq);
			writer.write_column(asset->gain);
			writer.write_column(asset->q);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.filterCount; i++)
			{
				write(&asset->soundTable.filters[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace mix
	{
		std::string SND_TAB_MIX_FIELDS[] =
		{
			"idString",
			"VolMod",
			"Volume",
			"Fade",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".mixes.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_MIX_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(MixDef* asset, csv_writer& writer)
		{
			writer.write_column(asset->id);
			writer.write_column(VOLMODS[asset->volModIndex]);
			writer.write_column(asset->volume);
			writer.write_column(asset->fade);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.mixCount; i++)
			{
				write(&asset->soundTable.mixes[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace adsr_zone
	{
		std::string lookup_hash_string(SndBank* bank, std::uint32_t hash)
		{
			for (auto i = 0u; i < bank->soundTable.zoneCount; i++)
			{
				if (snd_hash_name(bank->soundTable.zones[i].npcAdsrName) == hash)
				{
					return bank->soundTable.zones[i].npcAdsrName;
				}
				else if (snd_hash_name(bank->soundTable.zones[i].plrAdsrName) == hash)
				{
					return bank->soundTable.zones[i].plrAdsrName;
				}
			}
			return "";
		}

		void write(SndBank* bank, AdsrZoneEntry* asset, csv_writer& writer)
		{
			writer.write_column(lookup_hash_string(bank, asset->id));
			writer.write_column(asset->id);
			writer.write_column(asset->adsrIdx);
			writer.write_column(asset->weaponName ? asset->weaponName : "");
			writer.write_column(asset->weaponIdx);

			writer.increase_line();
		}

		namespace npc
		{
			std::string SND_TAB_ADSR_ZONE_NPC_FIELDS[] =
			{
				"Adsr_Zone_NPC",
				"idString",
				"ADSRIndex",
				"Weapon",
				"WeaponIdx",
			};

			std::string get_path(SndBank* asset)
			{
				return sound_path + asset->name + ".adsrZoneNPC.csv";
			}

			void write_header(csv_writer& writer)
			{
				for (const auto& field : SND_TAB_ADSR_ZONE_NPC_FIELDS)
				{
					writer.write_column(field);
				}
				writer.increase_line();
			}

			void dump(SndBank* asset)
			{
				csv_writer writer{};

				write_header(writer);

				for (auto i = 0u; i < asset->soundTable.npcADSRZoneCount; i++)
				{
					write(asset, &asset->soundTable.npcADSRZones[i], writer);
				}

				writer.save(get_path(asset));
			}
		}

		namespace plr
		{
			std::string SND_TAB_ADSR_ZONE_PLR_FIELDS[] =
			{
				"Adsr_Zone_Player",
				"idString",
				"ADSRIndex",
				"Weapon",
				"WeaponIdx",
			};

			std::string get_path(SndBank* asset)
			{
				return sound_path + asset->name + ".adsrZonePlayer.csv";
			}

			void write_header(csv_writer& writer)
			{
				for (const auto& field : SND_TAB_ADSR_ZONE_PLR_FIELDS)
				{
					writer.write_column(field);
				}
				writer.increase_line();
			}

			void dump(SndBank* asset)
			{
				csv_writer writer{};

				write_header(writer);

				for (auto i = 0u; i < asset->soundTable.playerADSRZoneCount; i++)
				{
					write(asset, &asset->soundTable.playerADSRZones[i], writer);
				}

				writer.save(get_path(asset));
			}
		}
	}

	namespace occlude_def
	{
		std::string SND_TAB_OCCL_FIELDS[] =
		{
			"idString",
			"Channel",
			"CutoffLevel1",
			"CutoffLevel2",
			"CutoffLevel3",
			"CutoffLevel4",
			"DbLevel1",
			"DbLevel2",
			"DbLevel3",
			"DbLevel4",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".occlusionFilters.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_OCCL_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(OccludeDef* asset, csv_writer& writer)
		{
			writer.write_column(asset->id);
			writer.write_column(ENTCHANNELS[asset->entChannelIdx]);
			writer.write_column(asset->cutoffLevel1);
			writer.write_column(asset->cutoffLevel2);
			writer.write_column(asset->cutoffLevel3);
			writer.write_column(asset->cutoffLevel4);
			writer.write_column(asset->attnLevel1);
			writer.write_column(asset->attnLevel2);
			writer.write_column(asset->attnLevel3);
			writer.write_column(asset->attnLevel4);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.occlusionFilterCount; i++)
			{
				write(&asset->soundTable.occlusionFilters[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace reverb_def
	{
		std::string SND_TAB_REVERB_FIELDS[] =
		{
			"reverb_name",
			"idString",
			"Roomtype",
			"DryLevel",
			"WetLevel",
			"Fade",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".reverbs.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_REVERB_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		std::string lookup_hash_string(SndBank* bank, std::uint32_t hash)
		{
			for (auto i = 0u; i < bank->soundTable.zoneCount; i++)
			{
				if (snd_hash_name(bank->soundTable.zones[i].reverbName) == hash)
				{
					return bank->soundTable.zones[i].reverbName;
				}
			}
			return "";
		}

		void write(SndBank* bank, ReverbDef* asset, csv_writer& writer)
		{
			writer.write_column(lookup_hash_string(bank, asset->id));
			writer.write_column(asset->id);
			writer.write_column(std::string(asset->roomType));
			writer.write_column(asset->dryLevel);
			writer.write_column(asset->wetLevel);
			writer.write_column(asset->fadeTime);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.reverbCount; i++)
			{
				write(asset, &asset->soundTable.reverbs[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace timescale
	{
		std::string SND_TAB_TIMESCALE_FIELDS[] =
		{
			"idString",
			"Timescale_Name",
			"Channel",
			"Scale",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".timescales.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_TIMESCALE_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(TimescaleEntry* asset, csv_writer& writer)
		{
			writer.write_column(asset->id);
			writer.write_column(asset->presetName);
			writer.write_column(ENTCHANNELS[asset->entChannelIdx]);
			writer.write_column(asset->scale);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.timeScaleSettingCount; i++)
			{
				write(&asset->soundTable.timeScaleSettings[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace zone
	{
		std::string SND_TAB_ZONE_FIELDS[] =
		{
			"ReverbIndex",
			"OcclusionIndex",
			"NumOcclusion",
			"FilterIndex",
			"NumFilter",
			"MixIndex",
			"NumMix",
			"PlrADSRZoneIndex",
			"NumPlrADSRZone",
			"NPCADSRZoneIndex",
			"NumNPCADSRZone",
			"AmbientIndex",
			"UnkIndex",
			"DisableFullOccIndex",
			"NumDisableFullOcc",
			"PlayerBreathStateIndex",
			"NumPlayerBreathStates",
			"Weapon_Reflection",
			//"Exterior",
			"EntityContextType1",
			"EntityContextValue1",
			"EntityContextType2",
			"EntityContextValue2",
			"EntityContextType3",
			"EntityContextValue3",
			"EntityContextType4",
			"EntityContextValue4",
			//"Duck",
			"Zone_Name",
			"State",
			"Ambience",
			"Ambient_Name",
			"Mix",
			"Reverb",
			"Filter",
			"Occlusion",
			"Player_Adsr",
			"NPC_Adsr",
			"Weapon_Reflection",
			"Disable_Full_Occ",
			"PlayerBreathState",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".zone.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_ZONE_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(ZoneDef* asset, csv_writer& writer)
		{
			writer.write_column(asset->reverbIndex);
			writer.write_column(asset->startOcclusionIndex);
			writer.write_column(asset->numOcclusion);
			writer.write_column(asset->startFilterIndex);
			writer.write_column(asset->numFilter);
			writer.write_column(asset->startMixIndex);
			writer.write_column(asset->numMix);
			writer.write_column(asset->startAdsrZoneIndex);
			writer.write_column(asset->numAdsrZone);
			writer.write_column(asset->startNPCAdsrZoneIndex);
			writer.write_column(asset->numNPCAdsrZone);
			writer.write_column(asset->ambientDefIndex);
			writer.write_column(asset->unkIndex);
			writer.write_column(asset->startFullOccIndex);
			writer.write_column(asset->numDisableFullOcc);
			writer.write_column(asset->startPlayerBreathStateIndex);
			writer.write_column(asset->numPlayerBreathStates);
			writer.write_column(asset->weapReflId);
			// exterior
			writer.write_column(asset->contextType1);
			writer.write_column(asset->contextValue1);
			writer.write_column(asset->contextType2);
			writer.write_column(asset->contextValue2);
			writer.write_column(asset->contextType3);
			writer.write_column(asset->contextValue3);
			writer.write_column(asset->contextType4);
			writer.write_column(asset->contextValue4);
			//duck
			writer.write_column(asset->zoneName ? asset->zoneName : "");
			writer.write_column(asset->stateName ? asset->stateName : "");
			writer.write_column(asset->ambientStream ? asset->ambientStream : "");
			writer.write_column(asset->ambientName ? asset->ambientName : "");
			writer.write_column(asset->mixName ? asset->mixName : "");
			writer.write_column(asset->reverbName ? asset->reverbName : "");
			writer.write_column(asset->filterName ? asset->filterName : "");
			writer.write_column(asset->occlusionName ? asset->occlusionName : "");
			writer.write_column(asset->plrAdsrName ? asset->plrAdsrName : "");
			writer.write_column(asset->npcAdsrName ? asset->npcAdsrName : "");
			writer.write_column(asset->weapReflName ? asset->weapReflName : "");
			writer.write_column(asset->fullOccName ? asset->fullOccName : "");
			writer.write_column(asset->playerBreathStateName ? asset->playerBreathStateName : "");

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.zoneCount; i++)
			{
				write(&asset->soundTable.zones[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace unk
	{
		std::string get_path(SndBank* asset)
		{
			return sound_path + "unk/"s + asset->name + ".json"s;
		}

		void dump(SndBank* asset)
		{
			auto file = filesystem::file(get_path(asset));
			file.open("wb");

			ordered_json data;

			for (auto i = 0u; i < asset->soundTable.unkCount; i++)
			{
				auto* unk = &asset->soundTable.unk[i];
				data[i]["id"] = unk->id;
				data[i]["name"] = unk->name;
				data[i]["unk3"] = unk->unk3;
				data[i]["unk4"] = unk->unk4;
				data[i]["unk5"] = unk->unk5;
				data[i]["unk6"] = unk->unk6;
				data[i]["unk7"] = unk->unk7;
				data[i]["unk8"] = unk->unk8;
				data[i]["unk9"] = unk->unk9;
				data[i]["unk10"] = unk->unk10;
				data[i]["unk11"] = unk->unk11;
				data[i]["unk12"] = unk->unk12;
			}

			file.write(data.dump(4));
			file.close();
		}
	}

	namespace full_occlusion_def
	{
		std::string SND_TAB_FULLOCC_FIELDS[] =
		{
			"idString",
			"PresetName",
			"Channel",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".fullOcclusions.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_FULLOCC_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(FullOcclusionDef* asset, csv_writer& writer)
		{
			writer.write_column(asset->id);
			writer.write_column(asset->presetName);
			writer.write_column(ENTCHANNELS[asset->entChannelIdx]);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.fullOcclusionDefCount; i++)
			{
				write(&asset->soundTable.fullOcclusionDefs[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace plr_breath_state
	{
		std::string SND_TAB_PLRBREATHSTATE_FIELDS[] =
		{
			"StateType",
			"InhaleAlias",
			"ExhaleAlias",
			"MinBreaths",
		};

		std::string get_path(SndBank* asset)
		{
			return sound_path + asset->name + ".playerBreathStates.csv";
		}

		void write_header(csv_writer& writer)
		{
			for (const auto& field : SND_TAB_PLRBREATHSTATE_FIELDS)
			{
				writer.write_column(field);
			}
			writer.increase_line();
		}

		void write(PlayerBreathStateDef* asset, csv_writer& writer)
		{
			writer.write_column(asset->stateType);
			writer.write_column(asset->inhaleAlias ? asset->inhaleAlias : "");
			writer.write_column(asset->exhaleAlias ? asset->exhaleAlias : "");
			writer.write_column(asset->minBreaths);

			writer.increase_line();
		}

		void dump(SndBank* asset)
		{
			csv_writer writer{};

			write_header(writer);

			for (auto i = 0u; i < asset->soundTable.plrBreathStateDefCount; i++)
			{
				write(&asset->soundTable.plrBreathStateDefs[i], writer);
			}

			writer.save(get_path(asset));
		}
	}

	namespace ducks
	{
		void dump_duck(SndDuck* asset)
		{
			const auto path = sound_path + "ducks/"s + asset->name + ".duk"s;
			auto file = filesystem::file(path);
			file.open("wb");

			ordered_json data;

			data["Name"] = asset->name;
			data["FadeIn"] = asset->fadeIn;
			data["FadeOut"] = asset->fadeOut;
			data["StartDelay"] = asset->startDelay;
			data["MinDistance"] = asset->minDistance;
			data["Distance"] = asset->distance;
			data["Length"] = asset->length;
			data["FadeInCurve"] = get_hashed_string(asset->fadeInCurve);
			data["FadeInCurveId"] = asset->fadeInCurve;
			data["FadeOutCurve"] = get_hashed_string(asset->fadeOutCurve);
			data["FadeOutCurveId"] = asset->fadeOutCurve;
			data["UpdateWhilePaused"] = asset->updateWhilePaused;
			data["TrackAmplitude"] = asset->trackAmplitude;
			data["DisableInSplitscreen"] = asset->disableInSplitscreen;
			data["DuckAliasAttenuation"] = asset->aliasAttenuation;
			data["DuckAliasLpf"] = asset->aliasLpf;
			data["DuckAlias"] = asset->duckAlias;
			data["Attenuation"] = {};
			if (asset->attenuation)
			{
				for (auto i = 0; i < 128; i++)
				{
					data["Attenuation"][i] = asset->attenuation[i];
				}
			}
			data["Lpf"] = {};
			if (asset->lpf)
			{
				for (auto i = 0; i < 128; i++)
				{
					data["Lpf"][i] = asset->lpf[i];
				}
			}

			file.write(data.dump(4));
			file.close();
		}

		void dump(SndBank* asset)
		{
			for (auto i = 0u; i < asset->duckCount; i++)
			{
				dump_duck(&asset->ducks[i]);
			}
		}

		bool parse_duck(const std::string& name, zone_memory* mem, SndDuck* asset)
		{
			const auto path = sound_path + "ducks/"s + name + ".duk"s;

			auto file = filesystem::file(path);
			if (!file.exists())
			{
				ZONETOOL_FATAL("Could not find sound duck file %s", path.data());
				return false;
			}

			ZONETOOL_INFO("Parsing duck \"%s\"...", name.data());

			// parse json file
			file.open("rb");
			ordered_json data = json::parse(file.read_bytes(file.size()));
			file.close();

			{
				auto name_str = get_json_value<std::string>(data["Name"]);
				memcpy_s(asset->name, sizeof(asset->name), name_str.data(), name_str.size());
				asset->id = snd_hash_name(asset->name);
			}
			asset->fadeIn = get_json_value<float>(data["FadeIn"]);
			asset->fadeOut = get_json_value<float>(data["FadeOut"]);
			asset->minDistance = get_json_value<float>(data["MinDistance"]);
			asset->distance = get_json_value<float>(data["Distance"]);
			asset->length = get_json_value<float>(data["Length"]);
			asset->fadeInCurve = get_json_value<std::uint32_t>(data["FadeInCurveId"]);
			{
				auto name_str = get_json_value<std::string>(data["FadeInCurve"]);
				if (!name_str.empty())
				{
					asset->fadeInCurve = snd_hash_name(name_str.data());
				}
			}
			asset->fadeOutCurve = get_json_value<std::uint32_t>(data["FadeOutCurveId"]);
			{
				auto name_str = get_json_value<std::string>(data["FadeOutCurve"]);
				if (!name_str.empty())
				{
					asset->fadeOutCurve = snd_hash_name(name_str.data());
				}
			}
			asset->updateWhilePaused = get_json_value<bool>(data["UpdateWhilePaused"]);
			asset->trackAmplitude = get_json_value<bool>(data["TrackAmplitude"]);
			asset->disableInSplitscreen = get_json_value<bool>(data["DisableInSplitscreen"]);
			asset->aliasAttenuation = get_json_value<float>(data["DuckAliasAttenuation"]);
			asset->aliasLpf = get_json_value<float>(data["DuckAliasLpf"]);
			asset->duckAlias = get_json_value<std::uint32_t>(data["DuckAlias"]);
			if (data["Attenuation"].is_array())
			{
				asset->attenuation = mem->allocate<float>(128);
				for (auto i = 0; i < 128; i++)
				{
					asset->attenuation[i] = get_json_value<float>(data["Attenuation"][i]);
				}
			}
			if (data["Lpf"].is_array())
			{
				asset->lpf = mem->allocate<float>(128);
				for (auto i = 0; i < 128; i++)
				{
					asset->lpf[i] = get_json_value<float>(data["Lpf"][i]);
				}
			}

			return true;
		}
	}

	namespace music
	{

	}

	namespace sound_asset_bank
	{
		constexpr unsigned int magic = 0x23585532;
		constexpr unsigned int version = 4;

		namespace flac
		{
			enum MetaDataBlockType : unsigned
			{
				STREAMINFO = 0,
				PADDING = 1,
				APPLICATION = 2,
				SEEKTABLE = 3,
				VORBIS_COMMENT = 4,
				CUESHEET = 5,
				PICTURE = 6
			};

			struct MetaDataBlockHeader
			{
				unsigned int isLastMetaDataBlock : 1;
				unsigned int blockType : 7;
				unsigned int blockLength : 24;
			};

#pragma pack(1)
			/*struct StreamInfo
			{
				uint16_t m_minimum_block_size : 16; // 0 
				uint16_t m_maximum_block_size : 16; // 16
				uint32_t m_minimum_frame_size : 24; // 32
				uint32_t m_maximum_frame_size : 24; // 56
				uint32_t m_sample_rate : 20; // 80
				uint8_t m_number_of_channels : 3; // 100
				uint8_t m_bits_per_sample : 5; // 103
				uint64_t m_total_samples : 36; // 108
				uint8_t m_md5_signature[16]; // 109?
			};*/
#pragma pack()

			void dump(SndAssetBankEntry entry, const std::string& name, uint8_t* data, size_t size)
			{
				std::string buffer{};

				// if someone can figure out how to generate this shit go ahead
				constexpr uint8_t header[] = { 
					// Signature
					0x66,0x4C,0x61,0x43,
					// MetadataBlockHeader
					0x0,0x0,0x0,0x22,
					// StreamInfo
					// min block size
					0x4,0x0,
					// max block size
					0x4,0x0,
					// bitfield bullshit
					0x0,0x1,0xB7,0x0,0x7,0x8F,0xA,0xC4,0x40,0xF0,0x0,0x0,0x26,0x84,
					// md5
					0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
					// idk
					0x83,0x0,0x0,0x0, };

				buffer.append(reinterpret_cast<const char*>(header), sizeof(header));

				buffer.append(reinterpret_cast<const char*>(data), size);

				const auto path = sound_path_assets + name + ".flac"s;
				auto file = filesystem::file(path);
				file.open("wb");
				file.write(buffer.data(), buffer.size());
				file.close();
			}
		}

		bool use_zone_dir()
		{
			bool use_zone = false;
			if (utils::io::directory_exists("zone")) use_zone = true;
			return use_zone;
		}

		bool validate_header(SndAssetBankHeader* header)
		{
			if (header->magic != magic)
			{
				ZONETOOL_ERROR("Sound Asset Bank has wrong header MAGIC");
				return false;
			}
			if (header->version != version)
			{
				ZONETOOL_ERROR("Sound Asset Bank has wrong header VERSION");
				return false;
			}

			return true;
		}

		void dump_pcm(const std::string& name, uint8_t* data, size_t size)
		{

		}

		bool dump_internal(std::string name, std::string language_folder)
		{
			std::string path;
			if (use_zone_dir())
			{
				path.append("zone/");
			}
			path.append(language_folder);
			path.append(name);

			auto file = filesystem::file(path);
			file.open("rb", false, false);
			if (!file.get_fp())
			{
				ZONETOOL_ERROR("Could not open file for read: %s", path.data());
				return false;
			}

			SndAssetBankHeader header{};
			file.read(&header, sizeof(SndAssetBankHeader));

			if (!validate_header(&header))
			{
				return false;
			}

			for (auto i = 0u; i < header.entryCount; i++)
			{
				SndAssetBankEntry entry{};
				file.seek(header.entryOffset + (sizeof(SndAssetBankEntry) * i), SEEK_SET);
				file.read(&entry, sizeof(SndAssetBankEntry));

				char asset_name[128]{};
				memset(asset_name, 0, sizeof(asset_name));
				file.seek(header.AssetNameOffset + (sizeof(asset_name) * i), SEEK_SET);
				file.read(asset_name, sizeof(asset_name));

				file.seek(entry.offset, SEEK_SET);
				auto data = file.read_bytes(entry.size);

				switch(entry.format)
				{
				case SND_ASSET_FORMAT_FLAC:
					flac::dump(entry, asset_name, data.data(), data.size());
					break;
				default:
					__debugbreak();
				}
			}

			return true;
		}

		namespace loaded
		{
			void dump(std::string name, std::string language_folder = "")
			{
				if (!name.ends_with(".sabl")) name.append(".sabl");

				dump_internal(name, language_folder);
			}
		}

		namespace streamed
		{
			void dump(std::string name, std::string language_folder = "")
			{
				if (!name.ends_with(".sabs")) name.append(".sabs");

				dump_internal(name, language_folder);
			}
		}

		void dump(const std::string& name)
		{
			loaded::dump(name);
			streamed::dump(name);
		}
	}

	SndBank* sound_bank::parse(const std::string& name, zone_memory* mem)
	{
		const auto path = "soundbank\\"s + name + ".json"s;

		auto file = filesystem::file(path);
		if (!file.exists())
		{
			return nullptr;
		}

		ZONETOOL_INFO("Parsing soundbank \"%s\"...", name.data());

		// parse json file
		file.open("rb");
		ordered_json data = json::parse(file.read_bytes(file.size()));
		file.close();

		auto asset = mem->allocate<SndBank>();

		asset->name = mem->duplicate_string(get_json_value<std::string>(data["name"]));
		asset->zone = mem->duplicate_string(get_json_value<std::string>(data["zone"]));
		asset->gameLanguage = mem->duplicate_string(get_json_value<std::string>(data["gameLanguage"]));
		asset->soundLanguage = mem->duplicate_string(get_json_value<std::string>(data["soundLanguage"]));

		aliases::parse(asset, mem, data["aliases"]);

		// send_effect_params

		// adsr_settings

		// ambient_def

		// ambient_event

		// ambient_elem

		// filter

		// mix

		// adsr_zone::npc

		// adsr_zone::plr

		// occlude_def

		// reverb_def

		// timescale

		// zone

		// unk

		// full_occlusion_def

		// plr_breath_state

		// ducks are parsed from alias list

		return asset;
	}

	void sound_bank::init(const std::string& name, zone_memory* mem)
	{
		this->name_ = name;

		if (this->referenced())
		{
			this->asset_ = mem->allocate<typename std::remove_reference<decltype(*this->asset_)>::type>();
			this->asset_->name = mem->duplicate_string(name);
			return;
		}

		this->asset_ = parse(name, mem);
		if (!this->asset_)
		{
			this->asset_ = db_find_x_asset_header_safe(XAssetType(this->type()), this->name_.data()).soundBank;
		}
	}

	void sound_bank::prepare(zone_buffer* buf, zone_memory* mem)
	{
	}

	void sound_bank::load_depending(zone_base* zone)
	{
	}

	std::string sound_bank::name()
	{
		return this->name_;
	}

	std::int32_t sound_bank::type()
	{
		return ASSET_TYPE_SOUND_BANK;
	}

	void sound_bank::write(zone_base* zone, zone_buffer* buf)
	{
		auto* data = this->asset_;
		auto* dest = buf->write(data);

		buf->push_stream(XFILE_BLOCK_VIRTUAL);

		dest->name = buf->write_str(this->name());

		if (data->zone)
		{
			dest->zone = buf->write_str(data->zone);
		}
		if (data->gameLanguage)
		{
			dest->gameLanguage = buf->write_str(data->gameLanguage);
		}
		if (data->soundLanguage)
		{
			dest->soundLanguage = buf->write_str(data->soundLanguage);
		}

		if (data->alias)
		{
			buf->align(7);
			dest->alias = buf->write(data->alias, data->aliasCount);
			for (auto i = 0u; i < data->aliasCount; i++)
			{
				if (data->alias[i].aliasName)
				{
					dest->alias[i].aliasName = buf->write_str(data->alias[i].aliasName);
				}
				if (data->alias[i].head)
				{
					buf->align(7);
					dest->alias[i].head = buf->write(data->alias[i].head, data->alias[i].count);
					for (auto j = 0; j < data->alias[i].count; j++)
					{
						if (data->alias[i].head[j].aliasName)
						{
							dest->alias[i].head[j].aliasName = buf->write_str(data->alias[i].head[j].aliasName);
						}
						if (data->alias[i].head[j].subtitle)
						{
							dest->alias[i].head[j].subtitle = buf->write_str(data->alias[i].head[j].subtitle);
						}
						if (data->alias[i].head[j].secondaryAliasName)
						{
							dest->alias[i].head[j].secondaryAliasName = buf->write_str(data->alias[i].head[j].secondaryAliasName);
						}
						if (data->alias[i].head[j].stopAliasName)
						{
							dest->alias[i].head[j].stopAliasName = buf->write_str(data->alias[i].head[j].stopAliasName);
						}
						if (data->alias[i].head[j].assetFileName)
						{
							dest->alias[i].head[j].assetFileName = buf->write_str(data->alias[i].head[j].assetFileName);
						}
					}
					buf->clear_pointer(&dest->alias[i].head);
				}
			}
			buf->clear_pointer(&dest->alias);
		}

		if (data->aliasIndex)
		{
			buf->align(7);
			buf->write(data->aliasIndex, data->aliasCount);
			buf->clear_pointer(&dest->aliasIndex);
		}

		if (data->sendEffects)
		{
			buf->align(3);
			buf->write(data->sendEffects, data->sendEffectCount);
			buf->clear_pointer(&dest->sendEffects);
		}

		if (data->soundTable.adsrSettings)
		{
			buf->align(7);
			dest->soundTable.adsrSettings = buf->write(data->soundTable.adsrSettings, data->soundTable.adsrCount);
			for (auto i = 0u; i < data->soundTable.adsrCount; i++)
			{
				if (data->soundTable.adsrSettings[i].name)
				{
					dest->soundTable.adsrSettings[i].name = buf->write_str(data->soundTable.adsrSettings[i].name);
				}
			}
			buf->clear_pointer(&dest->soundTable.adsrSettings);
		}

		if (data->soundTable.ambientDefs)
		{
			buf->align(7);
			dest->soundTable.ambientDefs = buf->write(data->soundTable.ambientDefs, data->soundTable.ambientDefCount);
			for (auto i = 0u; i < data->soundTable.ambientDefCount; i++)
			{
				if (data->soundTable.ambientDefs[i].name)
				{
					dest->soundTable.ambientDefs[i].name = buf->write_str(data->soundTable.ambientDefs[i].name);
				}
			}
			buf->clear_pointer(&dest->soundTable.ambientDefs);
		}

		if (data->soundTable.ambientEvents)
		{
			buf->align(3);
			buf->write(data->soundTable.ambientEvents, data->soundTable.ambientEventCount);
			buf->clear_pointer(&dest->soundTable.ambientEvents);
		}

		if (data->soundTable.ambientElements)
		{
			buf->align(7);
			dest->soundTable.ambientElements = buf->write(data->soundTable.ambientElements, data->soundTable.ambientElementsCount);
			for (auto i = 0u; i < data->soundTable.ambientElementsCount; i++)
			{
				if (data->soundTable.ambientElements[i].aliasName)
				{
					dest->soundTable.ambientElements[i].aliasName = buf->write_str(data->soundTable.ambientElements[i].aliasName);
				}
			}
			buf->clear_pointer(&dest->soundTable.ambientElements);
		}

		if (data->soundTable.filters)
		{
			buf->align(3);
			buf->write(data->soundTable.filters, data->soundTable.filterCount);
			buf->clear_pointer(&dest->soundTable.filters);
		}

		if (data->soundTable.mixes)
		{
			buf->align(3);
			buf->write(data->soundTable.mixes, data->soundTable.mixCount);
			buf->clear_pointer(&dest->soundTable.mixes);
		}

		if (data->soundTable.npcADSRZones)
		{
			buf->align(7);
			dest->soundTable.npcADSRZones = buf->write(data->soundTable.npcADSRZones, data->soundTable.npcADSRZoneCount);
			for (auto i = 0u; i < data->soundTable.npcADSRZoneCount; i++)
			{
				if (data->soundTable.npcADSRZones[i].name)
				{
					dest->soundTable.npcADSRZones[i].name = buf->write_str(data->soundTable.npcADSRZones[i].name);
				}
				if (data->soundTable.npcADSRZones[i].weaponName)
				{
					dest->soundTable.npcADSRZones[i].weaponName = buf->write_str(data->soundTable.npcADSRZones[i].weaponName);
				}
			}
			buf->clear_pointer(&dest->soundTable.npcADSRZones);
		}

		if (data->soundTable.occlusionFilters)
		{
			buf->align(3);
			buf->write(data->soundTable.occlusionFilters, data->soundTable.occlusionFilterCount);
			buf->clear_pointer(&dest->soundTable.occlusionFilters);
		}

		if (data->soundTable.playerADSRZones)
		{
			buf->align(7);
			dest->soundTable.playerADSRZones = buf->write(data->soundTable.playerADSRZones, data->soundTable.playerADSRZoneCount);
			for (auto i = 0u; i < data->soundTable.playerADSRZoneCount; i++)
			{
				if (data->soundTable.playerADSRZones[i].name)
				{
					dest->soundTable.playerADSRZones[i].name = buf->write_str(data->soundTable.playerADSRZones[i].name);
				}
				if (data->soundTable.playerADSRZones[i].weaponName)
				{
					dest->soundTable.playerADSRZones[i].weaponName = buf->write_str(data->soundTable.playerADSRZones[i].weaponName);
				}
			}
			buf->clear_pointer(&dest->soundTable.playerADSRZones);
		}

		if (data->soundTable.reverbs)
		{
			buf->align(3);
			buf->write(data->soundTable.reverbs, data->soundTable.reverbCount);
			buf->clear_pointer(&dest->soundTable.reverbs);
		}

		if (data->soundTable.timeScaleSettings)
		{
			buf->align(3);
			buf->write(data->soundTable.timeScaleSettings, data->soundTable.timeScaleSettingCount);
			buf->clear_pointer(&dest->soundTable.timeScaleSettings);
		}

		if (data->soundTable.zones)
		{
			buf->align(7);
			dest->soundTable.zones = buf->write(data->soundTable.zones, data->soundTable.zoneCount);
			for (auto i = 0u; i < data->soundTable.zoneCount; i++)
			{
				if (data->soundTable.zones[i].ambientStream)
				{
					dest->soundTable.zones[i].ambientStream = buf->write_str(data->soundTable.zones[i].ambientStream);
				}
				if (data->soundTable.zones[i].zoneName)
				{
					dest->soundTable.zones[i].zoneName = buf->write_str(data->soundTable.zones[i].zoneName);
				}
				if (data->soundTable.zones[i].stateName)
				{
					dest->soundTable.zones[i].stateName = buf->write_str(data->soundTable.zones[i].stateName);
				}
				if (data->soundTable.zones[i].ambientName)
				{
					dest->soundTable.zones[i].ambientName = buf->write_str(data->soundTable.zones[i].ambientName);
				}
				if (data->soundTable.zones[i].mixName)
				{
					dest->soundTable.zones[i].mixName = buf->write_str(data->soundTable.zones[i].mixName);
				}
				if (data->soundTable.zones[i].reverbName)
				{
					dest->soundTable.zones[i].reverbName = buf->write_str(data->soundTable.zones[i].reverbName);
				}
				if (data->soundTable.zones[i].filterName)
				{
					dest->soundTable.zones[i].filterName = buf->write_str(data->soundTable.zones[i].filterName);
				}
				if (data->soundTable.zones[i].occlusionName)
				{
					dest->soundTable.zones[i].occlusionName = buf->write_str(data->soundTable.zones[i].occlusionName);
				}
				if (data->soundTable.zones[i].plrAdsrName)
				{
					dest->soundTable.zones[i].plrAdsrName = buf->write_str(data->soundTable.zones[i].plrAdsrName);
				}
				if (data->soundTable.zones[i].npcAdsrName)
				{
					dest->soundTable.zones[i].npcAdsrName = buf->write_str(data->soundTable.zones[i].npcAdsrName);
				}
				if (data->soundTable.zones[i].weapReflName)
				{
					dest->soundTable.zones[i].weapReflName = buf->write_str(data->soundTable.zones[i].weapReflName);
				}
				if (data->soundTable.zones[i].fullOccName)
				{
					dest->soundTable.zones[i].fullOccName = buf->write_str(data->soundTable.zones[i].fullOccName);
				}
				if (data->soundTable.zones[i].playerBreathStateName)
				{
					dest->soundTable.zones[i].playerBreathStateName = buf->write_str(data->soundTable.zones[i].playerBreathStateName);
				}
			}
			buf->clear_pointer(&dest->soundTable.zones);
		}

		if (data->soundTable.unk)
		{
			buf->align(7);
			dest->soundTable.unk = buf->write(data->soundTable.unk, data->soundTable.unkCount);
			for (auto i = 0u; i < data->soundTable.unkCount; i++)
			{
				if (data->soundTable.unk[i].name)
				{
					dest->soundTable.unk[i].name = buf->write_str(data->soundTable.unk[i].name);
				}
			}
			buf->clear_pointer(&dest->soundTable.unk);
		}

		if (data->soundTable.fullOcclusionDefs)
		{
			buf->align(3);
			buf->write(data->soundTable.fullOcclusionDefs, data->soundTable.fullOcclusionDefCount);
			buf->clear_pointer(&dest->soundTable.fullOcclusionDefs);
		}

		if (data->soundTable.plrBreathStateDefs)
		{
			buf->align(7);
			dest->soundTable.plrBreathStateDefs = buf->write(data->soundTable.plrBreathStateDefs, data->soundTable.plrBreathStateDefCount);
			for (auto i = 0u; i < data->soundTable.plrBreathStateDefCount; i++)
			{
				if (data->soundTable.plrBreathStateDefs[i].inhaleAlias)
				{
					dest->soundTable.plrBreathStateDefs[i].inhaleAlias = buf->write_str(data->soundTable.plrBreathStateDefs[i].inhaleAlias);
				}
				if (data->soundTable.plrBreathStateDefs[i].exhaleAlias)
				{
					dest->soundTable.plrBreathStateDefs[i].exhaleAlias = buf->write_str(data->soundTable.plrBreathStateDefs[i].exhaleAlias);
				}
			}
			buf->clear_pointer(&dest->soundTable.plrBreathStateDefs);
		}

		if (data->ducks)
		{
			buf->align(7);
			dest->ducks = buf->write(data->ducks, data->duckCount);
			for (auto i = 0u; i < data->duckCount; i++)
			{
				if (data->ducks[i].attenuation)
				{
					buf->align(31);
					buf->write(data->ducks[i].attenuation, 128);
					buf->clear_pointer(&dest->ducks[i].attenuation);
				}
				if (data->ducks[i].lpf)
				{
					buf->align(31);
					buf->write(data->ducks[i].lpf, 128);
					buf->clear_pointer(&dest->ducks[i].lpf);
				}
			}
			buf->clear_pointer(&dest->ducks);
		}

		if (data->musicSets)
		{
			buf->align(7);
			dest->musicSets = buf->write(data->musicSets, data->musicSetCount);
			for (auto i = 0u; i < data->musicSetCount; i++)
			{
				if (data->musicSets[i].states)
				{
					buf->align(7);
					dest->musicSets[i].states = buf->write(data->musicSets[i].states, data->musicSets[i].stateCount);
					for (auto j = 0u; j < data->musicSets[i].stateCount; j++)
					{
						if (data->musicSets[i].states[j].loops)
						{
							buf->align(3);
							buf->write(data->musicSets[i].states[j].loops, data->musicSets[i].states[j].loopCount);
							buf->clear_pointer(&dest->musicSets[i].states[j].loops);
						}
					}
					buf->clear_pointer(&dest->musicSets[i].states);
				}
			}
			buf->clear_pointer(&dest->musicSets);
		}

		buf->pop_stream();
	}

	void sound_bank::dump(SndBank* asset)
	{
		auto file = filesystem::file("soundbank\\"s + asset->name + ".json"s);
		file.open("wb");

		ordered_json data;

		data["name"] = asset->name;
		data["zone"] = asset->zone;
		data["gameLanguage"] = asset->gameLanguage;
		data["soundLanguage"] = asset->soundLanguage;

		aliases::dump(asset);
		data["aliases"][0] = aliases::get_path(asset);

		send_effect_params::dump(asset);
		data["sendEffectParams"][0] = send_effect_params::get_path(asset);

		// sound table
		adsr_settings::dump(asset);
		data["ADSRSettings"][0] = adsr_settings::get_path(asset);

		ambient_def::dump(asset);
		data["AmbientDefs"][0] = ambient_def::get_path(asset);

		ambient_event::dump(asset);
		data["AmbientEvents"][0] = ambient_event::get_path(asset);

		ambient_elem::dump(asset);
		data["AmbientElements"][0] = ambient_elem::get_path(asset);

		filter::dump(asset);
		data["FilterDefs"][0] = filter::get_path(asset);

		mix::dump(asset);
		data["MixDefs"][0] = mix::get_path(asset);

		adsr_zone::npc::dump(asset);
		data["NPCAdsrZoneEntry"][0] = adsr_zone::npc::get_path(asset);

		adsr_zone::plr::dump(asset);
		data["PLRAdsrZoneEntry"][0] = adsr_zone::plr::get_path(asset);

		occlude_def::dump(asset);
		data["OccludeDefs"][0] = occlude_def::get_path(asset);

		reverb_def::dump(asset);
		data["ReverbDefs"][0] = reverb_def::get_path(asset);

		timescale::dump(asset);
		data["TimescaleEntrys"][0] = timescale::get_path(asset);

		zone::dump(asset);
		data["ZoneDefs"][0] = zone::get_path(asset);

		unk::dump(asset);
		data["Unks"][0] = unk::get_path(asset);

		full_occlusion_def::dump(asset);
		data["FullOcclusionDefs"][0] = full_occlusion_def::get_path(asset);

		plr_breath_state::dump(asset);
		data["PlayerBreathStateDefs"][0] = plr_breath_state::get_path(asset);

		ducks::dump(asset);
		// ducks are parsed from alias list

		// music

		sound_asset_bank::dump(asset->zone);

		file.write(data.dump(4));
		file.close();
	}
}