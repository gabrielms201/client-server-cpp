
#include "FirstExample.h"
#include <chrono>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

#ifdef _WIN32
#define _WIND32_WINT 0x0A00
#endif

namespace asio = boost::asio;


std::vector<char> vectorBuffer(20 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket)
{
	socket.async_read_some(asio::buffer(vectorBuffer.data(), vectorBuffer.size()),
		[&](std::error_code errorCode, std::size_t length)
		{
			if (!errorCode)
			{
				std::cout << "\n\n Read " << length << " bytes\n\n";

				for (int i = 0; i < length; i++)
				{
					std::cout << vectorBuffer[i];
				}

				GrabSomeData(socket);
			}
		}
	);
}


int main()
{
	// Error Code Instantiation
	boost::system::error_code errorCode;
	
	// Create the "context" (platform specific interface)
	asio::io_context context;
	
	// Give some fake tasks to asio to avoid finishing the context
	asio::io_context::work idleWork(context);

	// Start the context asynchronously
	std::thread threadContext = std::thread([&]() { context.run(); });
		
	// Get the address
	std::string exampleIp = "93.184.216.34";		// => Define the IP; in this case, i'm using "example.com" IP address
	size_t port = 80;								// => Define the Port
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address(exampleIp, errorCode), port);

	// Create the socket, and then, I pass the context as a parameter in order to deliver the implementation
	asio::ip::tcp::socket socket(context);

	// Now i shall tell the socket to try and connect:
	socket.connect(endpoint, errorCode);
	if (!errorCode) 
	{
		std::cout << "Connected!\nHello World"<< std::endl;
	}
	else
	{
		std::cout << "Failed to connect to the address:"<< errorCode.message() << std::endl;
	}

	if (socket.is_open())
	{
		GrabSomeData(socket);

		std::string socketRequest =
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n" 
			"Connection: close\r\n\r\n";

		// Here I'm telling the socket to write what I've sent
		socket.write_some(asio::buffer(socketRequest.data(), socketRequest.size()), errorCode);
		// Wait gotta wait a little bit
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(20000ms);
		context.stop();

		if (threadContext.joinable())
			threadContext.join();

		// Instantiating the available bytes, and showing:
		size_t bytesAvailable = socket.available();
		std::cout << "Bytes Available: " << bytesAvailable << std::endl;
		
		// If there's some bytes available, then...
		if (bytesAvailable > 0)
		{
			// Create a vector of char by the size of available bytes
			std::vector<char> vectorBuffer(bytesAvailable);

			for (auto character : vectorBuffer) 
			{
				std::cout << character;
			}
		}
	}
	return 0;
}