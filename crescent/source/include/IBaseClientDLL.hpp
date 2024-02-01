#pragma once
#include <cstddef>
#include "vfunc.hpp"
#include "view_shared.hpp"

class RecvTable;

//-----------------------------------------------------------------------------
// Purpose: The engine reports to the client DLL what stage it's entering so the DLL can latch events
//  and make sure that certain operations only happen during the right stages.
// The value for each stage goes up as you move through the frame so you can check ranges of values
//  and if new stages get added in-between, the range is still valid.
//-----------------------------------------------------------------------------
enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

enum struct classid_t;

typedef void* ( *create_client_class_fn )( int, int );
typedef void* ( *create_event_fn )( );

class ClientClass {
public:
	create_client_class_fn create_fn;
	create_event_fn create_event_fn;
	char* network_name;
	RecvTable* recv_table;
	ClientClass* next_class;
	classid_t class_id;
};

using client_class_t = ClientClass;

class IBaseClientDLL {
public:
	ClientClass* GetAllClasses() {
		return call_vfunc< ClientClass * (__thiscall*)(void*) >(this, 8)(this);
	}

	bool WriteUsercmdDeltaToBuffer(bf_write* buf, int from, int to, bool isnewcommand) {
		return call_vfunc<bool(__thiscall*)(PVOID, bf_write*, int, int, bool)>(this, 23)(this, buf, from, to, isnewcommand);
	}

	bool GetPlayerView( CViewSetup& setup ) {
		return call_vfunc<bool(__thiscall*)(PVOID, CViewSetup&)>(this, 59)(this, setup);
	}
};