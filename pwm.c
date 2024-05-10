int  k; 



//***���Ը���Ƭ�������������� 
void UART0IntHandler(void);
void PWM_Config(int k);

int UART0IntHandler(void){
		
				uint32_t ststus;
				char a;
				ststus=UARTIntStatus (UART0_BASE,true);
				UARTIntClear (UART0_BASE,ststus);
				a=UARTCharGet(UART0_BASE);//ʶ����������ݣ�������� 
			
		        return a;
		}
		
		
int UARTo_Config(void){
		
		
		
		
		SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA);
		SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0);
		
		GPIOPinConfigure( GPIO_PA0_U0RX);
		GPIOPinConfigure( GPIO_PA1_U0TX);
		GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
		
		UARTStdioConfig(0,115200,SysCtlClockGet());	
		
		
		UARTFIFOEnable(UART0_BASE);//��ʹ��
		UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX2_8, UART_FIFO_RX2_8);
		//Ϊ����0���� �����ж�
		UARTIntEnable(UART0_BASE, UART_INT_RX);
		//�����ж����ȼ�
		IntPrioritySet(INT_UART0, 0x0);
		//�ж�ע��                   �жϷ�����
		UARTIntRegister(UART0_BASE, UART0IntHandler);
		
		IntEnable(INT_UART0);
		IntMasterEnable();
		
		while(1){
		
		}
		
		}		










//***************PWM���� 



void PWM_Config(int k)
{
    
	SysCtlPWMClockSet( SYSCTL_PWMDIV_8);           //***************ϵͳ����80M��4��Ƶ��10M
	
	
    //ʹ��GPIOF��PWM1
    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
	
	
    //ΪGPIOF_PIN_2��GPIOF_PIN_3����PWM�ź�
	GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_2);
	GPIOPinTypePWM( GPIO_PORTF_BASE,  GPIO_PIN_3);
	
	
    //��GPIOF_PIN_2��GPIOF_PIN_3ʹ�����Ÿ���
	GPIOPinConfigure( GPIO_PF2_M1PWM6);
	GPIOPinConfigure( GPIO_PF3_M1PWM7);
	
	
	
    //����PWM1ģ��ĵ�����������Ϊ���¼����벻ͬ������
	PWMGenConfigure( PWM1_BASE,  PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	
	
	
    //����PWM1ģ��ĵ�����������ÿ����������Ϊ2000��������PWMʱ��Ϊ10MHz
    //��ôPWM���Ƶ�ʾ���10^7/2000Ϊ5KHz�����������Ϊ16λ�Ĵ��������ܳ���65535
    //�����5000Hz�ķ���

  PWMGenPeriodSet(PWM1_BASE,  PWM_GEN_3, 4000);
	
	
	
	
	
    //����PWM1ģ��ĵ�����ͨ����ռ�ձ�Ϊ10%����������ĵ���������Ϊ�����ڵĸߵ�ƽ����
    //���Կ���ͨ��PWMGenPeriodGet�ó�һ�������ڵļ��������ٳ�0.1Ȼ���1����
		
		
	PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_6,PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*k - 1);	
    //ͬ��ֻ���������õ��߸�ͨ��
	PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_7,PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*k - 1);
	
	
	
	
    //ʹ�ܵ�����ͨ��
	PWMOutputState( PWM1_BASE,  PWM_OUT_6_BIT,true);	
	PWMOutputState( PWM1_BASE,  PWM_OUT_7_BIT,true);
    //ʹ�ܵ�����������
	PWMGenEnable( PWM1_BASE,  PWM_GEN_3);
	
	
	
}










int main(){

     SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);	
     while(1){
     	
     PWM_Config(a);	
     	
	 }

}






















