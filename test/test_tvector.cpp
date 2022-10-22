#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length) //+
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector) //+
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length) //+ но ведь size_t это беззнаковый тип?
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector) //+
{
  TDynamicVector<int> v(10);
  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one) //+
{
  TDynamicVector<int> v(10);
  for (int i = 0; i < 10; i++)
	  v[i] = i;
  TDynamicVector<int> v1(v);
  for (int i = 0; i < 10; i++)
	  EXPECT_EQ(v[i], v1[i]);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory) //+
{
	TDynamicVector<int> v(10);
	for (int i = 0; i < 10; i++)
		v[i] = i;
	TDynamicVector<int> v1(v);
	v1[2] = 2022;
	EXPECT_NE(v[2], v1[2]);
}

TEST(TDynamicVector, can_get_size) //+
{
  TDynamicVector<int> v(4);
  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element) //+
{
  TDynamicVector<int> v(4);
  v[0] = 4;
  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index) //+
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-4) = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index) //+
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(4) = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself) //+
{
	TDynamicVector<int> v(10);
	for (int i = 0; i < 10; i++)
		v[i] = i;
	ASSERT_NO_THROW(v = v);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(v[i], i);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;
	TDynamicVector<int> v2(10);
	ASSERT_NO_THROW(v1 = v2);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(v1[i], v2[i]);
}

TEST(TDynamicVector, assign_operator_change_vector_size) //+
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(15);
	v2 = v1;
	EXPECT_NE(v2.size(), 15);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size) //+
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(15);
	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;
	TDynamicVector<int> v2(10);
	for (int i = 0; i < 10; i++)
		v2[i] = i;
	EXPECT_EQ(v1 == v2, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;
	EXPECT_EQ(v1 == v1, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;
	TDynamicVector<int> v2(15);
	for (int i = 0; i < 15; i++)
		v2[i] = i;
	EXPECT_NE(v1 == v2, true);
}

TEST(TDynamicVector, can_add_scalar_to_vector) //+
{
	TDynamicVector<int> v(10);
	for (int i = 0; i < 10; i++)
		v[i] = i;
	ASSERT_NO_THROW(v = v + 4);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(v[i], i + 4);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector) //+
{
	TDynamicVector<int> v(10);
	for (int i = 0; i < 10; i++)
		v[i] = i;
	ASSERT_NO_THROW(v = v - 4);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(v[i], i - 4);
}

TEST(TDynamicVector, can_multiply_vector_by_scalar) //+
{
	TDynamicVector<int> v(10);
	for (int i = 0; i < 10; i++)
		v[i] = i;
	ASSERT_NO_THROW(v = v * 4);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(v[i], i * 4);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;
	TDynamicVector<int> v2(10);
	for (int i = 0; i < 10; i++)
		v2[i] = 10 - i;
	TDynamicVector<int> v3;
	ASSERT_NO_THROW(v3 = v1 + v2);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(v3[i], 10);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;
	TDynamicVector<int> v2(15);
	for (int i = 0; i < 15; i++)
		v2[i] = 10 - i;
	TDynamicVector<int> v3;
	ASSERT_ANY_THROW(v3 = v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i + 3;
	TDynamicVector<int> v2(10);
	for (int i = 0; i < 10; i++)
		v2[i] = i + 2;
	TDynamicVector<int> v3;
	ASSERT_NO_THROW(v3 = v1 - v2);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(v3[i], 1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;
	TDynamicVector<int> v2(15);
	for (int i = 0; i < 15; i++)
		v2[i] = 10 - i;
	TDynamicVector<int> v3;
	ASSERT_ANY_THROW(v3 = v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;
	TDynamicVector<int> v2(10);
	for (int i = 0; i < 10; i++)
		v2[i] = 2 * i;
	int v = 0;
	ASSERT_NO_THROW(v = v1 * v2);
	int t = 0;
	for (int i = 0; i < 10; i++)
		t += 2 * i * i;
	EXPECT_EQ(v, t);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) //+
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;
	TDynamicVector<int> v2(15);
	for (int i = 0; i < 15; i++)
		v2[i] = 2 * i;
	int v = 0;
	ASSERT_ANY_THROW(v = v1 * v2);
}
