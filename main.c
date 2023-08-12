/*
 * main.c
 *
 *  Created on: Sep 9, 2022
 *      Author: hp
 */
# include "STD_TYPES.h"
# include "DIO_interface.h"
# include "LCD_interface.h"
# include "LCD_config.h"
# include "KPD_interface.h"
# include <util/delay.h>




int main ()
{
	/*Division*/
	u32 rule1,rule2,out1,rule,out,OPP1=0,OPP2=0,RESULT,result;
	u8 Line_Arr[16],Opp1_Arr[16],Opp2_Arr[16],BUTTON,count=0,i,flag1=0,c1=0,c2=0,operation;
	u8 Arr_Store[6];
	u8 ARRAY[16],y=15,remender,w=0,c3=0;

//*****************************************

	DIO_VidSetPortDirection(Port_D,0b11100000);
	DIO_VidSetPortDirection(Port_C,0b11111111);

	DIO_VidSetPortDirection(Port_A,0b00001111);
	DIO_VidSetPortValue(Port_A,0b11110000);



	LCD_VidInit();

	LCD_VidSendString(" WELCOME in our");
	LCD_VidGotoXY(1,1);
	LCD_VidSendString("* CALCULATOR *");
	_delay_ms(1000);
	LCD_VidDisplayClear();

	while (1)
	{

			while (1)
			{
				BUTTON=KPD_u8GetPressedKey();

				if (BUTTON!=101)
				{
					if (count==0)
					{
						LCD_VidDisplayClear();
					}

					if (BUTTON=='=')
					{
						/*if (flag1==1)
						{
							LCD_VidGotoXY(0,count);
							LCD_VidSendData('=');
							_delay_ms(500);
							flag1=0;
						}
						else
						{
							LCD_VidSendData('=');
							_delay_ms(500);
						}*/
					/*	_delay_ms(500);*/

						break;

					}
					else if (BUTTON=='C')
					{
						LCD_VidGotoXY(0,count-1);
						LCD_VidSendData(' ');
						flag1=1;

						count--;
					}
					else
					{
						LCD_VidGotoXY(0,count);

						Line_Arr[count]=BUTTON;
						LCD_VidSendData(Line_Arr[count]);

						count++;
					}

				}
			}

			LCD_VidGotoXY(1,0);

			for (i=0  ;  Line_Arr[i]!='+' && Line_Arr[i]!='-' && Line_Arr[i]!='x' && Line_Arr[i]!='/'  ;  i++)
			{
				Opp1_Arr[i]=Line_Arr[i];
				Line_Arr[i]=0;
				c1++;
			}

			OPP1=Opp1_Arr[0]-48;

			for (i=1 ; i<c1 ;  i++)
			{
				OPP1=OPP1*10+(Opp1_Arr[i]-48);
			}
			//LCD_VidSendNumber(OPP1);

			operation=Line_Arr[c1];
			//LCD_VidSendData(operation);

			c2=count-c1-1;

			for (i=(c1+1) ;  i<count  ;  i++)
			{
				OPP2=OPP2*10+(Line_Arr[i]-48);
			}

			/*OPP2=Opp2_Arr[c1+1]-48;

			for (i=(c1+1)+1 ; i<count ;  i++)
		    {
				OPP2=OPP2*10+(Opp2_Arr[i]-48);
		    }*/

			//LCD_VidSendNumber(OPP2);



	        switch (operation)
	        {
	        	case '+':
	        		RESULT=OPP1+OPP2;

	        		result=RESULT;
	        		while (RESULT>0)
	        		{
		        		remender=RESULT%10;
		        		RESULT=RESULT/10;
		        		LCD_VidGotoXY(1,y);

		        		LCD_VidSendNumber(remender);
		        		y--;
	        		}

	        		y=15;

            		break;

	        	case '-':

            		if (OPP1>=OPP2)
            		{
    	        		RESULT=OPP1-OPP2;
            		}
            		else
            		{
            			RESULT=OPP2-OPP1;
            			w=1;
            		}

	        		result=RESULT;
	        		while (RESULT>0)
	        		{
		        		remender=RESULT%10;
		        		RESULT=RESULT/10;
		        		LCD_VidGotoXY(1,y);

		        		LCD_VidSendNumber(remender);
		        		y--;
	        		}

	        		if (w==1)
	        		{
		        		LCD_VidGotoXY(1,y);
		        		LCD_VidSendData('-');
		        		w=0;
	        		}

	        		y=15;

            		break;

	        	case 'x':
	        		RESULT=OPP1*OPP2;

	        		result=RESULT;
	        		while (RESULT>0)
	        		{
		        		remender=RESULT%10;
		        		RESULT=RESULT/10;
		        		LCD_VidGotoXY(1,y);

		        		LCD_VidSendNumber(remender);
		        		y--;
	        		}

	        		y=15;

            		break;

	        	case '/':
            		if (OPP1>OPP2 && OPP1%OPP2==0)
            		{
            			RESULT=OPP1/OPP2;

    	        		result=RESULT;
    	        		while (RESULT>0)
    	        		{
    		        		remender=RESULT%10;
    		        		RESULT=RESULT/10;
    		        		LCD_VidGotoXY(1,y);

    		        		LCD_VidSendNumber(remender);
    		        		y--;
    	        		}

    	        		y=15;

            		}

            		else if (OPP1==OPP2  && OPP2!=0)
            		{
            			LCD_VidGotoXY(1,15);
            			LCD_VidSendData('1');
            		}

            		else if (OPP1>OPP2 && OPP1%OPP2!=0 && OPP2!=0)
            		{
                		//LCD_VidSendNumber(OPP1/OPP2);
                		//LCD_VidSendData('.');
            			u32 opper1=OPP1,opper2=OPP2;


            			rule=(OPP1/OPP2)*OPP2;
            			out=OPP1-rule;

            			OPP1=out;       /***********************/

            			OPP1=OPP1*10;
            			Arr_Store[0]=OPP1/OPP2;
            			rule1=Arr_Store[0]*OPP2;
            			out1=OPP1-rule1;

            		    for (i=1;i<=5;i++)
            			{
            				out1=(out1*10);
            				Arr_Store[i]=out1/OPP2;
            				rule2=Arr_Store[i]*OPP2;
            				out1=out1-rule2;
                			c3++;
            			}

            		    for (i=0;i<6;i++)
            		   	{
            		    	LCD_VidGotoXY(1,15-i);
                			LCD_VidSendNumber(Arr_Store[5-i]);
            		   	}
        		    	LCD_VidGotoXY(1,9);
        		    	LCD_VidSendData('.');
        		    	RESULT=opper1/opper2;

        		    	y=8;
    	        		while (RESULT>0)
    	        		{
    		        		remender=RESULT%10;
    		        		RESULT=RESULT/10;
    		        		LCD_VidGotoXY(1,y);

    		        		LCD_VidSendNumber(remender);
    		        		y--;
    	        		}

    	        		y=15;




            		}

            		else if(OPP1<OPP2  && OPP2!=0)
            		{

            			OPP1=OPP1*10;
            			Arr_Store[0]=OPP1/OPP2;
            			rule1=Arr_Store[0]*OPP2;
            			out1=OPP1-rule1;

            		    for (u8 i=1;i<=5;i++)
            			{
            				out1=(out1*10);
            				Arr_Store[i]=out1/OPP2;
            				rule2=Arr_Store[i]*OPP2;
            				out1=out1-rule2;
            			}

            		    for (i=0;i<6;i++)
            		   	{
            		    	LCD_VidGotoXY(1,15-i);
                			LCD_VidSendNumber(Arr_Store[5-i]);
            		   	}
        		    	LCD_VidGotoXY(1,9);
        		    	LCD_VidSendData('.');
        		    	LCD_VidGotoXY(1,8);
        		    	LCD_VidSendData('0');

        		    	y=15;
            		}

            		else if (OPP2==0)
            		{
            			LCD_VidSendString("       Undefined");
            		}

	        		break;


	        }

	        OPP1=0;
	        OPP2=0;

			c1=0;
			c2=0;

			count=0;



	}
}

