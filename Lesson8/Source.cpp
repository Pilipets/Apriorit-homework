/*A lot of people woul chose vector thread-safe implementation, so I have decided to pick up
another commonly used data structure - queue.

I have demonstrated the work of the ConcurrentQueue on the producer/consumer task example*/

#include<iostream>
#include<thread>
#include<atomic>
#include "ConcurrentQueue.h"
using namespace std;

void ProducerConsumerTest();
int main()
{
	ProducerConsumerTest();
	system("pause");
	return 0;
}

void ProducerConsumerTest()
{
	size_t const ThreadsNumber = 10;
	size_t const InsertCount = 20;
	std::mutex cerrMutex;

	//vectors for producers,consumer threads
	std::vector<std::thread> producers, consumers;
	//each producer will try to push InsertCount values to the queue
	//but _max_size for queue is 8 element, so threads will be waiting..

	ConcurrentQueue<int> queue(8);
	int balanceFactor(0);

	// Generating working threads for producers
	for (size_t threadID = 0; threadID < ThreadsNumber; ++threadID)
		producers.push_back(std::thread([&, threadID]() {
		for (size_t i = 0; i < InsertCount; ++i)
		{
			// Lock output stream for accurate output
			cerrMutex.lock();
			std::cout << "THREAD #" << threadID << " pushing " << threadID * ThreadsNumber + i << " to queue\n";
			balanceFactor += 1;
			cerrMutex.unlock();
			queue.push(threadID * ThreadsNumber + i);
		}
	}));

	//  Generating working threads for consumers
	for (size_t threadID = ThreadsNumber; threadID < 2 * ThreadsNumber; ++threadID)
		consumers.push_back(std::thread([&, threadID]() {
			int i = -1;
			while (queue.try_pop(i) != false)
			{
				std::lock_guard<std::mutex> lock(cerrMutex);
				std::cerr << "THREAD #" << threadID << " got: " << i << "\n";
				balanceFactor -= 1;
			}

			// Lock output stream for accurate output             
			cerrMutex.lock();
			std::cerr << "THREAD #" << threadID << " is done.\n";
			cerrMutex.unlock();
		}));

	// Wait for producers finished element inserting
	for (auto & t : producers)
		t.join();

	// Closing queue - making it valid only for poping
	{
		std::lock_guard<std::mutex> lock(cerrMutex);
		std::cerr << "Closing Queue.\n";
	}
	queue.close();

	// Wait for consumers to consume all items.
	{
		std::lock_guard<std::mutex> lock(cerrMutex);
		std::cerr << "Waiting for consumers...\n";
	}
	for (auto & t : consumers)
		t.join();

	std::cerr << (balanceFactor == 0 ? "Test finished succesfully" : "Test not passed") << endl;
}
