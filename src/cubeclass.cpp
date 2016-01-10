#include "cubeclass.h"
#include <stdbool.h>
#include <QMainWindow>
#include <QObject>
#include <QThread>
#include <QDebug>


CubeClass::CubeClass()
{
    currentEffect = newEffect = -1;
    for(int i=0; i<64; i++) img[i] = 0x00;

    snakeLen = SNAKE_MIN_LEN;

    frameCubeTime = 0;
    flagCubeShift = false;
    stringMode = 0;
    cubeStrPos = 0;

    rainDir = DOWN;
    rainAxis = Z;
}


void CubeClass::ModesDelay(uint16_t time)
{
//    qDebug() << "delay;" << time;
    if(currentEffect != newEffect)
        return;

    QThread::msleep(time);
}


void CubeClass::run()
{
    while (1)
    {
        switch(currentEffect)
        {
        case -1:
            break;
        case 0:
            ModesDelay(500);
            CubeSet();
            ModesDelay(500);
            CubeReset();
            break;
        case 1:
            RandomPixel();
            break;
        case 2:
            RandomPixelAccumulate();
            break;
        case 3:
            Rain();
            break;
        case 4:
            TrueSnake();
            break;
        case 5:
            MoveVoxelsAlongZ();
            break;
        case 6:
            OutlineBox();
            break;
        case 7:
            OutlineRandomBoxes();
            break;
        case 8:
            RandMidwayDest();
            break;
        case 9:
            Ripples();
            break;
        case 10:
            SideWaves();
            break;
        case 11:
            Firework();
            break;
        case 12:
            RandomInvert();
            break;
        case 13:
            SineLines();
            break;
        case 14:
            WormQqueeze();
            break;
        case 15:
            RandSelParallel();
            break;
        }
        if(currentEffect != newEffect)
        {
            currentEffect = newEffect;
            CubeReset();
        }
    }
}



/** =========== Basic Cube functions =============== **/

/*******************************************************************************
* Function Name  : CubeSet
* Description    : Make all cube voxels (LEDs) on
*******************************************************************************/
void CubeClass::CubeSet()
{
    for(int i=0; i<64; i++) img[i] = 255;
}


/*******************************************************************************
* Function Name  : CubeReset
* Description    : Make all cube voxels (LEDs) off
*******************************************************************************/
void CubeClass::CubeReset()
{
    for(int i=0; i<64; i++) img[i] = 0;
}


/*******************************************************************************
* Function Name  : CubeSetVoxel
* Description    : Sets one cube voxel (LED)
* Input          : Voxel coordinates
* Return         : opCode
*******************************************************************************/
int CubeClass::CubeSetVoxel( int x, int y, int z )
{
    if( x > 7 || y > 7 || z > 7  )    return 2; //invalid parameters
    //if( (img[8*z+x] & (1<<y)) == 1) return 1; //voxel is already set
    if( (img[8*z+7-y] & (1<<x)) == 1) return 1; //voxel is already set

    //img[8*z+x] |= (1<<y);
    img[8*z+7-y] |= (1<<x);
    return 0;
}


/*******************************************************************************
* Function Name  : CubResetVoxel
* Description    : Resets one cube voxel (LED)
* Input          : Voxel coordinates
* Return         : opCode
*******************************************************************************/
int CubeClass::CubeResetVoxel( int x, int y, int z )
{
    if( x > 7 || y > 7 || z > 7   )    return 2; //invalid parameters
    //if( (img[8*z+x] & (1<<y)) == 0 ) return 1; //voxel is already reset
    if( (img[8*z+7-y] & (1<<x)) == 0 ) return 1; //voxel is already reset

    //img[8*z+x] &= ~(1<<y);
    img[8*z+7-y] &= ~(1<<x);
    return 0;
}


/*******************************************************************************
* Function Name  : CubeSetPlane
* Description    : Set cube plane (XPLANE, YPLANE, ZPLANE)
* Input          : plane (XPLANE, YPLANE, ZPLANE) to Set all leds
*                : plane number (0-7)
*******************************************************************************/
void CubeClass::CubeSetPlane( int plane, int number )
{
    if(plane == XPLANE)
    {
        for(int i=0; i<8; i++)
            for(int n=0; n<8; n++)
                img[8*i + n] |= (1<<number);
    }

    if(plane == YPLANE)
    {
        //for(int i=0; i<8; i++) img[8*i+number] = 0xFF;
        for(uint8_t i=0; i<8; i++) img[8*i+7-number] = 0xFF;
    }

    if(plane == ZPLANE)
    {
        for(int i=0; i<8; i++) img[8*number+i] = 0xFF;
    }
}


/*******************************************************************************
* Function Name  : CubeResetPlane
* Description    : Reset cube plane (XPLANE, YPLANE, ZPLANE)
* Input          : plane (XPLANE, YPLANE, ZPLANE) to Reset all leds
*                : plane number (0-7)
*******************************************************************************/
void CubeClass::CubeResetPlane( int plane, int number )
{
    if(plane == XPLANE)
    {
        for(int i=0; i<8; i++)
            for(int n=0; n<8; n++)
                img[8*i+n] &= ~(1<<number);
    }

    if(plane == YPLANE)
    {
        //for(int i=0; i<8; i++)	img[8*i+number] = 0;
        for(uint8_t i=0; i<8; i++)	img[8*i+7-number] = 0;
    }

    if(plane == ZPLANE)
    {
        for(int i=0; i<8; i++)	img[8*number+i] = 0;
    }
}


/*******************************************************************************
* Function Name  : CubeSetLine
* Description    : Sets line in the cube
* Input          : plane (XPLANE, YPLANE, ZPLANE) to set leds line
*                : leds line coordinates
*******************************************************************************/
void CubeClass::CubeSetLine( int plane, int x, int y )
{
    if(plane == XPLANE)
    {
        //for(int i=0; i<8; i++)	img[8*y+x] |= (1<<i);
        for(uint8_t i=0; i<8; i++)	img[8*y+7-x] |= (1<<i);
    }

    if(plane == YPLANE)
    {
        for(int i=0; i<8; i++)	img[8*y+i] |= (1<<(x));
    }

    if(plane == ZPLANE)
    {
        for(int i=0; i<8; i++)	img[8*i+y] |= (1<<(x));
    }
}


/*******************************************************************************
* Function Name  : CubeResetLine
* Description    : Resets line in the cube
* Input          : plane (XPLANE, YPLANE, ZPLANE) to reset leds line
*                : leds line coordinates
*******************************************************************************/
void CubeClass::CubeResetLine( int plane, int x, int y )
{
    if(plane == XPLANE)
    {
        //for(int i=0; i<8; i++)	img[8*y+x] &= ~(1<<i);
        for(uint8_t i=0; i<8; i++)	img[8*y+7-x] &= ~(1<<i);
    }

    if(plane == YPLANE)
    {
        for(int i=0; i<8; i++)	img[8*y+i] &= ~(1<<(x));
    }

    if(plane == ZPLANE)
    {
        for(int i=0; i<8; i++)	img[8*i+y] &= ~(1<<(x));
    }
}


/*******************************************************************************
* Function Name  : CubeGetVoxel
* Description    : get Voxel state
* Input          : voxel coordinates
* Return         : voxel state
*******************************************************************************/
uint8_t CubeClass::CubeGetVoxel( uint8_t x, uint8_t y, uint8_t z )
{
    if( img[8*z+7-y] & (1<<x) )
        return 1;
    else
        return 0;
}


/*******************************************************************************
* Function Name  : Distance2D
* Description    :
*******************************************************************************/
float CubeClass::Distance2D(float x1, float y1, float x2, float y2)
{
    return (float)sqrt_((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


/*******************************************************************************
* Function Name  : Distance3D
* Description    :
*******************************************************************************/
float CubeClass::Distance3D(float x1, float y1, float z1, float x2, float y2, float z2)
{
    return sqrt_((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}


/*******************************************************************************
* Function Name  : Outline
* Description    :
*******************************************************************************/
void CubeClass::Outline(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2, uint8_t outlineMode)
{
    uint8_t origX = x2, origY = y2, origZ = z2;
    signed char xflg=0, yflg=0, zflg=0;

    if(x1<x2) 	{xflg = +1; x2++;}
    else		{xflg = -1; x2--;}

    if(y1<y2) 	{yflg = +1; y2++;}
    else		{yflg = -1; y2--;}

    if(z1<z2) 	{zflg = +1; z2++;}
    else		{zflg = -1; z2--;}

    for(uint8_t z=z1; z!=z2; z += zflg)
        for(uint8_t y=y1; y!=y2; y += yflg)
            for(uint8_t x=x1; x!=x2; x += xflg)
            {
                if(!outlineMode)
                {
                    /* only outline */
                    if(((x==x1 || x==origX) && (y==y1 || y==origY)) ||
                            ((x==x1 || x==origX) && (z==z1 || z==origZ)) ||
                            ((y==y1 || y==origY) && (z==z1 || z==origZ)))
                        CubeSetVoxel(x, y, z);
                }
                else
                    /* full volume */
                    CubeSetVoxel(x, y, z);
            }
}












/** =========== E F F E C T S ============ **/
/*******************************************************************************
* Function Name  : SetEqGraph
* Description    : Draws spectre on the cube
*******************************************************************************/
void CubeClass::SetEqGraph(int *mass)
{
    for(int i=0; i<8; i++)
        if(mass[i]>8) mass[i]=8;

    CubeReset();
#if 1
    //int y=0; //y volume k-freq
    for(int y=0; y<mass[8]; y++)
        for(int i=0; i<8; i++)
            for(int k=0; k<mass[i]; k++)
                img[8*y+7-i] |= (1<<(k));
    //img[8*k+7-i] |= (1<<(y));

    // for(uint8_t i=0; i<mass[8]; i++) CubeSetVoxel(7,0, i);

#else

    for(int i=0; i<8; i++)
        for(int k=0; k<mass[i]; k++)
            CubeSetLine(XPLANE, i, k);
#endif
}



/*******************************************************************************
* Function Name  : RandomPixel
* Description    : Draws random pixel without accumulation
*******************************************************************************/
void CubeClass::RandomPixel()
{
    //for (iterations = 0; iterations < 70; iterations++)
    {
        CubeReset();
        CubeSetVoxel(rand() % 8, rand() % 8, rand() % 8);

        ModesDelay(50);
    }
}


/*******************************************************************************
* Function Name  : RandomPixelAccumulate
* Description    :
*******************************************************************************/
void CubeClass::RandomPixelAccumulate()
{
    //for (iterations = 0; iterations < 512; iterations++)
    {
        static uint16_t massR[512];
        static uint16_t accFlag = 512;

        if (accFlag >= 512)
        {
            CubeReset();

            for (uint16_t i = 0; i < 512; i++)
                massR[i] = i;

            for (uint16_t i = 0; i < 512; i++)
            {
                uint8_t x[4];
                for (int oo = 0; oo < 4; oo++)
                    x[oo] = rand();


                uint16_t j = i
                        + (x[0] * 1000 + x[1] * 100 + x[2] * 10 + x[3])
                        / (9999 / (512 - i) + 1);
                j = j % 512;
                uint16_t t = massR[j];
                massR[j] = massR[i];
                massR[i] = t;
            }

            accFlag = 0;
        }
        else
            accFlag++;

        CubeSetVoxel(massR[accFlag] / 64, massR[accFlag] / 8 % 8,
                     massR[accFlag] % 8);

#define START_SPEED 50
#define END_SPEED 1

        ModesDelay(START_SPEED - (accFlag / (512 / (START_SPEED - END_SPEED))) + 1);
    }
}


/*******************************************************************************
* Function Name  : OutlineBox
* Description    :
*******************************************************************************/
void CubeClass::OutlineBox()
{
    //for(iterations=0; iterations<2; iterations++)
    {

#if 0
#define OUTLINE_MODE 1
#else
        static uint8_t OUTLINE_MODE=0;
        OUTLINE_MODE++;
#endif

        //000->777
        for(uint8_t i=0; i<8; i++)
        {
            CubeReset();
            Outline(0,0,0, i,i,i, OUTLINE_MODE%2);
            ModesDelay(140);
        }

        for(uint8_t i=0; i<8; i++)
        {
            CubeReset();
            Outline(7,7,7, i,i,i, OUTLINE_MODE%2);
            ModesDelay(140);
        }
        //700->077
        for(uint8_t i=0; i<8; i++)
        {
            CubeReset();
            Outline(7,0,0, 7-i,i,i, OUTLINE_MODE%2);
            ModesDelay(140);
        }

        for(uint8_t i=0; i<8; i++)
        {
            CubeReset();
            Outline(0,7,7, 7-i,i,i, OUTLINE_MODE%2);
            ModesDelay(140);
        }
        //from center to outside
        for(uint8_t i=0; i<4; i++)
        {
            CubeReset();
            Outline(3-i,3-i,3-i, 4+i,4+i,4+i, OUTLINE_MODE%2);
            ModesDelay(300);
        }

        for(uint8_t i=0; i<4; i++)
        {
            CubeReset();
            Outline(i,i,i, 7-i,7-i,7-i, OUTLINE_MODE%2);
            ModesDelay(300);
        }
    }
}


/*******************************************************************************
* Function Name  : OutlineRandomBoxes
* Description    :
*******************************************************************************/
void CubeClass::OutlineRandomBoxes()
{
    //for(iterations=0; iterations<100; iterations++)
    {
        static uint8_t flagReached = 0x3F;
        static uint8_t target[6], cur[6];

        if(flagReached == 0x3F) //all 6 bits set to 1
        {
            for(uint8_t i=0; i<3; i++)
            {
                target[i] = target[i+3] = 0;
                while( abs(target[i] - target[i+3]) < 3)
                {
                    target[i] = rand()%8;
                    target[i+3] = rand()%8;
                }
            }

            flagReached = 0;
            ModesDelay(800);
        }

        for(uint8_t i=0; i<6; i++)
        {
            if(BitIsReset(flagReached, i))
            {
                if(cur[i] < target[i])
                    cur[i]++;
                else if(cur[i] > target[i])
                    cur[i]--;
                else
                    BitSet(flagReached, i);
            }
        }

        CubeReset();
        Outline(cur[0],cur[1],cur[2], cur[3],cur[4],cur[5], 0);

        ModesDelay(50);
    }
}


/*******************************************************************************
* Function Name  : SideWaves
* Description    : wave from one side to another is rotating
*******************************************************************************/
void CubeClass::SideWaves()
{
    static uint16_t i = 16;

    if(++i>=184) i=16;

    //for(uint16_t i=0; i<184; i++)
    {
        CubeReset();

        for (uint8_t x=0; x<8; x++) //2ms
        {
            for (uint8_t y=0; y<8; y++)
            {
                float distance = Distance2D( 3.5 + sin_(i*2)*4, 3.5 + cos_(i*2)*4,   x,y);

                uint8_t height = (uint8_t)(4 + sin_(
                                               distance*35 + (i-16)*33
                                               )*3.5);
                CubeSetVoxel(x,y,(int) height);
            }
        }

        ModesDelay(100);
    }
}


/*******************************************************************************
* Function Name  : OutlineRandomBoxes
* Description    :
*******************************************************************************/
void CubeClass::SineLines()
{
    int x;

    float left, right, sine_base, x_dividor,ripple_height;

    static int i = 0;
    if(++i>=1000) i = 0;

    //for (i=0; i<1000; i++)
    {
        for (x=0; x<8 ;x++)
        {
            x_dividor = 2 + sin_((float)i/100*57.29)+1;
            ripple_height = 3 + (sin_((float)i/200*57.29)+1)*6;

            sine_base = (float) i/40 + (float) x/x_dividor;

            left = 4 + sin_(sine_base*57.29)*ripple_height;
            right = 4 + cos_(sine_base*57.29)*ripple_height;
            right = 7-left;

            //printf("%i %i \n", (int) left, (int) right);

            line_3d(0-3, x, (int) left, 7+3, x, (int) right);
            //line_3d((int) right, 7, x);
        }

        ModesDelay(10);
        CubeReset();
    }
}


/*******************************************************************************
* Function Name  : SphereMove
* Description    :
*******************************************************************************/
void CubeClass::SphereMove()
{
    CubeReset();

    float origin_x, origin_y, origin_z, distance, diameter;

    origin_x = 0;
    origin_y = 3.5;
    origin_z = 3.5;

    diameter = 3;

    int x, y, z, i;

    for (i=0; i<1500; i++)
    {
        origin_x = 3.5+sin_((float)i/50*57.29)*2.5;
        origin_y = 3.5+cos_((float)i/50*57.29)*2.5;
        origin_z = 3.5+cos_((float)i/30*57.29)*2;

        diameter = 2+sin_((float)i/150*57.29);

        for (x=0; x<8; x++)
        {
            for (y=0; y<8; y++)
            {
                for (z=0; z<8; z++)
                {
                    distance = Distance3D(x,y,z, origin_x, origin_y, origin_z);

                    if (distance>diameter && distance<diameter+1)
                    {
                        CubeSetVoxel(x,y,z);
                    }
                }
            }
        }

        ModesDelay(2);
        CubeReset();
    }
}


/*******************************************************************************
* Function Name  : Stairs
* Description    :
*******************************************************************************/
void CubeClass::Stairs()
{
    static uint8_t invert=1;
    static uint8_t fill = 0;

    for(uint8_t x = 0; x<16; x++)
    {
        uint8_t xx;

        if(invert)
            xx = 15-x;
        else
            xx = x;

        for(uint8_t y=0; y <= x; y++)
        {
            //uint8_t yy;
            if(xx) xx--;
            //if(xx>=16) xx=15;

            /*if(invert) yy=15-y;
            else yy=y;*/

            if(xx < 8 && y < 8)
            {

                img[xx*8 + y] = 0xFF;
            }
        }

        ModesDelay(100);

        if(fill) CubeReset();
        //CubeReset();

    }

    invert ^= (1<<0);
    if(invert) fill ^= (1<<0);
    CubeReset();
}


/*******************************************************************************
* Function Name  : WormQqueeze
* Description    :
*******************************************************************************/
void CubeClass::WormQqueeze()
{
    int size=2;//1 2
    int axis=Z;
    int direction=-1; // 1 -1

    int origin = (direction == -1)?7:0;
    uint8_t wormSize = 8-(size-1);

    uint8_t x = rand()%wormSize;
    uint8_t y = rand()%wormSize;

    for(uint16_t i=0; i<100; i++)
    {
        signed char dx = rand()%3 - 1;
        signed char dy = rand()%3 - 1;

        if ((x+dx) > 0 && (x+dx) < wormSize) x += dx;
        if ((y+dy) > 0 && (y+dy) < wormSize) y += dy;

        Shift(axis, direction);

        for(uint8_t j=0; j<size; j++)
        {
            for(uint8_t k=0; k<size; k++)
            {
                if (axis == Z) CubeSetVoxel(x+j,y+k,origin);
                if (axis == Y) CubeSetVoxel(x+j,origin,y+k);
                if (axis == X) CubeSetVoxel(origin,y+j,x+k);
            }
        }

        ModesDelay(150);
    }
}


/*******************************************************************************
* Function Name  : CharSpin
* Description    :
*******************************************************************************/
void CubeClass::CharSpin()
{
    unsigned int count=2;
    uint8_t bitmap=2;//0 1 2


    uint8_t dybde[] = {0,1,2,3,4,5,6,7,1,1,2,3,4,5,6,6,2,2,3,3,4,4,5,5,3,3,3,3,4,4,4,4};
    int d = 0;
    int flip = 0;
    uint8_t off;

    for(uint16_t i = 0; i<count; i++)
    {
        for(uint8_t mode=0; mode<4; mode++)
        {
            off = 0;
            flip = 0;
            d = 0;

            // front:
            for(uint8_t s=0; s<7; s++)
            {
                if(!flip)
                {
                    off++;
                    if(off == 4)
                    {
                        flip = 1;
                        off = 0;
                    }
                }
                else
                    off++;

                for(uint8_t x=0; x<8; x++)
                {
                    d = 0;

                    for(uint8_t y=0; y<8; y++)
                    {
                        if ((bitmaps[bitmap][7-x] >> y) & 0x01)
                        {
                            if(!flip)
                            {
                                if(mode%2==0)
                                    CubeSetVoxel(y,dybde[8*off+d++], x);
                                else
                                    CubeSetVoxel(dybde[8*off+d++], 7-y, x);
                            }
                            else
                            {
                                if(mode%2==0)
                                    CubeSetVoxel(y, dybde[31-8*off-d++], x);
                                else
                                    CubeSetVoxel(dybde[31-8*off-d++], 7-y, x);
                            }

                        }
                        else
                            d++;
                    }
                }

                ModesDelay(80);
                CubeReset();
            }
        }
    }
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
void CubeClass::effect_blinky2()
{
    CubeReset();

    int i = 750;
    while (i>0)
    {
        CubeReset();
        ModesDelay(i);

        CubeSet();
        ModesDelay(100);

        i = i - (15+(1000/(i/10)));
    }

    ModesDelay(1000);

    i = 750;
    while(i>0)
    {
        CubeReset();
        ModesDelay(751-i);

        CubeSet();
        ModesDelay(100);

        i = i - (15+(1000/(i/10)));
    }
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
void CubeClass::RandSelParallel ()
{
    /*
     * 	(AXIS_Z, 0 , 200,1);
        ModesDelay(1500);
        (AXIS_Z, 1 , 200,1);
        ModesDelay(1500);

        (AXIS_Z, 0 , 200,2);
        ModesDelay(1500);
        (AXIS_Z, 1 , 200,2);
        ModesDelay(1500);

        (AXIS_Y, 0 , 200,1);
        ModesDelay(1500);
        (AXIS_Y, 1 , 200,1);
        ModesDelay(1500);
     */

    static uint8_t origin=0; //0 1
    int delay=100;
    int mode=1; //1 2

    for(iterations=0; iterations<8; iterations++){

        char axis=rand()%6;

        int done;
        uint8_t cubePos[64];
        uint8_t pos[64] = {0};
        int sent = 0;

        while(1)
        {
            if(mode == 1)
            {
                //uint8_t notdone2 = 1;
                while(/*notdone2 && */sent<64)
                {
                    uint8_t i = (rand()*rand())%64;
                    if (pos[i] == 0)
                    {
                        sent++;
                        pos[i] += 1;
                        //notdone2 = 0;
                        break;
                    }
                }
            }
            else if(mode == 2)
            {
                if(sent < 64) pos[sent++] += 1;
            }

            done = 0;
            for(uint8_t i=0; i<64; i++)
            {
                if(pos[i]>0 && pos[i]<7)
                    pos[i] += 1;

                if(pos[i] == 7) done++;
            }

            if (done == 64) break;

            for(uint8_t i=0; i<64; i++)
                cubePos[i] = (origin == 0) ? pos[i] : (7-pos[i]);

            ModesDelay(delay);
            draw_positions_axis(axis, cubePos, 0);
        }

        origin ^= 1 /*rand()%2*/;
    }
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
void CubeClass::draw_positions_axis(char axis, uint8_t positions[64], int invert)
{
    CubeReset();

    for(uint8_t x=0; x<8; x++)
    {
        for(uint8_t y=0; y<8; y++)
        {
            if (axis >= Z) CubeSetVoxel(x, y, invert ? (7-positions[(x*8)+y]) : positions[(x*8)+y]);
            if (axis == Y) CubeSetVoxel(x, invert ? (7-positions[(x*8)+y]) : positions[(x*8)+y], y);
            if (axis == X) CubeSetVoxel(invert ? (7-positions[(x*8)+y]) : positions[(x*8)+y], y, x);
        }
    }
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
// Light all leds layer by layer,
// then unset layer by layer
void CubeClass::effect_loadbar()
{
    CubeReset();

    uint8_t plane = Z; // X Y Z
    uint8_t direction = 1; //0 not0

    for(uint8_t i=0; i<8; i++)
    {
        CubeSetPlane(plane, (direction)?(7-i):i);
        ModesDelay(100);
    }

    ModesDelay(100);

    for(uint8_t i=0; i<8; i++)
    {
        CubeResetPlane(plane, (direction)?(7-i):i);
        ModesDelay(100);
    }
}



/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
void CubeClass::line_3d(int x1, int y1, int z1, int x2, int y2, int z2)
{
    int dx, dy, dz, l, m, n, x_inc, y_inc, z_inc,
            err_1, err_2, dx2, dy2, dz2;
    int pixel[3];

    pixel[0] = x1;
    pixel[1] = y1;
    pixel[2] = z1;

    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;

    x_inc = (dx < 0) ? -1 : 1;
    y_inc = (dy < 0) ? -1 : 1;
    z_inc = (dz < 0) ? -1 : 1;

    l = abs(dx);
    m = abs(dy);
    n = abs(dz);

    dx2 = l << 1;
    dy2 = m << 1;
    dz2 = n << 1;

    if((l >= m) && (l >= n))
    {
        err_1 = dy2 - l;
        err_2 = dz2 - l;

        for(uint8_t i = 0; i < l; i++)
        {
            CubeSetVoxel(pixel[0], pixel[1], pixel[2]);

            if (err_1 > 0)
            {
                pixel[1] += y_inc;
                err_1 -= dx2;
            }

            if (err_2 > 0)
            {
                pixel[2] += z_inc;
                err_2 -= dx2;
            }

            err_1 += dy2;
            err_2 += dz2;
            pixel[0] += x_inc;
        }
    }
    else if((m >= l) && (m >= n))
    {
        err_1 = dx2 - m;
        err_2 = dz2 - m;

        for(uint8_t i = 0; i < m; i++)
        {
            CubeSetVoxel(pixel[0], pixel[1], pixel[2]);

            if(err_1 > 0)
            {
                pixel[0] += x_inc;
                err_1 -= dy2;
            }

            if(err_2 > 0)
            {
                pixel[2] += z_inc;
                err_2 -= dy2;
            }

            err_1 += dx2;
            err_2 += dz2;
            pixel[1] += y_inc;
        }
    }
    else
    {
        err_1 = dy2 - n;
        err_2 = dx2 - n;

        for(uint8_t i = 0; i < n; i++)
        {
            CubeSetVoxel(pixel[0], pixel[1], pixel[2]);

            if(err_1 > 0)
            {
                pixel[1] += y_inc;
                err_1 -= dz2;
            }

            if(err_2 > 0)
            {
                pixel[0] += x_inc;
                err_2 -= dz2;
            }

            err_1 += dy2;
            err_2 += dx2;
            pixel[2] += z_inc;
        }
    }

    CubeSetVoxel(pixel[0], pixel[1], pixel[2]);
}



/*******************************************************************************
* Function Name  : PlaneBoing
* Description    :
*******************************************************************************/
void CubeClass::PlaneBoing()
{
    for(iterations=0; iterations<3; iterations++){
        for(uint8_t k=XPLANE; k<ZPLANE+1; k++)
        {
            for(uint8_t i=0; i<8; i++)
            {
                CubeReset();
                CubeSetPlane(k, i);
                ModesDelay(50);
            }
            for(uint8_t i=7; i!=0; i--)
            {
                CubeReset();
                CubeSetPlane(k, i);
                ModesDelay(50);
            }
        }
    }
}


/*******************************************************************************
* Function Name  : MoveVoxelsAlongZInit
* Description    :
*******************************************************************************/
void CubeClass::MoveVoxelsAlongZInit()
{
    CubeReset();

    for (uint8_t x=0; x<8; x++)
        for (uint8_t y=0; y<8; y++)
            CubeSetVoxel(x, y, (rand()%2)*7);

    ModesDelay(200);
}


/*******************************************************************************
* Function Name  : MoveVoxelsAlongZ
* Description    :
*******************************************************************************/
// For each coordinate along X and Y, a voxel is set either at level 0 or at level 7
// for n iterations, a random voxel is sent to the opposite side of where it was.
void CubeClass::MoveVoxelsAlongZ()
{
    MoveVoxelsAlongZInit();

    for(iterations=0; iterations<100; iterations++){
        static uint8_t isInitialized = DISABLE;
        if(isInitialized == DISABLE)
        {
            isInitialized = ENABLE;
            MoveVoxelsAlongZInit();
        }

        static uint8_t lastX=0, lastY=0;
        uint8_t x = rand()%8, y = rand()%8;

        if(y != lastY && x != lastX)
        {
            MoveVoxelAlongZ(x, y, CubeGetVoxel(x, y, 0)?0:7);

            lastY = y;
            lastX = x;
            ModesDelay(80);
        }
    }
}


/*******************************************************************************
* Function Name  : MoveVoxelAlongZ
* Description    :
*******************************************************************************/
// Send a voxel flying from one side of the img to the other
// If its at the bottom, send it to the top..
void CubeClass::MoveVoxelAlongZ(uint8_t x, uint8_t y, uint8_t z)
{
    for(uint8_t i=0; i<8; i++)
    {
        if (z == 7)
        {
            CubeResetVoxel(x, y, 7-i+1);
            CubeSetVoxel(x, y, 7-i);
        }
        else
        {
            CubeResetVoxel(x, y, i-1);
            CubeSetVoxel(x, y, i);
        }

        ModesDelay(60);
    }
}


/*******************************************************************************
* Function Name  : RainSetMode
* Description    : Set Rain mode
*******************************************************************************/
void CubeClass::RainSetMode(uint8_t axis, uint8_t dir)
{
    rainAxis = axis;
    rainDir = dir;
}


/*******************************************************************************
* Function Name  : Rain
* Description    :
*******************************************************************************/
void CubeClass::Rain()
{
    for(iterations=0; iterations<12000/150; iterations++){
        static uint8_t prevPlane[8]; //2-led falling drops
        uint8_t newPoint = 7*(1-rainDir);

        switch(rainAxis)
        {
        case X:
            for(uint8_t i=0; i<8; i++)
                for(uint8_t j=0; j<8; j++)
                    BitWrite(BitIsSet(prevPlane[i], j), img[8*i+j], newPoint);

            for (uint8_t i=0; i<rand()%3; i++)
                CubeSetVoxel(newPoint, rand()%8, rand()%8);

            //A - B = (A xor B) and A
            for(uint8_t i=0; i<8; i++)
                for(uint8_t j=0; j<8; j++)
                    BitWrite(((BitIsSet(img[8*i+j], 7) ^ BitIsSet(prevPlane[i], j)) & BitIsSet(img[8*i+j], 7)),
                            prevPlane[i], j);
            break;

        case Y:
            for(uint8_t i=0; i<8; i++) img[8*i+newPoint] = prevPlane[i];

            for (uint8_t i=0; i<rand()%3; i++)
                CubeSetVoxel(rand()%8, newPoint, rand()%8);

            //A - B = (A xor B) and A
            for(uint8_t i=0; i<8; i++) prevPlane[i] = (img[8*i+newPoint] ^ prevPlane[i]) & img[8*i+newPoint];
            break;

        case Z:
            for(uint8_t i=0; i<8; i++) img[8*newPoint+i] = prevPlane[i];

            for (uint8_t i=0; i<rand()%3; i++)
                CubeSetVoxel(rand()%8, rand()%8, newPoint);

            //A - B = (A xor B) and A
            for(uint8_t i=0; i<8; i++) prevPlane[i] = (img[8*newPoint+i] ^ prevPlane[i]) & img[8*newPoint+i];
            break;
        }

        ModesDelay(150);
        Shift(rainAxis,-(1-rainDir));
    }
}


/*******************************************************************************
* Function Name  : Shift
* Description    :
*******************************************************************************/
// Shift the entire contents of the img along an axis
// This is great for effects where you want to draw something
// on one side of the img and have it flow towards the other
// side. Like rain flowing down the Z axiz.
void CubeClass::Shift (uint8_t axis, signed char direction)
{
    for (uint8_t i=0; i<8; i++)
    {
        uint8_t next = (direction == -1)?i:(7-i);

        for (uint8_t x=0; x<8; x++)
        {
            for (uint8_t y=0; y<8; y++)
            {
                uint8_t prev = (direction == -1)?(next+1):(next-1);

                if (axis == Z)
                    (CubeGetVoxel(x,y,prev)) ? CubeSetVoxel(x,y,next) :	CubeResetVoxel(x,y,next);
                if (axis == Y)
                    (CubeGetVoxel(x,prev,y)) ? CubeSetVoxel(x,next,y) :	CubeResetVoxel(x,next,y);
                if (axis == X)
                    (CubeGetVoxel(prev,y,x)) ? CubeSetVoxel(next,y,x) :	CubeResetVoxel(next,y,x);
            }
        }
    }

    uint8_t i = (direction == -1)?7:0;

    for (uint8_t x=0; x<8; x++)
    {
        for (uint8_t y=0; y<8; y++)
        {
            if (axis == X)	CubeResetVoxel(i,y,x);
            if (axis == Y)	CubeResetVoxel(x,i,y);
            if (axis == Z)	CubeResetVoxel(x,y,i);
        }
    }
}


/*******************************************************************************
 * Function Name  : OutlineRandomBoxes
 * Description    :
 *******************************************************************************/
void CubeClass::Firework()
{
    //const uint8_t n = 20;//50 orig 20 stable
#define n 20

    uint8_t origin_x = 3, origin_y = 3, origin_z = 3;
    signed int rand_y, rand_x, rand_z;

    float slowrate, gravity;

    // Particles and their position, x,y,z and their movement, dx, dy, dz
    float particles[n][6];

    CubeReset();
    for (uint8_t i=0; i<7; i++)
    {
        origin_x = rand()%4 + 2;
        origin_y = rand()%4 + 2;
        origin_z = rand()%2 + 5;

        // shoot a particle up in the air
        for(uint8_t e=0; e<origin_z; e++)
        {
            CubeSetVoxel(origin_x, origin_y, e);
            ModesDelay(50+10*e);
            CubeReset();
        }

        // Fill particle array
        for(uint8_t f=0; f<n; f++)
        {
            // Position
            particles[f][X] = origin_x;
            particles[f][Y] = origin_y;
            particles[f][Z] = origin_z;

            rand_x = (rand()*rand())%200 - 100;
            rand_y = (rand()*rand())%200 - 100;
            rand_z = (rand()*rand())%200 - 100;

            // Movement
            particles[f][3] = (float)rand_x/100; // dx
            particles[f][4] = (float)rand_y/100; // dy
            particles[f][5] = (float)rand_z/100; // dz
        }

        // explode
        for(uint8_t e=0; e<15; e++)
        {
            slowrate = 1.4 + tan_((e)*4);
            gravity = tan_(e/3)/2;

            CubeReset();
            for(uint8_t f=0; f<n; f++)
            {
                particles[f][X] += particles[f][3]/slowrate;
                particles[f][Y] += particles[f][4]/slowrate;
                particles[f][Z] += particles[f][5]/slowrate;
                particles[f][Z] -= gravity;

                CubeSetVoxel(particles[f][X], particles[f][Y], particles[f][Z]);
            }

            ModesDelay(130);
        }
    }
}



/*******************************************************************************
* Function Name  : DrawString
* Description    : Draws string
* Input			 :
* 				 :
*******************************************************************************/
void CubeClass::DrawString(char *pText, uint8_t mode)
{
    if(!cubeStrPos)
    {
        cubeStrPos = 0;
        flagCubeShift = true;

        pString = pText;
        stringMode = mode;

        DrawStringShift();
    }
}


/*******************************************************************************
* Function Name  : DrawStringShift
* Description    :
*******************************************************************************/
void CubeClass::DrawStringShift()
{
    uint16_t len = strlen(pString);
    CubeReset();

    if(stringMode == STRING_ONE_FACE || stringMode == STRING_PIPES)
    {
        for(uint8_t i=0; i<8; i++)
        {
            if( !( (cubeStrPos+i+1) % 6) || (cubeStrPos+i+1) > len*6 ) //Blank columns
            {
                for(uint8_t c=0; c<8; c++)
                {
                    if(stringMode == STRING_PIPES)
                        CubeResetLine(YPLANE, 7-i, 7-c);
                    else 			//STRING_ONE_FACE
                        img[8*(7-c)+7] &= ~(1<<(7-i));
                }
            }
            else
            {
                uint8_t col = font5x8[ 5*( *(pString + (cubeStrPos+i) / 6) -32) + (cubeStrPos+i)%6 ];

                for(uint8_t c=0; c<8; c++)
                {
                    if(stringMode == STRING_PIPES)	//draw chars - lines - 3D
                    {
                        if(col & (1<<c)) 	CubeSetLine(YPLANE, 7-i, 7-c);
                        else 		   		CubeResetLine(YPLANE, 7-i, 7-c);
                    }
                    else //STRING_ONE_FACE			draw flat chars
                    {
                        if(col & (1<<c)) 	img[8*(7-c)+7] |= (1<<(7-i));
                        else 			 	img[8*(7-c)+7] &= ~(1<<(7-i));
                    }
                }
            }
        }

        //End reached?
        if( ((++cubeStrPos/*+7*/)/6) >= strlen(pString) ) {flagCubeShift = false; cubeStrPos = 0;}

        //How long text frame will be displayed
        if(len > 8) frameCubeTime = TIMING/2;
        else 		frameCubeTime = TIMING;
    }
    else //STRING_TWO_FACES
    {
        for(uint8_t i=0; i<15; i++)
        {
            if( !( (cubeStrPos+i+1) % 6) || (cubeStrPos+i+1) > len*6 ) //Blank columns
            {
                for(uint8_t c=0; c<8; c++)
                {
                    if(i<=7)
                        img[8*(7-c)+7] &= ~(1<<(7-i));
                    else
                        img[8*(7-c)+7-(i-7)] &= ~(1<<(0));
                }
            }
            else
            {
                uint8_t col = font5x8[ 5*( *(pString + (cubeStrPos+i) / 6) -32) + (cubeStrPos+i)%6 ];

                for(uint8_t c=0; c<8; c++)
                {
                    if(i<=7)
                    {
                        if(col & (1<<c))
                            BitSet(img[8*(7-c)+7], 1<<(7-i));
                        else
                            BitReset(img[8*(7-c)+7], 1<<(7-i));
                    }
                    else
                    {
                        if(col & (1<<c)) img[8*(7-c)+7-(i-7)] |= (1<<(0));
                        else			 img[8*(7-c)+7-(i-7)] &= ~(1<<(0));

                    }
                }
            }
        }

        //End reached?
        if( ((++cubeStrPos)/6) >= len ) {flagCubeShift = false; cubeStrPos = 0;}

        //How long text frame will be displayed
        if(len > 8)
            frameCubeTime = TIMING/3;
        else
            frameCubeTime = TIMING;
    }
}





/*******************************************************************************
* Function Name  : RandMidwayDest
* Description    :
*******************************************************************************/
void CubeClass::RandMidwayDest()
{
    for(iterations=0; iterations<10; iterations++){
#define SMALL_DELAY 100
#define LONG_DELAY 	500

        uint8_t invert=0, axis;
        invert = rand();
        axis = rand()%3;

        uint8_t position[64] = {0}, destination[64];

        for(uint8_t i=0; i<64; i++)
            destination[i] = rand()%8;

        /* Loop 8 times to allow destination 7 to reach all the way */
        RandMidwayDest_Draw(axis, position, destination, invert%2);

        /* Set all destinations to 7 (opposite from the side they started out) */
        for(uint8_t i=0; i<64; i++)
            destination[i] = 7;

        /* Suspend the positions in mid-air for a while */
        ModesDelay(LONG_DELAY);

        /* Then do the same thing one more time */
        RandMidwayDest_Draw(axis, position, destination, invert%2);
    }
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
void CubeClass::RandMidwayDest_Draw(uint8_t axis, uint8_t position[64], uint8_t destination[64], uint8_t invert)
{
    for(uint8_t i=0; i<8; i++)
    {
        // For every iteration, move all position one step closer to their destination
        for(uint8_t px=0; px<64; px++)
        {
            if (position[px] < destination[px])
                position[px]++;
        }

        // Draw the positions and take a nap
        CubeReset();

        for(uint8_t x=0; x<8; x++)
        {
            for(uint8_t y=0; y<8; y++)
            {
                int p;

                if(invert)
                    p = (7-position[(x*8)+y]);
                else
                    p = position[(x*8)+y];

                if (axis == Z) CubeSetVoxel(x, y, p);
                if (axis == Y) CubeSetVoxel(x, p, y);
                if (axis == X) CubeSetVoxel(p, y, x);
            }
        }

        ModesDelay(SMALL_DELAY);
    }
}



/*******************************************************************************
* Function Name  : RandomInvert
* Description    :
*******************************************************************************/
void CubeClass::RandomInvert()
{
    //for(iterations=0; iterations<8*1000/15; iterations++)
    {
        uint8_t x = rand()%8, y = rand()%8, z = rand()%8;

        (CubeGetVoxel(x,y,z) == 1)?CubeResetVoxel(x,y,z):CubeSetVoxel(x,y,z);

        ModesDelay(25);
    }
}



/*******************************************************************************
* Function Name  : Ripples
* Description    :
*******************************************************************************/
void CubeClass::Ripples()
{
    for (signed int i=0; i<=32; i++)
    {
        CubeReset();

        for (uint8_t x=0; x<8; x++) //2ms
        {
            for (uint8_t y=0; y<8; y++)
            {
                uint8_t height = (uint8_t)(4 + sin_(
                                               Distance2D(3.5,3.5,x,y)*35 + (i-16)*33
                                               )*3.5);
                CubeSetVoxel(x, y, height);
            }
        }
        ModesDelay(120); //120
    }
}





/*******************************************************************************
* Function Name  : TrueSnake
* Description    :
*******************************************************************************/
void CubeClass::TrueSnake()
{
    //for(; snakeLen < SNAKE_MAX_LEN;)
    {
        const uint8_t variant[6][3] = {{0,1,2}, {0,2,1}, {1,2,0}, {1,0,2},	{2,1,0}, {2,0,1}};
        uint8_t i = rand()%6;

        do{
            int r =0;
            qDebug() << "Trying this shit out: "<<r++;
            target[X] = rand()%8;
            target[Y] = rand()%8;
            target[Z] = rand()%8;
        }
        while(	target[X] == Snake[0].voxel[X] ||
                target[Y] == Snake[0].voxel[Y] ||
                target[Z] == Snake[0].voxel[Z]);

#ifdef SNAKE_SHOW_TARGET
        CubeSetVoxel(target[X], target[Y], target[Z]);
#endif

        SnakeMove(variant[i][0]);
        SnakeMove(variant[i][1]);
        SnakeMove(variant[i][2]);

        Snake[0].complete[X] = Snake[0].complete[Y] = Snake[0].complete[Z] = 0;

        if(++snakeLen >= SNAKE_MAX_LEN)
        {
            qDebug() << ">> RESETTING SNAKE: ";
            snakeLen = SNAKE_MIN_LEN;
            CubeReset();
        }
        qDebug() << "SnakeLen=" << snakeLen;
    }
}


/*******************************************************************************
* Function Name  : SnakeMove.
* Description    :
* Input			 : axis to reach position
*******************************************************************************/
void CubeClass::SnakeMove(uint8_t axis)
{
    while(!Snake[0].complete[axis])
    {
        uint8_t dir;

        if(Snake[0].voxel[axis] < target[axis]) dir = INCREASE;
        if(Snake[0].voxel[axis] > target[axis]) dir = DECREASE;

        for(uint8_t i=snakeLen-1; i!=0; i--)
        {
            Snake[i].voxel[X] = Snake[i-1].voxel[X];
            Snake[i].voxel[Y] = Snake[i-1].voxel[Y];
            Snake[i].voxel[Z] = Snake[i-1].voxel[Z];
        }

        if(dir == INCREASE) Snake[0].voxel[axis]++;
        if(dir == DECREASE) Snake[0].voxel[axis]--;

        if(Snake[0].voxel[axis] == target[axis])
            Snake[0].complete[axis] = 1;

        for(uint8_t i=0; i<snakeLen; i++)
            CubeSetVoxel(Snake[i].voxel[X], Snake[i].voxel[Y], Snake[i].voxel[Z]);

        ModesDelay(SNAKE_DELAY);

        if(!(Snake[0].complete[X] && Snake[0].complete[Y] && Snake[0].complete[Z]))
            CubeResetVoxel( Snake[snakeLen-1].voxel[X],
                    Snake[snakeLen-1].voxel[Y],
                    Snake[snakeLen-1].voxel[Z]);
    }
}











/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
float CubeClass::sin_(float x)
{
    float sign = 1, sine;

    if(x<0)
    {
        while(x<0) {x += 180; sign=-sign;}
    }
    else if(x>180)
    {
        while(x>180) {x -= 180; sign=-sign;}
    }

    if(x<90)
        sine = sinTable[(uint16_t)x];
    else
        sine = sinTable[(uint16_t)(180-x)];

    return sign*sine /1024;
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
float CubeClass::cos_(float x)
{
    x -= 90;
    float sign = 1, sine;

    if(x<0)
    {
        while(x<0) {x += 180; sign=-sign;}
    }
    else if(x>180)
    {
        while(x>180) {x -= 180; sign=-sign;}
    }

    if(x<90)
        sine = sinTable[(uint16_t)x];
    else
        sine = sinTable[(uint16_t)(180-x)];

    return -sign*sine /1024;
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
float CubeClass::tan_(float x)
{
    return sin_(x)/cos_(x);
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
float CubeClass::factorial(double x)
{
    double result = 1;

    for(int i=1; i<=x; i++)
        result *= i;

    return result;
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
float CubeClass::pow_(float x,float y)
{
    double result = 1;

    for (int i=0; i<y; i++)
        result *= x;

    return result;
}


/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
float CubeClass::sqrt_(float x)
{
    union
    {
        int i;
        float x;
    }u;

    u.x = x;
    u.i = (1<<29) + (u.i >> 1) - (1<<22);
    return u.x;
}

