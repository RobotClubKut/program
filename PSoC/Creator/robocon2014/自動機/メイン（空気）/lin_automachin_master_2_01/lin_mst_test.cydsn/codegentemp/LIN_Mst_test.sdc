# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\tatsuya\Desktop\LIN_automachin_master_2_01\LIN_Mst_test.cydsn\LIN_Mst_test.cyprj
# Date: Mon, 24 Feb 2014 05:24:52 GMT
#set_units -time ns
create_clock -name {Clock_1(routed)} -period 20000000 -waveform {0 10000000} [list [get_pins {ClockBlock/dclk_4}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyMASTER_CLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {PS2_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 157 313} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {UART_2_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 157 313} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {LIN_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 313 627} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3751 7501} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 960001 1920001} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]


# Component constraints for C:\Users\tatsuya\Desktop\LIN_automachin_master_2_01\LIN_Mst_test.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\tatsuya\Desktop\LIN_automachin_master_2_01\LIN_Mst_test.cydsn\LIN_Mst_test.cyprj
# Date: Mon, 24 Feb 2014 05:24:37 GMT
