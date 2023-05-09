module RAM(
    input clk,
    input rst,

    input [63:0] global_clock,

    input[31:0] ifu_pc,
    input ifu_pc_valid,
    output ready,
    output reg [31:0] inst
);

assign ready = global_clock[1:0] == 'b0 ? 1'b1 : 1'b0;
always @(posedge clk) begin
    if(rst) inst <= 'b0;
    else if(ready && ifu_pc_valid)
        inst <= ifu_pc;
    else inst <= 'b0;
end
endmodule
