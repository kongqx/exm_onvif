#ifndef GATE_CONNECT_H
#define GATE_CONNECT_H
#include <pthread.h>
#include "mod_socket.h"
#define	MAX_GATE_LIST				6		//gatelist�д�ŵ����������б���

struct gate_struct{
//GT1000ϵͳ�ж����ص�����(��GT1000������������)
	pthread_mutex_t mutex;	//���ʽṹҪ�õ�����
	int	fd;					//�������ӵ������� -1��ʾ��û�н�������
	int	period;				/*��Ч�ڣ����������Ӻ����ֵ������һ����ʼֵ
							    ֮��ÿ�붼��1��ֱ��0�Ͽ����ӣ�����г�������һ������
							    �������ֵ�ָ�����ʼֵ*/
	struct sockaddr_in gateaddr;//Զ�����ص�ַ���˿�
};

typedef struct{
int dev_no;
struct gate_struct *gate;
}dev_gate_struct;
/**********************************************************************************************
 * ������	:get_gate_list()
 * ����	:��ȡһ���������ؽṹ�����ָ��
 * ����	:��
 * ����ֵ	:�������ؽṹ�����ָ�룬����Ԫ�صĸ���ΪMAX_GATE_LIST
 **********************************************************************************************/
struct gate_struct *get_gate_list(int dev_no);


/**********************************************************************************************
 * ������	:send_gate_pkt()
 * ����	:�����õ����ݰ�ί�з����̷߳��͸�����
 * ����	:fd:��������������,-1��ʾ�ɷ����߳̽���һ����������
 *									   -2��ʾ������ط����������Ӳ�ͨ�����ӽ�������������
 *			len:Ҫ���͵����ݳ���(mod_com_type�ṹ�а���cmd�������ֶεĳ���)
 *			send:�������ݵĽṹָ��,����env,encӦ��Ҳ����
 * ����ֵ	:�������ؽṹ�����ָ�룬����Ԫ�صĸ���ΪMAX_GATE_LIST
 * ע		:���߳�Ҫ�뷢�����ݸ�Զ����������ô˽ӿ�ͳһ����
 *			 ��������Ҫ��Ҫ���͸�Զ�����ط����������ݰ�ȫ������� mod_com_type�ṹ�е�para�ֶ�����
 **********************************************************************************************/

int send_gate_pkt(int fd,struct mod_com_type *send,int len,int dev_no);

/**********************************************************************************************
 * ������	:creat_connect_thread()
 * ����	:����һ�����Ӳ��������� �����ص��߳�
 * ����	:attr:�����̵߳�����
 *			 
 * ����ֵ	:0��ʾ�ɹ�����ֵ��ʾʧ��
 **********************************************************************************************/
int creat_connect_thread(pthread_attr_t *attr);

/**********************************************************************************************
 * ������	:gate_connect_second_proc()
 * ����	:���������̵߳��봦������
 * ����	:��	 
 * ����ֵ	:��
 **********************************************************************************************/
void gate_connect_second_proc(int count,int chn);

/**********************************************************************************************
 * ������	:set_gate_ip()
 * ����	:��һ��ip��ַ���õ�����ip��ַ�б���
 * ����	:place:Ҫ���õ��������
 *			 ip:������ip��ַ��ip3,ip2,ip1,ip0��
 *			 port:�������ṩ����Ķ˿ں�
 * ����ֵ	:0��ʾ�ɹ���ֵ��ʾʧ��
 **********************************************************************************************/
int set_gate_ip(int dev_no,int place,DWORD *ip,WORD port);


int create_recv_gate_ack_thread(dev_gate_struct *devgate);
#endif