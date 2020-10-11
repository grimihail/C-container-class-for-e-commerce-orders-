#include "OrderContainer.h"

#include <iostream>

/*
The function finds the first match by value in the map.
If there is no such value in the map, the function returns map::end.
*/
template<typename MapIter, typename Value>
MapIter find_value(MapIter begin, MapIter end, Value v)
{
	while (begin != end && begin->second != v) {
		++begin;
	}

	return begin;
}

int OrderContainer::addOrder(const std::string& productId, const std::string& orderId, int deliveryType, double price)
{
	if (deliveryType != deliveryType::normal && deliveryType != deliveryType::fast) {
		return -1;
	}

	if (price <= 0) {
		return -1;
	}

	std::pair<std::unordered_map<std::string, std::string>::iterator, bool> ret;
	ret = orderID_productID_map.emplace(orderId, productId);
	if (!ret.second) {
		return -1;
	}

	if (deliveryType == deliveryType::normal) {
		normal_price_orderID_mmap.insert(std::pair<double, std::string>(price, orderId));
	}
	else {
		fast_price_orderID_mmap.insert(std::pair<double, std::string>(price, orderId));
	}

	return 0;
}

int OrderContainer::removeOrder(const std::string& productId, const std::string& orderId)
{
	auto it = orderID_productID_map.find(orderId);

	if (it == orderID_productID_map.end() || it->second != productId) {
		return -1;
	}

	auto itPrice = find_value(normal_price_orderID_mmap.begin(), normal_price_orderID_mmap.end(), orderId);
	if (itPrice == normal_price_orderID_mmap.end()) {
		itPrice = find_value(fast_price_orderID_mmap.begin(), fast_price_orderID_mmap.end(), orderId);

		if (itPrice == fast_price_orderID_mmap.end()) {
			return -1;
		}

		fast_price_orderID_mmap.erase(itPrice);
	}
	else {
		normal_price_orderID_mmap.erase(itPrice);
	}

	orderID_productID_map.erase(it);

	return 0;
}

void OrderContainer::print()
{
	/*Fast delivery orders have to be printed in descending order of price*/
	for (auto ritPrice = fast_price_orderID_mmap.rbegin(); ritPrice != fast_price_orderID_mmap.rend(); ++ritPrice) {
		const auto itOrder = orderID_productID_map.find(ritPrice->second);
		printOrder(itOrder->second, itOrder->first, "Fast", ritPrice->first);
	}

	/*Normal delivery orders have to be printed in ascending order of price*/
	for (auto itPrice = normal_price_orderID_mmap.begin(); itPrice != normal_price_orderID_mmap.end(); ++itPrice) {
		const auto itOrder = orderID_productID_map.find(itPrice->second);
		printOrder(itOrder->second, itOrder->first, "Normal", itPrice->first);
	}
}

void OrderContainer::printOrder(const std::string& prId, const std::string& orId, const std::string& delivType, double price) const
{
	std::cout << prId << " " << orId << " " << delivType << " " << price << std::endl;
}
