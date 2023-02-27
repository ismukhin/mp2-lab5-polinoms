#include "database.h" 
#include <gtest.h>

TEST(database, can_create_SortVectorTable) {
	ASSERT_NO_THROW(SortVectorTable<int> svt);
}
TEST(database, can_push) {
	SortVectorTable<int> svt;

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	ASSERT_NO_THROW(svt.insert(1, a));
}
TEST(database, get_size_work_correctly) {
	SortVectorTable<int> svt;

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);
	svt.insert(1, a);

	EXPECT_EQ(1, svt.Vsize());
}
TEST(database, can_pop_no_empty_Stack) {
	SortVectorTable<int> svt;
	
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);
	svt.insert(1, a);

	ASSERT_NO_THROW(svt.remove(1));
}
TEST(database, cant_pop_empty_Stack) {
	SortVectorTable<int> svt;
	ASSERT_ANY_THROW(svt.remove(1));
}