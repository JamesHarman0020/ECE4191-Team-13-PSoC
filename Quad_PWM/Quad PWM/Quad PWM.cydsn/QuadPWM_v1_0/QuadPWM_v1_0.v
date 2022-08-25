
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 07/10/2015 at 14:26
// Component: QuadPWM_v1_0
module QuadPWM_v1_0 (
	output reg pwm1,
	output reg pwm2,
	output reg pwm3,
    output reg pwm4,
	input  wire clock
);

//`#start body` -- edit after this line, do not edit this line

reg  [1:0] toggle;
wire [2:0] cs_addr;
wire       ce0;
wire       ce1;
wire       ff0;
wire       ff1;

/* Toggle signal to control state of the datapath */
always @(posedge clock)
begin
    toggle <= toggle + 1;
end

/* Control States for the Datapath */
assign cs_addr = {1'b0, toggle[1], toggle[0]};

/* Logic for PWM1 output, based on D0 */
always @(posedge clock)
begin
    if (ff0 & (toggle[0]) & (~toggle[1]))
    begin
        pwm1 <= 1'b0;
    end
    else
    begin
        if (ce0 & (toggle[0]) & (~toggle[1]))
        begin
            pwm1 <= 1'b1;
        end
    end
end

/* Logic for PWM2 output, based on D1 */
always @(posedge clock)
begin
    if (ff0 & (~toggle[0]) & (~toggle[1]))
    begin
        pwm2 <= 1'b0;
    end
    else
    begin
        if (ce1 & (~toggle[0]) & (~toggle[1]))
        begin
            pwm2 <= 1'b1;
        end
    end
end

/* Logic for PWM3 output, based on F0 */
always @(posedge clock)
begin
    if (ff1 & (toggle[0]) & (toggle[1]))
    begin
        pwm3 <= 1'b0;
    end
    else
    begin
        if (ce1 & (toggle[0]) & (toggle[1]))
        begin
            pwm3 <= 1'b1;
        end
    end
end

/* Logic for PWM4 output, based on F1 */
always @(posedge clock)
begin
    if (ff0 & (toggle[0]) & (~toggle[1]))
    begin
        pwm4 <= 1'b0;
    end
    else
    begin
        if (ce1 & (toggle[0]) & (~toggle[1]))
        begin
            pwm4 <= 1'b1;
        end
    end
end

cy_psoc3_dp8 #(.a0_init_a(255), .a1_init_a(255), .d0_init_a(255), 
.d1_init_a(255), 
.cy_dpconfig_a(
{
    `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:        Inc A0 , F1->A1*/
    `CS_ALU_OP__AND, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGB, /*CFGRAM1:        A0->A1*/
    `CS_ALU_OP__AND, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGB, /*CFGRAM2:        F0->A0*/
    `CS_ALU_OP__AND, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGB, /*CFGRAM3:        A1->A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:           */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:           */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:             */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:                      */
    8'hFF, 8'h00,  /*CFG9:                      */
    8'hFF, 8'hFF,  /*CFG11-10:                      */
    `SC_CMPB_A1_A0, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:                      */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:                      */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:                      */
}
)) PwmDatapath (
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(clock),
        /*  input   [02:00]         */  .cs_addr(cs_addr),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output                  */  .ce0(ce0),
        /*  output                  */  .cl0(),
        /*  output                  */  .z0(),
        /*  output                  */  .ff0(ff0),
        /*  output                  */  .ce1(ce1),
        /*  output                  */  .cl1(),
        /*  output                  */  .z1(),
        /*  output                  */  .ff1(ff1),
        /*  output                  */  .ov_msb(),
        /*  output                  */  .co_msb(),
        /*  output                  */  .cmsb(),
        /*  output                  */  .so(),
        /*  output                  */  .f0_bus_stat(),
        /*  output                  */  .f0_blk_stat(),
        /*  output                  */  .f1_bus_stat(),
        /*  output                  */  .f1_blk_stat()
);
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line






















