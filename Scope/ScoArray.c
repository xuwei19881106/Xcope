#include <String.h>
#include "ScoArray.h"
#include "scopeport.h"
#include "assertEx.h"
DEFINE_THIS_MODULE(ScoArray.c)

/* ����ʵʱ�������ݵ�ȫ������ -------------------------------------------------*/
Uint16 scopeArray[SCOPE_MAX_CHN][SCOPE_CHN_PTS];

/* ���ڲ���ȫ������Ŀ��ƿ� ---------------------------------------------------*/
ScoArrayPCB scpAryPcb;

/* ��ʼ����������Ҫ���ڽ��ڴ���Ϊ0 --------------------------------------------*/
void ScoArray_init(void) {
    bzero((Uint8 *)&scpAryPcb, sizeof(ScoArrayPCB));
    scpAryPcb.isFulled = false;
    scpAryPcb.curPos = 0;
    scpAryPcb.pToPcb = (ScoEvtPCBFrame *)0;

    int i;
    for(i = 0; i < SCOPE_MAX_CHN; i++) {
        bzero((Uint8 *)scopeArray[i], sizeof(scopeArray[i]));
    }
}

Uint16 ScoArray_refresh(Uint16 *pdata, Uint8 len) {
    /* step1: ���жϴ�������ݳ����Ƿ�Ϸ� */
    if(len != SCOPE_MAX_CHN) {
        return resRefreshErr;
    }

    /* step2: Ϊÿ��ͨ����������*/
    int i;
    for(i = 0; i < SCOPE_MAX_CHN; i++){
        scopeArray[i][scpAryPcb.curPos] = *(pdata + i);
    }

    /* step3: �������ݲ��Ҽ���Ƿ���Ҫ���� */
    if(++scpAryPcb.curPos == SCOPE_CHN_PTS){
        scpAryPcb.curPos = 0;
        scpAryPcb.isFulled = true;
    }

    /* step4: ����Ƿ����¼�����������Ƿ��ڴ˿���Ҫ���� */


    return 0;
}


void ScoArray_channelLog(Uint8 chnID, Uint16 len) {
    /* step1 ���жϽ�ȡ�����Ƿ��� */
    ASSERT_EX(len <= SCOPE_CHN_PTS);

    /* step2 ������Ӧͨ������ */
    /* Ϊ�˷�ֹ���ݻ��ƣ�Ӧ����������COPY */
    Uint16 part1 = 0, part2 = 0;
    if(scpAryPcb.curPos < len) {
        part1 = len - scpAryPcb.curPos;
        part2 = scpAryPcb.curPos;

        memcpy(scoEvtChnLog, &(scopeArray[chnID][SCOPE_CHN_PTS - part1]), part1);
        memcpy(&scoEvtChnLog[part1], &(scopeArray[chnID][0]), part2);
    }else {
        memcpy(scoEvtChnLog, &(scopeArray[chnID][scpAryPcb.curPos - len]), len);
    }
}























