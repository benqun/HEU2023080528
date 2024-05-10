int  k; 



//***电脑给单片机（可行正常） 
void UART0IntHandler(void);
void PWM_Config(int k);

int UART0IntHandler(void){
		
				uint32_t ststus;
				char a;
				ststus=UARTIntStatus (UART0_BASE,true);
				UARTIntClear (UART0_BASE,ststus);
				a=UARTCharGet(UART0_BASE);//识别输入的数据，进行输出 
			
		        return a;
		}
		
		
int UARTo_Config(void){
		
		
		
		
		SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA);
		SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0);
		
		GPIOPinConfigure( GPIO_PA0_U0RX);
		GPIOPinConfigure( GPIO_PA1_U0TX);
		GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
		
		UARTStdioConfig(0,115200,SysCtlClockGet());	
		
		
		UARTFIFOEnable(UART0_BASE);//先使能
		UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX2_8, UART_FIFO_RX2_8);
		//为串口0配置 接收中断
		UARTIntEnable(UART0_BASE, UART_INT_RX);
		//配置中断优先级
		IntPrioritySet(INT_UART0, 0x0);
		//中断注册                   中断服务函数
		UARTIntRegister(UART0_BASE, UART0IntHandler);
		
		IntEnable(INT_UART0);
		IntMasterEnable();
		
		while(1){
		
		}
		
		}		










//***************PWM生成 



void PWM_Config(int k)
{
    
	SysCtlPWMClockSet( SYSCTL_PWMDIV_8);           //***************系统设置80M，4分频，10M
	
	
    //使能GPIOF与PWM1
    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
	
	
    //为GPIOF_PIN_2与GPIOF_PIN_3分配PWM信号
	GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_2);
	GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_3);
	
	
    //对GPIOF_PIN_2与GPIOF_PIN_3使能引脚复用
	GPIOPinConfigure( GPIO_PF2_M1PWM6);
	GPIOPinConfigure( GPIO_PF3_M1PWM7);
	
	
	
    //设置PWM1模块的第三个发生器为向下计数与不同步计数
	PWMGenConfigure( PWM1_BASE,  PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	
	
	
    //设置PWM1模块的第三个发生器每个计数周期为2000个数，而PWM时钟为10MHz
    //那么PWM输出频率就是10^7/2000为5KHz，但是这个数为16位寄存器，不能超过65535
    //想产生5000Hz的方波

  PWMGenPeriodSet(PWM1_BASE,  PWM_GEN_3, 4000);
	
	
	
	
	
    //设置PWM1模块的第六个通道的占空比为10%，这个函数的第三个参数为周期内的高电平数，
    //所以可以通过PWMGenPeriodGet得出一个周期内的计数总数再乘0.1然后减1就行
		
		
	PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_6,PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*k - 1);	
    //同理，只不过是设置第七个通道
	PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_7,PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*k - 1);
	
	
	
	
    //使能第六个通道
	PWMOutputState( PWM1_BASE,  PWM_OUT_6_BIT,true);	
	PWMOutputState( PWM1_BASE,  PWM_OUT_7_BIT,true);
    //使能第三个发生器
	PWMGenEnable( PWM1_BASE,  PWM_GEN_3);
	
	
	
}










int main(){

     SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);	
     while(1){
     	
     PWM_Config(a);	
     	
	 }

}






















