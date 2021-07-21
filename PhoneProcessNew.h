#ifndef _PHONE_PROCESS_NEW_H
#define _PHONE_PROCESS_NEW_H


/*************************************************************************************/
/*************************************************************************************/
//
// !!! 해당 프로세스 가동시 PhoneProcess는 중지해야함!!!!
//
/*************************************************************************************/
/*************************************************************************************/


/*************************************************************************************
 * Defines....
 *************************************************************************************/

#define MAX_WEATHER_STATUS			16

#define GRID_TIME					900
#define GRID_X						0.05
#define GRID_Y						0.05
#define GRID_X_EXTRA				0.1
#define GRID_Y_EXTRA				0.1

#define WEATHER_STATUS_1ST			'1'
#define WEATHER_STATUS_2ND			'2'
#define WEATHER_STATUS_2ND_EXTRA	'B'


#define PARSE_DATA(V, T, P)	if ( (ptr = get_next_token(buff, ptr, token, ';')) <= 0 || (strlen(token) < 1) ) \
							{ \
								Log("ParseMWSData: " T " 세팅 에러!\n"); \
								return (-1); \
							} \
							else \
							{ \
								pdata->V = P(token); \
							}

#define PARSE_STRING(V, T)	if ( (ptr = get_next_token(buff, ptr, token, ';')) <= 0 || (strlen(token) < 1) ) \
							{ \
								Log("ParseMWSData: " T " 세팅 에러!\n"); \
								return (-1); \
							} \
							else \
							{ \
								strcpy(pdata->V, token); \
								str_trim(pdata->V, TRIM_ALL); \
							}

#define PARSE_CHAR(V, T)	if ( (ptr = get_next_token(buff, ptr, token, ';')) <= 0 || (strlen(token) < 1) ) \
							{ \
								Log("ParseMWSData: " T " 세팅 에러!\n"); \
								return (-1); \
							} \
							else \
							{ \
								pdata->V = token[0]; \
							}
							
typedef struct
{
	int			data_date;			/* 날짜 */
	int			data_time;			/* 시간 */
	int			user_num;			/* 사용자고유번호 */
	char		ip[16];				/* 관측IP */
	double		lng;				/* 경도 */
	double		lat;				/* 위도 */
	double		PRE;				/* 기압 */
	char		w_status;			/* 기상제보 */
	char		w_group;			/* 기상제보그룹 */
	
	int			QC_PRE;
	char		QC_PRE_ERR[256];
	
	int			QC_W;
	char		QC_W_ERR[256];
	
	int			QC_NOW;
	char		QC_NOW_ERR[256];
	
	char		f_QC_W;
	int			date_idx;
} PHONE_DATA;

typedef struct
{
	char		status;
	int			count;
} FDATA;

/*************************************************************************************
 * Global 변수 정의
 *************************************************************************************/
 
char				program_name[64];
int 				process_id;

sql_context			ctx;
char				raw_file_name[256];

/*************************************************************************************
 * 함수 정의
 *************************************************************************************/

int		ParsePhoneData(char* buff, PHONE_DATA* pdata);
int		ProcessWeatherStatus2nd(time_t ftime);

int		QC_WeatherStatus(char step, PHONE_DATA* pdata);
int		QC_WeatherStatusNOW(char step, PHONE_DATA* pdata);
int		_qsort_wstatus( const void *a, const void *b );

int		InsertPhoneData(PHONE_DATA* pdata);
int		UpdatePhoneData(PHONE_DATA* pdata);
int		InsertQCError(int data_date, int date_idx, char qc_type, char* msg);
int		UpdatePhoneCount(PHONE_DATA* pdata);

void	InitServer();
void	interrupt(int sig);

#endif
