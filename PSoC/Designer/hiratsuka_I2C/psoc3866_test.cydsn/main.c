/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>

uint8 Ezi2c_master_write_buf(uint8 addr,uint8 data_addr,uint8* wrdata,uint8 cnt);
uint8 Ezi2c_master_read_buf(uint8 addr,uint8 data_addr,uint8* redata,uint8 cnt);

/*
struct{
    uint8 m_status;
    uint8 s_status;
}i2c_data;
*/

void main()
{
    uint8 i2c_data[3] = {127,255,0};
    uint8 i2c_data_r[2] = {0,0};
    uint8 status;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Counter_1_Start();
    LCD_Char_1_Start();
    I2C_1_Start();
    LCD_Char_1_ClearDisplay();
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    /* Set position for string output to row - 0 column - 0 */
    LCD_Char_1_Position(0u, 0u);
    LCD_Char_1_PrintString("PSoC3 test");
    LCD_Char_1_Position(1u, 0u);
    LCD_Char_1_PrintString("Debug Start!");
    CyDelay(1000u);
    
    LCD_Char_1_ClearDisplay();
    
    I2C_1_MasterClearStatus();
    
    for(;;)
    {
        i2c_data[0]++;
        LCD_Char_1_Position(0u, 0u);
        LCD_Char_1_PrintString("now writing!");
        status = Ezi2c_master_write_buf(26,0,i2c_data,1);
        status = Ezi2c_master_read_buf(26,3,i2c_data_r,2);
        LCD_Char_1_ClearDisplay();
        LCD_Char_1_Position(0u, 0u);
        LCD_Char_1_PrintString("x = ");
        LCD_Char_1_PrintInt8(i2c_data[0]);
        LCD_Char_1_PrintString("  t = ");
        LCD_Char_1_PrintInt16(i2c_data_r[1]+(i2c_data_r[0]*0x100));
        LCD_Char_1_Position(1u, 0u);
        LCD_Char_1_PrintString("status = ");
        LCD_Char_1_PrintInt8(status);
        
        
        CyDelay(250u);
    }
}
uint8 Ezi2c_master_write_buf(uint8 addr,uint8 data_addr,uint8* wrdata,uint8 cnt)
{
    uint8 status;
    uint8 i;
    
    status = I2C_1_MasterSendStart(addr, I2C_1_WRITE_XFER_MODE);
    if(status == I2C_1_MSTR_NO_ERROR) /* Check if transfer completed without errors */
    {
        status = I2C_1_MasterWriteByte(data_addr);
        if(status != I2C_1_MSTR_NO_ERROR)
        {
            I2C_1_MasterSendStop();
            return status;
        }
        for(i=0; i < cnt; i++)
        {
            status = I2C_1_MasterWriteByte(wrdata[i]);
            if(status != I2C_1_MSTR_NO_ERROR)
            {
                break;
            }
        }
    }
    I2C_1_MasterSendStop();
    return status;
}
uint8 Ezi2c_master_read_buf(uint8 addr,uint8 data_addr,uint8* redata,uint8 cnt)
{
    uint8 status;
    uint8 i;
    status = I2C_1_MasterSendStart(addr, I2C_1_WRITE_XFER_MODE);
    if(status == I2C_1_MSTR_NO_ERROR) /* Check if transfer completed without errors */
    {
        status = I2C_1_MasterWriteByte(data_addr);
        if(status != I2C_1_MSTR_NO_ERROR)
        {
            I2C_1_MasterSendStop();
            return status;
        }
    }
    I2C_1_MasterSendStop();
    status = I2C_1_MasterSendStart(0x08, I2C_1_READ_XFER_MODE);
    if(status == I2C_1_MSTR_NO_ERROR) /* Check if transfer completed without errors */
    {
        //I2C_1_MasterReadByte(I2C_1_ACK_DATA);
        for(i=0; i < cnt; i++)
        {
            if(i < cnt )
            {
                redata[i] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);
            }
            else
            {
                redata[i] = I2C_1_MasterReadByte(I2C_1_NAK_DATA);
            }
        }
    }
    I2C_1_MasterSendStop(); /* Send Stop */
    return status;
}
/* [] END OF FILE */
