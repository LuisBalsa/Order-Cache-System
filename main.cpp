#include "OrderCache.h"
#include <iostream>
#include <thread>

void printOrders(const std::vector<Order>& orders)
{
	for (const auto& order : orders) {
		std::cout << "Order ID: " << order.orderId()
				  << ", Security ID: " << order.securityId()
				  << ", Side: " << order.side()
				  << ", Quantity: " << order.qty()
				  << ", User: " << order.user()
				  << ", Company: " << order.company() << std::endl;
	}
}

void	simpleTest(void)
{
	OrderCache orderCache;

	orderCache.addOrder(Order("OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA"));
	orderCache.addOrder(Order("OrdId2", "SecId1", "Sell", 500, "User2", "CompanyB"));
	orderCache.addOrder(Order("OrdId3", "SecId1", "Sell", 2000, "User3", "CompanyA"));
	orderCache.addOrder(Order("OrdId4", "SecId2", "Buy", 1500, "User4", "CompanyB"));
	orderCache.addOrder(Order("OrdId5", "SecId2", "Sell", 1000, "User5", "CompanyC"));

	std::cout << "All orders:" << std::endl;
	printOrders(orderCache.getAllOrders());
	std::cout << std::endl;

	orderCache.cancelOrder("OrdId3");
	std::cout << "After cancelling OrdId3:" << std::endl;
	printOrders(orderCache.getAllOrders());
	std::cout << std::endl;

	orderCache.cancelOrdersForUser("User1");
	std::cout << "After cancelling orders for User1:" << std::endl;
	printOrders(orderCache.getAllOrders());
	std::cout << std::endl;

	orderCache.cancelOrdersForSecIdWithMinimumQty("SecId2", 1200);
	std::cout << "After cancelling orders for SecId2 with minimum quantity 1200:" << std::endl;
	printOrders(orderCache.getAllOrders());
	std::cout << std::endl;
}

void	testSizeExampleExplanation(void)
{
	OrderCache orderCache;

	orderCache.addOrder(Order("OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA"));
	orderCache.addOrder(Order("OrdId2", "SecId2", "Sell", 3000, "User2", "CompanyB"));
	orderCache.addOrder(Order("OrdId3", "SecId1", "Sell", 500, "User3", "CompanyA"));
	orderCache.addOrder(Order("OrdId4", "SecId2", "Buy", 600, "User4", "CompanyC"));
	orderCache.addOrder(Order("OrdId5", "SecId2", "Buy", 100, "User5", "CompanyB"));
	orderCache.addOrder(Order("OrdId6", "SecId3", "Buy", 1000, "User6", "CompanyD"));
	orderCache.addOrder(Order("OrdId7", "SecId2", "Buy", 2000, "User7", "CompanyE"));
	orderCache.addOrder(Order("OrdId8", "SecId2", "Sell", 5000, "User8", "CompanyE"));

	std::cout << "\n\nMatching size for SecId1: " << orderCache.getMatchingSizeForSecurity("SecId1") << std::endl;
	std::cout << "Matching size for SecId2: " << orderCache.getMatchingSizeForSecurity("SecId2") << std::endl;
	std::cout << "Matching size for SecId3: " << orderCache.getMatchingSizeForSecurity("SecId3") << std::endl;
}

void	testSizeExampleOne(void)
{
	OrderCache orderCache;

	orderCache.addOrder(Order("OrdId1", "SecId1", "Sell", 100, "User10", "Company2"));
	orderCache.addOrder(Order("OrdId2", "SecId3", "Sell", 200, "User8", "Company2"));
	orderCache.addOrder(Order("OrdId3", "SecId1", "Buy", 300, "User13", "Company2"));
	orderCache.addOrder(Order("OrdId4", "SecId2", "Sell", 400, "User12", "Company2"));
	orderCache.addOrder(Order("OrdId5", "SecId3", "Sell", 500, "User7", "Company2"));
	orderCache.addOrder(Order("OrdId6", "SecId3", "Buy", 600, "User3", "Company1"));
	orderCache.addOrder(Order("OrdId7", "SecId1", "Sell", 700, "User10", "Company2"));
	orderCache.addOrder(Order("OrdId8", "SecId1", "Sell", 800, "User2", "Company1"));
	orderCache.addOrder(Order("OrdId9", "SecId2", "Buy", 900, "User6", "Company2"));
	orderCache.addOrder(Order("OrdId10", "SecId2", "Sell", 1000, "User5", "Company1"));
	orderCache.addOrder(Order("OrdId11", "SecId1", "Sell", 1100, "User13", "Company2"));
	orderCache.addOrder(Order("OrdId12", "SecId2", "Buy", 1200, "User9", "Company2"));
	orderCache.addOrder(Order("OrdId13", "SecId1", "Sell", 1300, "User1", "Company2"));

	std::cout << "\n\nMatching size for SecId1: " << orderCache.getMatchingSizeForSecurity("SecId1") << std::endl;
	std::cout << "Matching size for SecId2: " << orderCache.getMatchingSizeForSecurity("SecId2") << std::endl;
	std::cout << "Matching size for SecId3: " << orderCache.getMatchingSizeForSecurity("SecId3") << std::endl;
}

void testSizeExampleTwo()
{
	OrderCache orderCache;

	orderCache.addOrder(Order("OrdId1", "SecId3", "Sell", 100, "User1", "Company1"));
	orderCache.addOrder(Order("OrdId2", "SecId3", "Sell", 200, "User3", "Company2"));
	orderCache.addOrder(Order("OrdId3", "SecId1", "Buy", 300, "User2", "Company1"));
	orderCache.addOrder(Order("OrdId4", "SecId3", "Sell", 400, "User5", "Company2"));
	orderCache.addOrder(Order("OrdId5", "SecId2", "Sell", 500, "User2", "Company1"));
	orderCache.addOrder(Order("OrdId6", "SecId2", "Buy", 600, "User3", "Company2"));
	orderCache.addOrder(Order("OrdId7", "SecId2", "Sell", 700, "User1", "Company1"));
	orderCache.addOrder(Order("OrdId8", "SecId1", "Sell", 800, "User2", "Company1"));
	orderCache.addOrder(Order("OrdId9", "SecId1", "Buy", 900, "User5", "Company2"));
	orderCache.addOrder(Order("OrdId10", "SecId1", "Sell", 1000, "User1", "Company1"));
	orderCache.addOrder(Order("OrdId11", "SecId2", "Sell", 1100, "User6", "Company2"));

	std::cout << "\n\nMatching size for SecId1: " << orderCache.getMatchingSizeForSecurity("SecId1") << std::endl;
	std::cout << "Matching size for SecId2: " << orderCache.getMatchingSizeForSecurity("SecId2") << std::endl;
	std::cout << "Matching size for SecId3: " << orderCache.getMatchingSizeForSecurity("SecId3") << std::endl;
	printOrders(orderCache.getAllOrders());
}

void addOrders(OrderCache& cache)
{
	for (int i = 0; i < 100; ++i)
	{
		cache.addOrder(Order("OrdId" + std::to_string(i), "SecId" + std::to_string(i % 10), i % 2 == 0 ? "Buy" : "Sell", i * 10, "User" + std::to_string(i % 5), "Company" + std::to_string(i % 3)));
	}
}

void cancelOrders(OrderCache& cache)
{
	for (int i = 0; i < 50; ++i)
	{
		cache.cancelOrder("OrdId" + std::to_string(i));
	}
}

void getMatchingSizes(OrderCache& cache)
{
	for (int i = 0; i < 10; ++i)
	{
		cache.getMatchingSizeForSecurity("SecId" + std::to_string(i));
	}
}

void getAllOrders(OrderCache& cache)
{
	cache.getAllOrders();
}

void testMutex()
{
	OrderCache orderCache;

	std::thread t1(addOrders, std::ref(orderCache));
	std::thread t2(getMatchingSizes, std::ref(orderCache));
	std::thread t3(getAllOrders, std::ref(orderCache));
	std::thread t4(cancelOrders, std::ref(orderCache));
	std::thread t5(getMatchingSizes, std::ref(orderCache));
	std::thread t6(cancelOrders, std::ref(orderCache));

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
}

int main()
{
	simpleTest();
	testSizeExampleExplanation();
	testSizeExampleOne();
	testSizeExampleTwo();
	testMutex();
	return 0;
}
