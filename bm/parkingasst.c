#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_lptmr.h"
#include "fsl_gpio.h"

#include "pin_mux.h"
#include "clock_config.h"

#include "parkingasst.h"

#include "fsl_port.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LPTMR_LED_HANDLER LPTMR0_LPTMR1_IRQHandler
#define LPTMR0_IRQn LPTMR0_LPTMR1_IRQn
/* Get source clock for LPTMR driver */
#define LPTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_LpoClk)
#define LED_INIT() LED_RED_INIT(LOGIC_LED_ON)
#define LED_TOGGLE() LED_RED_TOGGLE()

#define BOARD_LED_GPIO GPIOC
#define BOARD_LED_GPIO_PIN 12U


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile uint32_t lptmrCounter = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void LPTMR_LED_HANDLER(void)
{
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
    lptmrCounter++;
    //LED_TOGGLE();
}

uint32_t getTimer(void) { return lptmrCounter; }

uint32_t timeElapsed(uint32_t lastTime)
{
	uint32_t currentTime = lptmrCounter;

	if (currentTime>=lastTime) {
		return currentTime - lastTime;
	} else {
		return 0xFFFFFFFFU - (lastTime - currentTime);
	}
}


/*!
 * @brief Main function
 */
int init(void)
{
    lptmr_config_t lptmrConfig;
    /* Define the init structure for the output pin*/
     gpio_pin_config_t led_config = {
         kGPIO_DigitalOutput, 1,
     };



    /* Configure LPTMR */
    /*
     * lptmrConfig.timerMode = kLPTMR_TimerModeTimeCounter;
     * lptmrConfig.pinSelect = kLPTMR_PinSelectInput_0;
     * lptmrConfig.pinPolarity = kLPTMR_PinPolarityActiveHigh;
     * lptmrConfig.enableFreeRunning = false;
     * lptmrConfig.bypassPrescaler = true;
     * lptmrConfig.prescalerClockSource = kLPTMR_PrescalerClock_1;
     * lptmrConfig.value = kLPTMR_Prescale_Glitch_0;
     */
    LPTMR_GetDefaultConfig(&lptmrConfig);

    /* Initialize the LPTMR */
    LPTMR_Init(LPTMR0, &lptmrConfig);

    /* Set timer period */
    LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(10000U, LPTMR_SOURCE_CLOCK));

    /* Enable timer interrupt */
    LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(LPTMR0_IRQn);

    PRINTF("Low Power Timer Example\r\n");

    /* Start counting */
    LPTMR_StartTimer(LPTMR0);

    /* Init output LED GPIO. */
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(GPIOB, 16U, &led_config);

    port_pin_config_t vsyncPinConfig = {0};


    vsyncPinConfig.mux = kPORT_MuxAsGpio;
    vsyncPinConfig.pullSelect = kPORT_PullUp;
    vsyncPinConfig.slewRate = kPORT_FastSlewRate;
    PORT_SetPinConfig(PORTB, 16UL, &vsyncPinConfig);

    vsyncPinConfig.mux = kPORT_MuxAsGpio;
    vsyncPinConfig.pullSelect = kPORT_PullUp;
    vsyncPinConfig.slewRate = kPORT_SlowSlewRate;
    PORT_SetPinConfig(PORTC, 12UL, &vsyncPinConfig);




}


void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 8000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}


void delayT0H(void)
{
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
}

void delayT1H(void)
{
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
	__asm("NOP"); /* delay */
}



/*
static inline void GPIO_WritePinOutput(GPIO_Type *base, uint32_t pin, uint8_t output)
{
    if (output == 0U)
    {
        base->PCOR = 1 << pin;
    }
    else
    {
        base->PSOR = 1 << pin;
    }
}

*/
#define DELAY_10nS __asm("NOP");
#define DELAY_100nS __asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");

//#define DELAY_100nS; DELAY_10nS;DELAY_10nS;DELAY_10nS;DELAY_10nS;DELAY_10nS;DELAY_10nS;DELAY_10nS;DELAY_10nS;DELAY_10nS;DELAY_10nS;

void sendWS2812Data(GPIO_Type *base, uint32_t pin,uint32_t *data,int length)
{
	int bitcount;
	uint32_t dataWord;
	uint32_t pinMask = 1U << pin;

	while (length >0)
	{
		bitcount = 23;
		dataWord = *data;
		while (bitcount>0)
		{
			if (dataWord & 0x0800000U) {
			    base->PSOR = pinMask;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    base->PCOR = pinMask;
			    DELAY_100nS;
			    DELAY_100nS;
			} else {
			    base->PSOR = pinMask;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_10nS;
			    DELAY_10nS;
			    DELAY_10nS;
			    base->PCOR = pinMask;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			    DELAY_100nS;
			}
			bitcount--;
			dataWord = dataWord <<1;
		}
		// Last bit has to be handled differntly to meet timing
		if (dataWord & 0x0800000U) {
		    base->PSOR = pinMask;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    base->PCOR = pinMask;
		    DELAY_10nS;
		    DELAY_10nS;
		    DELAY_10nS;
		    DELAY_10nS;
		    DELAY_10nS;
		} else {
		    base->PSOR = pinMask;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_10nS;
		    DELAY_10nS;
		    DELAY_10nS;
		    base->PCOR = pinMask;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		    DELAY_100nS;
		}

		data++;
		length--;
	}
}

void presetLED(void)
{
	static uint8_t toggle = 0;
	static uint32_t LEDMask = 1<<12;
	//GPIO_TogglePinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
	//delay();
	//GPIO_TogglePinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);

	//GPIO_TogglePinsOutput(GPIOB, 16U);


	//send0(GPIOC, LEDMask);
	//send1(GPIOC, LEDMask);
	//send0(GPIOC, LEDMask);
	//send1(GPIOC, LEDMask);


	uint32_t data[3];

	data[0] = 0x00FF00;
	data[1] = 0xFF0000;
	data[2] = 0xFFFF00;
	sendWS2812Data(GPIOC, 12,data,3);



	//GPIO_WritePinOutput(GPIOC, 12, 1);
	//delayT0H();
	//GPIO_WritePinOutput(GPIOC, 12, 0);
	//delayT1H();
	//GPIO_WritePinOutput(GPIOC, 12, 1);
	//delay();
	//GPIO_WritePinOutput(GPIOC, 12, 0);



	//PRINTF("T");
	//GPIO_WritePinOutput(GPIOC, 12, toggle);
	//if (toggle==0) { toggle=1;} else {toggle=0;}

}


void presetIndicatorLEDs(int left,int stop, int right)
{
	uint32_t data[3];

	data[0] = 0x000000;
	data[1] = 0x000000;
	data[2] = 0x000000;

	if (left) {
		data[2] = 0xFF0000;
	}

	if (right) {
		data[0] = 0xFF0000;
	}

	if (stop==1) {
		data[1] = 0xFF0000;
	}

	if (stop==2) {
		data[1] = 0xFFFF00;
	}

	if (stop==3) {
		data[1] = 0x00FF00;
	}

	sendWS2812Data(GPIOC, 12,data,3);



}


#define STATE_IDLE 0

#define STATE_START_MOVEMENT 1




#define PARK_LIMIT_X 60
#define PARK_LIMIT_Y 30
#define PARK_TOLERANCE_Y 20
#define PARK_TOLERANCE_X 20





// This is run everytime a new image is captured
void runParkingAssistant(volatile uint8_t *buffer)
{
	static int state = 0;
	static int lastxcor = 0;
	static int lastycor = 0;


	int xcor,ycor;

	int objectLocX,objectLocY;


	//presetLED();

	locateMovingObject(buffer,0,&xcor,&ycor);
	convert2RGBandSavePrevious(buffer);


	shadowSquare(buffer,PARK_LIMIT_X, PARK_LIMIT_Y, PARK_TOLERANCE_X, IMAGE_Y_SIZE - PARK_LIMIT_Y, 5, 5, 0);

	if (xcor>0) {
		objectLocX = xcor;
	} else {
		objectLocX = lastxcor;
	}

	if (ycor>0) {
		objectLocY = ycor;
	} else {
		objectLocY = lastycor;
	}

	paintLineX(buffer,objectLocX);
	paintLineY(buffer,objectLocY);



	int leftSign = 0;
	int rightSign = 0;
	int stopLight = 0;



	switch (state) {
	case STATE_IDLE:
		// Detect Car coming in
		state = STATE_START_MOVEMENT;
		stopLight = 1;
		break;
	case STATE_START_MOVEMENT:
		if (objectLocX<PARK_LIMIT_X) {
			rightSign = 1;
		}
		if (objectLocX>(PARK_LIMIT_X+PARK_TOLERANCE_X)) {
			leftSign = 1;
		}
		stopLight = 1;
		if (objectLocY<(PARK_LIMIT_Y+PARK_TOLERANCE_Y)) {
			stopLight = 2;
		}
		if (objectLocY<PARK_LIMIT_Y) {
			stopLight = 3;
		}


		//void paintSymbols(volatile uint8_t *buffer,int left,int stop,int right,int state)

		break;

	default:;



	}

	paintSymbols(buffer,leftSign,stopLight,rightSign,state);
	presetIndicatorLEDs(leftSign,stopLight, rightSign);

	lastxcor = objectLocX;
	lastycor = objectLocY;


}

int run(void)
{
	static uint32_t lastTime = 0; //getTimer();


	if (timeElapsed(lastTime)>100) {
		lastTime = getTimer();
        //PRINTF("One Second Elapsed! Global Time: %d Time Elapsed: %d\r\n", lastTime,timeElapsed(lastTime));
        PRINTF("One Second Elapsed!\r\n");
	} else {
        //PRINTF(" Global Time: %d Time Elapsed: %d\r\n", lastTime,timeElapsed(lastTime));

	}

}




#define MIN_IMAGE_X_START 5
#define MIN_IMAGE_Y_START 5

// This flag indicates if processed images are modified to show processing
#define MODIFY_IMAGE
// Change in image pixel to consider movement - for noise filtering
#define MOVEMENT_THRESHOLD 10
// Size of kernel for pixel belonging to object detection
#define OBJECT_KERNEL_SIZE 2

// Size of image
#define IMAGE_X_SIZE 160
#define IMAGE_Y_SIZE 120

#define IMAGE_BUFFER_SIZE IMAGE_X_SIZE * IMAGE_Y_SIZE * 2

static uint8_t gPrevImage[19200];







// Function that locates a moving object in the camera frame
// Inputs:
//    buffer: Image in YUV format
//    direction: 1 left to right -1 right to left
// Outputs:
//    xcor: xcoordinate of moving object if -1 means not changed or unabled to retrieve
//    ycor: y coordinate of moving object if -1 means not changed or unabled to retrieve
void locateMovingObjectUD(volatile uint8_t *buffer,int direction,int *pxcor,int *pycor)
{
	int index = 0;
	int prevIndex = 0;
	*pxcor = -1;
	*pycor = -1;
	int x,y;
	int sub;

	for (x=MIN_IMAGE_X_START;x<(IMAGE_X_SIZE - OBJECT_KERNEL_SIZE);x++)
	{
		for(y=MIN_IMAGE_Y_START;y<(IMAGE_Y_SIZE - OBJECT_KERNEL_SIZE);y++)
		{
			prevIndex = (y*IMAGE_X_SIZE + x);
			index = (prevIndex<<1) +1;
			sub = buffer[index] - gPrevImage[prevIndex];
			if ((sub>MOVEMENT_THRESHOLD)||(sub<-MOVEMENT_THRESHOLD))
			{
				*pxcor = x;
				break;
			}
		}
		if (*pxcor > -1) break;
	}

	for(y=MIN_IMAGE_Y_START;y<(IMAGE_Y_SIZE - OBJECT_KERNEL_SIZE);y++)
	{
		for (x=MIN_IMAGE_X_START;x<(IMAGE_X_SIZE - OBJECT_KERNEL_SIZE);x++)
		{
			prevIndex = (y*IMAGE_X_SIZE + x);
			index = (prevIndex<<1)+1;
			sub = buffer[index] - gPrevImage[prevIndex];
			if ((sub>MOVEMENT_THRESHOLD)||(sub<-MOVEMENT_THRESHOLD))
			{
				*pycor = y;
				break;
			}
		}
		if (*pycor > -1) break;
	}


	//convert2RGBandSavePrevious(buffer);
}





// Function that locates a moving object in the camera frame
// Inputs:
//    buffer: Image in YUV format
//    direction: 1 left to right -1 right to left
// Outputs:
//    xcor: xcoordinate of moving object if -1 means not changed or unabled to retrieve
//    ycor: y coordinate of moving object if -1 means not changed or unabled to retrieve
void locateMovingObject(volatile uint8_t *buffer,int direction,int *pxcor,int *pycor)
{
	int index = 0;
	int prevIndex = 0;
	*pxcor = -1;
	*pycor = -1;
	int x,y;
	int sub;

	for (x=MIN_IMAGE_X_START;x<(IMAGE_X_SIZE - OBJECT_KERNEL_SIZE);x++)
	{
		for(y=MIN_IMAGE_Y_START;y<(IMAGE_Y_SIZE - OBJECT_KERNEL_SIZE);y++)
		{
			prevIndex = (y*IMAGE_X_SIZE + x);
			index = (prevIndex<<1) +1;
			sub = buffer[index] - gPrevImage[prevIndex];
			if ((sub>MOVEMENT_THRESHOLD)||(sub<-MOVEMENT_THRESHOLD))
			{
				*pxcor = x;
				break;
			}
		}
		if (*pxcor > -1) break;
	}

	for(y=MIN_IMAGE_Y_START;y<(IMAGE_Y_SIZE - OBJECT_KERNEL_SIZE);y++)
	{
		for (x=MIN_IMAGE_X_START;x<(IMAGE_X_SIZE - OBJECT_KERNEL_SIZE);x++)
		{
			prevIndex = (y*IMAGE_X_SIZE + x);
			index = (prevIndex<<1)+1;
			sub = buffer[index] - gPrevImage[prevIndex];
			if ((sub>MOVEMENT_THRESHOLD)||(sub<-MOVEMENT_THRESHOLD))
			{
				*pycor = y;
				break;
			}
		}
		if (*pycor > -1) break;
	}


	//convert2RGBandSavePrevious(buffer);
}



// Function that converts a Buffer to RGB (So it can be displayed via USB)
// and stores the previous Y channel as the previous image in a global variable
void convert2RGBandSavePrevious(volatile uint8_t *buffer)
{
	int i=0;
	uint8_t Y5 = 0;
	uint8_t Y6 = 0;
	int byte;
	uint8_t Y = 0;
	for (byte=0;byte < IMAGE_BUFFER_SIZE;byte+=2)
	{
		Y = buffer[byte+1];
		gPrevImage[i]=buffer[byte+1];

		Y5 = Y >> 3;
		Y6 = Y >> 2;
		buffer[byte] = Y5 + (Y6<<5);
		buffer[byte+1] = (Y6>>3) +(Y5<<3);
		i++;
	}
}





void paintXY(volatile uint8_t *buffer,uint8_t x,uint8_t y,uint8_t r,uint8_t g,uint8_t b)
{
	int cor = (y*160 + x)*2;
	buffer[cor] = (b&0x1F) + (g<<5);
	buffer[cor+1] = (g>>3) +(r<<3);
}


void shadowXY(volatile uint8_t *buffer,uint8_t x,uint8_t y,uint8_t r,uint8_t g,uint8_t b)
{
	uint8_t or,og,ob;
	int cor = (y*160 + x)*2;

	or = (buffer[cor+1] & 0xF8) >> 3;
	ob = (buffer[cor] & 0x1F);
	og = (buffer[cor]>>5) + ((buffer[cor+1]&0x7)<<3) ;

	or += r;
	ob += b;
	og += g;

	if (or>0x1F) or = 0x1F;
	if (ob>0x1F) ob = 0x1F;
	if (og>0x3F) og = 0x3F;

	buffer[cor] = (ob&0x1F) + (og<<5);
	buffer[cor+1] = (og>>3) +(or<<3);
}


//char TO_ASCII[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char *TO_ASCII[16] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};


void paintSquare(volatile uint8_t *buffer,int startx, int starty, int width, int height, uint8_t r, uint8_t g, uint8_t b)
{
	int x,y;
	for (x=startx;x<startx+width;x++)
	{
		for (y=starty;y<starty+height;y++)
		{
			paintXY(buffer,x,y,r,g,b);
		}
	}
}

void paintHArrow(volatile uint8_t *buffer,int startx, int starty, int width, int height, uint8_t r, uint8_t g, uint8_t b)
{
	int x,y;
	float yc=(float)height/(float)width; //y change
	float xstep = 0;
	if (width>0) {
		for (x=startx;x<startx+width;x++)
		{
			int yt = (xstep++)*yc;
			for (y=starty+yt;y<starty+height-yt;y++)
			{
				paintXY(buffer,x,y,r,g,b);
			}
		}
	} else {
		for (x=startx;x>startx+width;x--)
		{
			int yt = -(xstep++)*yc;
			for (y=starty+yt;y<starty+height-yt;y++)
			{
				paintXY(buffer,x,y,r,g,b);
			}
		}
	}
}




void shadowSquare(volatile uint8_t *buffer,int startx, int starty, int width, int height, uint8_t r, uint8_t g, uint8_t b)
{
	int x,y;
	for (x=startx;x<startx+width;x++)
	{
		for (y=starty;y<starty+height;y++)
		{
			shadowXY(buffer,x,y,r,g,b);
		}
	}
}



void paintSymbols(volatile uint8_t *buffer,int left,int stop,int right,int state)
{
	if (left) {
		paintHArrow(buffer,60,90,-10,8,0,63,0);
	}


	if (stop==1) {
		paintSquare(buffer,80,90,8,8,0,63,0);
	}
	if (stop==2) {
		paintSquare(buffer,80,90,8,8,31,63,0);
	}
	if (stop==3) {
		paintSquare(buffer,80,90,8,8,31,0,0);
	}



	if (right) {
		paintHArrow(buffer,100,90,10,8,0,63,0);
	}

	int i,x;

	for (i=0;i<15;i++)
	{
		x = 10+i*10;
		if (state==i) {
			paintSquare(buffer,x,110,6,6,0,63,0);
		} else {
			paintSquare(buffer,x,110,6,6,20,40,20);
		}
	}

}

void paintLineX(volatile uint8_t *buffer,int xcor)
{
	int i;
	for (i=0;i<120;i++) {
		paintXY(buffer,xcor,i,31,0,0);
		paintXY(buffer,xcor,i,31,0,0);
	}
}

void paintLineY(volatile uint8_t *buffer,int ycor)
{
	int i;
	for (i=0;i<160;i++) {
		paintXY(buffer,i,ycor,31,0,0);
		paintXY(buffer,i,ycor,31,0,0);
	}
}



