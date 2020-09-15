#include <QtCore/QCoreApplication>
#include "visa.h"
#include "ivi.h"
/*----------------------------------------------------------------------------*/
/* 宏定义声明                                                                 */
/*----------------------------------------------------------------------------*/
#define MAX_SCPI_LENGTH 255                         // 最大的SCPI命令 
#define DEFAULT_TIMEOUT 5000                    // 超时:5000ms   
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	ViStatus nReturnStatus = 0;
	ViSession rmSession = 0, pnInstrHandle;
	ViUInt32 retCnt = 0;
	ViByte wrtBuf[MAX_SCPI_LENGTH];                     // 写缓冲区
	ViByte rdBuf[MAX_SCPI_LENGTH];                      // 读缓冲区
	int Return_Count;

	nReturnStatus = viOpenDefaultRM(&rmSession);
	nReturnStatus = viOpen(rmSession, "TCPIP0::172.141.114.6::5001::SOCKET", VI_NULL, VI_NULL, &pnInstrHandle);

	/*- Configure VISA Formatted I/O ----------------------------------------*/
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_TMO_VALUE, DEFAULT_TIMEOUT);        // 设置超时
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SUPPRESS_END_EN, VI_FALSE);        // 不发送终止符
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SEND_END_EN, VI_FALSE);        // 不接收终止符

	nReturnStatus = viQueryf(pnInstrHandle, "*IDN?\n", "%s", rdBuf);
	viClose(pnInstrHandle);
	viClose(rmSession);
	return a.exec();
}
