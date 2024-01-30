// PowerDisplay class:
class PowerDisplay : public Component {

public:

	bool inRange(float val, float minimum, float maximum)
	{
	  return ((minimum <= val) && (val <= maximum));
	}

}; //class