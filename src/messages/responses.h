/*
 * responses.h
 *
 * Created: 08.06.2021 12:01:21
 *  Author: Micha³ Granda
 */ 


#ifndef RESPONSES_H_
#define RESPONSES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
	uint8_t status;
} execution_status_m;
#define EXEC_STATUS_SIZE sizeof(execution_status_m)

typedef struct {
	uint32_t count;
} count_result_m;
#define COUNT_RESULT_SIZE sizeof(count_result_m)

#ifdef __cplusplus
}
#endif

#endif /* RESPONSES_H_ */