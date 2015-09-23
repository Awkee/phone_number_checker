/**
*       ### ��; :  �����й�����Ӫ�̵ĺŶι�����Ӫ��ʶ��У��  ###
*       ### ��¼ÿ���޸�ʱ��   ###
*
* ###  ��� 1707,1708,175 �Ŷ� by awkee , 20150206 ###
* ###  ��� 1703,1706,172 �Ŷ� by awkee , 20150917 ###
*
**/

#include <stdio.h>
#include <string.h>


enum PHONE_TYPE
{
    CHINA_MOBILE_TYPE = 1 /*�й��ƶ������*/,
    CHINA_UNICOM_TYPE /*�й���ͨ�����*/,
    CHINA_TELECOM_TYPE /*�й����ź����*/,
    CHINA_MOBILE_VM_TYPE /*��������*/,
    CHINA_SINOSAT_TYPE /*�й���ͨ����*/,
    CHINA_VM_MOBILE /*�й��ƶ�������Ӫ�̺���*/,
    CHINA_VM_UNICOM /*�й���ͨ������Ӫ�̺���*/,
    CHINA_VM_TELECOM /*�й�����������Ӫ�̺���*/
};
char mobile_list[2000] = { -1 };/*�����ֻ�����η����б�*/

/*
 * �������ܣ���ʼ����Ӫ�̺Ŷη����
 *
 * */
void init_mobile_list()
{
    /*�й��ƶ������*/
    mobile_list[134] = CHINA_MOBILE_TYPE;
    mobile_list[135] = CHINA_MOBILE_TYPE;
    mobile_list[136] = CHINA_MOBILE_TYPE;
    mobile_list[137] = CHINA_MOBILE_TYPE;
    mobile_list[138] = CHINA_MOBILE_TYPE;
    mobile_list[139] = CHINA_MOBILE_TYPE;
    mobile_list[147] = CHINA_MOBILE_TYPE;
    mobile_list[150] = CHINA_MOBILE_TYPE;
    mobile_list[151] = CHINA_MOBILE_TYPE;
    mobile_list[152] = CHINA_MOBILE_TYPE;
    mobile_list[157] = CHINA_MOBILE_TYPE;
    mobile_list[158] = CHINA_MOBILE_TYPE;
    mobile_list[159] = CHINA_MOBILE_TYPE;
    mobile_list[178] = CHINA_MOBILE_TYPE;
    mobile_list[182] = CHINA_MOBILE_TYPE;
    mobile_list[183] = CHINA_MOBILE_TYPE;
    mobile_list[184] = CHINA_MOBILE_TYPE;
    mobile_list[187] = CHINA_MOBILE_TYPE;
    mobile_list[188] = CHINA_MOBILE_TYPE;

    /*�й���ͨ�����*/
    mobile_list[130] = CHINA_UNICOM_TYPE;
    mobile_list[131] = CHINA_UNICOM_TYPE;
    mobile_list[132] = CHINA_UNICOM_TYPE;
    mobile_list[145] = CHINA_UNICOM_TYPE;
    mobile_list[155] = CHINA_UNICOM_TYPE;
    mobile_list[156] = CHINA_UNICOM_TYPE;
    mobile_list[171] = CHINA_UNICOM_TYPE;
    mobile_list[176] = CHINA_UNICOM_TYPE;
    mobile_list[185] = CHINA_UNICOM_TYPE;
    mobile_list[186] = CHINA_UNICOM_TYPE;

    /*�й����ź����*/
    mobile_list[133] = CHINA_TELECOM_TYPE;
    mobile_list[153] = CHINA_TELECOM_TYPE;
    mobile_list[177] = CHINA_TELECOM_TYPE;
    mobile_list[180] = CHINA_TELECOM_TYPE;
    mobile_list[181] = CHINA_TELECOM_TYPE;
    mobile_list[189] = CHINA_TELECOM_TYPE;
    mobile_list[149] = CHINA_TELECOM_TYPE;

    /*�������*/
    mobile_list[10] = CHINA_MOBILE_VM_TYPE;

    /*�й���ͨ����*/
    mobile_list[1349] = CHINA_SINOSAT_TYPE;
    
    mobile_list[1703] = CHINA_VM_MOBILE;
    mobile_list[1705] = CHINA_VM_MOBILE;
    mobile_list[1706] = CHINA_VM_MOBILE;
    
    mobile_list[1709] = CHINA_VM_UNICOM;
    
    mobile_list[1700] = CHINA_VM_TELECOM;
    return;
}



/*********************
 * �������ܣ�
 *   �жϺ�������
 * ����ֵ˵����
 *  -1  �쳣����ֵ
 *  0   ���ֻ�����
 *  1   �й��ƶ�����
 *  2   �й���ͨ����
 *  3   �й����ź���
 *  4   ��������
 *  5   �й���ͨ����
 *  6   �й��ƶ�������Ӫ�̺���
 *  7   �й���ͨ������Ӫ�̺���
 *  8   �й�����������Ӫ�̺���
 *  ����ֵ�����Ժ���չʹ��
 */
int dl_check_number_type(const char *number)
{
    static int run_once_counter = 0;
    int l_num_len;
    char l_number[16];
    int l_num;

    if (run_once_counter < 1)
    {
        //��ʼ����Ӫ�̺Ŷη����,���Ƴ�ʼ��ֻ����һ��
        init_mobile_list();
        run_once_counter++;
    }

    if (number[0] != '1')
    {
        return 0;
    }
    switch (number[1])
    {
    case '0':/*10�������*/
        l_num_len = 2;
        break;

    case '3':/*13*/
        if( number[2] == '4' && number[3] == '9' )/*1349�й���ͨ*/
            l_num_len = 4;
        else
            l_num_len = 3;
        break;

    case '7':/*17*/
        if (number[2] == '0')
            l_num_len = 4;
        else
            l_num_len = 3;
        break;

    default:/*����Ĭ��*/
        l_num_len = 3;
        break;
    }
    strncpy(l_number, number, l_num_len);/*ȡ�Ŷε�ǰ��λ�����ж�*/
    l_number[ l_num_len ] ='\0';
    l_num = atoi(l_number);

    return mobile_list[l_num];
}

