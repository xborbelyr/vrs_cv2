#include <stddef.h>
#include "stm32l1xx.h"

int main(void)
{

	int button,counter;

	//Nastavenie GPIO periférie pre zelenú led (PA5)
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIOA->MODER |= (uint32_t)((0b01)<<(5*2));
	GPIOA->OTYPER &= ~((uint16_t)(0b1)<<5);
	GPIOA->PUPDR |= (uint32_t)((0b01)<<(5*2));
	GPIOA->OSPEEDR |= (uint32_t)((0b11)<<(5*2));

	//Nastavenie GPIO periférie pre user button (PC13)
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	GPIOC->MODER &=~ (uint32_t)((0b11)<<(13*2));
	GPIOC->OTYPER &=~ ((uint32_t)((0b11)<<(13*2)));
	GPIOC->PUPDR &=~ (uint32_t)((0b11)<<(13*2));

	while (1)
	{

		if(((((uint16_t)GPIOC->IDR) >> 13) & 0b01) == 1){
			counter=0;
			button=0;
			while(1){
				if(((((uint16_t)GPIOC->IDR) >> 13) & 0b01) == 0){
					while(1){
						if(counter>1000){
							if(((((uint16_t)GPIOC->IDR) >> 13) & 0b01) == 1){
								GPIOA->ODR ^= (uint32_t)((0b1)<<(5));
								button=1;
								break;
							}
						}
						counter++;
					}
					if(button==1)
						break;
				}
			}
		}

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
