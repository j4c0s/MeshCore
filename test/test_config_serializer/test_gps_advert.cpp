#include <gtest/gtest.h>
#include <cstring>
#include "helpers/ConfigSerializer.h"

#define ADVERT_LOC_NONE  0
#define ADVERT_LOC_SHARE 1
#define ADVERT_LOC_PREFS 2

// Test parsing of "gps advert" arguments as implemented in CommonCLI
static bool parseGpsAdvertCommand(const char* command, uint8_t& policy, char* reply) {
  if (memcmp(command, "gps advert", 10) == 0) {
    if (strlen(command) == 10) {
      switch (policy) {
        case ADVERT_LOC_NONE:
          strcpy(reply, "> none");
          break;
        case ADVERT_LOC_PREFS:
          strcpy(reply, "> prefs");
          break;
        case ADVERT_LOC_SHARE:
          strcpy(reply, "> share");
          break;
        default:
          strcpy(reply, "error");
      }
      return true;
    } else if (memcmp(command+11, "none", 4) == 0) {
      policy = ADVERT_LOC_NONE;
      strcpy(reply, "ok");
      return true;
    } else if (memcmp(command+11, "share", 5) == 0) {
      policy = ADVERT_LOC_SHARE;
      strcpy(reply, "ok");
      return true;
    } else if (memcmp(command+11, "prefs", 5) == 0) {
      policy = ADVERT_LOC_PREFS;
      strcpy(reply, "ok");
      return true;
    } else {
      strcpy(reply, "error");
      return true;
    }
  }
  return false;
}

TEST(GpsAdvert, CommandParsing) {
  uint8_t policy = ADVERT_LOC_NONE;
  char reply[64];

  EXPECT_TRUE(parseGpsAdvertCommand("gps advert", policy, reply));
  EXPECT_STREQ("> none", reply);

  EXPECT_TRUE(parseGpsAdvertCommand("gps advert prefs", policy, reply));
  EXPECT_STREQ("ok", reply);
  EXPECT_EQ(ADVERT_LOC_PREFS, policy);

  EXPECT_TRUE(parseGpsAdvertCommand("gps advert", policy, reply));
  EXPECT_STREQ("> prefs", reply);

  EXPECT_TRUE(parseGpsAdvertCommand("gps advert share", policy, reply));
  EXPECT_STREQ("ok", reply);
  EXPECT_EQ(ADVERT_LOC_SHARE, policy);

  EXPECT_TRUE(parseGpsAdvertCommand("gps advert none", policy, reply));
  EXPECT_STREQ("ok", reply);
  EXPECT_EQ(ADVERT_LOC_NONE, policy);

  EXPECT_TRUE(parseGpsAdvertCommand("gps advert invalid", policy, reply));
  EXPECT_STREQ("error", reply);
}
