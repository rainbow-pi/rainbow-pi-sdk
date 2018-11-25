
#ifndef __OSAL_QUEUE__
#define __OSAL_QUEUE__

#include <OMX_Types.h>
#include <OMX_Core.h>

typedef struct _OSAL_QElem
{
    void               *data;
    struct _OSAL_QElem *qNext;
} OSAL_QElem;

typedef struct _OSAL_QUEUE
{
    OSAL_QElem     *first;
    OSAL_QElem     *last;
    int            numElem;
    OMX_HANDLETYPE qMutex;
	int            maxElem;
} OSAL_QUEUE;


#ifdef __cplusplus
extern "C" {
#endif

OMX_ERRORTYPE OSAL_QueueCreate(OSAL_QUEUE *queueHandle, int maxQueueElem);
OMX_ERRORTYPE OSAL_QueueTerminate(OSAL_QUEUE *queueHandle);
int           OSAL_Queue(OSAL_QUEUE *queueHandle, void *data);
void         *OSAL_Dequeue(OSAL_QUEUE *queueHandle);
int           OSAL_GetElemNum(OSAL_QUEUE *queueHandle);
int           OSAL_SetElemNum(OSAL_QUEUE *queueHandle, int ElemNum);
int			  OSAL_QueueSetElem(OSAL_QUEUE *queueHandle, void *data);

#ifdef __cplusplus
}
#endif

#endif	// __OSAL_QUEUE__
