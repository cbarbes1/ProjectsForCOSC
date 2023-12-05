#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
#define GO 2
#define STOP 3

struct integers{
	int numbers[5];
	int counter;
};

struct usrData{
	int status;
	int gostop;
	struct integers data;
};
