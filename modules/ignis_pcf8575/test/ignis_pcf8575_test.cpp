/**
 ********************************************************************************
 * @file    ignis_pcf8575_test.cpp
 * @author  Massimiliano Ianniello
 * @date    30/01/26
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ignis_pcf8575.h"

#include "fff.h"
#include "gtest/gtest.h"
#include "k_hal_i2c_master_mock.h"
#include "k_osal_mock.h"

/* Macros --------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
/* Function Declarations -----------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
DEFINE_FFF_GLOBALS
extern ignis_pcf8575_ctx_t ignis_pcf8575_ctx;

/* Function Definitions ------------------------------------------------------*/
class IgnisPcf8575Test : public ::testing::Test
{
   protected:
    IgnisPcf8575Test()
    {
        k_hal_i2c_master_reset();
        k_osal_mock_reset();
        memset(&ignis_pcf8575_ctx, 0, sizeof(ignis_pcf8575_ctx_t));
    }
    ~IgnisPcf8575Test() override = default;
};

TEST_F(IgnisPcf8575Test, Initialize)
{
    ignis_pcf8575_init();
    EXPECT_TRUE(ignis_pcf8575_ctx.initialized);
    EXPECT_EQ(ignis_pcf8575_ctx.pins_state[0], 0xFF);
    EXPECT_EQ(ignis_pcf8575_ctx.pins_state[1], 0xFF);
    EXPECT_EQ(k_osal_mutex_create_fake.call_count, 1);
    ignis_pcf8575_init();
    EXPECT_EQ(k_osal_mutex_create_fake.call_count, 1);
}

TEST_F(IgnisPcf8575Test, SetStatus)
{
    ignis_pcf8575_init();
    ignis_pcf8575_set_status((uint8_t[]){0xFF, 0x80});
    EXPECT_EQ(ignis_pcf8575_ctx.pins_state[0], 0xFF);
    EXPECT_EQ(ignis_pcf8575_ctx.pins_state[1], 0x80);
}