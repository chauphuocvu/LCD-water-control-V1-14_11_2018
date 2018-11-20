/**
  ******************************************************************************
  * @file    httpclient-socket.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011  
  * @brief   Basic http server implementation using LwIP socket API   
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"
#include "fs.h"
#include "fsdata.h"
#include "string.h"
//#include "rfid_reader.h"
#include "stm32f4_discovery_user.h"

//#include "httpclient-socket.h"
/* Private typedef -----------------------------------------------------------*/
//static const char STR_TIMESTAMP_URL[] = "GET /timestamp ";
//static const char STR_CIK_HEADER[] = "X-Exosite-CIK: ";
//static const char STR_CONTENT_LENGTH[] = "Content-Length: ";
//static const char STR_READ_URL[] = "GET /onep:v1/stack/alias?";
//static const char STR_WRITE_URL[] = "POST /onep:v1/stack/alias ";
//static const char STR_ACTIVATE_URL[] = "POST /post.php ";
//static const char STR_RPC_URL[] = "POST /onep:v1/rpc/process ";
//static const char STR_HTTP[] = "HTTP/1.1";
//static const char STR_HOST[] = "Host: m2.exosite.com";
//static const char STR_ACCEPT[] = "Accept: application/x-www-form-urlencoded; charset=utf-8";
//static const char STR_ACCEPT_JSON[] = "Accept: application/json; charset=utf-8";
//static const char STR_CONTENT[] = "Content-Type: application/x-www-form-urlencoded; charset=utf-8";
//static const char STR_CONTENT_JSON[] = "Content-Type: application/json; charset=utf-8";
//static const char STR_CRLF[] = "\r\n";

//uint8_t CR95HF_Handle;
//uint8_t 	ReaderRecBuf[MAX_BUFFER_SIZE+3]; 	// buffer for SPI ou UART reception
/* Private define ------------------------------------------------------------*/
#define CLIENT_THREAD_PRIO    ( tskIDLE_PRIORITY + 3 )

//const struct sockaddr server_address = {AF_INET,14,"www.google.com"};
/**
  * @brief  http client thread 
  * @param arg: pointer on argument(not used here) 
  * @retval None
  */
void http_client_socket_thread(void *arg)
{
//	struct sockaddr_in server_address;
//	int sock;
//	int recv_data; 
//	char data_buffer[1500];
	//int8_t status =0;
//	uint8_t UIDout[ISO14443A_MAX_NBBYTE_UID];
//	do
//	{
//		CR95HF_IDN(ReaderRecBuf);
//		CR95HF_Handle = User_IsCR95HF();
//	}while(CR95HF_Handle !=RESULTOK);
	while(1)
	{
		// catch a 14 4443_A contacless tag
//		if((status =User_Get14443ATag (UIDout))==RESULTOK)
//		{
//			STM_EVAL_LEDOn(LED2);
//		}
//		if((status = User_Get14443BTag ())==RESULTOK)
//		{
//			STM_EVAL_LEDOn(LED2);
//		}
//		if((status =User_Get14443SRTag ())==RESULTOK)
//		{
//			STM_EVAL_LEDOn(LED2);
//		}
//		CR95HF_FieldOff();
//		//CR95HF_Echo(ReaderRecBuf);
//		do
//		{
//			CR95HF_Handle = User_IsCR95HF();
//		}while(CR95HF_Handle!=RESULTOK);
//		if(status==RESULTOK)
//		{
// 			 /* create a TCP socket */
// 			if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
// 			{
// 				printf("can not create socket");
// 				return;
// 			}
// 			
// 			server_address.sin_family = AF_INET;
// 			server_address.sin_addr.s_addr = inet_addr("31.170.165.228");
// 			server_address.sin_port = htons(80);
// 			if(connect(sock,(struct sockaddr*)&server_address,sizeof(server_address)) < 0)
// 			{

// 				printf("connect failed \n");
// 				close(sock);
// 			}
// 			else
// 			{
// 				printf("connect OK \n");
// 				
// 	 			strcat(data_buffer,"POST /post.php HTTP/1.1\r\n");
// 				strcat(data_buffer,"Host: www.rfidreader.16bm.com\r\n");
// 				strcat(data_buffer,"Host: www.rfidreader.16bm.com");
// 				strcat(data_buffer,"Content-Type: application/json; charset=utf-8\r\n");
// 				recv_data = send(sock,data_buffer,sizeof(data_buffer),0);
// 				if(recv_data < 0)
// 				{
// 					printf("Send failed \n");
// 					close(sock);
// 				}
// 				else
// 				{
// 					for(;;)
// 					{
// // 						recv_data = recv(sock,data_buffer,sizeof(data_buffer),MSG_DONTWAIT);
// // 						if(recv_data < 0)
// // 						{
// // 							recv_data = recv(sock,data_buffer,sizeof(data_buffer),MSG_DONTWAIT);
// // 							if(recv_data<0)
// // 							{
// // 								printf("recv failed \n");
// // 								break;
// // 							}
// // 						}
// 						recv_data = read(sock,data_buffer,sizeof(data_buffer));
// 						if(recv_data<0)
// 						{
// 							printf("Recv failed \n");
// 							break;
// 						}
// 						else if(recv_data >0)
// 						{
// 							data_buffer[recv_data] = '\0';
// 							printf("Received data: %s\n",data_buffer);
// 						}
// 						else
// 						{
// 							printf("Received Data = 0\n");
// 							break;
// 						}
// 					}
// 					close(sock);
// 				}
// 			}
//		}
//		else
//		{
//			STM_EVAL_LEDOff(LED2);
//		}
		vTaskDelay(500);
	}
}
/**
  * @brief  Initialize the HTTP Client (start its thread) 
  * @param  none
  * @retval None
  */
void http_client_socket_init()
{
	sys_thread_new("HTTPSERVER", http_client_socket_thread, NULL, DEFAULT_THREAD_STACKSIZE * 2, CLIENT_THREAD_PRIO);
}
