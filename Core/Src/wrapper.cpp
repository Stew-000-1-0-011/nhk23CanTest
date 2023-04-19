#include <can.h>

#include <CRSLibtmp/Can/Stm32/RM0008/filter_manager.hpp>
#include <CRSLibtmp/Can/Stm32/RM0008/can_bus.hpp>
#include <CRSLibtmp/Can/Stm32/RM0008/utility.hpp>

using namespace CRSLib::IntegerTypes;
using namespace CRSLib::Can::Stm32::RM0008;
using CRSLib::Can::DataField;

const char * error_msg{nullptr};

void init_can_msp_filter()
{
	 {
	 	// ピンなど初期化
	 	HAL_CAN_DeInit(&hcan);
	 	HAL_CAN_MspInit(&hcan);
	 }

	FilterConfig fc[1];
	fc[0] = FilterConfig{};

	FilterManager::initialize(filter_bank_size, fc);
	const auto f = FilterManager::make_mask32(0x300, 0x0);
	if(!FilterManager::set_filter(0, f))
	{
		error_msg = "Filter cannot set.";
		Error_Handler();
	}
	FilterManager::activate(0);
}

extern "C" void main_cpp(CAN_HandleTypeDef *const hcan) noexcept
{
	init_can_msp_filter();

	 CanBus can_bus{can1};

//	// HALを使う場合はここでHAL_CAN_Startを呼ぶ
//	{
//		HAL_CAN_Start(hcan);
//	}

	while(true)
	{
		[[maybe_unused]] volatile int dummy = 0;

//		 // 送信
//		 {
//		 	DataField tx_data;
//		 	tx_data.buffer[0] = (byte)'H';
//		 	tx_data.buffer[1] = (byte)'E';
//		 	tx_data.buffer[2] = (byte)'L';
//		 	tx_data.buffer[3] = (byte)'L';
//		 	tx_data.buffer[4] = (byte)'O';
//
//		 	tx_data.dlc = 5U;
//
//		 	(void)can_bus.post(0x300, tx_data);
//		 }


//		// HALで送信
//		{
//			CAN_TxHeaderTypeDef tx_header;
//			tx_header.StdId = 0x300;
//			tx_header.ExtId = 0;
//			tx_header.RTR = CAN_RTR_DATA;
//			tx_header.IDE = CAN_ID_STD;
//			tx_header.DLC = 8;
//
//			u8 buffer[] = {'H', 'E', 'L', 'L', 'O', 'C', 'R', 'S'};
//
//			u32 tx_mailbox;
//			auto t = HAL_GetTick();
//
//			if(HAL_CAN_GetTxMailboxesFreeLevel(hcan))
//			{
////				HAL_Delay(1000);
//				if(const auto now = HAL_GetTick(); t - now > 100)
//				{
//					t = now;
//					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
//				}
//				HAL_CAN_AddTxMessage(hcan, &tx_header, buffer, &tx_mailbox);
//			}
//		}


	}
}
