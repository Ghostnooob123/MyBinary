#include <iostream>
#include <memory>

#include "MyBinaryEngine.h"

int main()
{
    std::unique_ptr<MyBinaryEngine> MyBinary = std::make_unique<MyBinaryEngine>();

	while (MyBinary->isAppRunning())
	{
		MyBinary->update();

		MyBinary->render();
	}
}
