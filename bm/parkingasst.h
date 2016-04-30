
uint32_t getTimer(void);

uint32_t timeElapsed(uint32_t lastTime);


#define STATE_IDLE 0

#define STATE_START_MOVEMENT 1




// This is run everytime a new image is captured
void runParkingAssistant(volatile uint8_t *buffer);

int run(void);



#define MIN_IMAGE_X_START 5
#define MIN_IMAGE_Y_START 5

// This flag indicates if processed images are modified to show processing
#define MODIFY_IMAGE
// Change in image pixel to consider movement - for noise filtering
#define MOVEMENT_THRESHOLD 20
// Size of kernel for pixel belonging to object detection
#define OBJECT_KERNEL_SIZE 4

// Size of image
#define IMAGE_X_SIZE 160
#define IMAGE_Y_SIZE 120

#define IMAGE_BUFFER_SIZE IMAGE_X_SIZE * IMAGE_Y_SIZE * 2



#define PARK_UD_LIMIT_Y 80
#define PARK_UD_LIMIT_X 40
#define PARK_UD_TOLERANCE_Y 20
#define PARK_UD_TOLERANCE_X 40

#define HISTORY_LENGTH 10
#define MAX_SPEED 30
#define HISTORY_CHECK_SIZE 5





// Function that locates a moving object in the camera frame
// Inputs:
//    buffer: Image in YUV format
//    direction: 1 left to right -1 right to left
// Outputs:
//    xcor: xcoordinate of moving object if -1 means not changed or unabled to retrieve
//    ycor: y coordinate of moving object if -1 means not changed or unabled to retrieve
void locateMovingObject(volatile uint8_t *buffer,int direction,int *pxcor,int *pycor);

// Function that converts a Buffer to RGB (So it can be displayed via USB)
// and stores the previous Y channel as the previous image in a global variable
void convert2RGBandSavePrevious(volatile uint8_t *buffer);




void paintXY(volatile uint8_t *buffer,uint8_t x,uint8_t y,uint8_t r,uint8_t g,uint8_t b);

void paintSquare(volatile uint8_t *buffer,int startx, int starty, int width, int height, uint8_t r, uint8_t g, uint8_t b);

void paintSymbols(volatile uint8_t *buffer,int left,int stop,int right,int state);

void paintLineX(volatile uint8_t *buffer,int xcor);
void paintLineY(volatile uint8_t *buffer,int ycor);


void init(void);


void delay(void);
void sendWS2812Data(GPIO_Type *base, uint32_t pin,uint32_t *data,int length);
void presetLED(void);
void presetIndicatorLEDs(int left,int stop, int right);
// This is run everytime a new image is captured
void runParkingAssistant(volatile uint8_t *buffer);
void initHistory(void);
void addToHistory(int x, int y);
int inRange(int x,int y);
// This is run everytime a new image is captured
void runParkingAssistantUD(volatile uint8_t *buffer);




int kernelMoved(volatile uint8_t *buffer,int x, int y);
// Function that locates a moving object in the camera frame
// Inputs:
//    buffer: Image in YUV format
//    direction: 1 left to right -1 right to left
// Outputs:
//    xcor: xcoordinate of moving object if -1 means not changed or unabled to retrieve
//    ycor: y coordinate of moving object if -1 means not changed or unabled to retrieve
void locateMovingObjectUD(volatile uint8_t *buffer,int direction,int *pxcor,int *pycor);

// Function that locates a moving object in the camera frame
// Inputs:
//    buffer: Image in YUV format
//    direction: 1 left to right -1 right to left
// Outputs:
//    xcor: xcoordinate of moving object if -1 means not changed or unabled to retrieve
//    ycor: y coordinate of moving object if -1 means not changed or unabled to retrieve
void locateMovingObject(volatile uint8_t *buffer,int direction,int *pxcor,int *pycor);


void shadowXY(volatile uint8_t *buffer,uint8_t x,uint8_t y,uint8_t r,uint8_t g,uint8_t b);

void paintHArrow(volatile uint8_t *buffer,int startx, int starty, int width, int height, uint8_t r, uint8_t g, uint8_t b);


void shadowSquare(volatile uint8_t *buffer,int startx, int starty, int width, int height, uint8_t r, uint8_t g, uint8_t b);
void paintLineXrgb(volatile uint8_t *buffer,int xcor,uint8_t r,uint8_t g,uint8_t b);
void paintLineYrgb(volatile uint8_t *buffer,int ycor,uint8_t r,uint8_t g,uint8_t b);





