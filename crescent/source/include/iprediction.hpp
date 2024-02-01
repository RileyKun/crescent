#pragma once
#include <cstdint>
#include "c_tf_player.hpp"
#include "usercmd.hpp"

class CGlobalVarsBase
{
public:
	float realtime;
	int framecount;
	float absoluteframetime;
	float curtime;
	float frametime;
	int maxclients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
};

class CMoveData
{
public:
	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;
	uint32_t m_nPlayerHandle;
	int m_nImpulseCommand;
	vec3_t m_vecViewAngles;
	vec3_t m_vecAbsViewAngles;
	int m_nButtons;
	int m_nOldButtons;
	float m_flForwardMove;
	float m_flOldForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	float m_flMaxSpeed;
	float m_flClientMaxSpeed;
	vec3_t m_vecVelocity;
	vec3_t m_vecAngles;
	vec3_t m_vecOldAngles;
	float m_outStepHeight;
	vec3_t m_outWishVel;
	vec3_t m_outJumpVel;
	vec3_t m_vecConstraintCenter;
	float m_flConstraintRadius;
	float m_flConstraintWidth;
	float m_flConstraintSpeedFactor;
	vec3_t m_vecAbsOrigin;
};

class IPrediction
{
public:
	virtual ~IPrediction(void) {};
	virtual void Init(void) = 0;
	virtual void Shutdown(void) = 0;
	virtual void Update(int startframe, bool validframe, int incoming_acknowledged, int outgoing_command) = 0;
	virtual void PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) = 0;
	virtual void PostEntityPacketReceived(void) = 0;
	virtual void PostNetworkDataReceived(int commands_acknowledged) = 0;
	virtual void OnReceivedUncompressedPacket(void) = 0;
	virtual void GetViewOrigin(vec3_t& org) = 0;
	virtual void SetViewOrigin(vec3_t& org) = 0;
	virtual void GetViewAngles(vec3_t& ang) = 0;
	virtual void SetViewAngles(vec3_t& ang) = 0;
	virtual void GetLocalViewAngles(vec3_t& ang) = 0;
	virtual void SetLocalViewAngles(vec3_t& ang) = 0;
};

class CPrediction : public IPrediction
{
public:
	virtual ~CPrediction();
	virtual void Init();
	virtual void Shutdown();
	virtual void Update(int startframe, bool validframe, int incoming_acknowledged, int outgoing_command);
	virtual void OnReceivedUncompressedPacket();
	virtual void PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet);
	virtual void PostEntityPacketReceived();
	virtual void PostNetworkDataReceived(int commands_acknowledged);
	virtual bool InPrediction();
	virtual bool IsFirstTimePredicted();
	virtual int	GetIncomingPacketNumber();
	virtual void GetViewOrigin(vec3_t& org);
	virtual void SetViewOrigin(vec3_t& org);
	virtual void GetViewAngles(vec3_t& ang);
	virtual void SetViewAngles(vec3_t& ang);
	virtual void GetLocalViewAngles(vec3_t& ang);
	virtual void SetLocalViewAngles(vec3_t& ang);
	virtual void RunCommand(player_t* player, CUserCmd* ucmd, void* moveHelper);
	virtual void SetupMove(player_t* player, CUserCmd* ucmd, void* pHelper, CMoveData* move);
	virtual void FinishMove(player_t* player, CUserCmd* ucmd, CMoveData* move);
	virtual void SetIdealPitch(player_t* player, const vec3_t& origin, const vec3_t& angles, const vec3_t& viewheight);
	virtual void _Update(bool received_new_world_update, bool validframe, int incoming_acknowledged, int outgoing_command);

	uint32_t m_hLastGround;
	bool m_bInPrediction;
	bool m_bFirstTimePredicted;
	bool m_bOldCLPredictValue;
	bool m_bEnginePaused;
	int m_nPreviousStartFrame;
	int m_nCommandsPredicted;
	int m_nServerCommandsAcknowledged;
	int m_bPreviousAckHadErrors;
	int m_nIncomingPacketNumber;
	float m_flIdealPitch;
};

//-----------------------------------------------------------------------------
// Purpose: The basic player movement interface
//-----------------------------------------------------------------------------

class IGameMovement
{
public:
	virtual			~IGameMovement(void) {}

	// Process the current movement command
	virtual void	ProcessMovement(player_t* pPlayer, CMoveData * pMove) = 0;
	virtual void	StartTrackPredictionErrors(player_t* pPlayer) = 0;
	virtual void	FinishTrackPredictionErrors(player_t* pPlayer) = 0;
	virtual void	DiffPrint(char const* fmt, ...) = 0;

	// Allows other parts of the engine to find out the normal and ducked player bbox sizes
	virtual vec3_t	GetPlayerMins(bool ducked) const = 0;
	virtual vec3_t	GetPlayerMaxs(bool ducked) const = 0;
	virtual vec3_t  GetPlayerViewOffset(bool ducked) const = 0;

};
