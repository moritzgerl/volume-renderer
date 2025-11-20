#include <gtest/gtest.h>

#include <persistence/KeyValuePair.h>

class KeyValuePairTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        pair = Persistence::KeyValuePair{};
    }

    Persistence::KeyValuePair pair;
};

TEST_F(KeyValuePairTest, CanCreateDefaultKeyValuePair)
{
    EXPECT_NO_THROW(Persistence::KeyValuePair defaultPair{});
}

TEST_F(KeyValuePairTest, CanSetKeyAndValue)
{
    pair.key = "testKey";
    pair.value = "testValue";
    EXPECT_EQ(pair.key, "testKey");
    EXPECT_EQ(pair.value, "testValue");
}

TEST_F(KeyValuePairTest, CanCreateWithInitializer)
{
    const Persistence::KeyValuePair kvp{"myKey", "myValue"};
    EXPECT_EQ(kvp.key, "myKey");
    EXPECT_EQ(kvp.value, "myValue");
}
