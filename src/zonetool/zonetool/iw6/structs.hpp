#pragma once
#include <d3d11.h>

namespace zonetool::iw6
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];

	struct dummy
	{
	};

	enum scr_string_t : std::int32_t
	{
	};

	enum XAssetType : std::int32_t
	{
		ASSET_TYPE_PHYSPRESET = 0x0,
		ASSET_TYPE_PHYSCOLLMAP = 0x1,
		ASSET_TYPE_XANIMPARTS = 0x2,
		ASSET_TYPE_XMODEL_SURFS = 0x3,
		ASSET_TYPE_XMODEL = 0x4,
		ASSET_TYPE_MATERIAL = 0x5,
		ASSET_TYPE_COMPUTESHADER = 0x6,
		ASSET_TYPE_VERTEXSHADER = 0x7,
		ASSET_TYPE_HULLSHADER = 0x8,
		ASSET_TYPE_DOMAINSHADER = 0x9,
		ASSET_TYPE_PIXELSHADER = 0xA,
		ASSET_TYPE_VERTEXDECL = 0xB,
		ASSET_TYPE_TECHNIQUE_SET = 0xC,
		ASSET_TYPE_IMAGE = 0xD,
		ASSET_TYPE_SOUND = 0xE,
		ASSET_TYPE_SOUND_CURVE = 0xF,
		ASSET_TYPE_LPF_CURVE = 0x10,
		ASSET_TYPE_REVERB_CURVE = 0x11,
		ASSET_TYPE_LOADED_SOUND = 0x12,
		ASSET_TYPE_CLIPMAP = 0x13,
		ASSET_TYPE_COMWORLD = 0x14,
		ASSET_TYPE_GLASSWORLD = 0x15,
		ASSET_TYPE_PATHDATA = 0x16,
		ASSET_TYPE_VEHICLE_TRACK = 0x17,
		ASSET_TYPE_MAP_ENTS = 0x18,
		ASSET_TYPE_FXWORLD = 0x19,
		ASSET_TYPE_GFXWORLD = 0x1A,
		ASSET_TYPE_LIGHT_DEF = 0x1B,
		ASSET_TYPE_UI_MAP = 0x1C,
		ASSET_TYPE_FONT = 0x1D,
		ASSET_TYPE_MENULIST = 0x1E,
		ASSET_TYPE_MENU = 0x1F,
		ASSET_TYPE_ANIMCLASS = 0x20,
		ASSET_TYPE_LOCALIZE_ENTRY = 0x21,
		ASSET_TYPE_ATTACHMENT = 0x22,
		ASSET_TYPE_WEAPON = 0x23,
		ASSET_TYPE_SNDDRIVER_GLOBALS = 0x24,
		ASSET_TYPE_FX = 0x25,
		ASSET_TYPE_IMPACT_FX = 0x26,
		ASSET_TYPE_SURFACE_FX = 0x27,
		ASSET_TYPE_AITYPE = 0x28,
		ASSET_TYPE_MPTYPE = 0x29,
		ASSET_TYPE_CHARACTER = 0x2A,
		ASSET_TYPE_XMODELALIAS = 0x2B,
		ASSET_TYPE_RAWFILE = 0x2C,
		ASSET_TYPE_SCRIPTFILE = 0x2D,
		ASSET_TYPE_STRINGTABLE = 0x2E,
		ASSET_TYPE_LEADERBOARD = 0x2F,
		ASSET_TYPE_STRUCTURED_DATA_DEF = 0x30,
		ASSET_TYPE_TRACER = 0x31,
		ASSET_TYPE_VEHICLE = 0x32,
		ASSET_TYPE_ADDON_MAP_ENTS = 0x33,
		ASSET_TYPE_NET_CONST_STRINGS = 0x34,
		ASSET_TYPE_REVERB_PRESET = 0x35,
		ASSET_TYPE_LUA_FILE = 0x36,
		ASSET_TYPE_SCRIPTABLE = 0x37,
		ASSET_TYPE_COLORIZATION = 0x38,
		ASSET_TYPE_COLORIZATIONSET = 0x39,
		ASSET_TYPE_TONEMAPPING = 0x3A,
		ASSET_TYPE_EQUIPMENT_SND_TABLE = 0x3B,
		ASSET_TYPE_VECTORFIELD = 0x3C,
		ASSET_TYPE_DOPPLER_PRESET = 0x3D,
		ASSET_TYPE_PARTICLE_SIM_ANIMATION = 0x3E,
		ASSET_TYPE_COUNT = 0x3F,
		ASSET_TYPE_STRING = 0x3F,
		ASSET_TYPE_ASSETLIST = 0x40,
		max = 0x3F
	};

	enum PhysPresetScaling
	{
		PHYSPRESET_SCALING_LINEAR = 0x0,
		PHYSPRESET_SCALING_QUADRATIC = 0x1,
		PHYSPRESET_SCALING_COUNT = 0x2,
	};

	struct PhysPreset
	{
		const char* name;
		int type;
		float mass;
		float bounce;
		float friction;
		float bulletForceScale;
		float explosiveForceScale;
		const char* sndAliasPrefix;
		float piecesSpreadFraction;
		float piecesUpwardVelocity;
		float minMomentum;
		float maxMomentum;
		float minVolume;
		float maxVolume;
		float minPitch;
		float maxPitch;
		PhysPresetScaling volumeType;
		PhysPresetScaling pitchType;
		bool tempDefaultToCylinder;
		bool perSurfaceSndAlias;
	};

	struct Bounds
	{
		vec3_t midPoint;
		vec3_t halfSize;
	};

	struct GfxDrawSurfFields
	{
		unsigned __int64 objectId : 16;
		unsigned __int64 reflectionProbeIndex : 8;
		unsigned __int64 hasGfxEntIndex : 1;
		unsigned __int64 customIndex : 5;
		unsigned __int64 materialSortedIndex : 13;
		unsigned __int64 tessellation : 3;
		unsigned __int64 prepass : 2;
		unsigned __int64 useHeroLighting : 1;
		unsigned __int64 sceneLightEnvIndex : 16;
		unsigned __int64 viewModelRender : 1;
		unsigned __int64 surfType : 4;
		unsigned __int64 primarySortKey : 6;
		unsigned __int64 unused : 30;
	};

	struct Packed128
	{
		unsigned __int64 p0;
		unsigned __int64 p1;
	};

	union GfxDrawSurf
	{
		GfxDrawSurfFields fields;
		Packed128 packed;
	};

	struct MaterialInfo
	{
		const char* name; // 0
		unsigned char gameFlags; // 8
		unsigned char sortKey; // 9
		unsigned char textureAtlasRowCount; // 10
		unsigned char textureAtlasColumnCount; // 11
		unsigned char textureAtlasFrameBlend; // 12
		unsigned char textureAtlasAsArray; /// 13
		unsigned char renderFlags; // 14
		GfxDrawSurf drawSurf; // 16
		unsigned int surfaceTypeBits; // 32
		unsigned short hashIndex; // 36
	};

	struct GfxComputeShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
	};

	struct ComputeShaderProgram
	{
		ID3D11ComputeShader* cs;
		GfxComputeShaderLoadDef loadDef;
	};

	struct ComputeShader
	{
		const char* name;
		ComputeShaderProgram prog;
	};

	struct GfxVertexShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
		unsigned short loadForRenderer;
		unsigned int microCodeCrc;
	};

	struct MaterialVertexShaderProgram
	{
		ID3D11VertexShader* vs;
		GfxVertexShaderLoadDef loadDef;
	};

	struct MaterialVertexShader
	{
		const char* name;
		MaterialVertexShaderProgram prog;
	};

	struct MaterialStreamRouting
	{
		unsigned char source;
		unsigned char dest;
		unsigned char mask;
	};

	struct MaterialVertexStreamRouting
	{
		MaterialStreamRouting data[32];
		ID3D11InputLayout* decl[249];
	};

	struct MaterialVertexDeclaration
	{
		const char* name;
		unsigned char streamCount;
		bool hasOptionalSource;
		MaterialVertexStreamRouting routing;
	};

	struct GfxHullShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
		unsigned short loadForRenderer;
	};

	struct MaterialHullShaderProgram
	{
		ID3D11HullShader* hs;
		GfxHullShaderLoadDef loadDef;
	};

	struct MaterialHullShader
	{
		const char* name;
		MaterialHullShaderProgram prog;
	};

	struct GfxDomainShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
		unsigned short loadForRenderer;
	};

	struct MaterialDomainShaderProgram
	{
		ID3D11DomainShader* ds;
		GfxDomainShaderLoadDef loadDef;
	};

	struct MaterialDomainShader
	{
		const char* name;
		MaterialDomainShaderProgram prog;
	};

	struct GfxPixelShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
		unsigned short loadForRenderer;
		unsigned int microCodeCrc;
	};

	struct MaterialPixelShaderProgram
	{
		ID3D11PixelShader* ps;
		GfxPixelShaderLoadDef loadDef;
	};

	struct MaterialPixelShader
	{
		const char* name;
		MaterialPixelShaderProgram prog;
	};

	struct MaterialArgumentCodeConst
	{
		unsigned short index;
		unsigned char firstRow;
		unsigned char rowCount;
	};

	union MaterialArgumentDef
	{
		const float* literalConst;
		MaterialArgumentCodeConst codeConst;
		unsigned int codeSampler;
		unsigned int nameHash;
	};

	struct MaterialShaderArgument
	{
		unsigned char type;
		unsigned char shader;
		unsigned short dest;
		MaterialArgumentDef u;
	};

	struct MaterialPass
	{
		MaterialVertexShader* vertexShader;
		MaterialVertexDeclaration* vertexDecl;
		MaterialHullShader* hullShader;
		MaterialDomainShader* domainShader;
		MaterialPixelShader* pixelShader;
		unsigned char pixelOutputMask;
		unsigned char perPrimArgCount;
		unsigned char perObjArgCount;
		unsigned char stableArgCount;
		unsigned short perPrimArgSize;
		unsigned short perObjArgSize;
		unsigned short stableArgSize;
		unsigned char zone;
		unsigned char perPrimConstantBuffer;
		unsigned char perObjConstantBuffer;
		unsigned char stableConstantBuffer;
		unsigned int customBufferFlags;
		unsigned char customSamplerFlags;
		unsigned char precompiledIndex;
		unsigned char stageConfig;
		MaterialShaderArgument* args;
	};

	struct MaterialTechniqueHeader
	{
		const char* name;
		unsigned short flags;
		unsigned short passCount;
	};

	struct MaterialTechnique
	{
		MaterialTechniqueHeader hdr;
		MaterialPass passArray[1];
	};

	struct MaterialTechniqueSet
	{
		const char* name;
		unsigned short flags;
		unsigned char worldVertFormat;
		unsigned char preDisplacementOnlyCount;
		MaterialTechnique* techniques[412];
	};

	struct GfxImageLoadDef
	{
		char levelCount;
		char numElements;
		char pad[2];
		int flags;
		int format;
		int resourceSize;
		char data[1];
	};

	struct GfxTexture
	{
		union
		{
			ID3D11Texture1D* linemap;
			ID3D11Texture2D* map;
			ID3D11Texture3D* volmap;
			ID3D11Texture2D* cubemap;
			GfxImageLoadDef* loadDef;
		};
		ID3D11ShaderResourceView* shaderView;
		ID3D11ShaderResourceView* shaderViewAlternate;
	};

	struct Picmip
	{
		unsigned char platform[2];
	};

	struct GfxImageStreamData
	{
		unsigned short width;
		unsigned short height;
		unsigned int pixelSize;
	};

	enum MapType : std::uint8_t
	{
		MAPTYPE_NONE = 0x0,
		MAPTYPE_INVALID1 = 0x1,
		MAPTYPE_1D = 0x2,
		MAPTYPE_2D = 0x3,
		MAPTYPE_3D = 0x4,
		MAPTYPE_CUBE = 0x5,
		MAPTYPE_ARRAY = 0x6,
		MAPTYPE_COUNT = 0x7,
	};

	struct GfxImage
	{
		GfxTexture texture;
		DXGI_FORMAT imageFormat;
		MapType mapType;
		unsigned char sematic;
		unsigned char category;
		unsigned char flags;
		Picmip picmip;
		char __pad0[2];
		unsigned int dataLen1;
		unsigned int dataLen2;
		unsigned short width;
		unsigned short height;
		unsigned short depth;
		unsigned short numElements;
		unsigned char levelCount;
		unsigned char streamed;
		char __pad1[2];
		unsigned char* pixelData;
		GfxImageStreamData streams[4];
		const char* name;
	};

	struct GfxColorFloat
	{
		float array[4];
	};

	struct GfxLightImage
	{
		GfxImage* image;
		unsigned char samplerState;
	};

	struct GfxLightDef
	{
		const char* name;
		GfxLightImage attenuation;
		GfxLightImage cucoloris;
		int lmapLookupStart;
	};

	struct WaterWritable
	{
		float floatTime;
	};

	struct water_t
	{
		WaterWritable writable;
		float* H0X;
		float* H0Y;
		float* wTerm;
		int M;
		int N;
		float Lx;
		float Lz;
		float gravity;
		float windvel;
		float winddir[2];
		float amplitude;
		GfxImage* image;
		GfxImage* stagingImage;
	};

	union MaterialTextureDefInfo
	{
		GfxImage* image;
		water_t* water;
	};

	struct MaterialTextureDef
	{
		unsigned int nameHash;
		char nameStart;
		char nameEnd;
		unsigned char samplerState;
		unsigned char semantic;
		MaterialTextureDefInfo u;
	};

	struct MaterialConstantDef
	{
		unsigned int nameHash;
		char name[12];
		float literal[4];
	};

	struct GfxStateBits
	{
		unsigned int loadBits[3]; // [2] = blendState??
		unsigned char zone;
		unsigned char depthStencilState[11];
		unsigned char blendState;
		unsigned char rasterizerState;
	};

	struct MaterialConstantBufferDef
	{
		unsigned int vsDataSize;
		unsigned int hsDataSize;
		unsigned int dsDataSize;
		unsigned int psDataSize;
		unsigned int vsOffsetDataSize;
		unsigned int hsOffsetDataSize;
		unsigned int dsOffsetDataSize;
		unsigned int psOffsetDataSize;
		unsigned char* vsData;
		unsigned char* hsData;
		unsigned char* dsData;
		unsigned char* psData;
		unsigned short* vsOffsetData;
		unsigned short* hsOffsetData;
		unsigned short* dsOffsetData;
		unsigned short* psOffsetData;
		ID3D11Buffer* vsConstantBuffer;
		ID3D11Buffer* hsConstantBuffer;
		ID3D11Buffer* dsConstantBuffer;
		ID3D11Buffer* psConstantBuffer;
	};

	struct Material
	{
		union
		{
			const char* name;
			MaterialInfo info;
		};
		unsigned char stateBitsEntry[412]; // 40
		unsigned char textureCount; // 452
		unsigned char constantCount; // 453
		unsigned char stateBitsCount; // 454
		unsigned char stateFlags; // 455
		unsigned char cameraRegion; // 456
		unsigned char materialType; // 457
		unsigned char stringCount; // 458
		unsigned char assetFlags; // 459
		char __pad2[4]; // 460 - 464
		MaterialTechniqueSet* techniqueSet; // 464
		MaterialTextureDef* textureTable; // 472
		MaterialConstantDef* constantTable; // 480
		GfxStateBits* stateMap; // 488 (stateBitsTable)
		unsigned char constantBufferIndex[412]; // 496
		char __pad3[4]; // 500
		MaterialConstantBufferDef* constantBufferTable; // 912
		unsigned char constantBufferCount; // 920
		char __pad4[7]; // 921-928
		const char** xStringArray; // 928
	};

	union XAnimDynamicFrames
	{
		unsigned char(*_1)[3];
		unsigned short(*_2)[3];
	};

	union XAnimDynamicIndices
	{
		unsigned char _1[1];
		unsigned short _2[1];
	};

	struct XAnimPartTransFrames
	{
		float mins[3];
		float size[3];
		XAnimDynamicFrames frames;
		XAnimDynamicIndices indices;
	};

	union XAnimPartTransData
	{
		XAnimPartTransFrames frames;
		float frame0[3];
	};

	struct XAnimPartTrans
	{
		unsigned short size;
		unsigned char smallTrans;
		XAnimPartTransData u;
	};

	struct XAnimDeltaPartQuatDataFrames2
	{
		short(*frames)[2];
		XAnimDynamicIndices indices;
	};

	union XAnimDeltaPartQuatData2
	{
		XAnimDeltaPartQuatDataFrames2 frames;
		short frame0[2];
	};

	struct XAnimDeltaPartQuat2
	{
		unsigned short size;
		XAnimDeltaPartQuatData2 u;
	};

	struct XAnimDeltaPartQuatDataFrames
	{
		short(*frames)[4];
		XAnimDynamicIndices indices;
	};

	union XAnimDeltaPartQuatData
	{
		XAnimDeltaPartQuatDataFrames frames;
		short frame0[4];
	};

	struct XAnimDeltaPartQuat
	{
		unsigned short size;
		XAnimDeltaPartQuatData u;
	};

	struct XAnimDeltaPart
	{
		XAnimPartTrans* trans;
		XAnimDeltaPartQuat2* quat2;
		XAnimDeltaPartQuat* quat;
	};

	union XAnimIndices
	{
		unsigned char* _1;
		unsigned short* _2;
		void* data;
	};

	struct XAnimNotifyInfo
	{
		scr_string_t name;
		float time;
	};

	enum XAnimPartsFlags : std::int32_t
	{
		ANIM_LOOP = 0x1,
		ANIM_DELTA = 0x2,
		ANIM_DELTA_3D = 0x4,
		ANIM_DEFAULT = 0x8,
		ANIM_SHMEM = 0x10,
	};

	struct XAnimParts
	{
		const char* name; // 0
		unsigned short dataByteCount; // 8
		unsigned short dataShortCount; // 10
		unsigned short dataIntCount; // 12
		unsigned short randomDataByteCount; // 14
		unsigned short randomDataIntCount; // 16
		unsigned short numframes; // 18
		unsigned char flags; // 20
		unsigned char boneCount[10]; // 21
		unsigned char notifyCount; // 31
		unsigned char assetType; // 32
		unsigned char ikType; // 33
		unsigned int randomDataShortCount; // 36
		unsigned int indexCount; // 40
		float framerate;  // 44
		float frequency; // 48
		scr_string_t* names; // 56
		char* dataByte; // 64
		short* dataShort; // 72
		int* dataInt; // 80
		short* randomDataShort; // 88
		unsigned char* randomDataByte; // 96
		int* randomDataInt; // 104
		XAnimIndices indices; // 112
		XAnimNotifyInfo* notify; // 120
		XAnimDeltaPart* deltaPart; // 128
	};

	struct DObjAnimMat
	{
		float quat[4];
		float trans[3];
		float transWeight;
	};

	struct ReactiveMotionModelPart
	{
		float center[3];
		float stiffness;
	};

	struct XSurfaceCollisionAabb
	{
		unsigned short mins[3];
		unsigned short maxs[3];
	};

	struct XSurfaceCollisionNode
	{
		XSurfaceCollisionAabb aabb;
		unsigned short childBeginIndex;
		unsigned short childCount;
	};

	struct XSurfaceCollisionLeaf
	{
		unsigned short triangleBeginIndex;
	};

	struct XSurfaceCollisionTree
	{
		float trans[3];
		float scale[3];
		unsigned int nodeCount;
		XSurfaceCollisionNode* nodes;
		unsigned int leafCount;
		XSurfaceCollisionLeaf* leafs;
	};

	struct XRigidVertList
	{
		unsigned short boneOffset;
		unsigned short vertCount;
		unsigned short triOffset;
		unsigned short triCount;
		XSurfaceCollisionTree* collisionTree;
	};

	union PackedUnitVec
	{
		unsigned int packed;
	};

	union PackedTexCoords
	{
		unsigned int packed;
	};

	union GfxColor
	{
		unsigned char array[4];
		unsigned int packed;
	};

	struct GfxQuantizedNoColorMotionVertex
	{
		short xyz[3];
		short binormalSignAndHeight;
		PackedUnitVec normal;
		PackedUnitVec tangent;
		PackedTexCoords texCoord;
		GfxColor pieceIndex;
	};

	struct GfxQuantizedNoColorVertex
	{
		short xyz[3];
		short binormalSign;
		PackedUnitVec normal;
		PackedUnitVec tangent;
		PackedTexCoords texCoord;
	};

	struct GfxQuantizedVertex
	{
		short xyz[3];
		short binormalSign;
		PackedUnitVec normal;
		PackedUnitVec tangent;
		PackedTexCoords texCoord;
		GfxColor color;
	};

	struct GfxQuantizedMotionVertex
	{
		short xyz[3];
		short binormalSignAndHeight;
		PackedUnitVec normal;
		PackedUnitVec tangent;
		PackedTexCoords texCoord;
		GfxColor pieceIndex;
	};

	struct GfxPackedVertex
	{
		float xyz[3];
		float binormalSign;
		GfxColor color;
		PackedTexCoords texCoord;
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	struct GfxPackedMotionVertex
	{
		float xyz[3];
		float binormalSignAndHeight;
		GfxColor pieceIndex;
		PackedTexCoords texCoord;
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	union GfxVertexUnion0
	{
		GfxQuantizedNoColorVertex* quantizedNoColorVerts0;
		GfxQuantizedNoColorMotionVertex* quantizedNoColorMotionVerts0;
		GfxQuantizedVertex* quantizedVerts0;
		GfxQuantizedMotionVertex* quantizedMotionVerts0;
		GfxPackedVertex* packedVerts0;
		GfxPackedMotionVertex* packedMotionVerts0;
		void* verts0;
	};

	struct Face
	{
		unsigned short v1;
		unsigned short v2;
		unsigned short v3;
	};

	struct XSubdivRigidVertList
	{
		unsigned int firstFace;
		unsigned int faceCount;
		unsigned int firstRegularPatch;
		unsigned int regularPatchCount;
	};

	struct XSurfaceSubdivLevel
	{
		XSubdivRigidVertList* rigidVertLists;
		unsigned int faceCount;
		unsigned int regularPatchCount;
		unsigned int regularPatchOffset;
		unsigned int facePointCount;
		unsigned int facePointValence4Count;
		unsigned int facePointBufferSize;
		unsigned int edgePointCount;
		unsigned int edgePointSmoothEnd;
		unsigned int edgePointUVBorderEnd;
		unsigned int vertexPointCount;
		unsigned int vertexPointValence4Count;
		unsigned int vertexPointBufferSize;
		unsigned int normalCount;
		unsigned int normalBufferSize;
		unsigned int transitionPointCount;
		unsigned int vertCount;
		unsigned int vertOffset;
		unsigned short* faceIndices;
		unsigned short* regularPatchIndices;
		unsigned int* regularPatchFlags;
		unsigned int* facePoints;
		unsigned int* edgePoints;
		unsigned int* vertexPoints;
		unsigned int* normals;
		unsigned int* transitionPoints;
		float* regularPatchCones;
		ID3D11Buffer* regularPatchIndexBuffer;
		ID3D11Buffer* faceIndexBuffer;
		ID3D11ShaderResourceView* regularPatchIndexBufferView;
		ID3D11ShaderResourceView* regularPatchFlagsView;
		ID3D11ShaderResourceView* facePointsView;
		ID3D11ShaderResourceView* edgePointsView;
		ID3D11ShaderResourceView* vertexPointsView;
		ID3D11ShaderResourceView* normalsView;
		ID3D11ShaderResourceView* transitionPointsView;
		ID3D11ShaderResourceView* regularPatchConesView;
	};

	struct GfxSubdivCache
	{
		unsigned int size;
		ID3D11Buffer* subdivCacheBuffer;
		ID3D11ShaderResourceView* subdivCacheView;
	};

	struct XSurfaceSubdivInfo
	{
		XSurfaceSubdivLevel* levels;
		char __pad0[24];
		GfxSubdivCache cache;
	};

	struct BlendVertsUnknown
	{
		unsigned short b[15];
		unsigned short blendVertCountIndex; // 30
	};

	typedef unsigned short XBlendInfo;

	enum SurfaceFlags : std::int32_t
	{
		SURF_FLAG_VERTCOL_GREY = 0x1,
		SURF_FLAG_VERTCOL_NONE = 0x2,
		SURF_FLAG_SKINNED = 0x4,
		SURF_FLAG_REACTIVE_MOTION = 0x8,
		SURF_FLAG_LIGHTMAP_COORDS = 0x10,
		SURF_FLAG_TENSION = 0x20,
	};

	struct XSurface
	{
		unsigned short flags; // 0
		unsigned short vertCount; // 2
		unsigned short triCount; // 4
		unsigned char rigidVertListCount; // 6
		unsigned char subdivLevelCount; // 7
		short blendVertCounts[8]; // 8
		GfxVertexUnion0 verts0; // 24
		Face* triIndices; // 32
		ID3D11Buffer* vb0; // 40
		ID3D11ShaderResourceView* vb0View; // 48
		ID3D11Buffer* indexBuffer; // 56
		XRigidVertList* rigidVertLists; // 64
		XBlendInfo* blendVerts; // 72
		BlendVertsUnknown* blendVertsTable; // 80
		ID3D11Buffer* blendVertsBuffer; // 88
		ID3D11ShaderResourceView* blendVertsView; // 96
		float(*lmapUnwrap)[2]; // 104
		ID3D11Buffer* vblmapBuffer; // 112
		ID3D11ShaderResourceView* vblmapView; // 120
		XSurfaceSubdivInfo* subdiv; // 128
		float* tensionData; // 136
		unsigned short* tensionAccumTable; // 144
		ID3D11Buffer* tensionAccumTableBuffer; // 152
		ID3D11ShaderResourceView* tensionAccumTableView; // 160
		ID3D11Buffer* tensionDataBuffer; // 168
		ID3D11ShaderResourceView* tensionDataView; // 176
		ID3D11ShaderResourceView* indexBufferView; // 184
		unsigned int vertexLightingIndex; // 192
		int partBits[8]; // 196
	};

	struct XModelSurfs
	{
		const char* name;
		XSurface* surfs;
		unsigned short numsurfs;
		int partBits[8];
	};

	struct XModelLodInfo
	{
		float dist;
		unsigned short numsurfs;
		unsigned short surfIndex;
		XModelSurfs* modelSurfs;
		int partBits[8];
		XSurface* surfs;
		char unknown[8];
	};

	struct XModelCollSurf_s
	{
		Bounds bounds;
		int boneIdx;
		int contents;
		int surfFlags;
	};

	struct XBoneInfo
	{
		Bounds bounds;
		union
		{
			float radiusSquared;
			unsigned int radiusSquaredAsInt;
		};
	};

	struct cplane_s
	{
		float normal[3];
		float dist;
		unsigned char type;
		//unsigned char pad[3];
	};

	struct cbrushside_t
	{
		cplane_s* plane;
		unsigned short materialNum;
		unsigned char firstAdjacentSideOffset;
		unsigned char edgeCount;
	};

	typedef unsigned char cbrushedge_t;

	struct cbrush_t
	{
		unsigned short numsides;
		unsigned short glassPieceIndex;
		cbrushside_t* sides;
		cbrushedge_t* baseAdjacentSide;
		short axialMaterialNum[2][3];
		unsigned char firstAdjacentSideOffsets[2][3];
		unsigned char edgeCount[2][3];
	};

	struct BrushWrapper
	{
		Bounds bounds;
		cbrush_t brush;
		int totalEdgeCount;
		cplane_s* planes;
	};

	struct PhysGeomInfo
	{
		BrushWrapper* brushWrapper;
		int type;
		float orientation[3][3];
		Bounds bounds;
	};

	struct PhysMass
	{
		float centerOfMass[3];
		float momentsOfInertia[3];
		float productsOfInertia[3];
	};

	struct PhysCollmap
	{
		const char* name;
		unsigned int count;
		PhysGeomInfo* geoms;
		PhysMass mass;
		Bounds bounds;
	};

	struct XModelAngle
	{
		short x;
		short y;
		short z;
		short base;
	};

	struct XModelTagPos
	{
		float x;
		float y;
		float z;
	};

	struct XModel
	{
		const char* name; // 0
		unsigned char numBones; // 8
		unsigned char numRootBones; // 9
		unsigned char numsurfs; // 10
		unsigned char numReactiveMotionParts; // 11
		float scale; // 12
		char __pad0[4]; //unsigned char lodRampType; // 16
		unsigned int noScalePartBits[6]; // 20
		scr_string_t* boneNames; // 48
		unsigned char* parentList; // 56
		XModelAngle* tagAngles; // 64
		XModelTagPos* tagPositions; // 72
		unsigned char* partClassification; // 80
		DObjAnimMat* baseMat; // 88
		ReactiveMotionModelPart* reactiveMotionParts; // 96
		Material** materialHandles; // 104
		XModelLodInfo lodInfo[6]; // 112
		char maxLoadedLod; // 496
		char numLods; // 497
		char collLod; // 498
		unsigned char flags; // 499
		int numCollSurfs; // 500
		XModelCollSurf_s* collSurfs; // 504
		int contents; // 512
		XBoneInfo* boneInfo; // 520
		float radius; // 528
		Bounds bounds; // 532
		unsigned short* invHighMipRadius; // 560
		int memUsage; // 568
		PhysPreset* physPreset; // 576
		PhysCollmap* physCollmap; // 584
		float quantization; // 592
		float unk;
	};

	enum SoundChannel : std::uint32_t
	{
		SND_CHANNEL_PHYSICS,
		SND_CHANNEL_AMBDIST1,
		SND_CHANNEL_AMBDIST2,
		SND_CHANNEL_ALARM,
		SND_CHANNEL_AUTO,
		SND_CHANNEL_AUTO2,
		SND_CHANNEL_AUTO2D,
		SND_CHANNEL_AUTODOG,
		SND_CHANNEL_EXPLOSIONDIST1,
		SND_CHANNEL_EXPLOSIONDIST2,
		SND_CHANNEL_EXPLOSIVEIMPACT,
		SND_CHANNEL_ELEMENT,
		SND_CHANNEL_ELEMENT_INT,
		SND_CHANNEL_ELEMENT_EXT,
		SND_CHANNEL_FOLEY_PLR_MVMT,
		SND_CHANNEL_FOLEY_PLR_WEAP,
		SND_CHANNEL_FOLEY_NPC_MVMT,
		SND_CHANNEL_FOLEY_NPC_WEAP,
		SND_CHANNEL_FOLEY_DOG_MVMT,
		SND_CHANNEL_ELEMENT_LIM,
		SND_CHANNEL_ELEMENT2D,
		SND_CHANNEL_VOICE_DOG_DIST,
		SND_CHANNEL_BULLETFLESH1NPC_NPC,
		SND_CHANNEL_BULLETFLESH2NPC_NPC,
		SND_CHANNEL_BULLETIMPACT,
		SND_CHANNEL_BULLETFLESH1NPC,
		SND_CHANNEL_BULLETFLESH2NPC,
		SND_CHANNEL_BULLETFLESH1,
		SND_CHANNEL_BULLETFLESH2,
		SND_CHANNEL_VEHICLE,
		SND_CHANNEL_VEHICLELIMITED,
		SND_CHANNEL_MENU,
		SND_CHANNEL_MENULIM1,
		SND_CHANNEL_MENULIM2,
		SND_CHANNEL_BULLETWHIZBYIN,
		SND_CHANNEL_BULLETWHIZBYOUT,
		SND_CHANNEL_BODY,
		SND_CHANNEL_BODY2D,
		SND_CHANNEL_RELOAD,
		SND_CHANNEL_RELOAD2D,
		SND_CHANNEL_FOLEY_PLR_STEP,
		SND_CHANNEL_FOLEY_PLR_STEP_UNRES,
		SND_CHANNEL_FOLEY_NPC_STEP,
		SND_CHANNEL_FOLEY_DOG_STEP,
		SND_CHANNEL_ITEM,
		SND_CHANNEL_WEAPON_DRONE,
		SND_CHANNEL_EXPLOSION1,
		SND_CHANNEL_EXPLOSION2,
		SND_CHANNEL_EXPLOSION3,
		SND_CHANNEL_EXPLOSION4,
		SND_CHANNEL_EXPLOSION5,
		SND_CHANNEL_EFFECTS1,
		SND_CHANNEL_EFFECTS2,
		SND_CHANNEL_EFFECTS3,
		SND_CHANNEL_EFFECTS2D1,
		SND_CHANNEL_EFFECTS2D2,
		SND_CHANNEL_NORESTRICT,
		SND_CHANNEL_NORESTRICT2D,
		SND_CHANNEL_AIRCRAFT,
		SND_CHANNEL_VEHICLE2D,
		SND_CHANNEL_WEAPON_DIST,
		SND_CHANNEL_WEAPON_MID,
		SND_CHANNEL_WEAPON,
		SND_CHANNEL_WEAPON2D,
		SND_CHANNEL_NONSHOCK,
		SND_CHANNEL_NONSHOCK2,
		SND_CHANNEL_EFFECTS2DLIM,
		SND_CHANNEL_VOICE_DOG,
		SND_CHANNEL_MUSIC_EMITTER,
		SND_CHANNEL_VOICE_DOG_ATTACK,
		SND_CHANNEL_VOICE,
		SND_CHANNEL_LOCAL,
		SND_CHANNEL_LOCAL2,
		SND_CHANNEL_LOCAL3,
		SND_CHANNEL_AMBIENT,
		SND_CHANNEL_PLR_WEAP_FIRE_2D,
		SND_CHANNEL_PLR_WEAP_MECH_2D,
		SND_CHANNEL_HURT,
		SND_CHANNEL_PLAYER1,
		SND_CHANNEL_PLAYER2,
		SND_CHANNEL_MUSIC,
		SND_CHANNEL_MUSICNOPAUSE,
		SND_CHANNEL_MISSION,
		SND_CHANNEL_MISSIONFX,
		SND_CHANNEL_ANNOUNCER,
		SND_CHANNEL_SHELLSHOCK,
	};

	union SoundAliasFlags
	{
		struct _
		{
			unsigned int looping : 1;
			unsigned int isMaster : 1;
			unsigned int isSlave : 1;
			unsigned int fullDryLevel : 1;
			unsigned int noWetLevel : 1;
			unsigned int unknown1 : 1;
			unsigned int unknown2 : 1;
			unsigned int type : 2;
			SoundChannel channel : 7;
		};
		unsigned int intValue;
	};

	enum snd_alias_type_t
	{
		SAT_UNKNOWN = 0x0,
		SAT_LOADED = 0x1,
		SAT_STREAMED = 0x2,
		SAT_PRIMED = 0x3,
		SAT_COUNT = 0x4,
	};

	struct RiffAudioInfo
	{
		unsigned int sampleRate;
		unsigned int dataByteCount;
		unsigned int numSamples;
		unsigned int avgBytesPerSec;
		unsigned short channels;
		unsigned short numBits;
		unsigned short blockAlign;
		char format;
	};

	struct XA2Sound
	{
		char* data;
		char* seekTable;
		RiffAudioInfo format;
		int loadedSize;
		int seekTableSize;
	};

	struct LoadedSound
	{
		const char* name;
		XA2Sound sound;
	};

	struct StreamFileNameRaw
	{
		const char* dir;
		const char* name;
	};

	struct StreamFileNamePacked
	{
		unsigned __int64 offset;
		unsigned __int64 length;
	};

	union StreamFileInfo
	{
		StreamFileNameRaw raw;
		StreamFileNamePacked packed;
	};

	struct StreamFileName
	{
		unsigned short isLocalized;
		unsigned short fileIndex;
		StreamFileInfo info;
	};

	struct StreamedSound
	{
		StreamFileName filename;
		unsigned int totalMsec;
	};

	struct PrimedSound
	{
		StreamFileName filename;
		LoadedSound* loadedPart;
		int dataOffset;
		int totalSize;
		unsigned int primedCrc;
	};

	union SoundFileRef
	{
		LoadedSound* loadSnd;
		StreamedSound streamSnd;
		PrimedSound primedSnd;
	};

	struct SoundFile
	{
		unsigned char type;
		unsigned char exists;
		SoundFileRef u;
	};

	struct SndCurve
	{
		bool isDefault;
		union
		{
			const char* filename;
			const char* name;
		};
		unsigned short knotCount;
		float knots[16][2];
	};

	struct SpeakerLevels
	{
		int speaker;
		int numLevels;
		float levels[2];
	};

	struct ChannelMap
	{
		int speakerCount;
		SpeakerLevels speakers[6];
	};

	struct SpeakerMap
	{
		bool isDefault;
		const char* name;
		ChannelMap channelMaps[2][2];
	};

	struct OcclusionShape
	{
		bool isDefault;
		const char* name;
		int shapeKind;
		float innerAngle;
		float outerAngle;
		float occludedVolume;
	};

	struct DopplerPreset
	{
		union
		{
			const char* p_name;
			const char* name;
		};
		float speedOfSound;
		float playerVelocityScale;
		float minPitch;
		float maxPitch;
		float smoothing;
	};

	struct snd_alias_t
	{
		union
		{
			const char* aliasName;
			const char* name;
		};
		const char* subtitle;
		const char* secondaryAliasName;
		const char* chainAliasName;
		const char* mixerGroup;
		SoundFile* soundFile;
		int sequence;
		float volMin;
		float volMax;
		int volModIndex;
		float pitchMin;
		float pitchMax;
		float distMin;
		float distMax;
		float velocityMin;
		int flags;
		unsigned char masterPriority;
		float masterPercentage;
		float slavePercentage;
		float probability;
		float lfePercentage;
		float centerPercentage;
		int startDelay;
		SndCurve* volumeFalloffCurve;
		SndCurve* lpfCurve;
		SndCurve* reverbSendCurve;
		float envelopMin;
		float envelopMax;
		float envelopPercentage;
		SpeakerMap* speakerMap;
		float wetMixOverride;
		OcclusionShape* occlusionShape;
		unsigned char allowDoppler;
		DopplerPreset* dopplerPreset;
	};

	struct snd_alias_list_t
	{
		union
		{
			const char* aliasName;
			const char* name;
		};
		snd_alias_t* head;
		int count;
	};

	struct ComPrimaryLight
	{
		unsigned char type;
		unsigned char canUseShadowMap;
		unsigned char exponent;
		unsigned char unused;
		float color[3];
		float dir[3];
		float up[3];
		float origin[3];
		float radius;
		float cosHalfFovOuter;
		float cosHalfFovInner;
		float cosHalfFovExpanded;
		float rotationLimit;
		float translationLimit;
		float cucRotationOffsetRad;
		float cucRotationSpeedRad;
		float cucScrollVector[2];
		float cucScaleVector[2];
		float cucTransVector[2];
		const char* defName;
	};

	struct ComPrimaryLightEnv
	{
		unsigned short primaryLightIndices[4];
		unsigned char numIndices;
	};

	struct ComWorld
	{
		const char* name;
		int isInUse;
		unsigned int primaryLightCount;
		ComPrimaryLight* primaryLights;
		unsigned int primaryLightEnvCount;
		ComPrimaryLightEnv* primaryLightEnvs;
	};

	struct G_GlassPiece
	{
		unsigned short damageTaken;
		unsigned short collapseTime;
		int lastStateChangeTime;
		unsigned char impactDir;
		unsigned char impactPos[2];
	};

	struct G_GlassName
	{
		char* nameStr;
		scr_string_t name;
		unsigned short pieceCount;
		unsigned short* pieceIndices;
	};

	struct G_GlassData
	{
		G_GlassPiece* glassPieces;
		unsigned int pieceCount;
		unsigned short damageToWeaken;
		unsigned short damageToDestroy;
		unsigned int glassNameCount;
		G_GlassName* glassNames;
		unsigned char pad[108];
	};

	struct GlassWorld
	{
		const char* name;
		G_GlassData* g_glassData;
	};

	struct Glyph
	{
		unsigned short letter;
		char x0;
		char y0;
		unsigned char dx;
		unsigned char pixelWidth;
		unsigned char pixelHeight;
		float s0;
		float t0;
		float s1;
		float t1;
	};

	struct TriggerModel
	{
		int contents;
		unsigned short hullCount;
		unsigned short firstHull;
	};

	struct TriggerHull
	{
		Bounds bounds;
		int contents;
		unsigned short slabCount;
		unsigned short firstSlab;
	};

	struct TriggerSlab
	{
		float dir[3];
		float midPoint;
		float halfSize;
	};

	struct MapTriggers
	{
		unsigned int count;
		TriggerModel* models;
		unsigned int hullCount;
		TriggerHull* hulls;
		unsigned int slabCount;
		TriggerSlab* slabs;
	};

	struct ClientTriggerAabbNode
	{
		Bounds bounds;
		unsigned short firstChild;
		unsigned short childCount;
	};

	struct ClientTriggers
	{
		MapTriggers trigger;
		unsigned short numClientTriggerNodes;
		ClientTriggerAabbNode* clientTriggerAabbTree;
		unsigned int triggerStringLength;
		char* triggerString;
		short* visionSetTriggers;
		char* triggerType;
		float(*origins)[3];
		float* scriptDelay;
		short* audioTriggers;
		short* blendLookup;
		short* npcTriggers;
	};

	struct ClientTriggerBlendNode
	{
		float pointA[3];
		float pointB[3];
		unsigned short triggerA;
		unsigned short triggerB;
	};

	struct ClientTriggerBlend
	{
		unsigned short numClientTriggerBlendNodes;
		ClientTriggerBlendNode* blendNodes;
	};

	struct SpawnPointEntityRecord
	{
		unsigned short index;
		scr_string_t name;
		scr_string_t target;
		scr_string_t script_noteworthy;
		float origin[3];
		float angles[3];
	};

	struct SpawnPointRecordList
	{
		unsigned short spawnsCount;
		SpawnPointEntityRecord* spawns;
	};

	struct SplinePointEntityRecord
	{
		int splineId;
		int splineNodeId;
		char* splineNodeLabel;
		float splineNodeTension;
		float origin[3];
		float corridorDims[2];
		float tangent[3];
		float distToNextNode;
		vec3_t* positionCubic;
		vec3_t* tangentQuadratic;
	};

	struct SplinePointRecordList
	{
		unsigned short splinePointCount;
		float splineLength;
		SplinePointEntityRecord* splinePoints;
	};

	struct SplineRecordList
	{
		unsigned short splineCount;
		SplinePointRecordList* splines;
	};

	struct MapEnts
	{
		const char* name;
		char* entityString;
		int numEntityChars;
		MapTriggers trigger;
		ClientTriggers clientTrigger;
		ClientTriggerBlend clientTriggerBlend;
		SpawnPointRecordList spawnList;
		SplineRecordList splineList;
	};

	struct FxEffectDef;
	struct FxGlassDef
	{
		float halfThickness;
		float texVecs[2][2];
		GfxColor color;
		Material* material;
		Material* materialShattered;
		PhysPreset* physPreset;
		FxEffectDef* pieceBreakEffect;
		FxEffectDef* shatterEffect;
		FxEffectDef* shatterSmallEffect;
		FxEffectDef* crackDecalEffect;
		snd_alias_list_t* damagedSound;
		snd_alias_list_t* destroyedSound;
		snd_alias_list_t* destroyedQuietSound;
		char __pad[8];
		int numCrackRings;
		bool isOpaque;
	};

	struct FxSpatialFrame
	{
		float quat[4];
		float origin[3];
	};

	struct $03A8A7B39FA20F64B5AB79125E07CD62
	{
		FxSpatialFrame frame;
		float radius;
	};

	union FxGlassPiecePlace
	{
		$03A8A7B39FA20F64B5AB79125E07CD62 __s0;
		unsigned int nextFree;
	};

	struct FxGlassPieceState
	{
		float texCoordOrigin[2];
		unsigned int supportMask;
		unsigned short initIndex;
		unsigned short geoDataStart;
		unsigned short lightingIndex;
		unsigned char defIndex;
		unsigned char pad[3];
		unsigned char vertCount;
		unsigned char holeDataCount;
		unsigned char crackDataCount;
		unsigned char fanDataCount;
		unsigned short flags;
		float areaX2;
	};

	struct FxGlassPieceDynamics
	{
		int fallTime;
		__int64 physObjId;
		__int64 physJointId;
		float vel[3];
		float avel[3];
	};

	struct FxGlassVertex
	{
		short x;
		short y;
	};

	struct FxGlassHoleHeader
	{
		unsigned short uniqueVertCount;
		unsigned char touchVert;
		unsigned char pad[1];
	};

	struct FxGlassCrackHeader
	{
		unsigned short uniqueVertCount;
		unsigned char beginVertIndex;
		unsigned char endVertIndex;
	};

	union FxGlassGeometryData
	{
		FxGlassVertex vert;
		FxGlassHoleHeader hole;
		FxGlassCrackHeader crack;
		unsigned char asBytes[4];
		short anonymous[2];
	};

	struct FxGlassInitPieceState
	{
		FxSpatialFrame frame;
		float radius;
		float texCoordOrigin[2];
		unsigned int supportMask;
		float areaX2;
		unsigned short lightingIndex;
		unsigned char defIndex;
		unsigned char vertCount;
		unsigned char fanDataCount;
		unsigned char pad[1];
	};

	struct FxGlassSystem
	{
		int time;
		int prevTime;
		unsigned int defCount;
		unsigned int pieceLimit;
		unsigned int pieceWordCount;
		unsigned int initPieceCount;
		unsigned int cellCount;
		unsigned int activePieceCount;
		unsigned int firstFreePiece;
		unsigned int geoDataLimit;
		unsigned int geoDataCount;
		unsigned int initGeoDataCount;
		FxGlassDef* defs;
		FxGlassPiecePlace* piecePlaces;
		FxGlassPieceState* pieceStates;
		FxGlassPieceDynamics* pieceDynamics;
		FxGlassGeometryData* geoData;
		unsigned int* isInUse;
		unsigned int* cellBits;
		unsigned char* visData;
		vec3_t* linkOrg; //float(*linkOrg)[3];
		float* halfThickness;
		unsigned short* lightingHandles;
		FxGlassInitPieceState* initPieceStates;
		FxGlassGeometryData* initGeoData;
		bool needToCompactData;
		unsigned char initCount;
		float effectChanceAccum;
		int lastPieceDeletionTime;
	};

	struct FxWorld
	{
		const char* name;
		FxGlassSystem glassSys;
	};

	struct GfxSky
	{
		int skySurfCount;
		int* skyStartSurfs;
		GfxImage* skyImage;
		unsigned char skySamplerState;
	};

	struct GfxWorldDpvsPlanes
	{
		int cellCount;
		cplane_s* planes;
		unsigned short* nodes;
		unsigned int* sceneEntCellBits;
	};

	struct GfxCellTreeCount
	{
		int aabbTreeCount;
	};

	struct GfxAabbTree
	{
		Bounds bounds;
		unsigned short childCount;
		unsigned short surfaceCount;
		unsigned int startSurfIndex;
		unsigned short smodelIndexCount;
		unsigned short* smodelIndexes;
		int childrenOffset;
	};

	struct GfxCellTree
	{
		GfxAabbTree* aabbTree;
	};

	struct GfxPortal;

	struct GfxPortalWritable
	{
		bool isQueued;
		bool isAncestor;
		unsigned char recursionDepth;
		unsigned char hullPointCount;
		float(*hullPoints)[2];
		GfxPortal* queuedParent;
	};

	struct DpvsPlane
	{
		float coeffs[4];
	};

	struct GfxPortal
	{
		GfxPortalWritable writable;
		DpvsPlane plane;
		float(*vertices)[3];
		unsigned short cellIndex;
		unsigned short closeDistance;
		unsigned char vertexCount;
		float hullAxis[2][3];
	};

	struct GfxCell
	{
		Bounds bounds;
		int portalCount;
		GfxPortal* portals;
		unsigned char reflectionProbeCount;
		unsigned char* reflectionProbes;
		unsigned char reflectionProbeReferenceCount;
		unsigned char* reflectionProbeReferences;
	};

	struct GfxReflectionProbeVolumeData
	{
		float volumePlanes[6][4];
	};

	struct GfxReflectionProbe
	{
		float origin[3];
		GfxReflectionProbeVolumeData* probeVolumes;
		unsigned int probeVolumeCount;
	};

	struct GfxReflectionProbeReferenceOrigin
	{
		float origin[3];
	};

	struct GfxReflectionProbeReference
	{
		unsigned char index;
	};

	struct GfxLightmapArray
	{
		GfxImage* primary;
		GfxImage* secondary;
	};

	struct GfxWorldVertex
	{
		float xyz[3];
		float binormalSign;
		GfxColor color;
		float texCoord[2];
		float lmapCoord[2];
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	struct GfxWorldVertexData
	{
		GfxWorldVertex* vertices;
		ID3D11Buffer* worldVb;
	};

	struct GfxWorldVertexLayerData
	{
		unsigned char* data;
		ID3D11Buffer* layerVb;
	};

	struct GfxWorldDraw
	{
		unsigned int reflectionProbeCount;
		GfxImage** reflectionProbes;
		GfxReflectionProbe* reflectionProbeOrigins;
		GfxTexture* reflectionProbeTextures;
		unsigned int reflectionProbeReferenceCount;
		GfxReflectionProbeReferenceOrigin* reflectionProbeReferenceOrigins;
		GfxReflectionProbeReference* reflectionProbeReferences;
		int lightmapCount;
		GfxLightmapArray* lightmaps;
		GfxTexture* lightmapPrimaryTextures;
		GfxTexture* lightmapSecondaryTextures;
		GfxImage* lightmapOverridePrimary;
		GfxImage* lightmapOverrideSecondary;
		unsigned int trisType;
		unsigned int vertexCount;
		GfxWorldVertexData vd;
		unsigned int vertexLayerDataSize;
		GfxWorldVertexLayerData vld;
		unsigned int indexCount;
		unsigned short* indices;
		ID3D11Buffer* indexBuffer;
	};

	struct GfxLightGridEntry
	{
		unsigned int colorsIndex;
		unsigned short primaryLightEnvIndex;
		unsigned char unused;
		unsigned char needsTrace;
	};

	struct GfxLightGridColors
	{
		unsigned char rgb[56][3];
	};

	struct GfxLightGridColorsHDR
	{
		float colorVec3[56][3];
	};

	struct GfxLightGridTree
	{
		unsigned char maxDepth;
		int nodeCount;
		int leafCount;
		int coordMinGridSpace[3];
		int coordMaxGridSpace[3];
		int coordHalfSizeGridSpace[3];
		int defaultColorIndexBitCount;
		int defaultLightIndexBitCount;
		unsigned int* p_nodeTable;
		int leafTableSize;
		unsigned char* p_leafTable;
	};

	struct GfxLightGrid
	{
		bool hasLightRegions;
		bool useSkyForLowZ;
		unsigned int lastSunPrimaryLightIndex;
		unsigned short mins[3];
		unsigned short maxs[3];
		unsigned int rowAxis;
		unsigned int colAxis;
		unsigned short* rowDataStart;
		unsigned int rawRowDataSize;
		unsigned char* rawRowData;
		unsigned int entryCount;
		GfxLightGridEntry* entries;
		unsigned int colorCount;
		GfxLightGridColors* colors;
		unsigned int missingGridColorIndex;
		int tableVersion;
		int paletteVersion;
		char rangeExponent8BitsEncoding;
		char rangeExponent12BitsEncoding;
		char rangeExponent16BitsEncoding;
		unsigned char stageCount;
		float* stageLightingContrastGain;
		unsigned int paletteEntryCount;
		int* paletteEntryAddress;
		unsigned int paletteBitstreamSize;
		unsigned char* paletteBitstream;
		GfxLightGridColorsHDR skyLightGridColors;
		GfxLightGridColorsHDR defaultLightGridColors;
		GfxLightGridTree tree;
	};

	struct GfxBrushModelWritable
	{
		Bounds bounds;
	};

	struct GfxBrushModel
	{
		GfxBrushModelWritable writable;
		Bounds bounds;
		float radius;
		unsigned int startSurfIndex;
		unsigned short surfaceCount;
	};

	struct MaterialMemory
	{
		Material* material;
		int memory;
	};

	struct sunflare_t
	{
		bool hasValidData;
		Material* spriteMaterial;
		Material* flareMaterial;
		float spriteSize;
		float flareMinSize;
		float flareMinDot;
		float flareMaxSize;
		float flareMaxDot;
		float flareMaxAlpha;
		int flareFadeInTime;
		int flareFadeOutTime;
		float blindMinDot;
		float blindMaxDot;
		float blindMaxDarken;
		int blindFadeInTime;
		int blindFadeOutTime;
		float glareMinDot;
		float glareMaxDot;
		float glareMaxLighten;
		int glareFadeInTime;
		int glareFadeOutTime;
		float sunFxPosition[3];
	};

	struct XModelDrawInfo
	{
		unsigned char hasGfxEntIndex;
		unsigned char lod;
		unsigned short surfId;
	};

	struct GfxSceneDynModel
	{
		XModelDrawInfo info;
		unsigned short dynEntId;
	};

	struct BModelDrawInfo
	{
		unsigned short surfId;
	};

	struct GfxSceneDynBrush
	{
		BModelDrawInfo info;
		unsigned short dynEntId;
	};

	struct GfxShadowGeometry
	{
		unsigned short surfaceCount;
		unsigned short smodelCount;
		unsigned int* sortedSurfIndex;
		unsigned short* smodelIndex;
	};

	struct GfxLightRegionAxis
	{
		float dir[3];
		float midPoint;
		float halfSize;
	};

	struct GfxLightRegionHull
	{
		float kdopMidPoint[9];
		float kdopHalfSize[9];
		unsigned int axisCount;
		GfxLightRegionAxis* axis;
	};

	struct GfxLightRegion
	{
		unsigned int hullCount;
		GfxLightRegionHull* hulls;
	};

	struct GfxStaticModelInst
	{
		Bounds bounds;
		float lightingOrigin[3];
	};

	struct srfTriangles_t
	{
		unsigned int vertexLayerData;
		unsigned int firstVertex;
		float maxEdgeLength;
		unsigned short vertexCount;
		unsigned short triCount;
		unsigned int baseIndex;
	};

	struct GfxSurfaceLightingAndFlagsFields
	{
		unsigned char lightmapIndex;
		unsigned char reflectionProbeIndex;
		unsigned short primaryLightEnvIndex;
		unsigned char flags;
		unsigned char unused[3];
	};

	union GfxSurfaceLightingAndFlags
	{
		GfxSurfaceLightingAndFlagsFields fields;
		unsigned __int64 packed;
	};

	struct GfxSurface
	{
		srfTriangles_t tris;
		Material* material;
		GfxSurfaceLightingAndFlags laf;
	};

	struct GfxSurfaceBounds
	{
		Bounds bounds;
		unsigned char flags;
		char __pad[8];
	};

	struct GfxPackedPlacement
	{
		float origin[3];
		float axis[3][3];
		float scale;
	};

	struct GfxStaticModelVertexLighting
	{
		unsigned char visibility[4];
		unsigned short ambientColorFloat16[4];
		unsigned short highlightColorFloat16[4];
	};

	struct GfxStaticModelVertexLightingInfo
	{
		GfxStaticModelVertexLighting* lightingValues;
		ID3D11Buffer* lightingValuesVb;
		ID3D11Buffer* lightingValuesSb;
		unsigned int subdiv_count_maybe;
		ID3D11Buffer* subDivCacheBuffer;
		ID3D11ShaderResourceView* subDivCacheViewBuffer;
		int flags;
		unsigned int numLightingValues;
	};

	struct GfxStaticModelLightmapInfo
	{
		float offset[2];
		float scale[2];
		unsigned int lightmapIndex;
	};

	struct GfxStaticModelDrawInst
	{
		GfxPackedPlacement placement;
		XModel* model;
		float groundLighting[4];
		GfxStaticModelVertexLightingInfo vertexLightingInfo;
		GfxStaticModelLightmapInfo modelLightmapInfo;
		unsigned short lightingHandle;
		unsigned short cullDist;
		unsigned short flags;
		unsigned short staticModelId;
		unsigned short primaryLightEnvIndex;
		unsigned char reflectionProbeIndex;
		unsigned char firstMtlSkinIndex;
		unsigned char sunShadowFlags;
	};

	struct GfxWorldDpvsStatic
	{
		unsigned int smodelCount; // 0
		unsigned int staticSurfaceCount; // 4
		unsigned int litOpaqueSurfsBegin; // 8
		unsigned int litOpaqueSurfsEnd; // 12
		unsigned int litDecalSurfsBegin; // 16
		unsigned int litDecalSurfsEnd; // 20
		unsigned int litTransSurfsBegin; // 24
		unsigned int litTransSurfsEnd; // 28
		unsigned int shadowCasterSurfsBegin; // 32
		unsigned int shadowCasterSurfsEnd; // 36
		unsigned int emissiveSurfsBegin; // 40
		unsigned int emissiveSurfsEnd; // 44
		unsigned int smodelVisDataCount; // 48
		unsigned int surfaceVisDataCount; // 52
		unsigned int* smodelVisData[3]; // 56
		unsigned int* surfaceVisData[3]; // 80
		unsigned int* tessellationCutoffVisData[3]; // 104
		unsigned int* unknownData[3]; // 128
		unsigned int* lodData; // 152
		unsigned int* unknownData2[3]; // 160
		unsigned int* sortedSurfIndex; // 184
		GfxStaticModelInst* smodelInsts; // 192
		GfxSurface* surfaces; // 200
		GfxSurfaceBounds* surfacesBounds; // 208
		GfxStaticModelDrawInst* smodelDrawInsts; // 216
		GfxDrawSurf* surfaceMaterials; // 224
		unsigned int* surfaceCastsSunShadow; // 232
		unsigned int sunShadowOptCount; // 240
		unsigned int sunSurfVisDataCount; // 244
		unsigned int* surfaceCastsSunShadowOpt; // 248
		char** constantBuffersLit; // 256
		char** constantBuffersAmbient; // 264
		volatile int usageCount; // 272
	};

	struct GfxWorldDpvsDynamic
	{
		unsigned int dynEntClientWordCount[2];
		unsigned int dynEntClientCount[2];
		unsigned int* dynEntCellBits[2];
		unsigned char* dynEntVisData[2][3];
	};

	struct GfxHeroOnlyLight
	{
		unsigned char type;
		unsigned char unused[3];
		float color[3];
		float dir[3];
		float up[3];
		float origin[3];
		float radius;
		float cosHalfFovOuter;
		float cosHalfFovInner;
		int exponent;
	};

	typedef void* umbraTomePtr_t;

	enum FogTypes : std::int8_t
	{
		FOG_NORMAL = 0x1,
		FOG_DFOG = 0x2,
	};

	struct GfxWorld
	{
		const char* name; // 0
		const char* baseName; // 8
		unsigned int bspVersion; // 16
		int planeCount; // 20
		int nodeCount; // 24
		unsigned int surfaceCount; // 28
		int skyCount; // 32
		GfxSky* skies; // 40
		unsigned int lastSunPrimaryLightIndex; // 48
		unsigned int primaryLightCount; // 52
		unsigned int primaryLightEnvCount; // 56
		unsigned int sortKeyLitDecal; // 60
		unsigned int sortKeyEffectDecal; // 64
		unsigned int sortKeyTopDecal; // 68
		unsigned int sortKeyEffectAuto; // 72
		unsigned int sortKeyDistortion; // 76
		GfxWorldDpvsPlanes dpvsPlanes; // 80
		GfxCellTreeCount* aabbTreeCounts; // 112
		GfxCellTree* aabbTrees; // 120
		GfxCell* cells; // 128
		GfxWorldDraw draw; // 136
		GfxLightGrid lightGrid; // 312
		int modelCount; // 1880
		GfxBrushModel* models; // 1888
		Bounds bounds; // 1896
		unsigned int checksum; // 1920
		int materialMemoryCount; // 1924
		MaterialMemory* materialMemory; // 1928
		sunflare_t sun; // 1936
		float outdoorLookupMatrix[4][4]; // 2160
		GfxImage* outdoorImage; // 2176
		unsigned int* cellCasterBits; // 2120
		unsigned int* cellHasSunLitSurfsBits; // 2128
		GfxSceneDynModel* sceneDynModel; // 2136
		GfxSceneDynBrush* sceneDynBrush; // 2144
		unsigned int* primaryLightEntityShadowVis; // 2152
		unsigned int* primaryLightDynEntShadowVis[2]; // 2160
		unsigned short* nonSunPrimaryLightForModelDynEnt; // 2176
		GfxShadowGeometry* shadowGeom; // 2184
		GfxShadowGeometry* shadowGeomOptimized; // 2192
		GfxLightRegion* lightRegion; // 2200
		GfxWorldDpvsStatic dpvs; // 2208
		GfxWorldDpvsDynamic dpvsDyn; // 2488
		unsigned int mapVtxChecksum; // 2512
		unsigned int heroOnlyLightCount; // 2520
		GfxHeroOnlyLight* heroOnlyLights; // 2520
		unsigned char fogTypesAllowed; // 2528
		unsigned int umbraTomeSize; // 2588
		char* umbraTomeData; // 2592
		umbraTomePtr_t umbraTomePtr; // 2600
	};

	struct ClipMaterial
	{
		const char* name;
		int surfaceFlags;
		int contents;
	};

	struct cLeafBrushNodeLeaf_t
	{
		unsigned short* brushes;
	};

	struct cLeafBrushNodeChildren_t
	{
		float dist;
		float range;
		unsigned short childOffset[2];
	};

	union cLeafBrushNodeData_t
	{
		cLeafBrushNodeLeaf_t leaf;
		cLeafBrushNodeChildren_t children;
	};

	struct cLeafBrushNode_s
	{
		unsigned char axis;
		short leafBrushCount;
		int contents;
		cLeafBrushNodeData_t data;
	};

	struct ClipInfo
	{
		int planeCount;
		cplane_s* planes;
		unsigned int numMaterials;
		ClipMaterial* materials;
		unsigned int numBrushSides;
		cbrushside_t* brushsides;
		unsigned int numBrushEdges;
		cbrushedge_t* brushEdges;
		unsigned int leafbrushNodesCount;
		cLeafBrushNode_s* leafbrushNodes;
		unsigned int numLeafBrushes;
		unsigned short* leafbrushes;
		unsigned short numBrushes;
		cbrush_t* brushes;
		Bounds* brushBounds;
		int* brushContents;
	};

	struct cStaticModel_s
	{
		XModel* xmodel;
		float origin[3];
		float invScaledAxis[3][3];
		Bounds absBounds;
	};

	struct cNode_t
	{
		cplane_s* plane;
		short children[2];
	};

	struct cLeaf_t
	{
		unsigned short firstCollAabbIndex;
		unsigned short collAabbCount;
		int brushContents;
		int terrainContents;
		Bounds bounds;
		int leafBrushNode;
	};

	struct CollisionBorder
	{
		float distEq[3];
		float zBase;
		float zSlope;
		float start;
		float length;
	};

	struct CollisionPartition
	{
		unsigned char triCount;
		unsigned char borderCount;
		unsigned char firstVertSegment;
		int firstTri;
		CollisionBorder* borders;
	};

	union CollisionAabbTreeIndex
	{
		int firstChildIndex;
		int partitionIndex;
	};

	struct CollisionAabbTree
	{
		float midPoint[3];
		unsigned short materialIndex;
		unsigned short childCount;
		float halfSize[3];
		CollisionAabbTreeIndex u;
	};

	struct cmodel_t
	{
		Bounds bounds;
		float radius;
		ClipInfo* info;
		cLeaf_t leaf;
	};

	struct Stage
	{
		const char* name;
		float origin[3];
		unsigned short triggerIndex;
		unsigned char sunPrimaryLightIndex;
	};

	struct SModelAabbNode
	{
		Bounds bounds;
		unsigned short firstChild;
		unsigned short childCount;
	};

	enum DynEntityType : int
	{
		DYNENT_TYPE_INVALID = 0x0,
		DYNENT_TYPE_CLUTTER = 0x1,
		DYNENT_TYPE_DESTRUCT = 0x2,
		DYNENT_TYPE_HINGE = 0x3,
		DYNENT_TYPE_SCRIPTABLEINST = 0x4,
		DYNENT_TYPE_SCRIPTABLEPHYSICS = 0x5,
		DYNENT_TYPE_LINKED = 0x6,
		DYNENT_TYPE_LINKED_NOSHADOW = 0x7,
		DYNENT_TYPE_COUNT = 0x8,
	};

	struct GfxPlacement
	{
		float quat[4];
		float origin[3];
	};

	struct DynEntityHingeDef
	{
		float axisOrigin[3];
		float axisDir[3];
		bool isLimited;
		float angleMin;
		float angleMax;
		float momentOfInertia;
		float friction;
	};

	struct DynEntityLinkToDef
	{
		int anchorIndex;
		float originOffset[3];
		float angleOffset[3];
	};

	struct DynEntityDef
	{
		DynEntityType type;
		GfxPlacement pose;
		XModel* baseModel; //const XModel* baseModel;
		unsigned short brushModel;
		unsigned short physicsBrushModel;
		unsigned short scriptableIndex;
		unsigned short health;
		FxEffectDef* destroyFx; //const FxEffectDef* destroyFx;
		PhysPreset* physPreset;
		DynEntityHingeDef* hinge;
		DynEntityLinkToDef* linkTo;
		PhysMass mass;
		int contents;
	};

	struct DynEntityPose
	{
		GfxPlacement pose;
		float radius;
	};

	struct Hinge
	{
		float angle;
		float quat[4];
		float angularVel;
		float torqueAccum;
		bool active;
		float autoDisableTimeLeft;
		DynEntityHingeDef* def; //const DynEntityHingeDef* def;
		PhysPreset* physPreset; //const PhysPreset* physPreset;
		float centerOfMassRelToAxisOriginAtAngleZero[3];
	};

	struct DynEntityClient
	{
		__int64 physObjId;
		unsigned short flags;
		unsigned short lightingHandle;
		unsigned short health;
		Hinge* hinge;
		XModel* activeModel; //const XModel* activeModel;
		int contents;
	};

	struct DynEntityColl
	{
		unsigned short sector;
		unsigned short nextEntInSector;
		float linkMins[2];
		float linkMaxs[2];
	};

	enum ScriptableEventType : int
	{
		SCRIPTABLE_EVENT_MODEL = 0x0,
		SCRIPTABLE_EVENT_FX = 0x1,
		SCRIPTABLE_EVENT_SOUND = 0x2,
		SCRIPTABLE_EVENT_ANIMATION = 0x3,
		SCRIPTABLE_EVENT_EXPLODE = 0x4,
		SCRIPTABLE_EVENT_HEALTHDRAIN = 0x5,
		SCRIPTABLE_EVENT_PHYSICSLAUNCH = 0x6,
		SCRIPTABLE_EVENT_LIGHTSETTINGS = 0x7,
		SCRIPTABLE_EVENT_SUNLIGHTSETTINGS = 0x8,
		SCRIPTABLE_EVENT_SHAKE = 0x9,
		SCRIPTABLE_EVENT_STATECHANGE = 0xA,
		SCRIPTABLE_EVENT_COUNT = 0xB,
	};

	struct ScriptableEventStateChangeDef
	{
		unsigned char targetIndex;
		unsigned char delayStreamIndex;
		unsigned short delayMin;
		unsigned short delayMax;
	};

	struct ScriptableEventModelDef
	{
		XModel* model;
	};

	struct ScriptableEventFxDef
	{
		FxEffectDef* handle; //const FxEffectDef* handle;
		scr_string_t tagName;
		unsigned short loopTime;
		unsigned char loopTimeStreamIndex;
		bool tagUseAngles;
	};

	struct ScriptableEventSoundDef
	{
		snd_alias_list_t* alias;
		bool looping;
	};

	struct ScriptableEventAnimationDef
	{
		const char* animName;
		bool override;
		bool stateful;
		unsigned char animEntryIndex;
		unsigned char animPlaybackStreamIndex;
		unsigned short timeOffsetMin;
		unsigned short timeOffsetMax;
		unsigned short playbackRateMin;
		unsigned short playbackRateMax;
		unsigned short blendTime;
	};

	struct ScriptableEventExplodeDef
	{
		unsigned short forceMin;
		unsigned short forceMax;
		unsigned short radius;
		unsigned short damageMin;
		unsigned short damageMax;
		bool aiAvoid;
	};

	struct ScriptableEventHealthDef
	{
		unsigned short amount;
		unsigned short interval;
		unsigned short badPlaceRadius;
		unsigned char streamIndex;
	};

	struct ScriptableEventPhysicsDef
	{
		XModel* model;
		unsigned char launchDirX;
		unsigned char launchDirY;
		unsigned char launchDirZ;
		unsigned short explForceScale;
		unsigned short bulletForceScale;
	};

	struct ScriptableEventLightSettingsDef
	{
		unsigned char color[4];
		unsigned char lightIndexConstIndex;
		unsigned char transStateStreamIndex;
		unsigned char useColor;
		unsigned char useStateTransitionTime;
		unsigned short intensityScaleMin;
		unsigned short intensityScaleMax;
		unsigned short radiusScaleMin;
		unsigned short radiusScaleMax;
		const char* noteworthy;
		unsigned short transitionTimeMin;
		unsigned short transitionTimeMax;
	};

	struct ScriptableEventSunlightSettingsDef
	{
		unsigned char color[4];
		unsigned char transStateStreamIndex;
		unsigned char flags;
		unsigned short intensityScaleMin;
		unsigned short intensityScaleMax;
		unsigned short pitchMin;
		unsigned short pitchMax;
		unsigned short headingMin;
		unsigned short headingMax;
		unsigned short transitionTimeMin;
		unsigned short transitionTimeMax;
	};

	struct ScriptableEventShakeDef
	{
		const char* rumbleName;
		unsigned short duration;
		unsigned short durationFadeUp;
		unsigned short durationFadeDown;
		unsigned short radius;
		unsigned short exponent;
		unsigned short scaleEarthquake;
		unsigned char scalePitch;
		unsigned char scaleYaw;
		unsigned char scaleRoll;
		unsigned char frequencyPitch;
		unsigned char frequencyYaw;
		unsigned char frequencyRoll;
		unsigned char flags;
	};

	union ScriptableEventDataUnion
	{
		ScriptableEventStateChangeDef stateChange;
		ScriptableEventModelDef setModel;
		ScriptableEventFxDef playFx;
		ScriptableEventSoundDef playSound;
		ScriptableEventAnimationDef playAnim;
		ScriptableEventExplodeDef doExplosion;
		ScriptableEventHealthDef healthDrain;
		ScriptableEventPhysicsDef physicsLaunch;
		ScriptableEventLightSettingsDef lightSettings;
		ScriptableEventSunlightSettingsDef sunlightSettings;
		ScriptableEventShakeDef shake;
	};

	struct ScriptableEventDef
	{
		ScriptableEventType type;
		ScriptableEventDataUnion data;
	};

	struct ScriptableStateDef
	{
		scr_string_t name;
		scr_string_t tagName;
		ScriptableEventDef* onEnterEvents;
		unsigned char onEnterEventCount;
		unsigned char damageFlags;
		unsigned char damageParentTransferRate;
		unsigned char damageParentReceiveRate;
		unsigned short maxHealth;
	};

	struct ScriptablePartDef
	{
		ScriptableStateDef* states;
		scr_string_t name;
		unsigned char stateCount;
		unsigned char flags;
		unsigned char eventStreamTimeRemainIndex;
		unsigned char eventStreamNextChangeTimeIndex;
	};

	enum ScriptableNotetrackType : int
	{
		SCRIPTABLE_NT_FX = 0x0,
		SCRIPTABLE_NT_SOUND = 0x1,
		SCRIPTABLE_NT_COUNT = 0x2,
	};

	struct ScriptableNotetrackFxDef
	{
		FxEffectDef* handle; //const FxEffectDef* handle;
		scr_string_t tagName;
		bool useAngles;
	};

	struct ScriptableNotetrackSoundDef
	{
		snd_alias_list_t* alias;
	};

	union ScriptableNotetrackDataUnion
	{
		ScriptableNotetrackFxDef playFx;
		ScriptableNotetrackSoundDef playSound;
	};

	struct ScriptableNotetrackDef
	{
		scr_string_t name;
		ScriptableNotetrackType type;
		ScriptableNotetrackDataUnion data;
	};

	enum ScriptableType : int
	{
		SCRIPTABLE_TYPE_GENERAL = 0x0,
		SCRIPTABLE_TYPE_CHARACTER = 0x1,
		SCRIPTABLE_TYPE_COUNT = 0x2,
	};

	struct ScriptableDef
	{
		const char* name;
		XModel* baseModel;
		const char* baseCollisionBrush;
		const char* destroyedCollisionBrush;
		ScriptablePartDef* parts;
		ScriptableNotetrackDef* notetracks;
		ScriptableType type;
		unsigned char flags;
		unsigned char partCount;
		unsigned char serverInstancePartCount;
		unsigned char serverControlledPartCount;
		unsigned char notetrackCount;
		unsigned char eventStreamSize;
		unsigned char eventConstantsSize;
	};

	struct ScriptableInstancePartState
	{
		unsigned short curHealth;
		unsigned char lastExecutedStateIndex;
		unsigned char stateIndex;
	};

	struct ScriptableInstance
	{
		ScriptableDef* def;
		unsigned char* eventConstantsBuf;
		float origin[3];
		float angles[3];
		scr_string_t targetname;
		unsigned short preBrushModel;
		unsigned short postBrushModel;
		unsigned char flags;
		XModel* currentModel;
		ScriptableInstancePartState* partStates;
		unsigned char* eventStreamBuf;
		unsigned int currentPartBits[8];
		unsigned int damageOwnerEntHandle;
		unsigned short updateNextInstance;
		unsigned short linkedObject;
	};

	struct ScriptableAnimationEntry
	{
		const char* animName;
		unsigned __int64 runtimeBuf;
	};

	struct ScriptableMapEnts
	{
		unsigned int instanceStateSize;
		unsigned int instanceCount;
		unsigned int reservedInstanceCount;
		ScriptableInstance* instances;
		unsigned int animEntryCount;
		ScriptableAnimationEntry* animEntries;
		unsigned int replicatedInstanceCount;
	};

	struct clipMap_t // alignas(128)
	{
		const char* name;
		int isInUse;
		ClipInfo info;
		ClipInfo* pInfo;
		unsigned int numStaticModels;
		cStaticModel_s* staticModelList;
		unsigned int numNodes;
		cNode_t* nodes;
		unsigned int numLeafs;
		cLeaf_t* leafs;
		unsigned int vertCount;
		vec3_t* verts; //float(*verts)[3];
		int triCount;
		unsigned short* triIndices;
		unsigned char* triEdgeIsWalkable;
		int borderCount;
		CollisionBorder* borders;
		int partitionCount;
		CollisionPartition* partitions;
		int aabbTreeCount;
		CollisionAabbTree* aabbTrees;
		unsigned int numSubModels;
		cmodel_t* cmodels;
		MapEnts* mapEnts;
		Stage* stages;
		unsigned char stageCount;
		MapTriggers stageTrigger;
		unsigned short smodelNodeCount;
		SModelAabbNode* smodelNodes;
		unsigned short dynEntCount[2];
		DynEntityDef* dynEntDefList[2];
		DynEntityPose* dynEntPoseList[2];
		DynEntityClient* dynEntClientList[2];
		DynEntityColl* dynEntCollList[2];
		unsigned int dynEntAnchorCount;
		scr_string_t* dynEntAnchorNames;
		ScriptableMapEnts scriptableMapEnts;
		unsigned int checksum;
		char __pad[108]; // alignment padding
	};

	struct Font_s
	{
		union
		{
			const char* fontName;
			const char* name;
		};
		int pixelHeight;
		int glyphCount;
		Material* material;
		Material* glowMaterial;
		Glyph* glyphs;
	};

	struct LocalizeEntry
	{
		const char* value;
		const char* name;
	};

	struct FxFloatRange
	{
		float base;
		float amplitude;
	};

	struct FxSpawnDefLooping
	{
		int intervalMsec;
		int count;
	};

	struct FxIntRange
	{
		int base;
		int amplitude;
	};

	struct FxSpawnDefOneShot
	{
		FxIntRange count;
	};

	union FxSpawnDef
	{
		FxSpawnDefLooping looping;
		FxSpawnDefOneShot oneShot;
	};

	struct FxElemAtlas
	{
		unsigned char behavior;
		unsigned char index;
		unsigned char fps;
		unsigned char loopCount;
		unsigned char colIndexBits;
		unsigned char rowIndexBits;
		short entryCount;
	};

	struct FxEffectDef;
	union FxEffectDefRef
	{
		FxEffectDef* handle;
		const char* name;
	};

	struct FxElemVec3Range
	{
		float base[3];
		float amplitude[3];
	};

	struct FxElemVelStateInFrame
	{
		FxElemVec3Range velocity;
		FxElemVec3Range totalDelta;
	};

	const struct FxElemVelStateSample
	{
		FxElemVelStateInFrame local;
		FxElemVelStateInFrame world;
	};

	struct FxElemVisualState
	{
		float color[4];
		float unlitHDRScale;
		float rotationDelta;
		float rotationTotal;
		float size[2];
		float scale;
	};

	const struct FxElemVisStateSample
	{
		FxElemVisualState base;
		FxElemVisualState amplitude;
	};

	struct FxParticleSimAnimationHeader
	{
		float playbackRate;
		float duration;
		unsigned int frameCount;
		float minX;
		float minY;
		float minZ;
		float boundsXDelta;
		float boundsYDelta;
		float boundsZDelta;
		float maxWidth;
		float maxHeight;
		unsigned int colorTableSize;
		unsigned int particleDataCount;
		bool evalVisStatePerParticle;
		bool sortParticlesAtRuntime;
	};

	struct FxParticleSimAnimationParticleData
	{
		unsigned short xNormalizedPos;
		unsigned short yNormalizedPos;
		unsigned short zNormalizedPos;
		unsigned short xNormalizedWidth;
		unsigned short yNormalizedHeight;
		unsigned short orientation;
		unsigned short lifetime;
		unsigned short particleID;
		unsigned short xNormalizedPosNextFrame;
		unsigned short yNormalizedPosNextFrame;
		unsigned short zNormalizedPosNextFrame;
		unsigned short xNormalizedWidthNextFrame;
		unsigned short yNormalizedHeightNextFrame;
		short orientationDelta;
		unsigned short colorTableIndex;
		unsigned short nextColorTableIndex;
	};

	struct FxParticleSimAnimationFrame
	{
		unsigned int particleDataOffset;
		unsigned int numActiveParticles;
	};

	struct FxParticleSimAnimation
	{
		const char* name;
		Material* material;
		FxParticleSimAnimationHeader header;
		FxParticleSimAnimationParticleData* particleData;
		FxParticleSimAnimationFrame* frames;
		GfxColorFloat* colorTable;
	};

	union FxElemVisuals
	{
		const void* anonymous;
		Material* material;
		XModel* model;
		FxEffectDefRef effectDef;
		const char* soundName;
		const char* vectorFieldName;
		GfxLightDef* lightDef;
		FxParticleSimAnimation* particleSimAnimation;
	};

	struct FxElemMarkVisuals
	{
		Material* materials[3];
	};

	union FxElemDefVisuals
	{
		FxElemMarkVisuals* markArray;
		FxElemVisuals* array;
		FxElemVisuals instance;
	};

	struct FxTrailVertex
	{
		float pos[2];
		float normal[2];
		float texCoord[2];
	};

	struct FxTrailDef
	{
		int scrollTimeMsec;
		int repeatDist;
		float invSplitDist;
		float invSplitArcDist;
		float invSplitTime;
		int vertCount;
		FxTrailVertex* verts;
		int indCount;
		unsigned short* inds;
	};

	struct FxSparkFountainDef
	{
		float gravity;
		float bounceFrac;
		float bounceRand;
		float sparkSpacing;
		float sparkLength;
		int sparkCount;
		float loopTime;
		float velMin;
		float velMax;
		float velConeFrac;
		float restSpeed;
		float boostTime;
		float boostFactor;
	};

	struct FxSpotLightDef
	{
		float fovInnerFraction;
		float startRadius;
		float endRadius;
		float brightness;
		float maxLength;
		int exponent;
	};

	struct FxFlareDef
	{
		float position;
		int angularRotCount;
		int flags;
		FxFloatRange depthScaleRange;
		FxFloatRange depthScaleValue;
		FxFloatRange radialRot;
		FxFloatRange radialScaleX;
		FxFloatRange radialScaleY;
		float dir[3];
		int intensityXIntervalCount;
		int intensityYIntervalCount;
		int srcCosIntensityIntervalCount;
		int srcCosScaleIntervalCount;
		float* intensityX;
		float* intensityY;
		float* srcCosIntensity;
		float* srcCosScale;
	};

	union FxElemExtendedDefPtr
	{
		FxTrailDef* trailDef;
		FxSparkFountainDef* sparkFountainDef;
		FxSpotLightDef* spotLightDef;
		FxFlareDef* flareDef;
		char* unknownDef;
	};

	const struct FxElemDef
	{
		int flags;
		int flags2;
		FxSpawnDef spawn;
		FxFloatRange spawnRange;
		FxFloatRange fadeInRange;
		FxFloatRange fadeOutRange;
		float spawnFrustumCullRadius;
		FxIntRange spawnDelayMsec;
		FxIntRange lifeSpanMsec;
		FxFloatRange spawnOrigin[3];
		FxFloatRange spawnOffsetRadius;
		FxFloatRange spawnOffsetHeight;
		FxFloatRange spawnAngles[3];
		FxFloatRange angularVelocity[3];
		FxFloatRange initialRotation;
		FxFloatRange gravity;
		FxFloatRange reflectionFactor;
		FxElemAtlas atlas;
		unsigned char elemType;
		unsigned char elemLitType;
		unsigned char visualCount;
		unsigned char velIntervalCount;
		unsigned char visStateIntervalCount;
		FxElemVelStateSample* velSamples;
		FxElemVisStateSample* visSamples;
		FxElemDefVisuals visuals;
		Bounds collBounds;
		FxEffectDefRef effectOnImpact;
		FxEffectDefRef effectOnDeath;
		FxEffectDefRef effectEmitted;
		FxFloatRange emitDist;
		FxFloatRange emitDistVariance;
		FxElemExtendedDefPtr extended;
		unsigned char sortOrder;
		unsigned char lightingFrac;
		unsigned char useItemClip;
		unsigned char fadeInfo;
		int randomSeed;
		float litMaxColorChangePerSec;
		float unlitHDRScalar;
		float litHDRScalar;
		float litUnlitBlendFactor;
	};

	struct FxEffectDef
	{
		const char* name;
		int flags;
		int totalSize;
		int msecLoopingLife;
		int elemDefCountLooping;
		int elemDefCountOneShot;
		int elemDefCountEmission;
		float elemMaxRadius;
		float occlusionQueryDepthBias;
		int occlusionQueryFadeIn;
		int occlusionQueryFadeOut;
		FxFloatRange occlusionQueryScaleRange;
		FxElemDef* elemDefs;
	};

	enum weaponIconRatioType_t : std::int32_t
	{
		WEAPON_ICON_RATIO_1TO1 = 0x0,
		WEAPON_ICON_RATIO_2TO1 = 0x1,
		WEAPON_ICON_RATIO_4TO1 = 0x2,
		WEAPON_ICON_RATIO_COUNT = 0x3,
	};

	enum ammoCounterClipType_t : std::int32_t
	{
		AMMO_COUNTER_CLIP_NONE = 0x0,
		AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
		AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
		AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
		AMMO_COUNTER_CLIP_ROCKET = 0x4,
		AMMO_COUNTER_CLIP_BELTFED = 0x5,
		AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
		AMMO_COUNTER_CLIP_COUNT = 0x7,
	};

	enum ImpactType : std::int32_t
	{
		IMPACT_TYPE_NONE = 0x0,
		IMPACT_TYPE_BULLET_SMALL = 0x1,
		IMPACT_TYPE_BULLET_LARGE = 0x2,
		IMPACT_TYPE_BULLET_AP = 0x3,
		IMPACT_TYPE_BULLET_EXPLODE = 0x4,
		IMPACT_TYPE_SHOTGUN = 0x5,
		IMPACT_TYPE_SHOTGUN_EXPLODE = 0x6,
		IMPACT_TYPE_GRENADE_BOUNCE = 0x7,
		IMPACT_TYPE_GRENADE_EXPLODE = 0x8,
		IMPACT_TYPE_ROCKET_EXPLODE = 0x9,
		IMPACT_TYPE_PROJECTILE_DUD = 0xA,
		IMPACT_TYPE_COUNT = 0xB,
	};

	enum weapType_t : std::int32_t
	{
		WEAPTYPE_NONE = 0x0,
		WEAPTYPE_BULLET = 0x1,
		WEAPTYPE_GRENADE = 0x2,
		WEAPTYPE_PROJECTILE = 0x3,
		WEAPTYPE_RIOTSHIELD = 0x4,
		WEAPTYPE_NUM = 0x5,
	};

	enum weapClass_t : std::int32_t
	{
		WEAPCLASS_RIFLE = 0x0,
		WEAPCLASS_SNIPER = 0x1,
		WEAPCLASS_MG = 0x2,
		WEAPCLASS_SMG = 0x3,
		WEAPCLASS_SPREAD = 0x4,
		WEAPCLASS_PISTOL = 0x5,
		WEAPCLASS_GRENADE = 0x6,
		WEAPCLASS_ROCKETLAUNCHER = 0x7,
		WEAPCLASS_TURRET = 0x8,
		WEAPCLASS_THROWINGKNIFE = 0x9,
		WEAPCLASS_NON_PLAYER = 0xA,
		WEAPCLASS_ITEM = 0xB,
		WEAPCLASS_NUM = 0xC,
	};

	enum PenetrateType : std::int32_t
	{
		PENETRATE_TYPE_NONE = 0x0,
		PENETRATE_TYPE_SMALL = 0x1,
		PENETRATE_TYPE_MEDIUM = 0x2,
		PENETRATE_TYPE_LARGE = 0x3,
		PENETRATE_TYPE_COUNT = 0x4,
	};

	enum weapInventoryType_t : std::int32_t
	{
		WEAPINVENTORY_PRIMARY = 0x0,
		WEAPINVENTORY_OFFHAND = 0x1,
		WEAPINVENTORY_ITEM = 0x2,
		WEAPINVENTORY_ALTMODE = 0x3,
		WEAPINVENTORY_EXCLUSIVE = 0x4,
		WEAPINVENTORY_SCAVENGER = 0x5,
		WEAPINVENTORYCOUNT = 0x6,
	};

	enum weapFireType_t : std::int32_t
	{
		WEAPON_FIRETYPE_FULLAUTO = 0x0,
		WEAPON_FIRETYPE_SINGLESHOT = 0x1,
		WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
		WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
		WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
		WEAPON_FIRETYPE_DOUBLEBARREL = 0x5,
		WEAPON_FIRETYPECOUNT = 0x6,
		WEAPON_FIRETYPE_BURSTFIRE_FIRST = 0x2,
		WEAPON_FIRETYPE_BURSTFIRE_LAST = 0x4,
	};

	enum OffhandClass : std::int32_t
	{
		OFFHAND_CLASS_NONE = 0x0,
		OFFHAND_CLASS_FRAG_GRENADE = 0x1,
		OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
		OFFHAND_CLASS_FLASH_GRENADE = 0x3,
		OFFHAND_CLASS_THROWINGKNIFE = 0x4,
		OFFHAND_CLASS_OTHER = 0x5,
		OFFHAND_CLASS_COUNT = 0x6,
	};

	enum weapStance_t : std::int32_t
	{
		WEAPSTANCE_STAND = 0x0,
		WEAPSTANCE_DUCK = 0x1,
		WEAPSTANCE_PRONE = 0x2,
		WEAPSTANCE_NUM = 0x3,
	};

	enum activeReticleType_t : std::int32_t
	{
		VEH_ACTIVE_RETICLE_NONE = 0x0,
		VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
		VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
		VEH_ACTIVE_RETICLE_COUNT = 0x3,
	};

	enum weapOverlayReticle_t : std::int32_t
	{
		WEAPOVERLAYRETICLE_NONE = 0x0,
		WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
		WEAPOVERLAYRETICLE_NUM = 0x2,
	};

	enum WeapOverlayInteface_t : std::int32_t
	{
		WEAPOVERLAYINTERFACE_NONE = 0x0,
		WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
		WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
		WEAPOVERLAYINTERFACECOUNT = 0x3,
	};

	enum weapProjExposion_t : std::int32_t
	{
		WEAPPROJEXP_GRENADE = 0x0,
		WEAPPROJEXP_ROCKET = 0x1,
		WEAPPROJEXP_FLASHBANG = 0x2,
		WEAPPROJEXP_NONE = 0x3,
		WEAPPROJEXP_DUD = 0x4,
		WEAPPROJEXP_SMOKE = 0x5,
		WEAPPROJEXP_HEAVY = 0x6,
		WEAPPROJEXP_NUM = 0x7,
	};

	enum WeapStickinessType : std::int32_t
	{
		WEAPSTICKINESS_NONE = 0x0,
		WEAPSTICKINESS_ALL = 0x1,
		WEAPSTICKINESS_ALL_ORIENT = 0x2,
		WEAPSTICKINESS_GROUND = 0x3,
		WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
		WEAPSTICKINESS_KNIFE = 0x5,
		WEAPSTICKINESS_COUNT = 0x6,
	};

	enum guidedMissileType_t : std::int32_t
	{
		MISSILE_GUIDANCE_NONE = 0x0,
		MISSILE_GUIDANCE_SIDEWINDER = 0x1,
		MISSILE_GUIDANCE_HELLFIRE = 0x2,
		MISSILE_GUIDANCE_JAVELIN = 0x3,
		MISSILE_GUIDANCE_COUNT = 0x4,
	};

	struct StateTimers
	{
		int iFireDelay;
		int iMeleeDelay;
		int meleeChargeDelay;
		int iDetonateDelay;
		int iRechamberTime;
		int rechamberTimeOneHanded;
		int iRechamberBoltTime;
		int iHoldFireTime;
		int iHoldPrimeTime;
		int iDetonateTime;
		int iMeleeTime;
		int meleeChargeTime;
		int iReloadTime;
		int reloadShowRocketTime;
		int iReloadEmptyTime;
		int iReloadAddTime;
		int iReloadEmptyAddTime;
		int iReloadStartTime;
		int iReloadStartAddTime;
		int iReloadEndTime;
		int iDropTime;
		int iRaiseTime;
		int iAltDropTime;
		int quickDropTime;
		int quickRaiseTime;
		int iBreachRaiseTime;
		int iEmptyRaiseTime;
		int iEmptyDropTime;
		int sprintInTime;
		int sprintLoopTime;
		int sprintOutTime;
		int stunnedTimeBegin;
		int stunnedTimeLoop;
		int stunnedTimeEnd;
		int nightVisionWearTime;
		int nightVisionWearTimeFadeOutEnd;
		int nightVisionWearTimePowerUp;
		int nightVisionRemoveTime;
		int nightVisionRemoveTimePowerDown;
		int nightVisionRemoveTimeFadeInStart;
		int fuseTime;
		int aiFuseTime;
		int primeTime;
		bool bHoldFullPrime;
		int blastFrontTime;
		int blastRightTime;
		int blastBackTime;
		int blastLeftTime;
		int slideInTime;
		int slideLoopTime;
		int slideOutTime;
	};

	struct ADSOverlay
	{
		Material* shader;
		Material* shaderLowRes;
		Material* shaderEMP;
		Material* shaderEMPLowRes;
		weapOverlayReticle_t reticle;
		float width;
		float height;
		float widthSplitscreen;
		float heightSplitscreen;
	};

	struct TracerDef
	{
		const char* name;
		Material* material;
		unsigned int drawInterval;
		float speed;
		float beamLength;
		float beamWidth;
		float screwRadius;
		float screwDist;
		float colors[5][4];
	};

	struct AddonMapEnts
	{
		const char* name;
		char* entityString;
		int numEntityChars;
		MapTriggers trigger;
		ClipInfo* info;
		unsigned int numSubModels;
		cmodel_t* cmodels;
		GfxBrushModel* models;
	};

	enum weapAltModels_t : int
	{
		WEAP_ALT_MODEL0 = 0x0,
		WEAP_ALT_MODEL1 = 0x1,
		WEAP_ALT_MODEL2 = 0x2,
		WEAP_ALT_MODEL3 = 0x3,
		WEAP_ALT_MODEL4 = 0x4,
		WEAP_ALT_MODEL5 = 0x5,
		WEAP_ALT_MODEL6 = 0x6,
		WEAP_ALT_MODEL7 = 0x7,
		WEAP_ALT_MODEL8 = 0x8,
		WEAP_ALT_MODEL9 = 0x9,
		WEAP_ALT_MODEL10 = 0xA,
		WEAP_ALT_MODEL11 = 0xB,
		WEAP_ALT_MODEL12 = 0xC,
		WEAP_ALT_MODEL13 = 0xD,
		WEAP_ALT_MODEL14 = 0xE,
		WEAP_ALT_MODEL15 = 0xF,
		WEAP_ALT_MODEL16 = 0x10,
		WEAP_ALT_MODEL17 = 0x11,
		WEAP_ALT_MODEL18 = 0x12,
		WEAP_ALT_MODEL19 = 0x13,
		WEAP_ALT_MODEL20 = 0x14,
		WEAP_ALT_MODEL21 = 0x15,
		WEAP_ALT_MODEL22 = 0x16,
		WEAP_ALT_MODEL23 = 0x17,
		WEAP_ALT_MODEL24 = 0x18,
		WEAP_ALT_MODEL25 = 0x19,
		WEAP_ALT_MODEL26 = 0x1A,
		WEAP_ALT_MODEL27 = 0x1B,
		WEAP_ALT_MODEL28 = 0x1C,
		WEAP_ALT_MODEL29 = 0x1D,
		WEAP_ALT_MODEL30 = 0x1E,
		WEAP_ALT_MODEL31 = 0x1F,
		WEAP_ALT_MODEL32 = 0x20,
		WEAP_ALT_MODEL33 = 0x21,
		WEAP_ALT_MODEL34 = 0x22,
		WEAP_ALT_MODEL35 = 0x23,
		WEAP_ALT_MODEL36 = 0x24,
		WEAP_ALT_MODEL37 = 0x25,
		WEAP_ALT_MODEL38 = 0x26,
		WEAP_ALT_MODEL39 = 0x27,
		WEAP_ALT_MODEL40 = 0x28,
		WEAP_ALT_MODEL41 = 0x29,
		WEAP_ALT_MODEL42 = 0x2A,
		WEAP_ALT_MODEL43 = 0x2B,
		WEAP_ALT_MODEL44 = 0x2C,
		WEAP_ALT_MODEL45 = 0x2D,
		WEAP_ALT_MODEL46 = 0x2E,
		WEAP_ALT_MODEL47 = 0x2F,
		WEAP_ALT_MODEL48 = 0x30,
		WEAP_ALT_MODEL49 = 0x31,
		WEAP_ALT_MODEL50 = 0x32,
		WEAP_ALT_MODEL51 = 0x33,
		WEAP_ALT_MODEL52 = 0x34,
		WEAP_ALT_MODEL53 = 0x35,
		WEAP_ALT_MODEL54 = 0x36,
		WEAP_ALT_MODEL55 = 0x37,
		WEAP_ALT_MODEL56 = 0x38,
		WEAP_ALT_MODEL57 = 0x39,
		WEAP_ALT_MODEL58 = 0x3A,
		WEAP_ALT_MODEL59 = 0x3B,
		WEAP_ALT_MODEL60 = 0x3C,
		WEAP_ALT_MODEL61 = 0x3D,
		WEAP_ALT_MODEL62 = 0x3E,
		WEAP_ALT_MODEL63 = 0x3F,
		NUM_WEAP_ALTMODELS = 0x40,
	};

	struct WeaponDef
	{
		const char* szOverlayName;
		XModel** gunXModel;
		XModel* handXModel;
		XModel* camoWorldModel;
		XModel* camoViewModel;
		Material* camoWorldModelMaterialOverride;
		Material* camoViewModelMaterialOverride;
		Material** camoMaterialTarget;
		XAnimParts** szXAnimsRightHanded;
		XAnimParts** szXAnimsLeftHanded;
		const char* szModeName;
		scr_string_t* notetrackSoundMapKeys;
		scr_string_t* notetrackSoundMapValues;
		scr_string_t* notetrackRumbleMapKeys;
		scr_string_t* notetrackRumbleMapValues;
		scr_string_t* notetrackFXMapKeys;
		FxEffectDef** notetrackFXMapValues; // const FxEffectDef**
		scr_string_t* notetrackFXMapTagValues;
		int playerAnimType;
		weapType_t weapType;
		weapClass_t weapClass;
		PenetrateType penetrateType;
		weapInventoryType_t inventoryType;
		weapFireType_t fireType;
		float burstFireCooldown;
		OffhandClass offhandClass;
		weapStance_t stance;
		unsigned char rattleSoundType;
		const FxEffectDef* viewFlashEffect;
		const FxEffectDef* worldFlashEffect;
		const FxEffectDef* viewFlashADSEffect;
		snd_alias_list_t* pickupSound;
		snd_alias_list_t* pickupSoundPlayer;
		snd_alias_list_t* ammoPickupSound;
		snd_alias_list_t* ammoPickupSoundPlayer;
		snd_alias_list_t* projectileSound;
		snd_alias_list_t* pullbackSound;
		snd_alias_list_t* pullbackSoundPlayer;
		snd_alias_list_t* fireSound;
		snd_alias_list_t* fireSoundPlayer;
		snd_alias_list_t* fireSoundPlayerAkimbo;
		snd_alias_list_t* fireLoopSound;
		snd_alias_list_t* fireLoopSoundPlayer;
		snd_alias_list_t* fireStopSound;
		snd_alias_list_t* fireStopSoundPlayer;
		snd_alias_list_t* fireLastSound;
		snd_alias_list_t* fireLastSoundPlayer;
		snd_alias_list_t* emptyFireSound;
		snd_alias_list_t* emptyFireSoundPlayer;
		snd_alias_list_t* meleeSwipeSound;
		snd_alias_list_t* meleeSwipeSoundPlayer;
		snd_alias_list_t* meleeHitSound;
		snd_alias_list_t* meleeMissSound;
		snd_alias_list_t* rechamberSound;
		snd_alias_list_t* rechamberSoundPlayer;
		snd_alias_list_t* reloadSound;
		snd_alias_list_t* reloadSoundPlayer;
		snd_alias_list_t* reloadEmptySound;
		snd_alias_list_t* reloadEmptySoundPlayer;
		snd_alias_list_t* reloadStartSound;
		snd_alias_list_t* reloadStartSoundPlayer;
		snd_alias_list_t* reloadEndSound;
		snd_alias_list_t* reloadEndSoundPlayer;
		snd_alias_list_t* detonateSound;
		snd_alias_list_t* detonateSoundPlayer;
		snd_alias_list_t* nightVisionWearSound;
		snd_alias_list_t* nightVisionWearSoundPlayer;
		snd_alias_list_t* nightVisionRemoveSound;
		snd_alias_list_t* nightVisionRemoveSoundPlayer;
		snd_alias_list_t* altSwitchSound;
		snd_alias_list_t* altSwitchSoundPlayer;
		snd_alias_list_t* raiseSound;
		snd_alias_list_t* raiseSoundPlayer;
		snd_alias_list_t* firstRaiseSound;
		snd_alias_list_t* firstRaiseSoundPlayer;
		snd_alias_list_t* putawaySound;
		snd_alias_list_t* putawaySoundPlayer;
		snd_alias_list_t* scanSound;
		snd_alias_list_t* changeVariableZoomSound;
		snd_alias_list_t** bounceSound;
		snd_alias_list_t** rollingSound;
		const FxEffectDef* viewShellEjectEffect;
		const FxEffectDef* worldShellEjectEffect;
		const FxEffectDef* viewLastShotEjectEffect;
		const FxEffectDef* worldLastShotEjectEffect;
		const FxEffectDef* viewMagEjectEffect;
		Material* reticleCenter;
		Material* reticleSide;
		int iReticleCenterSize;
		int iReticleSideSize;
		int iReticleMinOfs;
		activeReticleType_t activeReticleType;
		float vStandMove[3];
		float vStandRot[3];
		float strafeMove[3];
		float strafeRot[3];
		float vDuckedOfs[3];
		float vDuckedMove[3];
		float vDuckedRot[3];
		float vProneOfs[3];
		float vProneMove[3];
		float vProneRot[3];
		float fPosMoveRate;
		float fPosProneMoveRate;
		float fStandMoveMinSpeed;
		float fDuckedMoveMinSpeed;
		float fProneMoveMinSpeed;
		float fPosRotRate;
		float fPosProneRotRate;
		float fStandRotMinSpeed;
		float fDuckedRotMinSpeed;
		float fProneRotMinSpeed;
		XModel** worldModel;
		XModel* worldClipModel;
		XModel* rocketModel;
		XModel* knifeModel;
		XModel* worldKnifeModel;
		Material* hudIcon;
		weaponIconRatioType_t hudIconRatio;
		Material* pickupIcon;
		weaponIconRatioType_t pickupIconRatio;
		Material* ammoCounterIcon;
		weaponIconRatioType_t ammoCounterIconRatio;
		ammoCounterClipType_t ammoCounterClip;
		int iStartAmmo;
		const char* szAmmoName;
		int iAmmoIndex;
		const char* szClipName;
		int iClipIndex;
		int iMaxAmmo;
		int shotCount;
		const char* szSharedAmmoCapName;
		int iSharedAmmoCapIndex;
		int iSharedAmmoCap;
		int damage;
		int playerDamage;
		int iMeleeDamage;
		int iDamageType;
		StateTimers stateTimers;
		StateTimers akimboStateTimers;
		float autoAimRange;
		float aimAssistRange;
		float aimAssistRangeAds;
		float aimPadding;
		float enemyCrosshairRange;
		float moveSpeedScale;
		float adsMoveSpeedScale;
		float sprintDurationScale;
		float fAdsZoomInFrac;
		float fAdsZoomOutFrac;
		ADSOverlay overlay;
		WeapOverlayInteface_t overlayInterface;
		float fAdsBobFactor;
		float fAdsViewBobMult;
		float fHipSpreadStandMin;
		float fHipSpreadDuckedMin;
		float fHipSpreadProneMin;
		float hipSpreadStandMax;
		float hipSpreadDuckedMax;
		float hipSpreadProneMax;
		float fHipSpreadDecayRate;
		float fHipSpreadFireAdd;
		float fHipSpreadTurnAdd;
		float fHipSpreadMoveAdd;
		float fHipSpreadDuckedDecay;
		float fHipSpreadProneDecay;
		float fHipReticleSidePos;
		float fAdsIdleAmount;
		float fHipIdleAmount;
		float adsIdleSpeed;
		float hipIdleSpeed;
		float fIdleCrouchFactor;
		float fIdleProneFactor;
		float fGunMaxPitch;
		float fGunMaxYaw;
		float adsIdleLerpStartTime;
		float adsIdleLerpTime;
		float swayMaxAngleSteadyAim;
		float swayMaxAngle;
		float swayLerpSpeed;
		float swayPitchScale;
		float swayYawScale;
		float swayHorizScale;
		float swayVertScale;
		float swayShellShockScale;
		float adsSwayMaxAngle;
		float adsSwayLerpSpeed;
		float adsSwayPitchScale;
		float adsSwayYawScale;
		float adsSwayHorizScale;
		float adsSwayVertScale;
		float adsFireRateScale;
		float adsDamageRangeScale;
		float adsFireAnimFrac;
		PhysCollmap* physCollmap;
		float dualWieldViewModelOffset;
		float fScopeDriftDelay;
		float fScopeDriftLerpInTime;
		float fScopeDriftSteadyTime;
		float fScopeDriftLerpOutTime;
		float fScopeDriftSteadyFactor;
		float fScopeDriftUnsteadyFactor;
		weaponIconRatioType_t killIconRatio;
		int iReloadAmmoAdd;
		int iReloadStartAdd;
		int ammoDropStockMin;
		int ammoDropClipPercentMin;
		int ammoDropClipPercentMax;
		int iExplosionRadius;
		int iExplosionRadiusMin;
		int iExplosionInnerDamage;
		int iExplosionOuterDamage;
		float damageConeAngle;
		float bulletExplDmgMult;
		float bulletExplRadiusMult;
		int iProjectileSpeed;
		int iProjectileSpeedUp;
		int iProjectileSpeedForward;
		int iProjectileActivateDist;
		float projLifetime;
		float timeToAccelerate;
		float projectileCurvature;
		const char* projectileName;
		XModel* projectileModel;
		weapProjExposion_t projExplosion;
		const FxEffectDef* projExplosionEffect;
		const FxEffectDef* projDudEffect;
		snd_alias_list_t* projExplosionSound;
		snd_alias_list_t* projDudSound;
		WeapStickinessType stickiness;
		float lowAmmoWarningThreshold;
		float ricochetChance;
		bool riotShieldEnableDamage;
		int riotShieldHealth;
		float riotShieldDamageMult;
		float* parallelBounce;
		float* perpendicularBounce;
		const FxEffectDef* projTrailEffect;
		const FxEffectDef* projBeaconEffect;
		float vProjectileColor[3];
		guidedMissileType_t guidedMissileType;
		float maxSteeringAccel;
		int projIgnitionDelay;
		const FxEffectDef* projIgnitionEffect;
		snd_alias_list_t* projIgnitionSound;
		float fAdsAimPitch;
		float fAdsCrosshairInFrac;
		float fAdsCrosshairOutFrac;
		bool adsShouldShowCrosshair;
		int adsGunKickReducedKickBullets;
		float adsGunKickReducedKickPercent;
		float fAdsGunKickPitchMin;
		float fAdsGunKickPitchMax;
		float fAdsGunKickYawMin;
		float fAdsGunKickYawMax;
		float fAdsGunKickMagMin;
		float fAdsGunKickAccel;
		float fAdsGunKickSpeedMax;
		float fAdsGunKickSpeedDecay;
		float fAdsGunKickStaticDecay;
		float fAdsViewKickPitchMin;
		float fAdsViewKickPitchMax;
		float fAdsViewKickYawMin;
		float fAdsViewKickYawMax;
		float fAdsViewKickMagMin;
		float fAdsViewScatterMin;
		float fAdsViewScatterMax;
		float fAdsSpread;
		int hipGunKickReducedKickBullets;
		float hipGunKickReducedKickPercent;
		float fHipGunKickPitchMin;
		float fHipGunKickPitchMax;
		float fHipGunKickYawMin;
		float fHipGunKickYawMax;
		float fHipGunKickMagMin;
		float fHipGunKickAccel;
		float fHipGunKickSpeedMax;
		float fHipGunKickSpeedDecay;
		float fHipGunKickStaticDecay;
		float fHipViewKickPitchMin;
		float fHipViewKickPitchMax;
		float fHipViewKickYawMin;
		float fHipViewKickYawMax;
		float fHipViewKickMagMin;
		float fHipViewScatterMin;
		float fHipViewScatterMax;
		float fightDist;
		float maxDist;
		const char* accuracyGraphName[2];
		float(*originalAccuracyGraphKnots[2])[2];
		unsigned short originalAccuracyGraphKnotCount[2];
		int iPositionReloadTransTime;
		float leftArc;
		float rightArc;
		float topArc;
		float bottomArc;
		float accuracy;
		float aiSpread;
		float playerSpread;
		float minTurnSpeed[2];
		float maxTurnSpeed[2];
		float pitchConvergenceTime;
		float yawConvergenceTime;
		float suppressTime;
		float maxRange;
		float fAnimHorRotateInc;
		float fPlayerPositionDist;
		const char* szUseHintString;
		const char* dropHintString;
		unsigned int iUseHintStringIndex;
		unsigned int dropHintStringIndex;
		float horizViewJitter;
		float vertViewJitter;
		float scanSpeed;
		float scanAccel;
		int scanPauseTime;
		const char* szScript;
		float fOOPosAnimLength[2];
		int minDamage;
		int minPlayerDamage;
		float fMaxDamageRange;
		float fMinDamageRange;
		float destabilizationRateTime;
		float destabilizationCurvatureMax;
		int destabilizeDistance;
		float* locationDamageMultipliers;
		const char* fireRumble;
		const char* meleeImpactRumble;
		TracerDef* tracerType;
		bool turretADSEnabled;
		float turretADSTime;
		float turretFov;
		float turretFovADS;
		float turretScopeZoomRate;
		float turretScopeZoomMin;
		float turretScopeZoomMax;
		float turretOverheatUpRate;
		float turretOverheatDownRate;
		float turretOverheatPenalty;
		snd_alias_list_t* turretOverheatSound;
		const FxEffectDef* turretOverheatEffect;
		const char* turretBarrelSpinRumble;
		float turretBarrelSpinSpeed;
		float turretBarrelSpinUpTime;
		float turretBarrelSpinDownTime;
		snd_alias_list_t* turretBarrelSpinMaxSnd;
		snd_alias_list_t* turretBarrelSpinUpSnd[4];
		snd_alias_list_t* turretBarrelSpinDownSnd[4];
		snd_alias_list_t* missileConeSoundAlias;
		snd_alias_list_t* missileConeSoundAliasAtBase;
		float missileConeSoundRadiusAtTop;
		float missileConeSoundRadiusAtBase;
		float missileConeSoundHeight;
		float missileConeSoundOriginOffset;
		float missileConeSoundVolumescaleAtCore;
		float missileConeSoundVolumescaleAtEdge;
		float missileConeSoundVolumescaleCoreSize;
		float missileConeSoundPitchAtTop;
		float missileConeSoundPitchAtBottom;
		float missileConeSoundPitchTopSize;
		float missileConeSoundPitchBottomSize;
		float missileConeSoundCrossfadeTopSize;
		float missileConeSoundCrossfadeBottomSize;
		scr_string_t knifeAttachTagOverride;
		bool knifeAlwaysAttached;
		bool meleeOverrideValues;
		float aim_automelee_lerp;
		float aim_automelee_range;
		float aim_automelee_region_height;
		float aim_automelee_region_width;
		float player_meleeHeight;
		float player_meleeRange;
		float player_meleeWidth;
		bool sharedAmmo;
		bool lockonSupported;
		bool requireLockonToFire;
		bool isAirburstWeapon;
		bool bigExplosion;
		bool noAdsWhenMagEmpty;
		bool avoidDropCleanup;
		bool inheritsPerks;
		bool crosshairColorChange;
		bool bRifleBullet;
		bool armorPiercing;
		bool bBoltAction;
		bool aimDownSight;
		bool canHoldBreath;
		bool meleeOnly;
		bool canVariableZoom;
		bool bRechamberWhileAds;
		bool bBulletExplosiveDamage;
		bool bCookOffHold;
		bool reticleSpin45;
		bool bClipOnly;
		bool noAmmoPickup;
		bool adsFireOnly;
		bool cancelAutoHolsterWhenEmpty;
		bool disableSwitchToWhenEmpty;
		bool suppressAmmoReserveDisplay;
		bool laserSightDuringNightvision;
		bool markableViewmodel;
		bool noDualWield;
		bool flipKillIcon;
		bool bNoPartialReload;
		bool bSegmentedReload;
		bool bMultipleReload;
		bool blocksProne;
		bool silenced;
		bool isRollingGrenade;
		bool projExplosionEffectForceNormalUp;
		bool projExplosionEffectInheritParentDirection;
		bool bProjImpactExplode;
		bool bProjTrajectoryEvents;
		bool bProjWhizByEnabled;
		bool stickToPlayers;
		bool stickToVehicles;
		bool stickToTurrets;
		bool thrownSideways;
		bool hasDetonator;
		bool disableFiring;
		bool timedDetonation;
		bool rotate;
		bool holdButtonToThrow;
		bool freezeMovementWhenFiring;
		bool thermalScope;
		bool thermalToggle;
		bool outlineEnemies;
		bool altModeSameWeapon;
		bool turretBarrelSpinEnabled;
		bool missileConeSoundEnabled;
		bool missileConeSoundPitchshiftEnabled;
		bool missileConeSoundCrossfadeEnabled;
		bool offhandHoldIsCancelable;
		bool doNotAllowAttachmentsToOverrideSpread;
		bool useFastReloadAnims;
		bool useScopeDrift;
		bool alwaysShatterGlassOnImpact;
		bool oldWeapon;
		scr_string_t stowTag;
		XModel* stowOffsetModel;
	};

	enum AttachmentType : std::int32_t
	{
		ATTACHMENT_SCOPE = 0x0,
		ATTACHMENT_UNDERBARREL = 0x1,
		ATTACHMENT_OTHER = 0x2,
		ATTACHMENT_COUNT = 0x3,
	};

	struct AttAmmoGeneral
	{
		PenetrateType penetrateType;
		float penetrateMultiplier;
		ImpactType impactType;
		weapFireType_t fireType;
		TracerDef* tracerType;
		bool rifleBullet;
		bool armorPiercing;
	};

	struct AttSight
	{
		bool aimDownSight;
		bool adsFire;
		bool rechamberWhileAds;
		bool noAdsWhenMagEmpty;
		bool canHoldBreath;
		bool canVariableZoom;
		bool hideRailWithThisScope;
		bool useScopeDrift;
		bool useDualFOV;
	};

	struct AttReload
	{
		bool noPartialReload;
		bool segmentedReload;
	};

	struct AttAddOns
	{
		bool motionTracker;
		bool silenced;
		bool riotShield;
	};

	struct AttGeneral
	{
		bool boltAction;
		bool inheritsPerks;
		bool reticleSpin45;
		float enemyCrosshairRange;
		Material* reticleCenter;
		Material* reticleSide;
		int reticleCenterSize;
		int reticleSideSize;
		float moveSpeedScale;
		float adsMoveSpeedScale;
	};

	struct AttAimAssist
	{
		float autoAimRange;
		float aimAssistRange;
		float aimAssistRangeAds;
	};

	struct AttAmmunition
	{
		int maxAmmo;
		int startAmmo;
		int clipSize;
		int shotCount;
		int reloadAmmoAdd;
		int reloadStartAdd;
	};

	struct AttDamage
	{
		int damage;
		int minDamage;
		int meleeDamage;
		float maxDamageRange;
		float minDamageRange;
		int playerDamage;
		int minPlayerDamage;
	};

	struct AttLocationDamage
	{
		float locNone;
		float locHelmet;
		float locHead;
		float locNeck;
		float locTorsoUpper;
		float locTorsoLower;
		float locRightArmUpper;
		float locRightArmLower;
		float locRightHand;
		float locLeftArmUpper;
		float locLeftArmLower;
		float locLeftHand;
		float locRightLegUpper;
		float locRightLegLower;
		float locRightFoot;
		float locLeftLegUpper;
		float locLeftLegLower;
		float locLeftFoot;
		float locGun;
	};

	struct AttIdleSettings
	{
		float hipIdleAmount;
		float hipIdleSpeed;
		float idleCrouchFactor;
		float idleProneFactor;
		float adsIdleLerpStartTime;
		float adsIdleLerpTime;
	};

	struct AttADSSettings
	{
		float adsSpread;
		float adsAimPitch;
		float adsTransInTime;
		float adsTransOutTime;
		int adsReloadTransTime;
		float adsCrosshairInFrac;
		float adsCrosshairOutFrac;
		float adsZoomFov;
		float adsZoomInFrac;
		float adsZoomOutFrac;
		float adsFovLerpTime;
		float adsBobFactor;
		float adsViewBobMult;
		float adsFireRateScale;
		float adsDamageRangeScale;
		float adsFireAnimFrac;
	};

	struct AttScopeDriftSettings
	{
		float fScopeDriftDelay;
		float fScopeDriftLerpInTime;
		float fScopeDriftSteadyTime;
		float fScopeDriftLerpOutTime;
		float fScopeDriftSteadyFactor;
		float fScopeDriftUnsteadyFactor;
	};

	struct AttHipSpread
	{
		float hipSpreadStandMin;
		float hipSpreadDuckedMin;
		float hipSpreadProneMin;
		float hipSpreadMax;
		float hipSpreadDuckedMax;
		float hipSpreadProneMax;
		float hipSpreadFireAdd;
		float hipSpreadTurnAdd;
		float hipSpreadMoveAdd;
		float hipSpreadDecayRate;
		float hipSpreadDuckedDecay;
		float hipSpreadProneDecay;
	};

	struct AttGunKick
	{
		int hipGunKickReducedKickBullets;
		float hipGunKickReducedKickPercent;
		float hipGunKickPitchMin;
		float hipGunKickPitchMax;
		float hipGunKickYawMin;
		float hipGunKickYawMax;
		float hipGunKickMagMin;
		float hipGunKickAccel;
		float hipGunKickSpeedMax;
		float hipGunKickSpeedDecay;
		float hipGunKickStaticDecay;
		int adsGunKickReducedKickBullets;
		float adsGunKickReducedKickPercent;
		float adsGunKickPitchMin;
		float adsGunKickPitchMax;
		float adsGunKickYawMin;
		float adsGunKickYawMax;
		float adsGunKickMagMin;
		float adsGunKickAccel;
		float adsGunKickSpeedMax;
		float adsGunKickSpeedDecay;
		float adsGunKickStaticDecay;
	};

	struct AttViewKick
	{
		float hipViewKickPitchMin;
		float hipViewKickPitchMax;
		float hipViewKickYawMin;
		float hipViewKickYawMax;
		float hipViewKickMagMin;
		float hipViewKickCenterSpeed;
		float adsViewKickPitchMin;
		float adsViewKickPitchMax;
		float adsViewKickYawMin;
		float adsViewKickYawMax;
		float adsViewKickMagMin;
		float adsViewKickCenterSpeed;
	};

	struct AttADSOverlay
	{
		ADSOverlay overlay;
		bool hybridToggle;
		bool thermalScope;
		bool thermalToggle;
		bool outlineEnemies;
	};

	struct AttUI
	{
		Material* dpadIcon;
		Material* ammoCounterIcon;
		weaponIconRatioType_t dpadIconRatio;
		weaponIconRatioType_t ammoCounterIconRatio;
		ammoCounterClipType_t ammoCounterClip;
	};

	struct AttRumbles
	{
		const char* fireRumble;
		const char* meleeImpactRumble;
	};

	struct AttProjectile
	{
		int explosionRadius;
		int explosionInnerDamage;
		int explosionOuterDamage;
		float damageConeAngle;
		int projectileSpeed;
		int projectileSpeedUp;
		int projectileActivateDist;
		float projectileLifetime;
		const char* projectileName;
		XModel* projectileModel;
		weapProjExposion_t projExplosionType;
		const FxEffectDef* projExplosionEffect;
		bool projExplosionEffectForceNormalUp;
		snd_alias_list_t* projExplosionSound;
		const FxEffectDef* projDudEffect;
		snd_alias_list_t* projDudSound;
		bool projImpactExplode;
		float destabilizationRateTime;
		float destabilizationCurvatureMax;
		int destabilizeDistance;
		const FxEffectDef* projTrailEffect;
		int projIgnitionDelay;
		const FxEffectDef* projIgnitionEffect;
		snd_alias_list_t* projIgnitionSound;
	};

	struct WeaponAttachment
	{
		union
		{
			const char* szInternalName;
			const char* name;
		};
		const char* szDisplayName;
		AttachmentType type;
		weapType_t weaponType;
		weapClass_t weapClass;
		XModel** worldModels;
		XModel** viewModels;
		XModel** reticleViewModels;
		AttAmmoGeneral* ammogeneral;
		AttSight* sight;
		AttReload* reload;
		AttAddOns* addOns;
		AttGeneral* general;
		AttAimAssist* aimAssist;
		AttAmmunition* ammunition;
		AttDamage* damage;
		AttLocationDamage* locationDamage;
		AttIdleSettings* idleSettings;
		AttADSSettings* adsSettings;
		AttADSSettings* adsSettingsMain;
		AttScopeDriftSettings* scopeDriftSettings;
		AttScopeDriftSettings* scopeDriftSettingsMain;
		AttHipSpread* hipSpread;
		AttGunKick* gunKick;
		AttViewKick* viewKick;
		AttADSOverlay* adsOverlay;
		AttUI* ui;
		AttRumbles* rumbles;
		AttProjectile* projectile;
		float ammunitionScale;
		float damageScale;
		float damageScaleMin;
		float stateTimersScale;
		float fireTimersScale;
		float idleSettingsScale;
		float adsSettingsScale;
		float adsSettingsScaleMain;
		float hipSpreadScale;
		float gunKickScale;
		float viewKickScale;
		float viewCenterScale;
		int loadIndex;
		bool hideIronSightsWithThisAttachment;
		bool shareAmmoWithAlt;
	};

	struct AnimOverrideEntry
	{
		unsigned short attachment1;
		unsigned short attachment2;
		XAnimParts* overrideAnim;
		XAnimParts* altmodeAnim;
		unsigned int animTreeType;
		int animTime;
		int altTime;
	};

	struct SoundOverrideEntry
	{
		unsigned short attachment1;
		unsigned short attachment2;
		snd_alias_list_t* overrideSound;
		snd_alias_list_t* altmodeSound;
		unsigned int soundType;
	};

	struct FXOverrideEntry
	{
		unsigned short attachment1;
		unsigned short attachment2;
		const FxEffectDef* overrideFX;
		const FxEffectDef* altmodeFX;
		unsigned int fxType;
	};

	struct ReloadStateTimerEntry
	{
		int attachment;
		int reloadAddTime;
		int reloadEmptyAddTime;
		int reloadStartAddTime;
	};

	struct NoteTrackToSoundEntry
	{
		int attachment;
		scr_string_t* notetrackSoundMapKeys;
		scr_string_t* notetrackSoundMapValues;
	};

	enum weapAnimFiles_t : int
	{
		WEAP_ANIM_ROOT = 0x0,
		WEAP_ANIM_IDLE = 0x1,
		WEAP_ANIM_EMPTY_IDLE = 0x2,
		WEAP_ANIM_FIRE = 0x3,
		WEAP_ANIM_HOLD_FIRE = 0x4,
		WEAP_ANIM_LASTSHOT = 0x5,
		WEAP_ANIM_RECHAMBER = 0x6,
		WEAP_ANIM_GRENADE_PRIME = 0x7,
		WEAP_ANIM_GRENADE_PRIME_READY_TO_THROW = 0x8,
		WEAP_ANIM_MELEE_SWIPE = 0x9,
		WEAP_ANIM_MELEE_HIT = 0xA,
		WEAP_ANIM_MELEE_FATAL = 0xB,
		WEAP_ANIM_MELEE_MISS = 0xC,
		WEAP_ANIM_MELEE_VICTIM_CROUCHING_HIT = 0xD,
		WEAP_ANIM_MELEE_VICTIM_CROUCHING_FATAL = 0xE,
		WEAP_ANIM_MELEE_VICTIM_CROUCHING_MISS = 0xF,
		WEAP_ANIM_RELOAD = 0x10,
		WEAP_ANIM_RELOAD_EMPTY = 0x11,
		WEAP_ANIM_RELOAD_START = 0x12,
		WEAP_ANIM_RELOAD_END = 0x13,
		WEAP_ANIM_FAST_RELOAD = 0x14,
		WEAP_ANIM_FAST_RELOAD_EMPTY = 0x15,
		WEAP_ANIM_FAST_RELOAD_START = 0x16,
		WEAP_ANIM_FAST_RELOAD_END = 0x17,
		WEAP_ANIM_RAISE = 0x18,
		WEAP_ANIM_FIRST_RAISE = 0x19,
		WEAP_ANIM_BREACH_RAISE = 0x1A,
		WEAP_ANIM_DROP = 0x1B,
		WEAP_ANIM_ALT_RAISE = 0x1C,
		WEAP_ANIM_ALT_DROP = 0x1D,
		WEAP_ANIM_ALT_OVERRIDE = 0x1E,
		WEAP_ANIM_TOGGLE_OVERRIDE = 0x1F,
		WEAP_ANIM_SCOPE_TOGGLE_ON = 0x20,
		WEAP_ANIM_SCOPE_TOGGLE_OFF = 0x21,
		WEAP_ANIM_QUICK_RAISE = 0x22,
		WEAP_ANIM_QUICK_DROP = 0x23,
		WEAP_ANIM_EMPTY_RAISE = 0x24,
		WEAP_ANIM_EMPTY_DROP = 0x25,
		WEAP_ANIM_SPRINT_IN = 0x26,
		WEAP_ANIM_SPRINT_IN_CANCEL = 0x27,
		WEAP_ANIM_SPRINT_LOOP = 0x28,
		WEAP_ANIM_SPRINT_OUT = 0x29,
		WEAP_ANIM_STUNNED_START = 0x2A,
		WEAP_ANIM_STUNNED_LOOP = 0x2B,
		WEAP_ANIM_STUNNED_END = 0x2C,
		WEAP_ANIM_DETONATE = 0x2D,
		WEAP_ANIM_NIGHTVISION_WEAR = 0x2E,
		WEAP_ANIM_NIGHTVISION_REMOVE = 0x2F,
		WEAP_ANIM_ADS_FIRE = 0x30,
		WEAP_ANIM_ADS_LASTSHOT = 0x31,
		WEAP_ANIM_ADS_RECHAMBER = 0x32,
		WEAP_ANIM_BLAST_FRONT = 0x33,
		WEAP_ANIM_BLAST_RIGHT = 0x34,
		WEAP_ANIM_BLAST_BACK = 0x35,
		WEAP_ANIM_BLAST_LEFT = 0x36,
		WEAP_ANIM_SLIDE_IN = 0x37,
		WEAP_ANIM_SLIDE_LOOP = 0x38,
		WEAP_ANIM_SLIDE_OUT = 0x39,
		WEAP_ANIM_RECOIL_SETTLE = 0x3A,
		WEAP_ANIM_SWIM_LOOP = 0x3B,
		WEAP_ANIM_MANTLE_UP_64 = 0x3C,
		WEAP_ANIM_MANTLE_UP_56 = 0x3D,
		WEAP_ANIM_MANTLE_UP_48 = 0x3E,
		WEAP_ANIM_MANTLE_UP_40 = 0x3F,
		WEAP_ANIM_MANTLE_UP_32 = 0x40,
		WEAP_ANIM_MANTLE_UP_24 = 0x41,
		WEAP_ANIM_MANTLE_UP_16 = 0x42,
		WEAP_ANIM_MANTLE_OVER_64 = 0x43,
		WEAP_ANIM_MANTLE_OVER_56 = 0x44,
		WEAP_ANIM_MANTLE_OVER_48 = 0x45,
		WEAP_ANIM_MANTLE_OVER_40 = 0x46,
		WEAP_ANIM_MANTLE_OVER_32 = 0x47,
		WEAP_ANIM_MANTLE_OVER_24 = 0x48,
		WEAP_ANIM_MANTLE_OVER_16 = 0x49,
		WEAP_ANIM_RELOAD_MULTIPLE_1 = 0x4A,
		WEAP_ANIM_RELOAD_MULTIPLE_2 = 0x4B,
		WEAP_ANIM_RELOAD_MULTIPLE_3 = 0x4C,
		WEAP_ANIM_RELOAD_MULTIPLE_4 = 0x4D,
		WEAP_ANIM_RELOAD_MULTIPLE_5 = 0x4E,
		WEAP_ANIM_RELOAD_MULTIPLE_6 = 0x4F,
		WEAP_ANIM_RELOAD_MULTIPLE_7 = 0x50,
		WEAP_ANIM_RELOAD_MULTIPLE_8 = 0x51,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_1 = 0x52,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_2 = 0x53,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_3 = 0x54,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_4 = 0x55,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_5 = 0x56,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_6 = 0x57,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_7 = 0x58,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_8 = 0x59,
		WEAP_ANIM_ADS_UP = 0x5A,
		WEAP_ANIM_ADS_DOWN = 0x5B,
		WEAP_ANIM_RECOIL = 0x5C,
		WEAP_ALT_ANIM_ADJUST = 0x5D,
		WEAP_ANIM_ADDITIVE_ADS_ROOT = 0x5E,
		WEAP_ANIM_ADDITIVE_ADS_UP = 0x5F,
		WEAP_ANIM_ADDITIVE_DRAG_LEFT_ROOT = 0x60,
		WEAP_ANIM_ADDITIVE_DRAG_LEFT = 0x61,
		WEAP_ANIM_ADDITIVE_DRAG_RIGHT_ROOT = 0x62,
		WEAP_ANIM_ADDITIVE_DRAG_RIGHT = 0x63,
		WEAP_ANIM_ADDITIVE_DRAG_UP_ROOT = 0x64,
		WEAP_ANIM_ADDITIVE_DRAG_UP = 0x65,
		WEAP_ANIM_ADDITIVE_DRAG_DOWN_ROOT = 0x66,
		WEAP_ANIM_ADDITIVE_DRAG_DOWN = 0x67,
		WEAP_ANIM_ADDITIVE_SWIM_FORWARD_ROOT = 0x68,
		WEAP_ANIM_ADDITIVE_SWIM_FORWARD = 0x69,
		WEAP_ANIM_ADDITIVE_SWIM_BACKWARD_ROOT = 0x6A,
		WEAP_ANIM_ADDITIVE_SWIM_BACKWARD = 0x6B,
		WEAP_ANIM_ADDITIVE_JUMP_ROOT = 0x6C,
		WEAP_ANIM_ADDITIVE_JUMP = 0x6D,
		WEAP_ANIM_ADDITIVE_JUMP_LAND_ROOT = 0x6E,
		WEAP_ANIM_ADDITIVE_JUMP_LAND = 0x6F,
		WEAP_ANIM_ADDITIVE_WALK_ROOT = 0x70,
		WEAP_ANIM_ADDITIVE_WALK = 0x71,
		WEAP_ANIM_ADDITIVE_CRAWL_IN_ROOT = 0x72,
		WEAP_ANIM_ADDITIVE_CRAWL_IN = 0x73,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_ROOT = 0x74,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP = 0x75,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_LEFT_ROOT = 0x76,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_LEFT = 0x77,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_RIGHT_ROOT = 0x78,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_RIGHT = 0x79,
		WEAP_ANIM_ADDITIVE_PRONE_DROP_ROOT = 0x7A,
		WEAP_ANIM_ADDITIVE_PRONE_DROP = 0x7B,
		NUM_WEAP_ANIMS = 0x7C,
		WEAP_ANIM_VIEWMODEL_START = 0x1,
		WEAP_ANIM_VIEWMODEL_END = 0x5A,
		WEAP_ANIM_ADDITIVE_START = 0x5E,
		WEAP_ANIM_ADDITIVE_END = 0x7C,
	};

	struct WeaponCompleteDef
	{
		union
		{
			const char* szInternalName;
			const char* name;
		};
		WeaponDef* weapDef;
		const char* szDisplayName;
		scr_string_t* hideTags;
		WeaponAttachment** scopes;
		WeaponAttachment** underBarrels;
		WeaponAttachment** others;
		XAnimParts** szXAnims; // XAnimParts* const*
		unsigned int numAnimOverrides;
		AnimOverrideEntry* animOverrides;
		unsigned int numSoundOverrides;
		SoundOverrideEntry* soundOverrides;
		unsigned int numFXOverrides;
		FXOverrideEntry* fxOverrides;
		unsigned int numReloadStateTimerOverrides;
		ReloadStateTimerEntry* reloadOverrides;
		unsigned int numNotetrackOverrides;
		NoteTrackToSoundEntry* notetrackOverrides;
		float fAdsZoomFov;
		int iAdsTransInTime;
		int iAdsTransOutTime;
		int iClipSize;
		ImpactType impactType;
		int iFireTime;
		int iFireTimeAkimbo;
		weaponIconRatioType_t dpadIconRatio;
		float penetrateMultiplier;
		float fAdsViewKickCenterSpeed;
		float fHipViewKickCenterSpeed;
		const char* szAltWeaponName;
		int altWeapon;
		int iAltRaiseTime;
		int iAltRaiseTimeAkimbo;
		Material* killIcon;
		Material* dpadIcon;
		int fireAnimLength;
		int fireAnimLengthAkimbo;
		int iFirstRaiseTime;
		int iFirstRaiseTimeAkimbo;
		int ammoDropStockMax;
		float adsDofStart;
		float adsDofEnd;
		unsigned short accuracyGraphKnotCount[2];
		float(*accuracyGraphKnots[2])[2];
		bool motionTracker;
		bool enhanced;
		bool dpadIconShowsAmmo;
		const char* szAdsrBaseSetting;
	};

	struct RawFile
	{
		const char* name;
		int compressedLen;
		int len;
		const char* buffer;
	};

	struct LuaFile
	{
		const char* name;
		int len;
		char strippingType;
		const char* buffer;
	};

	struct ScriptFile
	{
		const char* name;
		int compressedLen;
		int len;
		int bytecodeLen;
		const char* buffer;
		char* bytecode;
	};

	struct StringTableCell
	{
		const char* string;
		int hash;
	};

	struct StringTable
	{
		const char* name;
		int columnCount;
		int rowCount;
		StringTableCell* values;
	};

	struct StructuredDataEnumEntry
	{
		scr_string_t string;
		unsigned short index;
	};

	struct StructuredDataEnum
	{
		int entryCount;
		int reservedEntryCount;
		StructuredDataEnumEntry* entries;
	};

	enum StructuredDataTypeCategory
	{
		DATA_INT = 0x0,
		DATA_BYTE = 0x1,
		DATA_BOOL = 0x2,
		DATA_STRING = 0x3,
		DATA_ENUM = 0x4,
		DATA_STRUCT = 0x5,
		DATA_INDEXED_ARRAY = 0x6,
		DATA_ENUM_ARRAY = 0x7,
		DATA_FLOAT = 0x8,
		DATA_SHORT = 0x9,
		DATA_COUNT = 0xA,
	};

	union StructuredDataTypeUnion
	{
		unsigned int stringDataLength;
		int enumIndex;
		int structIndex;
		int indexedArrayIndex;
		int enumedArrayIndex;
		int index;
	};

	struct StructuredDataType
	{
		StructuredDataTypeCategory type;
		StructuredDataTypeUnion u;
	};

	enum StructuredDataValidationType
	{
		VALIDATION_NONE = 0x0,
		VALIDATION_CONSTANT = 0x1,
		VALIDATION_INCREASECLAMP = 0x2,
		VALIDATION_INCREASESTRICT = 0x3,
		VALIDATION_DELTACLAMP = 0x4,
		VALIDATION_DELTASTRICT = 0x5,
		VALIDATION_XP = 0x6,
		VALIDATION_COUNT = 0x7,
	};

	struct StructuredDataStructProperty
	{
		scr_string_t name;
		StructuredDataType type;
		unsigned int offset;
		StructuredDataValidationType validation;
	};

	struct StructuredDataStruct
	{
		int propertyCount;
		StructuredDataStructProperty* properties;
		int size;
		unsigned int bitOffset;
	};

	struct StructuredDataIndexedArray
	{
		int arraySize;
		StructuredDataType elementType;
		unsigned int elementSize;
	};

	struct StructuredDataEnumedArray
	{
		int enumIndex;
		StructuredDataType elementType;
		unsigned int elementSize;
	};

	struct StructuredDataDef
	{
		int version;
		unsigned int formatChecksum;
		int enumCount;
		StructuredDataEnum* enums;
		int structCount;
		StructuredDataStruct* structs;
		int indexedArrayCount;
		StructuredDataIndexedArray* indexedArrays;
		int enumedArrayCount;
		StructuredDataEnumedArray* enumedArrays;
		StructuredDataType rootType;
		unsigned int size;
	};

	struct StructuredDataDefSet
	{
		const char* name;
		unsigned int defCount;
		StructuredDataDef* defs;
	};

	enum NetConstStringType
	{
		NETCONSTSTRINGTYPE_XMODEL = 0x0,
		NETCONSTSTRINGTYPE_MATERIAL = 0x1,
		NETCONSTSTRINGTYPE_RUMBLE = 0x2,
		NETCONSTSTRINGTYPE_VEHICLES = 0x3,
		NETCONSTSTRINGTYPE_FX = 0x4,
		NETCONSTSTRINGTYPE_LOCSTRING = 0x5,
		NETCONSTSTRINGTYPE_SOUNDALIAS = 0x6,
		NETCONSTSTRINGTYPE_SOUNDALIAS_LOOPING = 0x7,
		NETCONSTSTRINGTYPE_SHOCK = 0x8,
		NETCONSTSTRINGTYPE_SCRIPTMENU = 0x9,
		NETCONSTSTRINGTYPE_CLIENT_TAGS = 0xA,
		NETCONSTSTRINGTYPE_HEADICON = 0xB,
		NETCONSTSTRINGTYPE_STATUSICON = 0xC,
		NETCONSTSTRINGTYPE_NAMEPLATE = 0xD,
		NETCONSTSTRINGTYPE_MINIMAPICON = 0xE,
		NETCONSTSTRINGTYPE_LOCSELMAT = 0xF,
		NETCONSTSTRINGTYPE_WEAPON = 0x10,
		NETCONSTSTRINGTYPE_HINTSTRING = 0x11,
		NETCONSTSTRINGTYPE_ANIM = 0x12,
		NETCONSTSTRINGTYPE_TAGS = 0x13,
		NETCONSTSTRINGTYPE_ANIMCLASS = 0x14,
		NETCONSTSTRINGTYPE_LUI = 0x15,
		NETCONSTSTRINGTYPE_ASSET_COUNT = 0x16,
		NETCONSTSTRINGTYPE_CODINFO_DVAR = 0x16,
		NETCONSTSTRINGTYPE_NETWORK_DVAR = 0x17,
		NETCONSTSTRINGTYPE_COUNT = 0x18,
		NETCONSTSTRINGTYPE_NONE = 0x18,
	};

	enum NetConstStringSource
	{
		NETCONSTSTRINGSOURCE_MAP = 0x0,
		NETCONSTSTRINGSOURCE_PRE_MAP = 0x1,
		NETCONSTSTRINGSOURCE_COMMON = 0x2,
		NETCONSTSTRINGSOURCE_COUNT = 0x3,
		NETCONSTSTRINGSOURCE_NONE = 0x3,
	};

	struct NetConstStrings
	{
		const char* name;
		NetConstStringType stringType;
		NetConstStringSource sourceType;
		unsigned int entryCount;
		const char** stringList;
	};

	union XAssetHeader
	{
		PhysPreset* physPreset;
		PhysCollmap* physCollmap;
		XAnimParts* parts;
		XModelSurfs* modelSurfs;
		XModel* model;
		Material* material;
		ComputeShader* computeShader;
		MaterialVertexShader* vertexShader;
		MaterialHullShader* hullShader;
		MaterialDomainShader* domainShader;
		MaterialPixelShader* pixelShader;
		MaterialVertexDeclaration* vertexDecl;
		MaterialTechniqueSet* techniqueSet;
		GfxImage* image;
		snd_alias_list_t* sound;
		SndCurve* sndCurve;
		SndCurve* lpfCurve;
		SndCurve* reverbCurve;
		LoadedSound* loadSnd;
		clipMap_t* clipMap;
		ComWorld* comWorld;
		GlassWorld* glassWorld;
		//PathData* pathData;
		//VehicleTrack* vehicleTrack;
		MapEnts* mapEnts;
		FxWorld* fxWorld;
		GfxWorld* gfxWorld;
		GfxLightDef* lightDef;
		Font_s* font;
		//MenuList* menuList;
		//menuDef_t* menu;
		//AnimationClass* animClass;
		LocalizeEntry* localize;
		WeaponAttachment* attachment;
		WeaponCompleteDef* weapon;
		//SndDriverGlobals* sndDriverGlobals;
		FxEffectDef* fx;
		//FxImpactTable* impactFx;
		//SurfaceFxTable* surfaceFx;
		RawFile* rawfile;
		ScriptFile* scriptfile;
		StringTable* stringTable;
		//LeaderboardDef* leaderboardDef;
		StructuredDataDefSet* structuredDataDefSet;
		TracerDef* tracerDef;
		//VehicleDef* vehDef;
		AddonMapEnts* addonMapEnts;
		NetConstStrings* netConstStrings;
		//ReverbPreset* reverbPreset;
		LuaFile* luaFile;
		ScriptableDef* scriptable;
		//Colorization* colorization;
		//ColorizationSet* colorizationSet;
		//ToneMapping* toneMapping;
		//EquipmentSoundTable* equipSndTable;
		//VectorField* vectorField;
		DopplerPreset* dopplerPreset;
		FxParticleSimAnimation* particleSimAnimation;
		void* data;
	};

	struct XAsset
	{
		XAssetType type;
		XAssetHeader header;
	};

	struct XAssetEntry
	{
		XAsset asset;
		unsigned char zoneIndex;
		volatile char inuseMask;
		unsigned int nextHash;
		unsigned int nextOverride;
		unsigned int nextPoolEntry;
	};

	struct ScriptStringList
	{
		int count;
		const char** strings;
	};

	union GfxZoneTableEntry
	{
		char* dataPtr;
		void* voidPtr;
		ID3D11Buffer* buffer;
		ID3D11DepthStencilState* depthStencilState;
		ID3D11BlendState* blendState;
	};

	typedef std::uint32_t GfxBlendStateBits[1];

	struct XGfxGlobals
	{
		unsigned int depthStencilStateCount; // 0
		unsigned int blendStateCount; // 4
		std::uint64_t* depthStencilStateBits; // 8
		GfxBlendStateBits* blendStateBits; // 16
		GfxZoneTableEntry* depthStencilStates; // 24
		GfxZoneTableEntry* blendStates; // 32
		unsigned int perPrimConstantBufferCount; // 40
		unsigned int perObjConstantBufferCount; // 44
		unsigned int stableConstantBufferCount; // 48
		unsigned int* perPrimConstantBufferSizes; // 56
		unsigned int* perObjConstantBufferSizes; // 64
		unsigned int* stableConstantBufferSizes; // 72
		GfxZoneTableEntry* perPrimConstantBuffers; // 80
		GfxZoneTableEntry* perObjConstantBuffers; // 88
		GfxZoneTableEntry* stableConstantBuffers; // 96
	};

	struct XGlobals
	{
		XGfxGlobals* gfxGlobals;
	};

	struct XAssetList
	{
		ScriptStringList stringList;
		int assetCount;
		XAsset* assets;
		XGlobals* globals;
	};

	struct XFile
	{
		unsigned __int64 size;
		unsigned __int64 externalSize;
		unsigned __int64 blockSize[7];
	};

	struct XBlock
	{
		unsigned char* data;
		unsigned __int64 size;
	};

	struct XZoneMemory_
	{
		XBlock blocks[7];
	};

	enum DBAllocFlags : std::int32_t
	{
		DB_ZONE_NONE = 0x0,
		DB_ZONE_COMMON = 0x1,
		DB_ZONE_UI = 0x2,
		DB_ZONE_GAME = 0x4,
		DB_ZONE_LOAD = 0x8,
		DB_ZONE_DEV = 0x10,
		DB_ZONE_BASEMAP = 0x20,
		DB_ZONE_TRANSIENT_POOL = 0x40,
		DB_ZONE_TRANSIENT_MASK = 0x40,
		DB_ZONE_CUSTOM = 0x80 // added for custom zone loading
	};

	struct XZoneInfo
	{
		const char* name;
		int allocFlags;
		int freeFlags;
	};

	struct XZoneInfoInternal
	{
		char name[64];
		int flags;
		int isBaseMap;
	};

	struct DBFile
	{
		void* handle;
		unsigned __int64 memoryBufferSize;
		char* memoryBuffer;
		char name[64];
	};

	enum DBSyncMode : std::int32_t
	{
		DB_LOAD_ASYNC = 0x0,
		DB_LOAD_SYNC = 0x1,
		DB_LOAD_ASYNC_WAIT_ALLOC = 0x2,
		DB_LOAD_ASYNC_FORCE_FREE = 0x3,
		DB_LOAD_ASYNC_NO_SYNC_THREADS = 0x4,
		DB_LOAD_SYNC_SKIP_ALWAYS_LOADED = 0x5,
	};

	enum DB_CompressorType : std::int32_t
	{
		DB_COMPRESSOR_INVALID = 0xFFFF,
		DB_COMPRESSOR_ZLIB = 0x0,
		DB_COMPRESSOR_LZX = 0x1,
		DB_COMPRESSOR_PASSTHROUGH = 0x2,
	};
}