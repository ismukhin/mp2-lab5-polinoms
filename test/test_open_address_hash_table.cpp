#include "open_address_hash_table.h"
#include "polinoms.h"
#include "gtest/gtest.h"

template <class T>
class HashTable_with_same_types : public ::testing::Test {
	static T _shared;
	T value_;
};

using MyTypes = ::testing::Types<unsigned int, int, char, Polinom<double>, long>;

TYPED_TEST_SUITE(HashTable_with_same_types, MyTypes);

TYPED_TEST(HashTable_with_same_types, can_create_table_with_some_parametrs) {
	ASSERT_NO_THROW(HashTable_OpAdd<MyTypes> a);
}

TEST(HashTable_OpAdd, can_insert_key_and_value) {
	HashTable_OpAdd<int> tbl;
	ASSERT_NO_THROW(tbl.insert("Hello, world!", 2));
}

TEST(HashTable_OpAdd, can_find_key_and_get_value) {
	HashTable_OpAdd<int> tbl;
	tbl.insert("Hello, world!", 2);
	EXPECT_EQ(tbl["Hello, world!"], 2);
}

TEST(HashTable_OpAdd, can_erase_key) {
	HashTable_OpAdd<int> tbl;
	tbl.insert("Hello, world!", 2);
	ASSERT_NO_THROW(tbl.erase("Hello, world!"));
}

TEST(HashTable_OpAdd, cant_erase_if_table_is_empty) {
	HashTable_OpAdd<int> tbl;
	ASSERT_ANY_THROW(tbl.erase("1"));
}

TEST(HashTable_OpAdd, cant_find_empty_string) {
	HashTable_OpAdd<int> tbl;
	ASSERT_ANY_THROW(tbl[""]);
}

TEST(HashTable_OpAdd, cant_insert_empty_string) {
	HashTable_OpAdd<int> tbl;
	ASSERT_ANY_THROW(tbl.insert("", 2));
}

TEST(HashTable_OpAdd, erase_really_erase) {
	HashTable_OpAdd<int> tbl;
	tbl.insert("Hello, world!", 2);
	tbl.erase("Hello, world!");
	ASSERT_ANY_THROW(tbl["Hello, world!"]);
}

TEST(HashTable_OpAdd, can_resize_if_table_is_full) {
	HashTable_OpAdd<int> tbl;

	tbl.insert("a", 1);
	tbl.insert("b", 2);
	tbl.insert("c", 3);
	tbl.insert("d", 4);
	EXPECT_EQ(tbl.size(), 4);

	tbl.insert("e", 5);
	EXPECT_EQ(tbl.size(), 8);
}

TEST(HashTable_OpAdd, many_pushes_and_erases_into_table) {
	std::vector<std::string> exmpls({"A", "B", "C", "D", "E", "F", "G", "H", "K", "L", "J", "M", "N", "O", "P", "S", "I"});
	HashTable_OpAdd<int> tbl;

	for (int i = 0; i < exmpls.size(); i++) {
		tbl.insert(exmpls[i], i);
		if (i == 4) {
			EXPECT_EQ(tbl.size(), 8);
		}
		if (i == 8) {
			EXPECT_EQ(tbl.size(), 16);
		}
		if (i == 16) {
			EXPECT_EQ(tbl.size(), 32);
		}
	}

	for (int i = 0; i < exmpls.size(); i++) {
		tbl.erase(exmpls[i]);
	}
	EXPECT_EQ(0, tbl.get_count_of_busy_cells());
}

TEST(HashTable_OpAdd, a_lot_of_collusion) {
	std::vector<std::string> exmpls1({ "A", "B", "C", "D" });
	std::vector<std::string> exmpls2({ "I", "J", "K", "L" });
	HashTable_OpAdd<int> tbl;

	for (int i = 0; i < exmpls1.size(); i++) {
		tbl.insert(exmpls1[i], i);
	}
	for (int i = 0; i < exmpls2.size(); i++) {
		tbl.insert(exmpls2[i], i);
	}
	
}

TEST(HashTable_OpAdd, can_find_value_by_key) {
	std::vector<std::string> exmpls({ "A", "B", "C", "D", "E", "F", "G", "H", "K", "L", "J", "M", "N", "O", "P", "S", "I" });
	HashTable_OpAdd<int> tbl;

	for (int i = 0; i < exmpls.size(); i++) {
		tbl.insert(exmpls[i], i);
	}
	for (int i = 0; i < exmpls.size(); i++) {
		EXPECT_EQ(tbl[exmpls[i]], i);
	}
}