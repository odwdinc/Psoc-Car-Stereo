// ======================================================================
// CarStairo.v generated from TopDesign.cysch
// 10/26/2011 at 10:17
// ======================================================================

`define CYDEV_CHIP_REV_PANTHER_ES1 1
`define CYDEV_CHIP_REV_LEOPARD ""
`define CYDEV_CHIP_REV_PANTHER "ES1"

// Component: cy_analog_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// ADC_SAR_v1_10(ADC_Clock=1, ADC_Clock_Frequency=14000000, ADC_Input_Range=1, ADC_Power=0, ADC_Reference=0, ADC_Resolution=8, ADC_SampleMode=0, Ref_Voltage=3.7, Ref_Voltage_mV=3700, Sample_Rate=1000000, CY_COMPONENT_NAME=ADC_SAR_v1_10, CY_INSTANCE_SHORT_NAME=Volume_ADC, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=Volume_ADC, )
module ADC_SAR_v1_10_0 (vplus, vminus, soc, eoc, aclk, vdac_ref);
    inout   vplus;
    electrical   vplus;
    inout   vminus;
    electrical   vminus;
    input   soc;
    output  eoc;
    input   aclk;
    inout   vdac_ref;
    electrical   vdac_ref;


    wire [3:0] vp_ctl;
    wire [3:0] vn_ctl;
    electrical  Net_233;
    wire  Net_205;
    wire  Net_252;
    wire [11:0] Net_207;
    electrical  Net_209;
    electrical  Net_210;
    electrical  Net_255;
    electrical  Net_257;
    electrical  Net_216;
    electrical  Net_149;
    electrical  Net_126;
    electrical  Net_215;
    electrical  Net_248;
    wire  Net_221;
    wire  Net_188;

	// cy_analog_virtualmux_3 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_3_connect(Net_248, Net_216);
	defparam cy_analog_virtualmux_3_connect.sig_width = 1;


	cy_isr_v1_0
		IRQ
		 (.int_signal(eoc));


    ZeroTerminal ZeroTerminal_1 (
        .z(vp_ctl[0]));

    ZeroTerminal ZeroTerminal_2 (
        .z(vp_ctl[2]));

    ZeroTerminal ZeroTerminal_3 (
        .z(vn_ctl[1]));

    ZeroTerminal ZeroTerminal_4 (
        .z(vn_ctl[3]));

    ZeroTerminal ZeroTerminal_5 (
        .z(vp_ctl[1]));

    ZeroTerminal ZeroTerminal_6 (
        .z(vp_ctl[3]));

    ZeroTerminal ZeroTerminal_7 (
        .z(vn_ctl[0]));

    ZeroTerminal ZeroTerminal_8 (
        .z(vn_ctl[2]));

cy_clock_v1_0 theACLK(.clock_out(Net_221));
defparam theACLK.id = "46afdc21-4c24-405b-83ef-e9e18b65e5e5/696a0979-21fc-4185-bf38-6c79febcde7a";
defparam theACLK.source_clock_id = "";
defparam theACLK.is_direct = 0;
defparam theACLK.divisor = 0;
defparam theACLK.period = "71428571.4285714";
defparam theACLK.is_digital = 1;

	// Clock_VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_188 = Net_221;

    cy_psoc5_sar_v2_0 ADC_SAR (
        .clock(Net_188),
        .sof_udb(soc),
        .clk_udb(),
        .vp_ctl_udb(vp_ctl[3:0]),
        .vn_ctl_udb(vn_ctl[3:0]),
        .vplus(vplus),
        .vminus(Net_126),
        .irq(Net_252),
        .data_out(Net_207[11:0]),
        .eof_udb(eoc),
        .pump_clock(Net_188),
        .ext_pin(Net_215),
        .vrefhi_out(Net_257),
        .vref(Net_248));

	// cy_analog_virtualmux_2 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_2_connect(Net_215, Net_210);
	defparam cy_analog_virtualmux_2_connect.sig_width = 1;

	// cy_analog_virtualmux_1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_1_connect(Net_126, Net_149);
	defparam cy_analog_virtualmux_1_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 noconnect (
        .noconnect(Net_210));

    cy_vref_v1_0 vRef_Vdda (
        .vout(Net_216));
    defparam vRef_Vdda.guid = "4720866E-BC14-478d-B8A0-3E44F38CADAC";

	// cy_analog_virtualmux_4 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_4_connect(Net_257, Net_149);
	defparam cy_analog_virtualmux_4_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 cy_analog_noconnect_1 (
        .noconnect(Net_255));



endmodule

// Component: B_UART_v1_20
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v1_20"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v1_20\B_UART_v1_20.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v1_20"
`include "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v1_20\B_UART_v1_20.v"
`endif

// UART_v1_20(Address1=0, Address2=0, BaudRate=9600, BreakDetect=true, CRCoutputsEn=false, Enable_RX=0, Enable_RXIntInterrupt=0, Enable_TX=1, Enable_TXIntInterrupt=0, EnableHWAddress=1, EnIntRXInterrupt=false, EnIntTXInterrupt=false, ExClockFrequency=0, FlowControl=0, HalfDuplexEn=false, HwTXEnSignal=true, InternalClock=true, InternalClockUsed=1, InterruptOnAddDetect=0, InterruptOnAddressMatch=0, InterruptOnBreak=0, InterruptOnByteRcvd=0, InterruptOnOverrunError=0, InterruptOnParityError=0, InterruptOnStopError=0, InterruptOnTXComplete=false, InterruptOnTXFifoEmpty=false, InterruptOnTXFifoFull=false, InterruptOnTXFifoNotFull=false, IntOnAddressDetect=false, IntOnAddressMatch=false, IntOnBreak=false, IntOnByteRcvd=false, IntOnOverrunError=false, IntOnParityError=false, IntOnStopError=false, NumDataBits=8, NumStopBits=1, OverSamplingRate=8, ParityType=0, PSOC32bit=true, RequiredClock=76800, RXAddressMode=1, RXBufferSize=1, RXEnable=false, TXBitClkGenDP=true, TXBufferSize=1, TXEnable=true, Use23Polling=true, CY_COMPONENT_NAME=UART_v1_20, CY_INSTANCE_SHORT_NAME=UART, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=20, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=UART, )
module UART_v1_20_1 (rx, clock, cts_n, reset, rts_n, tx_en, tx, tx_interrupt, rx_interrupt, tx_data, tx_clk, rx_data, rx_clk);
    input   rx;
    input   clock;
    input   cts_n;
    input   reset;
    output  rts_n;
    output  tx_en;
    output  tx;
    output  tx_interrupt;
    output  rx_interrupt;
    output  tx_data;
    output  tx_clk;
    output  rx_data;
    output  rx_clk;

    parameter Address1 = 0;
    parameter Address2 = 0;
    parameter EnIntRXInterrupt = 0;
    parameter EnIntTXInterrupt = 0;
    parameter FlowControl = 0;
    parameter HalfDuplexEn = 0;
    parameter HwTXEnSignal = 1;
    parameter NumDataBits = 8;
    parameter NumStopBits = 1;
    parameter ParityType = 0;
    parameter RXEnable = 0;
    parameter TXEnable = 1;

    wire  Net_9;
    wire  Net_61;

cy_clock_v1_0 IntClock(.clock_out(Net_9));
defparam IntClock.id = "e5cbd8cc-85c7-4fca-ae94-0fec0ada62ef/be0a0e37-ad17-42ca-b5a1-1a654d736358";
defparam IntClock.source_clock_id = "";
defparam IntClock.is_direct = 0;
defparam IntClock.divisor = 0;
defparam IntClock.period = "13020833333.3333";
defparam IntClock.is_digital = 1;

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_61 = Net_9;

    B_UART_v1_20 BUART (
        .cts_n(cts_n),
        .tx(tx),
        .rts_n(rts_n),
        .tx_en(tx_en),
        .clock(Net_61),
        .reset(reset),
        .rx(rx),
        .tx_interrupt(tx_interrupt),
        .rx_interrupt(rx_interrupt),
        .tx_data(tx_data),
        .tx_clk(tx_clk),
        .rx_data(rx_data),
        .rx_clk(rx_clk));
    defparam BUART.Address1 = 0;
    defparam BUART.Address2 = 0;
    defparam BUART.BreakDetect = 1;
    defparam BUART.CRCoutputsEn = 0;
    defparam BUART.FlowControl = 0;
    defparam BUART.HalfDuplexEn = 0;
    defparam BUART.HwTXEnSignal = 1;
    defparam BUART.NumDataBits = 8;
    defparam BUART.NumStopBits = 1;
    defparam BUART.OverSampleCount = 8;
    defparam BUART.ParityType = 0;
    defparam BUART.RXAddressMode = 1;
    defparam BUART.RXEnable = 0;
    defparam BUART.RXStatusIntEnable = 0;
    defparam BUART.TXBitClkGenDP = 1;
    defparam BUART.TXEnable = 1;
    defparam BUART.Use23Polling = 1;



endmodule

// Component: not_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0\not_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0\not_v1_0.v"
`endif

// Component: CyControlReg_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_0\CyControlReg_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_0\CyControlReg_v1_0.v"
`endif

// Component: OneTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "C:\Program Files\Cypress\PSoC Creator\1.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`endif

// Counter_v1_20(CaptureMode=0, CaptureModeSoftware=0, ClockMode=0, CompareMode=1, CompareModeSoftware=0, CompareStatusEdgeSense=true, CompareValue=7, ControlRegRemoved=0, CyGetRegReplacementString=CY_GET_REG8, CySetRegReplacementString=CY_SET_REG8, EnableMode=0, FixedFunction=true, FixedFunctionUsed=1, InitCounterValue=0, InterruptOnCapture=false, InterruptOnCompare=false, InterruptOnOverUnderFlow=false, InterruptOnTC=false, Period=75, RegDefReplacementString=reg8, RegSizeReplacementString=uint8, ReloadOnCapture=false, ReloadOnCompare=false, ReloadOnOverUnder=true, ReloadOnReset=true, Resolution=8, UseInterrupt=true, VerilogSectionReplacementString=sC8, CY_COMPONENT_NAME=Counter_v1_20, CY_INSTANCE_SHORT_NAME=Counter_1, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=20, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=Counter_1, )
module Counter_v1_20_2 (clock, comp, tc, reset, interrupt, enable, capture, upCnt, downCnt, up_ndown, count);
    input   clock;
    output  comp;
    output  tc;
    input   reset;
    output  interrupt;
    input   enable;
    input   capture;
    input   upCnt;
    input   downCnt;
    input   up_ndown;
    input   count;

    parameter CaptureMode = 0;
    parameter ClockMode = 0;
    parameter CompareMode = 1;
    parameter CompareStatusEdgeSense = 1;
    parameter EnableMode = 0;
    parameter ReloadOnCapture = 0;
    parameter ReloadOnCompare = 0;
    parameter ReloadOnOverUnder = 1;
    parameter ReloadOnReset = 1;
    parameter Resolution = 8;
    parameter UseInterrupt = 1;

    wire  Net_102;
    wire  Net_95;
    wire  Net_82;
    wire  Net_91;
    wire  Net_89;
    wire  Net_60;
    wire  Net_55;
    wire  Net_54;
    wire  Net_49;
    wire  Net_48;
    wire  Net_42;
    wire  Net_43;

    cy_psoc3_timer_v1_0 CounterHW (
        .timer_reset(reset),
        .capture(capture),
        .enable(Net_91),
        .kill(Net_82),
        .clock(Net_60),
        .tc(Net_48),
        .compare(Net_54),
        .interrupt(Net_42));

	// int_vm (cy_virtualmux_v1_0)
	assign interrupt = Net_42;

	// TC_vm (cy_virtualmux_v1_0)
	assign tc = Net_48;

	// compare_vm (cy_virtualmux_v1_0)
	assign comp = Net_54;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_82));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_89 = up_ndown;

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_95));

	// vmEnableMode (cy_virtualmux_v1_0)
	assign Net_91 = enable;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign Net_60 = count;



endmodule

// top
module top ;

    wire  Net_109;
    wire  Net_108;
    wire  Net_107;
    wire  Net_106;
    wire  Net_105;
    wire  Net_104;
    wire  Net_103;
    wire  Net_102;
    wire  Net_101;
    wire  Net_100;
    wire  Net_41;
    wire  Net_40;
    wire  Net_39;
    wire  Net_38;
    wire  Net_37;
    wire  Net_36;
    wire  Net_35;
    wire  Net_44;
    wire  Net_33;
    wire  Net_32;
    wire  Net_31;
    wire  Net_29;
    wire  Net_43;
    wire  Net_10;
    electrical  Net_6;
    wire  Net_5;
    wire  Net_4;
    wire  Net_3;
    electrical  Net_2;
    electrical  Net_1;
    wire  Net_52;
    wire [7:0] Net_17;
    wire [7:0] Net_42;

    ADC_SAR_v1_10_0 Volume_ADC (
        .vplus(Net_1),
        .vminus(Net_2),
        .soc(1'b1),
        .eoc(Net_4),
        .aclk(1'b0),
        .vdac_ref(Net_6));

	wire [0:0] tmpOE__Button_net;
	wire [0:0] tmpIO_0__Button_net;
	wire [0:0] tmpINTERRUPT_0__Button_net;
	electrical [0:0] tmpSIOVREF__Button_net;

	cy_psoc3_pins_v1_10
		#(.id("1425177d-0d0e-4468-8bcc-e638e5509a9b"),
		  .drive_mode(3'b011),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		Button
		 (.oe(tmpOE__Button_net),
		  .y({1'b0}),
		  .fb({Net_10}),
		  .io({tmpIO_0__Button_net[0:0]}),
		  .siovref(tmpSIOVREF__Button_net),
		  .interrupt({tmpINTERRUPT_0__Button_net[0:0]}));

	assign tmpOE__Button_net = (`CYDEV_CHIP_REV_LEOPARD == "ES1" || `CYDEV_CHIP_REV_LEOPARD == "ES2") ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Volum_Line_net;
	wire [0:0] tmpFB_0__Volum_Line_net;
	wire [0:0] tmpIO_0__Volum_Line_net;
	wire [0:0] tmpINTERRUPT_0__Volum_Line_net;
	electrical [0:0] tmpSIOVREF__Volum_Line_net;

	cy_psoc3_pins_v1_10
		#(.id("cc3bcd7e-5dc0-48ea-9bf6-6aa082be1ada"),
		  .drive_mode(3'b000),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("NONCONTIGUOUS"),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("A"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(1),
		  .vtrip(2'b10),
		  .width(1))
		Volum_Line
		 (.oe(tmpOE__Volum_Line_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Volum_Line_net[0:0]}),
		  .analog({Net_1}),
		  .io({tmpIO_0__Volum_Line_net[0:0]}),
		  .siovref(tmpSIOVREF__Volum_Line_net),
		  .interrupt({tmpINTERRUPT_0__Volum_Line_net[0:0]}));

	assign tmpOE__Volum_Line_net = (`CYDEV_CHIP_REV_LEOPARD == "ES1" || `CYDEV_CHIP_REV_LEOPARD == "ES2") ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__TX_net;
	wire [0:0] tmpFB_0__TX_net;
	wire [0:0] tmpIO_0__TX_net;
	wire [0:0] tmpINTERRUPT_0__TX_net;
	electrical [0:0] tmpSIOVREF__TX_net;

	cy_psoc3_pins_v1_10
		#(.id("ed092b9b-d398-4703-be89-cebf998501f6"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		TX
		 (.oe(tmpOE__TX_net),
		  .y({Net_43}),
		  .fb({tmpFB_0__TX_net[0:0]}),
		  .io({tmpIO_0__TX_net[0:0]}),
		  .siovref(tmpSIOVREF__TX_net),
		  .interrupt({tmpINTERRUPT_0__TX_net[0:0]}));

	assign tmpOE__TX_net = (`CYDEV_CHIP_REV_LEOPARD == "ES1" || `CYDEV_CHIP_REV_LEOPARD == "ES2") ? ~{1'b1} : {1'b1};

    UART_v1_20_1 UART (
        .cts_n(1'b0),
        .tx(Net_43),
        .rts_n(Net_31),
        .tx_en(Net_32),
        .clock(1'b0),
        .reset(Net_44),
        .rx(1'b0),
        .tx_interrupt(Net_36),
        .rx_interrupt(Net_37),
        .tx_data(Net_38),
        .tx_clk(Net_39),
        .rx_data(Net_40),
        .rx_clk(Net_41));
    defparam UART.Address1 = 0;
    defparam UART.Address2 = 0;
    defparam UART.EnIntRXInterrupt = 0;
    defparam UART.EnIntTXInterrupt = 0;
    defparam UART.FlowControl = 0;
    defparam UART.HalfDuplexEn = 0;
    defparam UART.HwTXEnSignal = 1;
    defparam UART.NumDataBits = 8;
    defparam UART.NumStopBits = 1;
    defparam UART.ParityType = 0;
    defparam UART.RXEnable = 0;
    defparam UART.TXEnable = 1;

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_44));


    assign Net_17[7:0] = ~Net_42[7:0];

    CyControlReg_v1_0 LED_Control_Reg (
        .control_1(Net_42[1]),
        .control_2(Net_42[2]),
        .control_3(Net_42[3]),
        .control_0(Net_42[0]),
        .control_4(Net_42[4]),
        .control_5(Net_42[5]),
        .control_6(Net_42[6]),
        .control_7(Net_42[7]));
    defparam LED_Control_Reg.NumOutputs = 8;

	wire [3:0] tmpOE__dPins_LSB_net;
	wire [3:0] tmpFB_3__dPins_LSB_net;
	wire [3:0] tmpIO_3__dPins_LSB_net;
	wire [0:0] tmpINTERRUPT_0__dPins_LSB_net;
	electrical [0:0] tmpSIOVREF__dPins_LSB_net;

	cy_psoc3_pins_v1_10
		#(.id("cb3bdb07-a868-4af8-b60c-8115b813d5b4"),
		  .drive_mode(12'b110_110_110_110),
		  .ibuf_enabled(4'b1_1_1_1),
		  .init_dr_st(4'b0_0_0_0),
		  .input_sync(4'b1_1_1_1),
		  .intr_mode(8'b00_00_00_00),
		  .io_voltage(", , , "),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(4'b1_1_1_1),
		  .output_sync(4'b0_0_0_0),
		  .pin_aliases(",,,"),
		  .pin_mode("OOOO"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(4'b0_0_0_0),
		  .sio_ibuf(""),
		  .sio_info(8'b00_00_00_00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(4'b0_0_0_0),
		  .spanning(0),
		  .vtrip(8'b10_10_10_10),
		  .width(4))
		dPins_LSB
		 (.oe(tmpOE__dPins_LSB_net),
		  .y({Net_17[3:0]}),
		  .fb({tmpFB_3__dPins_LSB_net[3:0]}),
		  .io({tmpIO_3__dPins_LSB_net[3:0]}),
		  .siovref(tmpSIOVREF__dPins_LSB_net),
		  .interrupt({tmpINTERRUPT_0__dPins_LSB_net[0:0]}));

	assign tmpOE__dPins_LSB_net = (`CYDEV_CHIP_REV_LEOPARD == "ES1" || `CYDEV_CHIP_REV_LEOPARD == "ES2") ? ~{4'b1} : {4'b1};

	wire [3:0] tmpOE__dPins_MSB_net;
	wire [3:0] tmpFB_3__dPins_MSB_net;
	wire [3:0] tmpIO_3__dPins_MSB_net;
	wire [0:0] tmpINTERRUPT_0__dPins_MSB_net;
	electrical [0:0] tmpSIOVREF__dPins_MSB_net;

	cy_psoc3_pins_v1_10
		#(.id("a5f3b957-f813-4e43-8da2-eaccacc298c3"),
		  .drive_mode(12'b110_110_110_110),
		  .ibuf_enabled(4'b1_1_1_1),
		  .init_dr_st(4'b0_0_0_0),
		  .input_sync(4'b1_1_1_1),
		  .intr_mode(8'b00_00_00_00),
		  .io_voltage(", , , "),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(4'b1_1_1_1),
		  .output_sync(4'b0_0_0_0),
		  .pin_aliases(",,,"),
		  .pin_mode("OOOO"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(4'b0_0_0_0),
		  .sio_ibuf(""),
		  .sio_info(8'b00_00_00_00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(4'b0_0_0_0),
		  .spanning(0),
		  .vtrip(8'b10_10_10_10),
		  .width(4))
		dPins_MSB
		 (.oe(tmpOE__dPins_MSB_net),
		  .y({Net_17[7:4]}),
		  .fb({tmpFB_3__dPins_MSB_net[3:0]}),
		  .io({tmpIO_3__dPins_MSB_net[3:0]}),
		  .siovref(tmpSIOVREF__dPins_MSB_net),
		  .interrupt({tmpINTERRUPT_0__dPins_MSB_net[0:0]}));

	assign tmpOE__dPins_MSB_net = (`CYDEV_CHIP_REV_LEOPARD == "ES1" || `CYDEV_CHIP_REV_LEOPARD == "ES2") ? ~{4'b1} : {4'b1};

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_100));

cy_clock_v1_0 timer_clock(.clock_out(Net_52));
defparam timer_clock.id = "c0fb34bd-1044-4931-9788-16b01ce89812";
defparam timer_clock.source_clock_id = "";
defparam timer_clock.is_direct = 0;
defparam timer_clock.divisor = 0;
defparam timer_clock.period = "4444444444444.44";
defparam timer_clock.is_digital = 1;

    Counter_v1_20_2 Counter_1 (
        .reset(Net_100),
        .tc(Net_101),
        .comp(Net_102),
        .clock(1'b0),
        .interrupt(Net_104),
        .enable(1'b0),
        .capture(1'b0),
        .upCnt(1'b0),
        .downCnt(1'b0),
        .up_ndown(1'b1),
        .count(Net_52));
    defparam Counter_1.CaptureMode = 0;
    defparam Counter_1.ClockMode = 0;
    defparam Counter_1.CompareMode = 1;
    defparam Counter_1.CompareStatusEdgeSense = 1;
    defparam Counter_1.EnableMode = 0;
    defparam Counter_1.ReloadOnCapture = 0;
    defparam Counter_1.ReloadOnCompare = 0;
    defparam Counter_1.ReloadOnOverUnder = 1;
    defparam Counter_1.ReloadOnReset = 1;
    defparam Counter_1.Resolution = 8;
    defparam Counter_1.UseInterrupt = 1;



endmodule

