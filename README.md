# In-Memory Order Cache System

## Project Overview

This project implements an in-memory cache for managing financial order objects as part of a recruitment challenge. The system supports the following operations:

- **Add new orders**
- **Cancel existing orders**
- **Cancel orders for a specific user or security with minimum quantity**
- **Match buy and sell orders for the same security but different companies**
- **Retrieve all orders or match size for specific securities**

An order is a request to buy or sell a financial security (e.g., bonds, stocks, commodities), uniquely identified by an order ID, and associated with a security ID and user details.

## Key Classes and Files

- **Order Class (`Order.h`)**: This class holds information about each order, such as order ID, security ID, buy/sell flag, quantity, user, and company.
- **OrderCacheInterface (`OrderCacheInterface.h`)**: An abstract interface defining the methods that the `OrderCache` class implements.
- **OrderCache Class (`OrderCache.h`, `OrderCache.cpp`)**: Implements the `OrderCacheInterface`, handling the logic for managing orders and matching them. Includes thread safety mechanisms for concurrent order management.
- **Main File (`main.cpp`)**: This file demonstrates basic usage of the system, including adding, cancelling, and matching orders.
- **Makefile**: Provides build instructions for the project.

## Functionality

The `OrderCache` class implements the following methods as defined in the `OrderCacheInterface`:

1. **addOrder(Order order)**: Adds a new order to the cache.
2. **cancelOrder(int orderId)**: Cancels a specific order based on its unique ID.
3. **cancelOrdersForUser(int userId)**: Cancels all orders made by a specific user.
4. **cancelOrdersForSecIdWithMinimumQty(int secId, int minQty)**: Cancels all orders for a specific security ID where the quantity is greater than or equal to a given minimum quantity.
5. **getMatchingSizeForSecurity(int secId)**: Calculates the total matching quantity for a specific security by comparing buy and sell orders.
6. **getAllOrders()**: Retrieves a list of all orders currently in the cache.

### Thread Safety

The `OrderCache` class implements thread safety mechanisms, ensuring that operations on the cache are safe in a concurrent environment. This allows multiple threads to add, cancel, and match orders without risking data corruption or race conditions.

## Example Usage

```cpp
OrderCache orderCache;
orderCache.addOrder(Order("OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA"));
orderCache.addOrder(Order("OrdId2", "SecId2", "Sell", 3000, "User2", "CompanyB")); orderCache.addOrder(Order("OrdId3", "SecId1", "Sell", 500, "User3", "CompanyA"));
orderCache.addOrder(Order("OrdId4", "SecId2", "Buy", 600, "User4", "CompanyB"));

std::cout << "\nMatching size for SecId1: " << orderCache.getMatchingSizeForSecurity("SecId1") << std::endl;
std::cout << "Matching size for SecId2: " << orderCache.getMatchingSizeForSecurity("SecId2") << std::endl; printOrders(orderCache.getAllOrders());
```

## How to Build

1. Clone the repository.
2. Run the following command to build the project:

```bash
make
```

3. Execute the program:

```bash
./book
```

## Assumptions

- The project uses C++17, so a compatible compiler is required.
- Orders are uniquely identified by their order IDs.
- Matching is performed only for orders with the same security ID but opposite sides (buy/sell) and different companies.
