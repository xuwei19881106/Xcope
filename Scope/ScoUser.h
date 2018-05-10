/* ���ļ���Ҫ�ṩ���û���Ӧ�ò�ֱ�ӵ��õĽӿ� */
#ifndef SCOPE_SCOUSER_H_
#define SCOPE_SCOUSER_H_

#include "scopeport.h"
#include "scoreal.h"
#include "ScoEvt.h"
#include "ScoEvtPcb.h"
#include "ScoArray.h"
#include "scopetypes.h"

extern Uint16 scoUserbuff[SCOPE_MAX_CHN];

/* ��ʼ������  --------------------------------------------------*/
void ScoUser_init(void);
/* ����ʹ�ܺ��� ---------------------------------------------------*/
ScoRes ScoUser_eventTriger(Uint16 forwardCyc,                  //ǰ���¼������
                         Uint16 afterwardCyc,                  //�����¼������
                         char *description,                    //�¼�����
                         Evtlevel level,                       //�¼��ȼ�
                         Uint32 chnIDs);                       //ͨ��ID

/* ����ˢ���û��ӿ� -----------------------------------------------------*/
void ScoUser_eventPro(void);



#endif /* SCOPE_SCOUSER_H_ */
