/**
*       ### 用途 :  用于中国各运营商的号段归属运营商识别校验  ###
*       ### 记录每次修改时间   ###
*
* ###  添加 1707,1708,175 号段 by awkee , 20150206 ###
* ###  添加 1703,1706,172 号段 by awkee , 20150917 ###
*
**/

#include <stdio.h>
#include <string.h>


enum PHONE_TYPE
{
    CHINA_MOBILE_TYPE = 1 /*中国移动号码段*/,
    CHINA_UNICOM_TYPE /*中国联通号码段*/,
    CHINA_TELECOM_TYPE /*中国电信号码段*/,
    CHINA_MOBILE_VM_TYPE /*虚拟号码段*/,
    CHINA_SINOSAT_TYPE /*中国卫通号码*/,
    CHINA_VM_MOBILE /*中国移动虚拟运营商号码*/,
    CHINA_VM_UNICOM /*中国联通虚拟运营商号码*/,
    CHINA_VM_TELECOM /*中国电信虚拟运营商号码*/
};
char mobile_list[2000] = { -1 };/*设置手机号码段分配列表*/

/*
 * 函数功能：初始化运营商号段分配表
 *
 * */
void init_mobile_list()
{
    /*中国移动号码段*/
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

    /*中国联通号码段*/
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

    /*中国电信号码段*/
    mobile_list[133] = CHINA_TELECOM_TYPE;
    mobile_list[153] = CHINA_TELECOM_TYPE;
    mobile_list[177] = CHINA_TELECOM_TYPE;
    mobile_list[180] = CHINA_TELECOM_TYPE;
    mobile_list[181] = CHINA_TELECOM_TYPE;
    mobile_list[189] = CHINA_TELECOM_TYPE;
    mobile_list[149] = CHINA_TELECOM_TYPE;

    /*虚拟号码*/
    mobile_list[10] = CHINA_MOBILE_VM_TYPE;

    /*中国卫通号码*/
    mobile_list[1349] = CHINA_SINOSAT_TYPE;
    
    mobile_list[1703] = CHINA_VM_MOBILE;
    mobile_list[1705] = CHINA_VM_MOBILE;
    mobile_list[1706] = CHINA_VM_MOBILE;
    
    mobile_list[1709] = CHINA_VM_UNICOM;
    
    mobile_list[1700] = CHINA_VM_TELECOM;
    return;
}



/*********************
 * 函数功能：
 *   判断号码类型
 * 返回值说明：
 *  -1  异常参数值
 *  0   非手机号码
 *  1   中国移动号码
 *  2   中国联通号码
 *  3   中国电信号码
 *  4   虚拟号码段
 *  5   中国卫通号码
 *  6   中国移动虚拟运营商号码
 *  7   中国联通虚拟运营商号码
 *  8   中国电信虚拟运营商号码
 *  其他值可以以后扩展使用
 */
int dl_check_number_type(const char *number)
{
    static int run_once_counter = 0;
    int l_num_len;
    char l_number[16];
    int l_num;

    if (run_once_counter < 1)
    {
        //初始化运营商号段分配表,控制初始化只加载一次
        init_mobile_list();
        run_once_counter++;
    }

    if (number[0] != '1')
    {
        return 0;
    }
    switch (number[1])
    {
    case '0':/*10虚拟号码*/
        l_num_len = 2;
        break;

    case '3':/*13*/
        if( number[2] == '4' && number[3] == '9' )/*1349中国卫通*/
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

    default:/*其他默认*/
        l_num_len = 3;
        break;
    }
    strncpy(l_number, number, l_num_len);/*取号段的前三位进行判断*/
    l_number[ l_num_len ] ='\0';
    l_num = atoi(l_number);

    return mobile_list[l_num];
}

