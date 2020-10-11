#pragma once

#include "Order.h"

#include <map>
#include <unordered_map>

enum deliveryType {
	normal	= 0,
	fast	= 1
};

class OrderContainer : public Order {
public:
	int addOrder(const std::string& productId, const std::string& orderId, int deliveryType, double price) override;
	int removeOrder(const std::string& productId, const std::string& orderId) override;
	void print() override;

private:
	void printOrder(const std::string& prId, const std::string& orId, const std::string& delivType, double price) const;

	std::unordered_map<std::string, std::string> orderID_productID_map;
	std::multimap<double, std::string> fast_price_orderID_mmap;
	std::multimap<double, std::string> normal_price_orderID_mmap;
};