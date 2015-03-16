#if !defined USING_SERVER_ISUP
	#define USING_SERVER_ISUP true
	
	#define SERVER_ISUP_INCLUDE_VER 1
#endif

native IsServerOnline(IP[], port=7777);
native get_ping_timeout();
native set_ping_timeout(timeout);