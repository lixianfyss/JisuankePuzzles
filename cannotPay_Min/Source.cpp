#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdint>
using namespace std;

class Wallet
{
private:
	uint16_t cash_count; size_t min_uvalue, v_size;
	vector<uint16_t> cash_values; vector<uint16_t> num_cash; vector<uint8_t> num_cash_s;
public:
	Wallet();
	size_t verify_size();
	size_t unaffordable();
	size_t unaffordable_lite();
	size_t unaffordable_math();
};
Wallet::Wallet()
{
	uint16_t type_count;
	cin >> cash_count; cin >> type_count; cash_values.resize(type_count, 0);
	for (size_t i = 0; i < type_count; i++) cin >> cash_values[i];
	sort(cash_values.begin(), cash_values.end()); v_size = cash_count * *cash_values.crbegin();
}
size_t Wallet::verify_size()
{
	size_t gcm_value = 1, lcm_value = 1;
	for_each(cash_values.cbegin(), cash_values.cend(), [&lcm_value, &gcm_value](const int& val){
		size_t rem = 1, a, b;
		if (val > lcm_value) { a = val; b = lcm_value; }
		else { a = lcm_value; b = val; }
		while (rem != 0)
		{
			rem = a%b; a = b; b = rem;
		}	gcm_value = a;
		lcm_value *= val / gcm_value;
	});
	if (lcm_value < v_size) {
		v_size = lcm_value; return true;
	}
	return false;
}
size_t Wallet::unaffordable()
{
	size_t num_pay = 2, temp_count, local_count; num_cash.resize(4098, 0);
	if (cash_values[0] > 1)
	{
		min_uvalue = 1; return 1;
	}
	else num_cash[1] = 1;
	while (1)
	{
		local_count = cash_count + 1;
		for (auto i = cash_values.begin(); i < cash_values.end(); i++)
		{
			if (*i > num_pay) break; temp_count = num_cash[num_pay - (*i)];
			local_count = (temp_count < local_count) ? temp_count : local_count;
		}
		if (local_count == cash_count) break;
		else num_cash[num_pay] = local_count + 1;
		if (num_pay % 4096 == 1) num_cash.resize(num_pay + 4095, 0);
		num_pay++;
	}
	min_uvalue = num_pay; return num_pay;
}
size_t Wallet::unaffordable_lite()
{
	size_t num_pay = 2; uint8_t temp_count, local_count; 
	const uint16_t v_size = *(cash_values.rbegin()) * 2;	num_cash_s.resize(v_size, 0);
	if (cash_values[0] > 1)
	{
		min_uvalue = 1; return 1;
	}
	else num_cash_s[1] = 1;
	while (1)
	{
		local_count = cash_count + 1;
		for (auto i = cash_values.begin(); i < cash_values.end(); i++)
		{
			if (*i > num_pay) break; temp_count = num_cash_s[(num_pay - (*i)) % v_size];
			local_count = (temp_count < local_count) ? temp_count : local_count;
		}
		if (local_count == cash_count) break;
		else num_cash_s[num_pay%v_size] = local_count + 1;
		num_pay++;
	}
	min_uvalue = num_pay; return num_pay;
}
size_t Wallet::unaffordable_math()
{
	size_t num_pay = 1, num_period = 1; uint8_t temp_count, local_count;
	if (cash_values[0] > 1)
	{
		min_uvalue = 1; return 1;
	}
	if (verify_size()) num_period = v_size / *cash_values.crbegin();
	num_cash_s.resize(v_size, 0);
	for (auto base_pos = num_cash_s.begin() + 1; base_pos < num_cash_s.end(); base_pos++)
	{
		local_count = cash_count + 1;
		for (auto i = cash_values.begin(); i < cash_values.end(); i++)
		{
			if (*i > num_pay) break; temp_count = num_cash_s[(num_pay - (*i))];
			local_count = (temp_count < local_count) ? temp_count : local_count;
		}
		if (local_count == cash_count) {
			min_uvalue = num_pay;  return min_uvalue;
		}
		else *base_pos = local_count + 1; num_pay++;
	}
	auto base_max_count = max_element(num_cash_s.cbegin(), num_cash_s.cend());
	while ((cash_count + 1 - *base_max_count)%num_period) 
		base_max_count = find(num_cash_s.cbegin(), num_cash_s.cend(), *base_max_count - 1);
	auto base_max_position = distance(num_cash_s.cbegin(), base_max_count);
	min_uvalue = (cash_count - *base_max_count + 1) / num_period * v_size + base_max_position;
	return min_uvalue;
}

int main()
{
	Wallet G; cout << G.unaffordable_math()<<endl;
	cout << G.unaffordable_lite() << endl;
	cout << G.unaffordable() << endl;
	return 0;
}