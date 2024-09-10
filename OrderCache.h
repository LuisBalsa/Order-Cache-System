#pragma once

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <cmath>
#include "OrderCacheInterface.h"

class OrderCache : public OrderCacheInterface
{
public:
  OrderCache() = default;
  ~OrderCache() = default;

  void addOrder(Order order);
  void cancelOrder(const std::string& orderId);
  void cancelOrdersForUser(const std::string& user);
  void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty);
  unsigned int getMatchingSizeForSecurity(const std::string& securityId);
  std::vector<Order> getAllOrders() const;

private:
  std::map<std::string, Order> m_orders;
  mutable std::mutex m_mutex;
};
