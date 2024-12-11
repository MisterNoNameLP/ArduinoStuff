#include <Thread.h>
#include <ThreadController.h>

ThreadController controll = ThreadController();
Thread thread1 = Thread();
Thread thread2 = Thread();

// callback for myThread
void threadCallback1(){
	Serial.println("Thread1");
}

// callback for hisThread
void threadCallback2(){
	Serial.println("Thread2");
}

void setup(){
	Serial.begin(9600);

	// Configure myThread
	thread1.onRun(threadCallback1);
	thread1.setInterval(500);

	// Configure myThread
	thread2.onRun(threadCallback2);
	thread2.setInterval(250);

	// Adds both threads to the controller
	controll.add(&thread1); // & to pass the pointer to it
	controll.add(&thread2); 
}

void loop(){
	// run ThreadController
	// this will check every thread inside ThreadController,
	// if it should run. If yes, he will run it;
	controll.run();

	
}