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

static uint8_t gPrevImage[19200];



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
void init(void)
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


    initHistory();

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

	uint32_t data[3];

	data[0] = 0x00FF00;
	data[1] = 0xFF0000;
	data[2] = 0xFFFF00;
	sendWS2812Data(GPIOC, 12,data,3);



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


struct coordinates
{
	int x;
	int y;
};

struct coordinates posHistory[HISTORY_LENGTH];
int posHistoryIndex;

void initHistory(void)
{
	for (int i=0;i<HISTORY_LENGTH;i++)
	{
		posHistory[i].x = -1;
		posHistory[i].y = -1;
	}
	posHistoryIndex = 0;
}

void addToHistory(int x, int y)
{
	posHistory[posHistoryIndex].x = x;
	posHistory[posHistoryIndex].y = y;
	posHistoryIndex++;
	posHistoryIndex = posHistoryIndex % HISTORY_LENGTH;
}

int inRange(int x,int y)
{
	//int maxChange = 0;
	int count = 0;
	for (int i=0;i<HISTORY_LENGTH;i++)
	{
		if ((posHistory[i].x > -1) && (posHistory[i].y > -1))
		{
			if ((abs(posHistory[i].x-x)<MAX_SPEED) &&
			    (abs(posHistory[i].y-y)<MAX_SPEED))
			{
				count++;
			}
		}
	}

	if (count>HISTORY_CHECK_SIZE) return 1;
	return 0;
}


int drawHistory(volatile uint8_t *buffer)
{
	//int maxChange = 0;
	int count = 0;
	for (int i=0;i<HISTORY_LENGTH;i++)
	{
		if ((posHistory[i].x > -1) && (posHistory[i].y > -1))
		{
			paintLineXrgb(buffer,posHistory[i].x,0,0,31);
			paintLineYrgb(buffer,posHistory[i].y,0,0,31);
		}
	}

	if (count>HISTORY_CHECK_SIZE) return 1;
	return 0;
}


// This is run everytime a new image is captured
void runParkingAssistantUD(volatile uint8_t *buffer)
{
	static int state = 0;
	static int lastxcor = 0;
	static int lastycor = 0;



	int xcor,ycor;

	int objectLocX,objectLocY;


	//presetLED();

	locateMovingObjectUD(buffer,0,&xcor,&ycor);
	convert2RGBandSavePrevious(buffer);


	//shadowSquare(buffer,PARK_LIMIT_X, PARK_LIMIT_Y, PARK_TOLERANCE_X, IMAGE_Y_SIZE - PARK_LIMIT_Y, 5, 5, 0);

	shadowSquare(buffer,PARK_UD_LIMIT_X, PARK_UD_LIMIT_Y-PARK_UD_TOLERANCE_Y, IMAGE_X_SIZE - PARK_UD_LIMIT_X, PARK_UD_TOLERANCE_Y, 5, 5, 0);

	/*
	if (xcor>0) {
		objectLocX = xcor;
		paintLineX(buffer,objectLocX);
	} else {
		objectLocX = lastxcor;
	}

	if (ycor>0) {
		objectLocY = ycor;
		paintLineY(buffer,objectLocY);
	} else {
		objectLocY = lastycor;
	}
*/

	if (xcor>0) {
		//objectLocX = xcor;
		paintLineX(buffer,xcor);
	} else {
		//objectLocX = lastxcor;
	}

	if (ycor>0) {
		//objectLocY = ycor;
		paintLineY(buffer,ycor);
	} else {
		//objectLocY = lastycor;
	}

	drawHistory(buffer);

	if ((xcor>0)&(ycor>0)) { // If movement has been detected
		if (inRange(xcor,ycor)) {
			paintLineXrgb(buffer,xcor,0,63,0);
			paintLineYrgb(buffer,ycor,0,63,0);
			objectLocX = xcor;
			objectLocY = ycor;
		} else {
			objectLocX = lastxcor;
			objectLocY = lastycor;
		}
		addToHistory(xcor, ycor);
	} else {
		objectLocX = lastxcor;
		objectLocY = lastycor;
	}



	int leftSign = 0;
	int rightSign = 0;
	int stopLight = 0;

	static int movementCount = 0;

	switch (state) {
	case STATE_IDLE: // Detect Car coming in
		// Detect object moving in
		/*
		if ((lastxcor - objectLocX)>0) {
			movementCount+=2;
			PRINTF("+movementCount: %d\r\n",movementCount);
			if (movementCount>5)
			{
				state = STATE_START_MOVEMENT;
			}
		} else {
			movementCount--;
			if (movementCount<0) movementCount = 0;
			PRINTF("-movementCount: %d\r\n",movementCount);
		}*/
		//stopLight = 1;
		state = STATE_START_MOVEMENT;

		break;
	case STATE_START_MOVEMENT:
		/*
		if (((lastxcor - objectLocX)>0) &&(lastycor - objectLocY)>0) {
			movementCount+=5;
			if (movementCount>60) movementCount=60;
		} else {
			movementCount--;
			if (movementCount<0)
			{
				movementCount = 0;
				state = STATE_IDLE;
			}
		}
*/
		if (objectLocY>PARK_UD_LIMIT_Y) {
			rightSign = 1;
		}
		if (objectLocY<(PARK_UD_LIMIT_Y-PARK_UD_TOLERANCE_Y)) {
			leftSign = 1;
		}
		stopLight = 1;
		if (objectLocX<(PARK_UD_LIMIT_X+PARK_UD_TOLERANCE_X)) {
			stopLight = 2;
		}
		if (objectLocX<PARK_UD_LIMIT_X) {
			stopLight = 3;
		}
		PRINTF("Loc: %d,%d xcor,ycor: %d,%d\r\n",objectLocX,objectLocY,xcor,ycor);


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







int kernelMoved(volatile uint8_t *buffer,int x, int y)
{
	int index = 0;
	int prevIndex = 0;
	int sub;

	int xs,ys;
	int numChanges = 0;

	for (xs=x;xs<x+OBJECT_KERNEL_SIZE;xs++)
	{
		for (ys=y;ys>y-OBJECT_KERNEL_SIZE;ys--)
		{
			prevIndex = (y*IMAGE_X_SIZE + x);
			index = (prevIndex<<1) +1;
			sub = buffer[index] - gPrevImage[prevIndex];
			if ((sub>MOVEMENT_THRESHOLD)||(sub<-MOVEMENT_THRESHOLD))
			{
				numChanges++;
			}

		}
	}
	if (numChanges == OBJECT_KERNEL_SIZE*OBJECT_KERNEL_SIZE) return 1;
	return 0;
}

// Function that locates a moving object in the camera frame
// Inputs:
//    buffer: Image in YUV format
//    direction: 1 left to right -1 right to left
// Outputs:
//    xcor: xcoordinate of moving object if -1 means not changed or unabled to retrieve
//    ycor: y coordinate of moving object if -1 means not changed or unabled to retrieve
void locateMovingObjectUD(volatile uint8_t *buffer,int direction,int *pxcor,int *pycor)
{
	*pxcor = -1;
	*pycor = -1;
	int x,y;
	for (x=MIN_IMAGE_X_START;x<(IMAGE_X_SIZE - OBJECT_KERNEL_SIZE);x++)
	{
		for (y=(IMAGE_Y_SIZE-MIN_IMAGE_Y_START); y > OBJECT_KERNEL_SIZE;y--)
		{
			if (kernelMoved(buffer,x,y)) {
				*pxcor = x;
				break;
			}
		}
		if (*pxcor > -1) break;
	}

	for(y=(IMAGE_Y_SIZE-MIN_IMAGE_Y_START);y>OBJECT_KERNEL_SIZE;y--)
	{
		for (x=MIN_IMAGE_X_START;x<(IMAGE_X_SIZE - OBJECT_KERNEL_SIZE);x++)
		{
			if (kernelMoved(buffer,x,y)) {
				*pycor = y;
				break;
			}
		}
		if (*pycor > -1) break;
	}
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


void paintVArrow(volatile uint8_t *buffer,int startx, int starty, int width, int height, uint8_t r, uint8_t g, uint8_t b)
{
	int x,y;
	float xc=(float)height/(float)width; //y change
	float ystep = 0;
	if (width>0) {
		for (y=starty;y<starty+width;y++)
		{
			int xt = (ystep++)*xc;
			for (x=startx+xt;x<startx+height-xt;x++)
			{
				paintXY(buffer,x,y,r,g,b);
			}
		}
	} else {
		for (y=starty;y>starty+width;y--)
		{
			int xt = -(ystep++)*xc;
			for (x=startx+xt;x<startx+height-xt;x++)
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
		paintVArrow(buffer,140,40,-10,8,0,63,0);
	}


	if (stop==1) {
		paintSquare(buffer,140,60,8,8,0,63,0);
	}
	if (stop==2) {
		paintSquare(buffer,140,60,8,8,31,63,0);
	}
	if (stop==3) {
		paintSquare(buffer,140,60,8,8,31,0,0);
	}



	if (right) {
		paintVArrow(buffer,140,80,10,8,0,63,0);
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
		//paintXY(buffer,xcor,i,31,0,0);
		paintXY(buffer,xcor,i,31,0,0);
	}
}

void paintLineY(volatile uint8_t *buffer,int ycor)
{
	int i;
	for (i=0;i<160;i++) {
		//paintXY(buffer,i,ycor,31,0,0);
		paintXY(buffer,i,ycor,31,0,0);
	}
}

void paintLineXrgb(volatile uint8_t *buffer,int xcor,uint8_t r,uint8_t g,uint8_t b)
{
	int i;
	for (i=0;i<120;i++) {
		//paintXY(buffer,xcor,i,r,g,b);
		paintXY(buffer,xcor,i,r,g,b);
	}
}

void paintLineYrgb(volatile uint8_t *buffer,int ycor,uint8_t r,uint8_t g,uint8_t b)
{
	int i;
	for (i=0;i<160;i++) {
		//paintXY(buffer,i,ycor,r,g,b);
		paintXY(buffer,i,ycor,r,g,b);
	}
}



