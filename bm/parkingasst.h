
uint32_t getTimer(void);

uint32_t timeElapsed(uint32_t lastTime);


/*!
 * @brief Main function
 */
int init(void);

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
#define MOVEMENT_THRESHOLD 10
// Size of kernel for pixel belonging to object detection
#define OBJECT_KERNEL_SIZE 2

// Size of image
#define IMAGE_X_SIZE 160
#define IMAGE_Y_SIZE 120

#define IMAGE_BUFFER_SIZE IMAGE_X_SIZE * IMAGE_Y_SIZE * 2






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
