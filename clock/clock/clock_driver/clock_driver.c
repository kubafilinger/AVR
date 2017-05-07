ISR(TIMER2_OVF_vect)
{
	TCCR2 = (1 << CS22) | (1 << CS20);
	
	if(CLOCKStatus & (1 << REVERSE_CLOCK))
	{
		if(CLOCKTime > 0)
			CLOCKTime -= 1;
	}
	else
		CLOCKTime = (CLOCKTime + 1);
	
	CLOCKStatus |= (1 << CHANGE_STATUS);
}

int getSeconds()
{
	return (int)CLOCKTime;
}

int getMinutes()
{
	return (int)CLOCKTime / MINUTE_SECONDS;
}

int getHours()
{
	return (int)CLOCKTime / HOUR_SECONDS;
}

int * getTime()
{
	static int time[3]; // [0] -> h, [1] -> m, [2] -> s
	uint32_t tmpTime = CLOCKTime;
	
	time[0] = getHours(),					tmpTime %= HOUR_SECONDS;
	time[1] = tmpTime / MINUTE_SECONDS,		tmpTime %= MINUTE_SECONDS;
	time[2] = tmpTime;
	
	return time;
}

void CLOCKReset()
{
	CLOCKTime = 0;
}

void CLOCKStart()
{
	CLOCKStatus |= (1 << ACTIVE_STATUS);
	TIMSK |= (1 << TOIE2);
}

void CLOCKStop()
{
	CLOCKStatus &= ~(1 << ACTIVE_STATUS);
	TIMSK &= ~(1 << TOIE2);
}

int CLOCKIsActive()
{
	if(CLOCKStatus && (1 << ACTIVE_STATUS))
		return 1;
	else
		return 0;
}

void CLOCKInit()
{
	ASSR |= (1 << AS2); // set timer in async mode
	
	TCNT2 = 0;
	TCCR2 = (1 << CS22) | (1 << CS20);
	
	while(ASSR & 0x07);
}