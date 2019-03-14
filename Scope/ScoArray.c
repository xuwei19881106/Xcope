#include <String.h>
#include "ScoArray.h"
#include "scopeport.h"
#include "assertEx.h"
/* 2019.03.14 Git Test*/
DEFINE_THIS_MODULE(ScoArray.c)

/* 鐢ㄤ簬瀹炴椂淇濆瓨鏁版嵁鐨勫叏灞�鏁扮粍 -------------------------------------------------*/
Uint16 scopeArray[SCOPE_MAX_CHN][SCOPE_CHN_PTS];

/* 鐢ㄤ簬鎿嶄綔鍏ㄥ眬鏁扮粍鐨勬帶鍒跺潡 ---------------------------------------------------*/
ScoArrayPCB scpAryPcb;

/* 鍒濆鍖栧嚱鏁帮紝涓昏鐢ㄤ簬灏嗗唴瀛樼疆涓�0 --------------------------------------------*/
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
    /* step1: 鍏堝垽鏂紶鍏ョ殑鏁版嵁闀垮害鏄惁鍚堟硶 */
    if(len != SCOPE_MAX_CHN) {
        return resRefreshErr;
    }

    /* step2: 涓烘瘡涓�氶亾鏇存柊鏁版嵁*/
    int i;
    for(i = 0; i < SCOPE_MAX_CHN; i++){
        scopeArray[i][scpAryPcb.curPos] = *(pdata + i);
    }

    /* step3: 鏇存柊鏁版嵁骞朵笖妫�娴嬫槸鍚﹂渶瑕佺幆鍥� */
    if(++scpAryPcb.curPos == SCOPE_CHN_PTS){
        scpAryPcb.curPos = 0;
        scpAryPcb.isFulled = true;
    }

    /* step4: 妫�娴嬫槸鍚︽湁浜嬩欢鍙戠敓骞舵娴嬫槸鍚﹀湪姝ゅ埢闇�瑕佷繚瀛� */


    return 0;
}


void ScoArray_channelLog(Uint8 chnID, Uint16 len) {
    /* step1 鍏堝垽鏂埅鍙栭暱搴︽槸鍚﹁秴闄� */
    ASSERT_EX(len <= SCOPE_CHN_PTS);

    /* step2 鎷疯礉鐩稿簲閫氶亾鏁版嵁 */
    /* 涓轰簡闃叉鏁版嵁鍥炵粫锛屽簲褰撳垎涓ら儴鍒咰OPY */
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























