/**
 ********************************************************************************
 * @file    ignis_core_test.cpp
 * @author  Massimiliano Ianniello
 * @date    30/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_core.h"

#include "fff.h"
#include "gtest/gtest.h"
#include "ignis_core_priv.h"
#include "ignis_display_mock.h"
#include "ignis_keymap_mock.h"
#include "k_osal/thread.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
DEFINE_FFF_GLOBALS

/* Function Definitions ------------------------------------------------------*/
FAKE_VALUE_FUNC(int, k_osal_thread_create, k_osal_thread_t *, const char *, k_osal_thread_priority_t, size_t, k_osal_thread_func_t, void *)
FAKE_VOID_FUNC(k_osal_thread_sleep, size_t)

#include <stddef.h>
class IgnisCoreTest : public ::testing::Test
{
   protected:
    IgnisCoreTest()
    {
        ignis_keymap_mock_reset_fakes();
        memset(&ignis_core_context, 0, sizeof(ignis_core_context_t));
        memset(ignis_core_context.display_digits, 0xFF, sizeof(ignis_core_context.display_digits));
    }
    ~IgnisCoreTest() override = default;
};

TEST_F(IgnisCoreTest, AddDigitToDisplayBuffer)
{
    ignis_core_add_digit_to_display_buffer(1);
    EXPECT_EQ(ignis_core_context.display_digits[0], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[1], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[2], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[3], 1);
    ignis_core_add_digit_to_display_buffer(2);
    EXPECT_EQ(ignis_core_context.display_digits[0], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[1], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[2], 1);
    EXPECT_EQ(ignis_core_context.display_digits[3], 2);
    ignis_core_add_digit_to_display_buffer(3);
    EXPECT_EQ(ignis_core_context.display_digits[0], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[1], 1);
    EXPECT_EQ(ignis_core_context.display_digits[2], 2);
    EXPECT_EQ(ignis_core_context.display_digits[3], 3);
    ignis_core_add_digit_to_display_buffer(4);
    EXPECT_EQ(ignis_core_context.display_digits[0], 1);
    EXPECT_EQ(ignis_core_context.display_digits[1], 2);
    EXPECT_EQ(ignis_core_context.display_digits[2], 3);
    EXPECT_EQ(ignis_core_context.display_digits[3], 4);
    ignis_core_add_digit_to_display_buffer(5);
    EXPECT_EQ(ignis_core_context.display_digits[0], 2);
    EXPECT_EQ(ignis_core_context.display_digits[1], 3);
    EXPECT_EQ(ignis_core_context.display_digits[2], 4);
    EXPECT_EQ(ignis_core_context.display_digits[3], 5);
}

TEST_F(IgnisCoreTest, ResetDisplayBuffer)
{
    ignis_core_add_digit_to_display_buffer(1);
    ignis_core_add_digit_to_display_buffer(2);
    ignis_core_add_digit_to_display_buffer(3);
    ignis_core_add_digit_to_display_buffer(4);
    EXPECT_EQ(ignis_core_context.display_digits[0], 1);
    EXPECT_EQ(ignis_core_context.display_digits[1], 2);
    EXPECT_EQ(ignis_core_context.display_digits[2], 3);
    EXPECT_EQ(ignis_core_context.display_digits[3], 4);
    ignis_core_reset_display_buffer();
    EXPECT_EQ(ignis_core_context.display_digits[0], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[1], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[2], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[3], 0xFF);
}

TEST_F(IgnisCoreTest, SendDataToDisplayWhenAKeyIsPressed)
{
    ignis_core_context.state = IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME;
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_1);
    EXPECT_EQ(ignis_display_send_data_fake.call_count, 1);
    EXPECT_EQ(ignis_display_send_data_fake.arg0_val[0], 0xFF);
    EXPECT_EQ(ignis_display_send_data_fake.arg0_val[1], 0xFF);
    EXPECT_EQ(ignis_display_send_data_fake.arg0_val[2], 0xFF);
    EXPECT_EQ(ignis_display_send_data_fake.arg0_val[3], 1);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_2);
    EXPECT_EQ(ignis_display_send_data_fake.call_count, 2);
    EXPECT_EQ(ignis_core_context.display_digits[0], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[1], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[2], 1);
    EXPECT_EQ(ignis_core_context.display_digits[3], 2);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_3);
    EXPECT_EQ(ignis_display_send_data_fake.call_count, 3);
    EXPECT_EQ(ignis_core_context.display_digits[0], 0xFF);
    EXPECT_EQ(ignis_core_context.display_digits[1], 1);
    EXPECT_EQ(ignis_core_context.display_digits[2], 2);
    EXPECT_EQ(ignis_core_context.display_digits[3], 3);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_4);
    EXPECT_EQ(ignis_display_send_data_fake.call_count, 4);
    EXPECT_EQ(ignis_display_send_data_fake.arg0_val[0], 1);
    EXPECT_EQ(ignis_display_send_data_fake.arg0_val[1], 2);
    EXPECT_EQ(ignis_display_send_data_fake.arg0_val[2], 3);
    EXPECT_EQ(ignis_display_send_data_fake.arg0_val[3], 4);
}

TEST_F(IgnisCoreTest, CalculateTimeFromDigits)
{
    constexpr uint8_t digits_10_minutes[4]          = {0, 0, 1, 0};
    constexpr uint8_t digits_1_hour[4]              = {0, 1, 0, 0};
    constexpr uint8_t digits_1_hour_10_minutes[4]   = {0, 1, 1, 0};
    constexpr uint8_t digits_14_hours_25_minutes[4] = {1, 4, 2, 5};
    EXPECT_EQ(ignis_core_calculate_time_min(digits_10_minutes), 10);
    EXPECT_EQ(ignis_core_calculate_time_min(digits_1_hour), 60);
    EXPECT_EQ(ignis_core_calculate_time_min(digits_1_hour_10_minutes), 70);
    EXPECT_EQ(ignis_core_calculate_time_min(digits_14_hours_25_minutes), 60 * 14 + 25);
}

TEST_F(IgnisCoreTest, SetUpGame)
{
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_IDLE);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_ENTER);
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_1);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_ENTER);
    EXPECT_EQ(ignis_core_context.total_time_min, 60);
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_1);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_ENTER);
    EXPECT_EQ(ignis_core_context.buzzing_time_min, 10);
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_PROGRAMMING_CODE);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_5);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_7);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_1);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_8);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_ENTER);
    EXPECT_EQ(ignis_core_context.defuse_code[0], 5);
    EXPECT_EQ(ignis_core_context.defuse_code[1], 7);
    EXPECT_EQ(ignis_core_context.defuse_code[2], 1);
    EXPECT_EQ(ignis_core_context.defuse_code[3], 8);
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_READY_TO_BE_ARMED);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_ENTER);
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_ARMED);
}