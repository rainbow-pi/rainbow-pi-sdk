#ifndef  _GSENSOR_H_
#define  _GSENSOR_H_

/*******************************************/
//输入参数
/*******************************************/
typedef	  struct
{
	    struct
		{
			   float xa;//x轴加速度
			   float ya;//y轴加速度
			   float za;//z轴加速度
		}data;

}GFRAMEIN;

/*******************************************/
//输出参数
/*******************************************/

typedef struct
{
	    struct
		{
			  int    isStop;//是否停止
			  float  a;     //加速度
			  float  v;     //车速		
		}data;

}GSENSOROUT;


/*******************************************/
//初始化参数
/*******************************************/
typedef struct
{
	    char *version;  //版本号,不需要输入，调用初始化函数后可以读取
		int  enable;    //是否有gsensor模块
}GSENSORIN;

///*******************************************/
typedef void (*GsensorIn)(GFRAMEIN &frameIn,void *dv);
typedef void (*GsensorOut)(GSENSOROUT &gsensorOut,void *dv);
extern GsensorIn  gcallbackIn;
extern GsensorOut gcallbackOut;


//#ifdef __cplusplus
//extern "C" {
//#endif
///*******************************************/
void InitialGsensor(GSENSORIN &gsensorIn, void **dev);
///*******************************************/
void ReleaseGsensor();
/*******************************************/
//#ifdef __cplusplus
//}  /* end of extern "C" */
//#endif
#endif