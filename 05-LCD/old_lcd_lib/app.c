/* 
Replace this file with your code. Put your source files in this directory and any libraries in the lib folder. 
If your main program should be assembly-language replace this file with main.S instead.

Libraries (other than vendor SDK and gcc libraries) must have .h-files in /lib/[library name]/include/ and .c-files in /lib/[library name]/src/ to be included automatically.
*/

#include "gd32vf103.h"
#include "string.h"
#include "lcd.h"
#define BITMASK 0xFFFFFFF8

typedef  enum {Idle, Angle, Shake, ShakeFeedback, Exhale, Click, Inhale, HoldBreath, HoldBreathCounter, Done, Feedback} states ;
static states State;

int main(){
	Lcd_SetType(LCD_INVERTED);
	Lcd_Init();
	LCD_Clear(BLACK);
	char READY[] = "Redo att anvandas ";
	char LIDOFF[] = "Ta av munstycket ";
	char ANGLE[] = "HALL INHALATORN ";
	char ANGLE2[] = "UPPRATT ";
	char SHAKE[] = "SKAKA ";
	char SHAKE2[] = "3-5ggr ";
	//char FEEDBACK[] = "Bra! ";
	char EXHALE[] = "Andas ut ";
	char CLICK[] = "Klicka ";
	char INHALE[] = "Andas in ";
	char HOLDBREATH[] = "Hall andan ";
	char DONE[] = "KLAR! ";
	char FEEDBACK1[] = "HALL UPPRATT: ";
	char FEEDBACK2[] = "SKAKA: ";
	char FEEDBACK3[] = "ANDAS UT: ";
	char FEEDBACK4[] = "ANDAS IN: ";

	uint64_t start_time = 0;
	uint64_t timePassed = 0;
	uint32_t timeLimit = 0; 
	uint32_t oneSec; 

	State = Idle;

	while(1){

		switch (State) {

			case Idle:
			//if (digitalRead(BTN_PIN) == LOW){  // if button is pressed
				//TEXT[] = "Redo att anvandas";
				//strcpy(TEXT, "Redo att anvandas");
				LCD_DrawPoint(113,29,WHITE);
				LCD_DrawPoint(115,29,WHITE);
				LCD_ShowString(13, 30, READY, WHITE);
				delay_1ms(2000);
				LCD_Clear(BLACK);
				State = Angle;
			//}
			break;
			
			case Angle:
				LCD_Clear(BLACK);
				LCD_DrawPoint_big(31,19,WHITE);
				LCD_DrawPoint_big(83,39,WHITE);
				LCD_DrawPoint_big(87,39,WHITE);
				LCD_ShowString(20, 20, ANGLE, WHITE);
				LCD_ShowString(50, 40, ANGLE2, WHITE);
				delay_1ms(2500);
				LCD_Clear(BLACK);
				State = Shake;
			break;

			case Shake: 
			//while(digitalRead(BTN_PIN) == HIGH){
				LCD_ShowString(15, 30, LIDOFF, WHITE);
				delay_1ms(4000);
				LCD_Clear(BLACK);
				LCD_ShowString(60, 20, SHAKE, WHITE);
				LCD_ShowString(57, 40, SHAKE2, WHITE);
				delay_1ms(3000);
				State = ShakeFeedback;
			//}
			break;

			case ShakeFeedback:  
				LCD_Clear(GREEN);
				//LCD_ShowString(60, 30, FEEDBACK, BLACK);
				delay_1ms(2000);
				State = Exhale;
			break;

			case Exhale: 
				LCD_Clear(BLACK);
				LCD_ShowString(50, 30, EXHALE, WHITE);
				delay_1ms(3000);
				State = Click;
			break;

			case Click: 
				LCD_Clear(BLACK);
				LCD_ShowString(60, 30, CLICK, WHITE);
				delay_1ms(2000);
				State = Inhale;
			break;

			case Inhale: 
				LCD_Clear(BLACK);
				LCD_ShowString(50, 30, INHALE, WHITE);
				delay_1ms(4000);
				// LÄGG TILL EN COUNTER som räknar ner... eller försök hitta något som fyller upp skärmen = tiden går
				State = HoldBreath;
			break;

			case HoldBreath: 
				LCD_Clear(BLACK);
				LCD_DrawPoint_big(52,30,WHITE);
				LCD_ShowString(40, 30, HOLDBREATH, WHITE);
				delay_1ms(1000);
				State = HoldBreathCounter;				
			break;

			case HoldBreathCounter:
				LCD_ShowString(40, 30, HOLDBREATH, WHITE);

				if (timeLimit <= 5){
					if (start_time == 0){
						start_time = get_timer_value();	

					} else {
						timePassed = get_timer_value();
						oneSec = (timePassed - start_time)/(SystemCoreClock/(4.0));
						if(oneSec == 1){
							LCD_Fill(40, 30, 100, 60, BLACK);
							if (5-timeLimit != 0){
								LCD_ShowNum(80, 50, (5-timeLimit), 1, WHITE);
							}
							start_time = 0;
							timeLimit++;
						}
					}
				} else {
					State = Done;
					timeLimit = 0;
				}
			break;

			case Done:
				LCD_Clear(GREEN);
				//LCD_ShowString(60, 30, DONE, BLACK);
				LCD_ShowStr(60, 30, DONE, BLACK, 1);
				delay_1ms(3000);
				LCD_Clear(BLACK);
				State = Feedback;
			break;

			case Feedback: 
				LCD_DrawPoint_big(14,1,WHITE);
				LCD_DrawPoint_big(77,1,WHITE);
				LCD_DrawPoint_big(81,1,WHITE);
				LCD_ShowStr(3, 1, FEEDBACK1, WHITE, 1);
				LCD_ShowStr(59, 20, FEEDBACK2, WHITE, 1);
				LCD_ShowStr(35, 40, FEEDBACK3, WHITE, 1);
				LCD_ShowStr(35, 60, FEEDBACK4, WHITE, 1);
				LCD_Fill(120,3,135,16,RED);
				LCD_Fill(120,22,135,35,GREEN);
				LCD_Fill(120,42,135,55,BRRED);
				LCD_Fill(120,62,135,83,GREEN);
				delay_1ms(6000);
				LCD_Clear(BLACK);
				State = Idle;
			break;
  		}

	}
}
