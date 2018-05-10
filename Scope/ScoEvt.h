/* ���ļ������ṩ�����ϴ��¼�����ʱ��ͨ���������ݵĽӿ� */
#ifndef SCOPE_SCOEVT_H_
#define SCOPE_SCOEVT_H_

#include "scopetypes.h"

/* �������ڱ�����Ҫ�ϴ������ݽṹ --------------------------------------------*/

typedef struct ScoEvtTag{
    Uint8 chnID;                        //ͨ��ID��
    Uint8 points;                       //��Ч���ݳ��ȣ�����������
    Uint16 data[SCOPE_EVTDATA_NUM];     //���ϴ�����Ч����
}ScoEvt;

typedef struct ScoEvtFrameTag{
    struct ScoEvtFrameTag *pNext;
    ScoEvt eventData;
}ScoEvtFrame;

/* ���建�漰���ƿ� --------------------------------------------------------*/
extern ScoEvtFrame scoEvtBuffSto[SCOPE_EVTDATA_FNUM];
extern MemPool scoEvtPool;

void ScoEvt_poolInit(void *poolSto, Uint16 poolSize, Uint16 blockSize);
void ScoEvt_add(ScoEvtFrame **root, ScoEvtFrame *pf);
ScoEvtFrame *ScoEvt_pop(ScoEvtFrame **root);
ScoRes ScoEvt_chainFrame(ScoEvtFrame **root, Uint8 chnID, Uint16 *pdata, Uint16 len);


#endif /* SCOPE_SCOEVT_H_ */
