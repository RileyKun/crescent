#pragma once
#include "vfunc.hpp"
#include "util.hpp"
#include "view_shared.hpp"
#include "netchannel.hpp"

typedef struct player_info_s {
	char			name[32];
	int				userID;
	char			guid[33];
	unsigned long	friendsID;
	char			friendsName[32];
	bool			fakeplayer;
	bool			ishltv;
	unsigned long	customFiles[4];
	std::byte	filesDownloaded;
} player_info_t;

class CClockDriftMgr
{
private:
	enum
	{
		// This controls how much it smoothes out the samples from the server.
		NUM_CLOCKDRIFT_SAMPLES = 16
	};

	// This holds how many ticks the client is ahead each time we get a server tick.
	// We average these together to get our estimate of how far ahead we are.
	float m_ClockOffsets[NUM_CLOCKDRIFT_SAMPLES];
	int m_iCurClockOffset;

	int m_nServerTick;		// Last-received tick from the server.
	int	m_nClientTick;		// The client's own tick counter (specifically, for interpolation during rendering).
	// The server may be on a slightly different tick and the client will drift towards it.
};

class CClientState
{
public:
	byte pad0[0x10];
	INetChannel* m_NetChannel;			// 0x10
	byte pad1[0x140];
	CClockDriftMgr	m_ClockDriftMgr;		// 0x154
	int				m_nDeltaTick;			// 0x1A0
	byte pad2[0x110];
	int				m_nMaxClients;			// 0x2B4	
	byte pad3[0x486C];
	int				lastoutgoingcommand;	// 0x4B24
	int				chokedcommands;			// 0x4B28
	int				last_command_ack;		// 0x4B2C
};

class IVEngineClient {
public:
	void GetScreenSize(int& width, int& height) {
		return call_vfunc< void(__thiscall*)(void*, int&, int&) >(this, 5)(this, width, height);
	}

	void ClientCmd(const char* command) {
		return call_vfunc< void(__thiscall*)(void*, const char*) >(this, 7)(this, command);
	}

	bool GetPlayerInfo(int index, player_info_t* info) {
		return call_vfunc< bool(__thiscall*)(void*, int, player_info_t*) >(this, 8)(this, index, info);
	}

	int GetPlayerForUserID(int UserID) {
		return call_vfunc< int(__thiscall*)(void*, int) >(this, 9)(this, UserID);
	}

	bool Cov_IsVisible() {
		return call_vfunc< bool(__thiscall*)(void*) >(this, 11)(this);
	}

	int GetLocalPlayer() {
		return call_vfunc< int(__thiscall*)(void*) >(this, 12)(this);
	}

	float Time() {
		return call_vfunc< float(__thiscall*)(void*) >(this, 14)(this);
	}

	void GetViewAngles(vec3_t& angles) {
		return call_vfunc< void(__thiscall*)(void*, vec3_t&) >(this, 19)(this, angles);
	}

	vec3_t GetViewAngles( ) {
		vec3_t temp = vec3_t( );
		GetViewAngles( temp );
		return temp;
	}

	void SetViewAngles(vec3_t& angles) {
		return call_vfunc< void(__thiscall*)(void*, vec3_t&) >(this, 20)(this, angles);
	}

	const matrix3x4_t& GetWorldToScreenMatrix() {
		return call_vfunc< const matrix3x4_t & (__thiscall*)(void*) >(this, 36)(this);
	}

	int GetMaxClients() {
		return call_vfunc< int(__thiscall*)(void*) >(this, 21)(this);
	}

	bool IsInGame() {
		return call_vfunc< bool(__thiscall*)(void*) >(this, 26)(this);
	}

	bool IsConnected() {
		return call_vfunc< bool(__thiscall*)(void*) >(this, 27)(this);
	}

	void ClientCmd_Unrestricted(const char* command) {
		return call_vfunc< void(__thiscall*)(void*, const char*) >(this, 106)(this, command);
	}

	INetChannelInfo* GetNetChannelInfo() {
		return call_vfunc< INetChannelInfo * (__thiscall*)(void*) >(this, 72)(this);
	}
};