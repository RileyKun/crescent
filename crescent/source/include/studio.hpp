#pragma once
#include "vector.hpp"

struct mstudiobbox_t
{
	int					bone;
	int					group;
	vec3_t				bbmin;
	vec3_t				bbmax;
	int					szhitboxnameindex;
	vec3_t angle;
	float radius;
	uint8_t _padding[ 0x10 ];
};

struct mstudiohitboxset_t
{
	int					sznameindex;
	inline char* const	pszName(void) const { return ((char*)this) + sznameindex; }
	int					numhitboxes;
	int					hitboxindex;
	inline mstudiobbox_t* pHitbox(int i) const { return (mstudiobbox_t*)(((std::byte*)this) + hitboxindex) + i; };
};

struct mstudiobone_t
{
	int					sznameindex;
	inline char* const pszName(void) const { return ((char*)this) + sznameindex; }
	int		 			parent;
	int					bonecontroller[6];
	vec3_t				pos;
	float				quat[4];
	vec3_t				rot;
	vec3_t				posscale;
	vec3_t				rotscale;
	float				poseToBone[3][4];
	float				qAlignment[4];
	int					flags;
	int					proctype;
	int					procindex;
	mutable int			physicsbone;
	inline void* pProcedure() const { if (procindex == 0) return NULL; else return  (void*)(((std::byte*)this) + procindex); };
	int					surfacepropidx;
	inline char* const pszSurfaceProp(void) const { return ((char*)this) + surfacepropidx; }
	int					contents;
	int					unused[8];
};

struct studiohdr_t
{
	int id;
	int version;
	int checksum;
	char name[64];
	int length;
	vec3_t eyeposition;
	vec3_t illumposition;
	vec3_t hull_min;
	vec3_t hull_max;
	vec3_t view_bbmin;
	vec3_t view_bbmax;
	int flags;
	int numbones;
	int boneindex;
	inline mstudiobone_t* GetBone(int i) const { return (mstudiobone_t*)(((std::byte*)this) + boneindex) + i; };

	int numbonecontrollers;
	int bonecontrollerindex;
	int numhitboxsets;
	int hitboxsetindex;

	mstudiohitboxset_t* GetHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((std::byte*)this) + hitboxsetindex) + i;
	}

	inline mstudiobbox_t* GetHitbox(int i, int set) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet(set);

		if (!s)
			return NULL;

		return s->pHitbox(i);
	}

	inline int GetHitboxCount(int set) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet(set);

		if (!s)
			return 0;

		return s->numhitboxes;
	}

	int numlocalanim;
	int localanimindex;
	int numlocalseq;
	int localseqindex;
	mutable int activitylistversion;
	mutable int eventsindexed;
	int numtextures;
	int textureindex;
	int numcdtextures;
	int cdtextureindex;
	int numskinref;
	int numskinfamilies;
	int skinindex;
	int numbodyparts;
	int bodypartindex;
	int numlocalattachments;
	int localattachmentindex;
	int numlocalnodes;
	int localnodeindex;
	int localnodenameindex;
	int numflexdesc;
	int flexdescindex;
	int numflexcontrollers;
	int flexcontrollerindex;
	int numflexrules;
	int flexruleindex;
	int numikchains;
	int ikchainindex;
	int nummouths;
	int mouthindex;
	int numlocalposeparameters;
	int localposeparamindex;
	int surfacepropindex;
	int keyvalueindex;
	int keyvaluesize;
	int numlocalikautoplaylocks;
	int localikautoplaylockindex;
	float mass;
	int contents;
	int numincludemodels;
	int includemodelindex;
	mutable void* virtualModel;
	int szanimblocknameindex;
	int numanimblocks;
	int animblockindex;
	mutable void* animblockModel;
	int bonetablebynameindex;
	void* pVertexBase;
	void* pIndexBase;
	std::byte constdirectionallightdot;
	std::byte rootLOD;
	std::byte numAllowedRootLODs;
	std::byte unused[1];
	int unused4;
	int numflexcontrollerui;
	int	flexcontrolleruiindex;
	float flVertAnimFixedPointScale;
	int	unused3[1];
	int	studiohdr2index;
	int	unused2[1];
};