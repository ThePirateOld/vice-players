//-----------------------------------------------------
//
// VC:Players Multiplayer Modification For GTA:VC
// Copyright 2010 GTA:Online team
//
// File Authors: Christopher
//               adamix
// License: See LICENSE in root directory
//
//-----------------------------------------------------

#include "StdInc.h"

extern CNetGame *pNetGame;

using namespace RakNet;

// Vehicle natives //

// createVehicle
SQInteger sq_createVehicle(SQVM * pVM)
{
	SQInteger byteVehicleType;
	Vector3 pos;
	float fRotation;
	SQInteger iColor1, iColor2;
	sq_getinteger(pVM, -7, &byteVehicleType);
	sq_getfloat(pVM, -6, &pos.X);
	sq_getfloat(pVM, -5, &pos.Y);
	sq_getfloat(pVM, -4, &pos.Z);
	sq_getfloat(pVM, -3, &fRotation);
	sq_getinteger(pVM, -2, &iColor1);
	sq_getinteger(pVM, -1, &iColor2);


	int vehID = pNetGame->GetVehiclePool()->New(byteVehicleType, &pos, fRotation, iColor1, iColor2);
	CVehicle *pVehicle = pNetGame->GetVehiclePool()->GetAt(vehID);
	pVehicle->SpawnForWorld();
	sq_pushinteger(pVM, vehID);
	return 1;
}

// destroyVehicle
SQInteger sq_destroyVehicle(SQVM * pVM)
{
	SQInteger byteVehicle;
	sq_getinteger(pVM, -1, &byteVehicle);
	if(pNetGame->GetVehiclePool()->GetSlotState(byteVehicle))
	{
		pNetGame->GetVehiclePool()->Delete(byteVehicle);
		sq_pushbool(pVM, true);

		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

// setVehicleHealth
SQInteger sq_setVehicleHealth(SQVM * pVM)
{
	SQInteger vehicle;
	float newHealthValue;

	sq_getinteger(pVM, -2, &vehicle);
    sq_getfloat(pVM, -1, &newHealthValue);
	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		pNetGame->GetVehiclePool()->GetAt(vehicle)->SetHealth(newHealthValue);

		sq_pushbool(pVM, true);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger sq_getVehicleHealth(SQVM * pVM)
{
	SQInteger vehicle;

	sq_getinteger(pVM, -1, &vehicle);

	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		float fHealth = pNetGame->GetVehiclePool()->GetAt(vehicle)->GetHealth();

		sq_pushfloat(pVM, fHealth);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

// setVehicleColor
SQInteger sq_setVehicleColor(SQVM * pVM)
{
	SQInteger vehicle, color1, color2;

	sq_getinteger(pVM, -3, &vehicle);
    sq_getinteger(pVM, -2, &color1);
	sq_getinteger(pVM, -1, &color2);
	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		pNetGame->GetVehiclePool()->GetAt(vehicle)->SetColor(color1, color2);

		sq_pushbool(pVM, true);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger sq_getVehicleColors(SQVM * pVM)
{
	SQInteger vehicle;

	sq_getinteger(pVM, -1, &vehicle);

	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		int iColors[2];
		pNetGame->GetVehiclePool()->GetAt(vehicle)->GetColor(&iColors[0], &iColors[1]);

		sq_newarray(pVM, 0);
		sq_pushinteger(pVM, iColors[0]);
		sq_arrayappend(pVM, -2);
		sq_pushinteger(pVM, iColors[1]);
		sq_arrayappend(pVM, -2);
		sq_push(pVM, -1);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

// getVehicleTurnSpeed
SQInteger sq_getVehicleTurnSpeed(SQVM * pVM)
{
	Vector3 speed;
	SQInteger vehicle;
	sq_getinteger(pVM, -1, &vehicle);

	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		CVehicle *pVehicle = pNetGame->GetVehiclePool()->GetAt(vehicle);
		pVehicle->GetTurnSpeed(&speed);

		sq_newarray(pVM, 0);
		sq_pushfloat(pVM, speed.X);
		sq_arrayappend(pVM, -2);
		sq_pushfloat(pVM, speed.Y);
		sq_arrayappend(pVM, -2);
		sq_pushfloat(pVM, speed.Z);
		sq_arrayappend(pVM, -2);
		sq_push(pVM, -1);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}

// getVehicleMoveSpeed
SQInteger sq_getVehicleMoveSpeed(SQVM * pVM)
{
	Vector3 speed;
	SQInteger vehicle;
	sq_getinteger(pVM, -1, &vehicle);

	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		CVehicle *pVehicle = pNetGame->GetVehiclePool()->GetAt(vehicle);
		pVehicle->GetMoveSpeed(&speed);

		sq_newarray(pVM, 0);
		sq_pushfloat(pVM, speed.X);
		sq_arrayappend(pVM, -2);
		sq_pushfloat(pVM, speed.Y);
		sq_arrayappend(pVM, -2);
		sq_pushfloat(pVM, speed.Z);
		sq_arrayappend(pVM, -2);
		sq_push(pVM, -1);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}

// getVehiclePos
SQInteger sq_getVehiclePosition(SQVM * pVM)
{
	Vector3 pos;
	SQInteger vehicle;
	sq_getinteger(pVM, -1, &vehicle);

	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		CVehicle *pVehicle = pNetGame->GetVehiclePool()->GetAt(vehicle);
		pVehicle->GetPosition(&pos);

		sq_newarray(pVM, 0);
		sq_pushfloat(pVM, pos.X);
		sq_arrayappend(pVM, -2);
		sq_pushfloat(pVM, pos.Y);
		sq_arrayappend(pVM, -2);
		sq_pushfloat(pVM, pos.Z);
		sq_arrayappend(pVM, -2);
		sq_push(pVM, -1);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}

// setVehiclePos
SQInteger sq_setVehiclePosition(SQVM * pVM)
{
	SQInteger vehicle;

	Vector3 pVec;

	sq_getinteger(pVM, -4, &vehicle);
	sq_getfloat(pVM, -3, &pVec.X);
	sq_getfloat(pVM, -2, &pVec.Y);
	sq_getfloat(pVM, -1, &pVec.Z);

	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		RakNet::BitStream bsSend;
		bsSend.Write(vehicle);
		bsSend.Write((char *)&pVec, sizeof(Vector3));
		pNetGame->GetRPC4()->Call("Script_SetVehiclePos",&bsSend,HIGH_PRIORITY,RELIABLE,0,UNASSIGNED_SYSTEM_ADDRESS,true);

		sq_pushbool(pVM, true);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}

// setVehicleTurnSpeed
SQInteger sq_setVehicleTurnSpeed(SQVM * pVM)
{
	SQInteger vehicle;

	Vector3 pVec;

	sq_getinteger(pVM, -4, &vehicle);
	sq_getfloat(pVM, -3, &pVec.X);
	sq_getfloat(pVM, -2, &pVec.Y);
	sq_getfloat(pVM, -1, &pVec.Z);

	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		RakNet::BitStream bsSend;
		bsSend.Write(vehicle);
		bsSend.Write((char *)&pVec, sizeof(Vector3));
		pNetGame->GetRPC4()->Call("Script_SetVehicleTurnSpeed",&bsSend,HIGH_PRIORITY,RELIABLE,0,UNASSIGNED_SYSTEM_ADDRESS,true);

		sq_pushbool(pVM, true);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}

// setVehicleMoveSpeed
SQInteger sq_setVehicleMoveSpeed(SQVM * pVM)
{
	SQInteger vehicle;

	Vector3 pVec;

	sq_getinteger(pVM, -4, &vehicle);
	sq_getfloat(pVM, -3, &pVec.X);
	sq_getfloat(pVM, -2, &pVec.Y);
	sq_getfloat(pVM, -1, &pVec.Z);

	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		RakNet::BitStream bsSend;
		bsSend.Write(vehicle);
		bsSend.Write((char *)&pVec, sizeof(Vector3));
		pNetGame->GetRPC4()->Call("Script_SetVehicleMoveSpeed",&bsSend,HIGH_PRIORITY,RELIABLE,0,UNASSIGNED_SYSTEM_ADDRESS,true);

		sq_pushbool(pVM, true);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}

// Added by VC-Players team.
SQInteger sq_popVehicleTrunk(SQVM * pVM)
{
	SQInteger vehicle;

	sq_getinteger(pVM, -1, &vehicle);

	if(pNetGame->GetVehiclePool()->GetSlotState(vehicle))
	{
		pNetGame->GetVehiclePool()->GetAt(vehicle)->PopTrunk();

		sq_pushbool(pVM, true);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}