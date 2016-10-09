#include <stddef.h>
#include "stm32l1xx.h"

int main(void)
{
  int i = 0;
  int button;

  //Nastavenie GPIO periférie pre user button (PC13)
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  GPIOC->MODER &=~ (uint32_t)((0b11)<<(13*2));
  GPIOC->OTYPER &=~ ((uint32_t)((0b11)<<(13*2)));
  GPIOC->PUPDR &=~ (uint32_t)((0b11)<<(13*2));

  while (1)
  {
	  if (((((uint16_t)GPIOC->IDR) >> 13) & 0b01) == 0){
		  button=0;
	  }else{
		  button=1;
	  }
	  i++;
  }
  return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
