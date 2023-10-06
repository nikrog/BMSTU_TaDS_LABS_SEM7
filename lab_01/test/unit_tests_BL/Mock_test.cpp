#include <gtest/gtest.h>
#include <gmock/gmock.h>


class MyClass
{
  std::string id;

public:
  MyClass(std::string _id) : id(_id) {}
  std::string GetId() { return id; }
  void AppendToId(std::string postfix) { id += postfix; }
};

struct MyClassTest : public testing::Test {
  MyClass *mc;

  void SetUp() { mc = new MyClass("root"); } // аналог конструктора
  void TearDown() { delete mc; } // аналог деструктора
};

TEST_F(MyClassTest, init_class)
{
  // Act
  std::string value = mc->GetId();

  // Assert
  EXPECT_STREQ(value.c_str(), "root");
}

TEST_F(MyClassTest, append_test)
{
  // Act
  mc->AppendToId("_good");
  std::string value = mc->GetId();

  // Assert
  EXPECT_STREQ(value.c_str(), "root_good");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}