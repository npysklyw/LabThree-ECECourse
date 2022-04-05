#define ADC_BASE 0xFF204000  
#define Mask_12_bits 0x00000FFF 
#define gpmask 0x000001FF
#define gpio 0xFF200060
#define g 0xFF200000
#define SW_BASE 0xFF200040

volatile int * ADC_BASE_ptr = (int *)ADC_BASE;
volatile int * gp_BASE_ptr = (int *)gpmask;
volatile int* const modeSwitch = (int*)SW_BASE;
volatile int * gb = (int *)g;
volatile int * gpio_int = (int *)gpio;
int mask = Mask_12_bits;
int gpmaskc = gpmask;


int getADC() {
	*(ADC_BASE_ptr) =0; // write anything to channel 0 to update ADC
	*(ADC_BASE_ptr+1) =0;
	volatile int channel0, channel2;
	channel0 = (*(ADC_BASE_ptr) & mask);
	channel2 = (*(ADC_BASE_ptr +1) & mask);
		
	if (*modeSwitch == 0) {
		return channel0;
	}
	if (*modeSwitch == 1) {
		printf("%d",channel2);
		return channel2;
	}
	
	
}

//for specific ranges return a different value of leds
int setColour() {

	int scale = 0;

	if (getADC() < 500 && getADC() > 0) {
		scale = 1;
	}
	if (getADC() > 500 && getADC() < 1000 ) {
		scale = 2;
	}
	if (getADC() > 1000 && getADC() < 1500 ) {
		scale = 3;
	}
	if (getADC() > 1500 && getADC() < 2000 ) {
		scale = 4;
	}
	if (getADC() > 2000 && getADC() < 2500 ) {
		scale = 5;
	}
	if (getADC() > 2500 && getADC() < 3000 ) {
		scale = 6;
	}
	if (getADC() > 3000 && getADC() < 3500 ) {
		scale = 7;
	}
	if (getADC() > 3500 && getADC() < 3750 ) {
		scale = 8;
	}
	if (getADC() > 3750 && getADC() < 4000 ) {
		scale =9;
	}
	if (getADC() > 4000) {
		scale =10;
	}
	//power(2,scale)-1
	
	*(gpio_int) = power(2,scale)-1;

}

//power function
int power(int x, int y){
      if(y == 0)
        return 1;
     return (x * power(x,y-1) );
    }

int main(void)
{
	*(gpio_int + 1) = 0x000003FF;//0x000001FF;

	while(1) {
		setColour();
	}
	
}		

