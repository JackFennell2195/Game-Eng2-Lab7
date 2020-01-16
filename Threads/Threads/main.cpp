#include <iostream>
#include <thread>
#include <chrono>


int buf, p = 0, c = 0;
const int n = 5;

void producer()
{
	int a[n] = { 10,20,30,40,50 };
	bool run = true;
	while (run)
	{
		while (p < n)
		{
			std::cout << "ID:" << std::this_thread::get_id() << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			while (!(p == c))
			{
				std::cout << "spinning:" << std::endl;
			}
			buf = a[p];
			std::cout << a[p] << " deposited in buffer" << std::endl;
			p = p + 1;
		}
		std::cout << "Production Finished" << std::endl;
		run = false;
	}
}

void consumer()
{
	int b[n];
	bool run = true;
	while (run)
	{
		while (c < n)
		{
			std::cout << "ID:" << std::this_thread::get_id() << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			while ((p <= c))
			{
				std::cout << "spinning:" << std::endl;
			}
			b[c] = buf;
			std::cout << buf << " deposited in b[]" << std::endl;
			c = c + 1;
		}
		std::cout << "Consumption Finished" << std::endl;
		run = false;
	}
}
int main(void)
{
	std::thread producer(producer);
	std::thread consumer(consumer);
	producer.join();
	consumer.join();
	std::cin.get();
	
}