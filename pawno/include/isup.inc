#if !defined USING_SERVER_ISUP
	#define USING_SERVER_ISUP true
	
	#define SERVER_ISUP_INCLUDE_VER 1
#endif

native IsServerOnline(IP[], port=7777);

// Upcoming features
native GetServerInformation(IP[], port=7777);
