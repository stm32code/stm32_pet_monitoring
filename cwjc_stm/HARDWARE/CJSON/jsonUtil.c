#include "jsonUtil.h"
#include "cJSON.h"
#include "stdio.h"
 cJSON		* root;
cJSON		* itemName;
double temperatureLimit = 0;
int		flameLimit = 0;
int		gasLimit = 0;
int		smokeLimit = 0;



int  msg = 999;
int  g1 = 999;
int  g2 = 999;
int  g3 = 999;
int  g4 = 999;


extern int  bwindow,curtains,buzz,fan,ser;

extern float  tempL,turbidityL,o2L,lightL;
extern int keyStatus;
void parseJson( char* p )
{
	
	printf("\n\r json:%s\n\r",p);
	root		= cJSON_Parse( p );

//	bwindow,curtains,humidifier,fan,war;
	itemName	= cJSON_GetObjectItem( root, "buzz" );
	if ( itemName )
	{
			
		buzz = itemName->valueint;
	
	}

	

	cJSON_Delete( root );
	

}

int strIntercept( char *pcBuf, char *start, char *end, char *pcRes )
{
	int pcBegin	= NULL;
	int  pcEnd		= NULL;

	pcBegin = strstr( pcBuf, start );
	printf("begin:%s",pcBegin);
	/* printf( "pcBegin:%s \n", pcBegin ); */
	pcEnd = strstr( pcBuf, end );
	printf("pcEnd:%s",pcEnd);
	/* printf( "pcEnd:%s \n", pcEnd ); */
	if ( pcBegin == NULL || pcEnd == NULL || pcBegin > pcEnd )
	{
		printf( "Mail name not found!\n" );
	}else {
		/*	pcBegin += strlen(":"); */
		memcpy( pcRes, pcBegin + strlen( start ), pcEnd - pcBegin - strlen( start ) );
		printf("pcEnd:%s",pcRes);
	}

	return(1);
}
