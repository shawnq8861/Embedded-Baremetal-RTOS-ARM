/*
              mem.h
              Header file for memory functions
              Paul Lever

*/

#ifndef __MEM_H__
#define __MEM_H__

#define MEM_HEAPSIZE   4096

/* tmemalloc - allocate memory 
 *             can only be used after UCOS begins
 */
void * tmemalloc(INT32S size);
/* tmemfree - deallocate memory 
 *             can only be used after UCOS begins
 */
void tmemfree(void *pData);

/* _tmemalloc - allocate memory 
 *              unprotected             
 */
void * _tmemalloc(INT32S Size);
/* _tmemfree - deallocate memory 
 *              unprotected             
 */
void _tmemfree(void *pData);

#endif //__MEM_H__

