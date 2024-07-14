#include "cmd_tools.h"
#include "net/netinfo.h"
#include "upgrade/upgrade.h"
#include "argparse.h"

#include <gtest/gtest.h>

using namespace std;


TEST(NetworkInfoTest, Zero)
{
	EXPECT_STRNE("hello", "world");
	EXPECT_EQ(7 * 6, 42);
	EXPECT_EQ(0, printAllAdapterNames());
}

TEST(UpgradeInfoTest, Trivial) {
	EXPECT_FALSE(info_check(0));
	EXPECT_FALSE(info_check(1));
	EXPECT_TRUE(info_check(2));
	EXPECT_TRUE(info_check(3));
}