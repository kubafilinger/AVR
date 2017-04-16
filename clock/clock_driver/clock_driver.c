ISR(TIMER2_OVF_vect)
{
	TCCR2 = (1 << CS22) | (1 << CS20);
	
	CLOCKTime = (CLOCKTime + 1) % DAY_SECONDS;
	CLOCKStatus |= (1 << CHANGE_STATUS);
}

int getSeconds() {
	return (int)CLOCKTime;
}

int getMinutes() {
	return (int)CLOCKTime / MINUTE_SECONDS;
}

int getHours() {
	return (int)CLOCKTime / HOUR_SECONDS;
}

int * getTime() {
	static int time[3]; // [0] -> h, [1] -> m, [2] -> s
	uint32_t tmpTime = CLOCKTime;
	
	time[0] = getHours(),					tmpTime %= HOUR_SECONDS;
	time[1] = tmpTime / MINUTE_SECONDS,		tmpTime %= MINUTE_SECONDS;
	time[2] = tmpTime;
	
	return time;
}

void set_timer_rtc()
{
	ASSR |= (1 << AS2); // prze�aczenie timera na tryb asynchroniczny
	
	TCNT2 = 0; // zerowanie timera2, poniewa� domy�lnie jest warto�� losowa, kt�ra powoduje, �e nie wiemy kiedy uruchomi si� timer
	TCCR2 = (1 << CS22) | (1 << CS20); // ustawienie preskalera
	// po co jest ustawianie preskalera sokor obojetnie jaka wartosc bedzie to i tak nie zadziala ??????????????
	//????????????????????????????????????????????????????????????S
	
	while(ASSR & 0x07);  // ????????
	
	TIMSK |= (1 << TOIE2); // odblokowanie przerwania xppppp
}