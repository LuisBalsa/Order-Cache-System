#include "OrderCache.h"
#include <iostream>

void OrderCache::addOrder(Order order)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto pair = m_orders.emplace(order.orderId(), order);
    if (!pair.second)
    {
        throw std::runtime_error("Order already exists");
    }
}

void OrderCache::cancelOrder(const std::string& orderId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_orders.erase(orderId);
}

void OrderCache::cancelOrdersForUser(const std::string& user)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto it = m_orders.begin(); it != m_orders.end();)
    {
        if (it->second.user() == user)
        {
            it = m_orders.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void OrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto it = m_orders.begin(); it != m_orders.end();)
    {
        if (it->second.securityId() == securityId && it->second.qty() >= minQty)
        {
            it = m_orders.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

unsigned int OrderCache::getMatchingSizeForSecurity(const std::string& securityId)
{
    unsigned int totalQty = 0;
    unsigned int diffQty = 0;
    std::map<std::string, unsigned int> qtyBuyByCompany;
    std::map<std::string, unsigned int> qtySellByCompany;
    std::unique_lock<std::mutex> lock(m_mutex);

    for (auto it = m_orders.begin(); it != m_orders.end(); ++it)
    {
        if (it->second.securityId() == securityId)
        {
            if (it->second.side() == "Buy")
            {
                qtyBuyByCompany[it->second.company()] += it->second.qty();
            }
            else
            {
                qtySellByCompany[it->second.company()] += it->second.qty();
            }
        }
    }
    lock.unlock();

    for (auto it = qtyBuyByCompany.begin(); it != qtyBuyByCompany.end(); ++it)
    {
        for (auto it2 = qtySellByCompany.begin(); it2 != qtySellByCompany.end(); ++it2)
        {
            if (it->first != it2->first)
            {
                diffQty = std::min(it->second, it2->second);
                totalQty += diffQty;
                it->second -= diffQty;
                it2->second -= diffQty;
            }
        }
    }

    return totalQty;
}

std::vector<Order> OrderCache::getAllOrders() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<Order> orders;
    for (const auto& order : m_orders)
    {
        orders.push_back(order.second);
    }
    return orders;
}
