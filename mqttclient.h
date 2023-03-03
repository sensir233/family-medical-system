#ifndef __MALLOC_H
#define __MALLOC_H
#include "stm32f10x.h"

#define   MSG_MAX_LEN     500
#define   MSG_TOPIC_LEN   50
#define   KEEPLIVE_TIME   300
#define   MQTT_VERSION    4

#if    LWIP_DNS
#define   HOST_NAME       "a161a58a78.iot-mqtts.cn-north-4.myhuaweicloud.com"//"a1VVK6fd3qB.iot-as-mqtt.cn-shanghai.aliyuncs.com"     //����������
#else
#define   HOST_NAME       "121.36.42.100"//"47.102.164.191"     //������IP��ַ
#endif


#define   HOST_PORT     1883   //������TCP���ӣ��˿ڱ�����1883

#define   CLIENT_ID     "628215c623aaf461a0f8b6c0_26262625_0_0_2022051609"//"ESP8266_TEST|securemode=3,signmethod=hmacsha1|"         //
#define   USER_NAME     "628215c623aaf461a0f8b6c0_26262625"//"ESP8266_TEST&a1Oaa9Ce83b"     //�û���
#define   PASSWORD      "9785918cabe1c87f2fa15a26d37d25e2e2721d57503a7be927fe39bd0a437a0b"//"C33620BFC4FBACEFAC52CE03BD9559104662C8DF"  //��Կ

#define   TOPIC         "$oc/devices/628215c623aaf461a0f8b6c0_26262625/sys/messages/down"//"/a1VVK6fd3qB/wlwtest/user/LEDDY"//"cmd/5538e9a0769540b1a01e2cca5a6b6d12/datadown"      //���ĵ�����
#define   PUBTOPIC      "$oc/devices/628215c623aaf461a0f8b6c0_26262625/sys/properties/report"//"/a1VVK6fd3qB/wlwtest/user/temp"      //����������

enum QoS 
{ QOS0 = 0, 
  QOS1, 
  QOS2 
};

enum MQTT_Connect
{
  Connect_OK = 0,
  Connect_NOK,
  Connect_NOTACK
};

//���ݽ����ṹ��
typedef struct __MQTTMessage
{
    uint32_t qos;
    uint8_t retained;
    uint8_t dup;
    uint16_t id;
	  uint8_t type;
    void *payload;
    int32_t payloadlen;
}MQTTMessage;

//�û�������Ϣ�ṹ��
typedef struct __MQTT_MSG
{
	  uint8_t  msgqos;                 //��Ϣ����
		uint8_t  msg[MSG_MAX_LEN];       //��Ϣ
	  uint32_t msglenth;               //��Ϣ����
	  uint8_t  topic[MSG_TOPIC_LEN];   //����    
	  uint16_t packetid;               //��ϢID
	  uint8_t  valid;                  //������Ϣ�Ƿ���Ч
}MQTT_USER_MSG;

//������Ϣ�ṹ��
typedef struct
{
    int8_t topic[MSG_TOPIC_LEN];
    int8_t qos;
    int8_t retained;

    uint8_t msg[MSG_MAX_LEN];
    uint8_t msglen;
} mqtt_recv_msg_t, *p_mqtt_recv_msg_t, mqtt_send_msg_t, *p_mqtt_send_msg_t;


void mqtt_thread( void *pvParameters);

/************************************************************************
** ��������: my_mqtt_send_pingreq								
** ��������: ����MQTT������
** ��ڲ���: ��
** ���ڲ���: >=0:���ͳɹ� <0:����ʧ��
** ��    ע: 
************************************************************************/
int32_t MQTT_PingReq(int32_t sock);

/************************************************************************
** ��������: MQTT_Connect								
** ��������: ��¼������
** ��ڲ���: int32_t sock:����������
** ���ڲ���: Connect_OK:��½�ɹ� ����:��½ʧ��
** ��    ע: 
************************************************************************/
uint8_t MQTT_Connect(void);

/************************************************************************
** ��������: MQTTSubscribe								
** ��������: ������Ϣ
** ��ڲ���: int32_t sock���׽���
**           int8_t *topic������
**           enum QoS pos����Ϣ����
** ���ڲ���: >=0:���ͳɹ� <0:����ʧ��
** ��    ע: 
************************************************************************/
int32_t MQTTSubscribe(char *topic,enum QoS pos);

/************************************************************************
** ��������: UserMsgCtl						
** ��������: �û���Ϣ������
** ��ڲ���: MQTT_USER_MSG  *msg����Ϣ�ṹ��ָ��
** ���ڲ���: ��
** ��    ע: 
************************************************************************/
void UserMsgCtl(MQTT_USER_MSG  *msg);

/************************************************************************
** ��������: GetNextPackID						
** ��������: ������һ�����ݰ�ID
** ��ڲ���: ��
** ���ڲ���: uint16_t packetid:������ID
** ��    ע: 
************************************************************************/
uint16_t GetNextPackID(void);

/************************************************************************
** ��������: mqtt_msg_publish						
** ��������: �û�������Ϣ
** ��ڲ���: MQTT_USER_MSG  *msg����Ϣ�ṹ��ָ��
** ���ڲ���: >=0:���ͳɹ� <0:����ʧ��
** ��    ע: 
************************************************************************/
//int32_t MQTTMsgPublish(int32_t sock, char *topic, int8_t qos, int8_t retained,uint8_t* msg,uint32_t msg_len);
int32_t MQTTMsgPublish(char *topic, int8_t qos, uint8_t* msg);
/************************************************************************
** ��������: ReadPacketTimeout					
** ��������: ������ȡMQTT����
** ��ڲ���: int32_t sock:����������
**           uint8_t *buf:���ݻ�����
**           int32_t buflen:��������С
**           uint32_t timeout:��ʱʱ��--0-��ʾֱ�Ӳ�ѯ��û��������������
** ���ڲ���: -1������,����--������
** ��    ע: 
************************************************************************/
int32_t ReadPacketTimeout(uint8_t *buf,int32_t buflen);

/************************************************************************
** ��������: mqtt_pktype_ctl						
** ��������: ���ݰ����ͽ��д���
** ��ڲ���: uint8_t packtype:������
** ���ڲ���: ��
** ��    ע: 
************************************************************************/
void mqtt_pktype_ctl(uint8_t packtype,uint8_t *buf,uint32_t buflen);

/************************************************************************
** ��������: WaitForPacket					
** ��������: �ȴ��ض������ݰ�
** ��ڲ���: int32_t sock:����������
**           uint8_t packettype:������
**           uint8_t times:�ȴ�����
** ���ڲ���: >=0:�ȵ����ض��İ� <0:û�еȵ��ض��İ�
** ��    ע: 
************************************************************************/
int32_t WaitForPacket(uint8_t packettype,uint8_t times);
void Proscess(void* data);
#endif



