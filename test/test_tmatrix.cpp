#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length) //+
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix) //+
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) //+
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix) //+
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) //+
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m[i][j] = i * 5 + j;
	TDynamicMatrix<int> m1(m);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			EXPECT_EQ(m[i][j], m1[i][j]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) //+
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m[i][j] = i * 5 + j;
	TDynamicMatrix<int> m1(m);
	m1[2][2] = 1000;
	EXPECT_NE(m[2][2], m1[2][2]);
}

TEST(TDynamicMatrix, can_get_size) //+
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(int a = m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element) //+
{
	TDynamicMatrix<int> m(5);
	m[2][2] = 1000;
	EXPECT_EQ(m[2][2], 1000);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) //+
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(-2).at(2) = 1000);
	ASSERT_ANY_THROW(m.at(2).at(-2) = 1000);
	ASSERT_ANY_THROW(m.at(-2).at(-2) = 1000);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) //+
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(10).at(2) = 1000);
	ASSERT_ANY_THROW(m.at(2).at(10) = 1000);
	ASSERT_ANY_THROW(m.at(10).at(10) = 1000);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself) //+
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m[i][j] = i * 5 + j;
	ASSERT_NO_THROW(m = m);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			EXPECT_EQ(m[i][j], i * 5 + j);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) //+
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m[i][j] = i * 5 + j;
	TDynamicMatrix<int> m2(5);
	ASSERT_NO_THROW(m2 = m);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			EXPECT_EQ(m[i][j], m2[i][j]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size) //+
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m[i][j] = i * 5 + j;
	TDynamicMatrix<int> m2(10);
	ASSERT_NO_THROW(m2 = m);
	EXPECT_NE(m2.size(), 10);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size) //+
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m[i][j] = i * 5 + j;
	TDynamicMatrix<int> m2(10);
	ASSERT_NO_THROW(m2 = m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true) //+
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m1[i][j] = m2[i][j] = i * 5 + j;
	EXPECT_EQ(m1 == m2, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true) //+
{
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m1[i][j] = i * 5 + j;
	EXPECT_EQ(m1 == m1, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal) //+
{
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m1[i][j] = i * 5 + j;
	TDynamicMatrix<int> m2(6);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			m2[i][j] = i * 5 + j;
	EXPECT_NE(m1 == m2, true);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size) //+
{
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m1[i][j] = i * 5 + j;
	TDynamicMatrix<int> m2(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m2[i][j] = (i * 5 + j) * 2;
	TDynamicMatrix<int> m3;
	ASSERT_NO_THROW(m3 = m1 + m2);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			EXPECT_EQ(m3[i][j], (i * 5 + j) * 3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) //+
{
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m1[i][j] = i * 5 + j;
	TDynamicMatrix<int> m2(6);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			m2[i][j] = i * 5 + j;
	TDynamicMatrix<int> m3;
	ASSERT_ANY_THROW(m3 = m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) //+
{
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m1[i][j] = i * 5 + j;
	TDynamicMatrix<int> m2(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m2[i][j] = (i * 5 + j) * 2;
	TDynamicMatrix<int> m3;
	ASSERT_NO_THROW(m3 = m2 - m1);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			EXPECT_EQ(m3[i][j], i * 5 + j);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			m1[i][j] = i * 5 + j;
	TDynamicMatrix<int> m2(6);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			m2[i][j] = (i * 5 + j) * 2;
	TDynamicMatrix<int> m3;
	ASSERT_ANY_THROW(m3 = m2 - m1);
}
