#include "user_cpu_test.h"


void CPU_Task(void* parameter)
{	
  uint8_t CPU_RunInfo[400];		//保存任务运行时间信息
  
  while (1)
  {
    memset(CPU_RunInfo,0,400);				//信息缓冲区清零
    
    vTaskList((char *)&CPU_RunInfo);  //获取任务运行时间信息
    
    printf("---------------------------------------------\r\n");
    printf("task_name      task_status priority    stack task_id\r\n");
    printf("%s", CPU_RunInfo);
    printf("---------------------------------------------\r\n");
    
    memset(CPU_RunInfo,0,400);				//信息缓冲区清零
    
    vTaskGetRunTimeStats((char *)&CPU_RunInfo);
    
    printf("task_name       run_cnt         usage_rate\r\n");
    printf("%s", CPU_RunInfo);
    printf("---------------------------------------------\r\n\n");
    vTaskDelay(500 / portTICK_PERIOD_MS);   /* 延时500个tick */		
  }
}


void cpu_task_create(void)
{
    xTaskCreatePinnedToCore(CPU_Task,"CPU_Task",4096,NULL,1,NULL,tskNO_AFFINITY);
}







