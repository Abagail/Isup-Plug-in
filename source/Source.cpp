#include "SDK\amx\amx.h"
#include "SDK\plugincommon.h"

#include "Query/query.h"


typedef void(*logprintf_t)(char* format, ...);


logprintf_t logprintf;
extern void *pAMXFunctions;

int PING_TIMEOUT = 100;
cell AMX_NATIVE_CALL Server_SetPingTimeout(AMX *amx, cell* params)
{
	if (PING_TIMEOUT != params[1])
	{
		PING_TIMEOUT = params[1];
	}
	return 0;
}
cell AMX_NATIVE_CALL Server_IsOnline(AMX* amx, cell* params)
{
	int
		len = NULL,
		ret = NULL,
		port = params[2];

	cell *addr;

	amx_GetAddr(amx, params[1], &addr);
	amx_StrLen(addr, &len);

	if (len)
	{
		len++;

		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		Query query(text, port);
		std::string recvval = query.Ping("1000", PING_TIMEOUT);
		if (recvval.empty())
		{
			delete[] text;
			return 0;
		}
		const char* val = new char[5];
		val = recvval.c_str();
		int PingVar;
		PingVar = strtol(val, 0, 10);

		delete[] text;
		return PingVar;
	}
	return 0;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("IsUp plugin by Abagail loaded.");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("IsUp plugin by Abagail unloaded.");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "IsServerOnline", Server_IsOnline },
	{ "set_ping_timeout", Server_SetPingTimeout },
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
