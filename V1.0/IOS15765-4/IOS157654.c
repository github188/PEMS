

#include "includes.h"



CanDSstru CAN_DS[100];//[0]~[99]依次存放id0x000a~0x0044的can数据，只放data以及一个更新标志位，上传清0 
CanRxMsg RxMessage;



/**
  * @brief  初始化CAN
  * @param  None
  * @retval None
  */
void OBD2_CANInit(void)
{
  CAN1_GPIOConfig();
  CAN_Cofig(CAN125K);
	ClearRAM((u8*)CAN_DS,900);
	CAN1_Config16BitFilter(0,0, 0, 0, 0);
//   CAN1_Config16BitFilter( 0,0x000A, 0x000A, 0xFFFF, 0xFFFF);   		// 这里只判断接收我们关心的ID其余的屏蔽
//   CAN1_Config16BitFilter( 1,0x000B, 0x000B, 0xFFFF, 0xFFFF); 
//   CAN1_Config16BitFilter( 2,0x000C, 0x000C, 0xFFFF, 0xFFFF); 
//   CAN1_Config16BitFilter( 3,0x000E, 0x000E, 0xFFFF, 0xFFFF);
//   CAN1_Config16BitFilter( 4,0x000F, 0x000F, 0xFFFF, 0xFFFF);
//   CAN1_Config16BitFilter( 5,0x0011, 0x0011, 0xFFFF, 0xFFFF);
}
/**
//   * @brief  发送一帧CAN数据
//   * @param  None
//   * @retval None
//   */
// ErrorStatus SendFrame(CanTxMsg* TxMessage)
// {
//   u8 TransmitMailbox;
//   u32 i;
//   CANRbuf.CANRXMAIL = ERROR;
//   TransmitMailbox = CAN_Transmit(CAN1, TxMessage);
//   while(CAN_TransmitStatus(CAN1,TransmitMailbox) != CANTXOK);
//   for (i = 0;i < 10000000/3;i++) //大概3S/3吧
//   {
//     if (CANRbuf.CANRXMAIL == SUCCESS) break;
//   }
//   return CANRbuf.CANRXMAIL;
// }



void CAN1_DS_UPDATE(CanRxMsg* RxMessage)
{
    u16 id;
	u8 i;
	
  	id = (u16)(RxMessage->StdId) ;
	if((id <= MAX_USER_CANID)&&((id >= MIN_USER_CANID)))
	{
        for(i=0;i<8;i++)
 	    {
            if(CAN_DS[id - MIN_USER_CANID].Data[i] != RxMessage->Data[i])
 		    {
                CAN_DS[id - MIN_USER_CANID].Data[i] = RxMessage->Data[i];
 			    CAN_DS[id - MIN_USER_CANID].UpdateFlag = 1;
			    CanUpdateFlag = 1;
 		    }
 	    }
    }
}







