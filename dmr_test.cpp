#include "dmr.h"

#include "gtest/gtest.h"

TEST(DMRTest, IsPrime) {
  EXPECT_TRUE(isPrime(2));
  EXPECT_TRUE(isPrime(3));
  EXPECT_TRUE(isPrime(5));
  EXPECT_TRUE(isPrime(7));
  EXPECT_TRUE(isPrime(11));
  EXPECT_TRUE(isPrime(13));
  EXPECT_TRUE(isPrime(17));
  EXPECT_TRUE(isPrime(19));
  EXPECT_TRUE(isPrime(23));

  EXPECT_FALSE(isPrime(1));
  EXPECT_FALSE(isPrime(4));
  EXPECT_FALSE(isPrime(6));
  EXPECT_FALSE(isPrime(8));
  EXPECT_FALSE(isPrime(9));
  EXPECT_FALSE(isPrime(15));
  EXPECT_FALSE(isPrime(21));
  EXPECT_FALSE(isPrime(25));

  EXPECT_TRUE(isPrime(65537));
  EXPECT_TRUE(isPrime(65539));
  EXPECT_TRUE(isPrime(114689));

  EXPECT_FALSE(isPrime(65541));
  EXPECT_FALSE(isPrime(114693));
}
