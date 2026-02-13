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
#include "ignis_keymap_mock.h"

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
        ignis_core_context.current_digit = 3;
    }
    ~IgnisCoreTest() override = default;
};

TEST_F(IgnisCoreTest, GameSetup)
{
    ignis_core_context.state = IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME;
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    EXPECT_EQ(ignis_core_context.total_time_sec, 0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_4);
    EXPECT_EQ(ignis_core_context.total_time_sec, 3600 * 4);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_2);
    EXPECT_EQ(ignis_core_context.total_time_sec, 3600 * 4 + 60 * 2 * 10);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    EXPECT_EQ(ignis_core_context.total_time_sec, 3600 * 4 + 60 * 2 * 10);
    EXPECT_EQ(ignis_core_context.total_time_digits[3], 0);
    EXPECT_EQ(ignis_core_context.total_time_digits[2], 4);
    EXPECT_EQ(ignis_core_context.total_time_digits[1], 2);
    EXPECT_EQ(ignis_core_context.total_time_digits[0], 0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_ENTER);
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_PROGRAMMING_BUZZER_TIME);

    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_0);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_1);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_ENTER);
    EXPECT_EQ(ignis_core_context.buzzer_time_sec, 60);
    EXPECT_EQ(ignis_core_context.buzzer_time_digits[3], 0);
    EXPECT_EQ(ignis_core_context.buzzer_time_digits[2], 0);
    EXPECT_EQ(ignis_core_context.buzzer_time_digits[1], 0);
    EXPECT_EQ(ignis_core_context.buzzer_time_digits[0], 1);
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_PROGRAMMING_CODE);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_5);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_7);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_2);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_1);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_ENTER);
    EXPECT_EQ(ignis_core_context.code, 5721);
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_READY_TO_BE_ARMED);
}

TEST_F(IgnisCoreTest, CancelInput)
{
    ignis_core_context.state = IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME;
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_5);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_7);
    ignis_core_keymap_callback(IGNIS_KEYMAP_KEY_ESC);
    EXPECT_EQ(ignis_core_context.total_time_sec, 0);
    EXPECT_EQ(ignis_core_context.total_time_digits[3], 0);
    EXPECT_EQ(ignis_core_context.total_time_digits[2], 0);
    EXPECT_EQ(ignis_core_context.total_time_digits[1], 0);
    EXPECT_EQ(ignis_core_context.total_time_digits[0], 0);
    EXPECT_EQ(ignis_core_context.state, IGNIS_CORE_STATE_PROGRAMMING_TOTAL_TIME);
    EXPECT_EQ(ignis_core_context.current_digit, 3);
}