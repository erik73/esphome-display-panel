// PowerDisplay class:
class PowerDisplay : public Component {

public:
	
private:

    void DrawGraphLine(display::Display *buff, double x1, double x2, double y1, double y2, Color color = COLOR_ON) {
	buff->line(xPos + x1*xFactor, yPos+graphHeight-(y1*yFactor), xPos + x2*xFactor, yPos+graphHeight-(y2*yFactor), color);		
//	ESP_LOGD("GraphGrid x1: ", to_string(xPos + x1*xFactor).c_str());
}

	double AddPrice(display::Display *buff, int hour, double price, int lastHour, double lastPrice)	{
		if(lastHour<0)
			lastHour=0;	  
		if(lastPrice==0)
			lastPrice = price;	
		DrawGraphLine(buff, lastHour, hour, lastPrice, price, PriceColour(lastPrice));
	  return price;
	}
	
// The block below is used to determine text and graph colors based on the price
    Color PriceColour (float nNewPrice) {
	    Color colour;
	    if (inRange(nNewPrice, EXTREMELY_EXPENSIVE, 100)) {colour = COLOR_CSS_MAROON;}
	    else if (inRange(nNewPrice, VERY_EXPENSIVE, EXTREMELY_EXPENSIVE)){colour =  COLOR_CSS_RED;}
	    else if (inRange(nNewPrice, EXPENSIVE, VERY_EXPENSIVE)){colour =  COLOR_CSS_ORANGE;}
	    else if (inRange(nNewPrice, NORMAL, EXPENSIVE)){colour = COLOR_CSS_GREENYELLOW;}
	    else if (inRange(nNewPrice, CHEAP, NORMAL)){colour = COLOR_CSS_GREEN;}
	    else if (inRange(nNewPrice, VERY_CHEAP, CHEAP)){colour = COLOR_CSS_DARKGREEN;}
	    else if (inRange(nNewPrice, -100, VERY_CHEAP)){colour = COLOR_CSS_DARKGREEN;}     
	    return colour; 
	    }

    Color PhaseColour (float nphaseCurrent) {
	    Color colour;
	    if (inRange(nphaseCurrent, -100, 5)) {colour = COLOR_CSS_GREEN;}
	    else if (inRange(nphaseCurrent, 5, 10)){colour =  COLOR_CSS_GREENYELLOW;}
	    else if (inRange(nphaseCurrent, 10, 100)){colour =  COLOR_CSS_RED;}
	    return colour; 
	}

    Color VoltageColour (float nphaseVoltage) {
	    Color colour;
	    if (inRange(nphaseVoltage, -100, 225)) {colour = COLOR_CSS_GREENYELLOW;}  
	    else if (inRange(nphaseVoltage, 225, 240)){colour =  COLOR_CSS_GREEN;}
	    else if (inRange(nphaseVoltage, 240, 300)){colour =  COLOR_CSS_GREENYELLOW;}
	    return colour; 
	}
	
	double CalculateAccumulatedCost(double currentPrice, double dailyEnergy) {
		if (currentPrice == 0)
			return 0;
		double nEnergyDelta = dailyEnergy - prevDailyEnergy; 	
		prevDailyEnergy = dailyEnergy;
		accumulatedCost += (nEnergyDelta * currentPrice);
		//SaveValueToNvm("AccumulatedCost", accumulatedCost);
		return accumulatedCost;
	}

	bool inRange(float val, float minimum, float maximum)
	{
	  return ((minimum <= val) && (val <= maximum));
	}
	



}; //class