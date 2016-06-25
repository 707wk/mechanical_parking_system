/**************************************
 *FILE    :D:\c\car\parking management\ControlCode.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/12/4 21:13:36
 *TEXT    :������ͷ�ļ�
 *EMAIL   :gtsoft_wk@foxmail.com
 *CODE    :https://github.com/707wk
 *LOGO    :
               #########                       
              ############                     
              #############                    
             ##  ###########                   
            ###  ###### #####                  
            ### #######   ####                 
           ###  ########## ####                
          ####  ########### ####               
        #####   ###########  #####             
       ######   ### ########   #####           
       #####   ###   ########   ######         
      ######   ###  ###########   ######       
     ######   #### ##############  ######      
    #######  ##################### #######     
    #######  ##############################    
   #######  ###### ################# #######   
   #######  ###### ###### #########   ######   
   #######    ##  ######   ######     ######   
   #######        ######    #####     #####    
    ######        #####     #####     ####     
     #####        ####      #####     ###      
      #####      ;###        ###      #        
        ##       ####        ####              
***************************************/

/*////////////////////////////////////////////////////////////////////////
����

��־
{
	��żλΪ1
}

00000000 ��ַ
{
	00000000~01111111
}

��־
{
	��żλΪ0
}

00000000 ������
{
	0x01 �泵
	0x02 ȡ��
	0x03 ��ȡ��е��λ��
	0x04 ��ȡģ��״̬
	{
		������
		״̬
	}
	0x05 ����ֹͣ
	0x06 ��λ
}

00000000 ����
{
	������
	������
	״̬��ʶ
	{
		������
		���״̬
	}
	��Χ 1-127
}

��������
{
	��־ ��ַ ��־ ������ ���� У��
	1�ֽ�1�ֽ�1�ֽ�1�ֽ�1�ֽ�
}

��������
{
	��ַ ״̬
	״̬
	{
		0:����
		1:�泵
		2:ȡ��
		3:ֹͣ
		4:��λ
	}
	��е��λ��
	{
		������
		������
	}
	У��

	��ַ ״̬ ���� У��
	1�ֽ�1�ֽ�1�ֽ�1�ֽ�1�ֽ�
}
////////////////////////////////////////////////////////////////////////*/
//////////////////////////////////////////////////////////////////////////
//������
#define SAVECAR     0x01            //�泵
#define DELETECAR   0x02            //ȡ��
#define GETLOCATION 0x03            //��ȡ��е��λ��
#define GETSTATE    0x04            //��ȡģ��״̬
#define STOP        0x05            //����ֹͣ
#define RESET       0x06            //��λ

//״̬��
#define STATEFREE   0x00            //����
#define STATESAVE   0x01            //�泵
#define STATEDELETE 0x02            //ȡ��
#define STATESTOP   0x03            //ֹͣ
#define STATERSET   0x04            //��λ
#define ACCEPTED    0x05            //�ѽ���
#define BUSY        0x06            //������
#define ONLINE      0x0f            //����
#define OFFLINE     0xff            //����

//У����
#define CHECKMOD    128             //У��ȡ��

//��ַ��־
#define ADDFIRST    (char)0x55      //�ױ�־
#define ADDEND      (char)0xaa      //β��־
//////////////////////////////////////////////////////////////////////////

/*////////////////////////////////////////////////////////////////////////
sock

��������
{
	INPUTSAVE      ������[unsigned char] �ָ��� ���ƺ�[char 40] �ָ��� ���id
	OUTPUTDELE     ������[unsigned char] �ָ��� ���ƺ�[char 40]
	OUTPUTGARAGE   ������[unsigned char] �ָ��� ���ƺ�[char 40]
	RESERVATION    ������[unsigned char] У��[unsigned char]
	UNRESERVATION  ������[unsigned char] У��[unsigned char]
	GETGARAGEINFO  ������[unsigned char] У��[unsigned char]
	PANTBAG        ������[unsigned char] �ָ��� id
}

��������
{
	INPUTSAVE      ������[unsigned char] �ָ��� ���������[int]
	OUTPUTDELE     ������[unsigned char] �ָ��� �洢ʱ��[double] �ָ��� �շ�[double]
	OUTPUTGARAGE   ������[unsigned char]
	RESERVATION    ������[unsigned char]
	UNRESERVATION  ������[unsigned char]
	GETGARAGEINFO  ������[unsigned char] �ָ��� ʣ�೵λ[int] �ָ��� ʣ��ʱ��[int]
	PANTBAG        ������[unsigned char] �ָ��� �ܳ�λ[int]   �ָ��� ʣ�೵λ[int]
}
////////////////////////////////////////////////////////////////////////*/
//////////////////////////////////////////////////////////////////////////
//������
#define INPUTSAVE      0x01         //��ڴ泵
#define OUTPUTDELE     0x02         //���ڳ���
#define OUTPUTGARAGE   0x03         //����ģ��ȡ��
#define RESERVATION    0x04         //ԤԼ�泵
#define UNRESERVATION  0x05         //ȡ��ԤԼ
#define GETGARAGEINFO  0x06         //��ȡͣ������Ϣ
#define PANTBAG        0x07         //������

//������
#define TASKSUCCEED    0x01         //����ɹ�
#define NOCAR          0x02         //��λ����
#define GARAGEBUSY     0x03         //�޿���ģ��
#define NOTFOUND       0x04         //δ�ҵ�����
#define PLATEREPEAT    0x05         //�����ظ�
#define NOTOUTPUT      0x06         //δ�ҵ�����
#define NOTDEFINE      0x07         //δ���������
#define TASKFAIL       0xff         //����ʧ��
//////////////////////////////////////////////////////////////////////////

/*////////////////////////////////////////////////////////////////////////
web�û�
Ȩ��
{
	1:��������Ա
	2:����Ա
	3:����
}
////////////////////////////////////////////////////////////////////////*/
