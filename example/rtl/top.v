module top(
    input clk,
    input rst
);

reg [63:0] global_clock = 0;

always@(posedge clk)
    global_clock <= global_clock + 'b1;

wire [31:0] ifu_pc;
wire ifu_pc_valid;
wire [31:0] ram_inst;
wire ram_ready;

IFU ifu(
    .clk(clk),
    .rst(rst),
    .ram_ready(ram_ready),
    .pc(ifu_pc),
    .pc_valid(ifu_pc_valid)
);

RAM ram(
    .clk(clk),
    .rst(rst),
    .global_clock(global_clock),
    .ifu_pc(ifu_pc),
    .ifu_pc_valid(ifu_pc_valid),
    .ready(ram_ready),
    .inst(ram_inst)
);

endmodule
