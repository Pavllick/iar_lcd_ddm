#ifndef __MAIN_H_
#define __MAIN_H_
 
#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif // __MAIN_H_
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
