#ifndef __MENU_H
#define __MENU_H
#include <includes.h>

// dlg ID
typedef enum DLG_ID
{
    DLG_CLEAR_LCD                = 0,
    DLG_LOGO                     = 1,                 /*  */
    DLG_STATUS                   = 2,                 /*  */
    DLG_MAIN                     = 3,                 /*  */
    DLG_PASS                     = 4,                 /*  */
    DLG_CARD_ID                  = 5,                 /*  */
    DLG_WORKING_SET              = 6,                 /*  */

    DLG_CARD_MAIN                = 20,                 /*  */
    DLG_STATUS_ONE               = 21,                 /*  */
    DLG_STATUS_TWO               = 22,                 /*  */

    DLG_CONNETCT_SET             = 23,                 /*  */

    DLG_CARD_COUNT_SET           = 30,                 /*  */

    DLG_DEBUG_MAIN               = 40,                 /*  */
    DLG_DEBUG_ONE                = 41,                 /*  */
    DLG_DEBUG_TWO                = 42,                 /*  */
    DLG_DEBUG_THREE              = 43,                 /*  */

    DLG_FAULT_CODE               = 60,                 /* ������ */

}DLG_ID;

// ����ṹ��
typedef struct Dlg
{
   unsigned char ID;
   char MsgRow[4][36];
   unsigned char highLightRow;
   unsigned char prevDlgID;            // ��һ���˵�ID
   unsigned char nextDlgID;            // ��һ���˵�ID
}Dlg;


void doShowStatusMenu (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowMainMenu (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowCardCountSet (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowConnectModeSet (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowStatusOne (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowStatusTwo (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowIdSetMenu (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowWorkingSet (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowDebugMain (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowDebugOne (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowDebugTwo (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);
void doShowFaultCode (unsigned char dlg_id, unsigned char isNotRow, void * p_parm);

unsigned char check_menu(unsigned char ch);

#endif
