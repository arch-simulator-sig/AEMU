module IFU(
    input clk,
    input rst,

    input ram_ready,

    output reg [31:0] pc,
    output reg pc_valid

);
always@(posedge clk)
begin
    if(rst) begin
        pc <= 'h8000_0000;
        pc_valid <= 'b1;
    end else begin
        pc_valid <= 'b1;
        if(ram_ready&&pc_valid) begin
            pc <= pc + 'd4;
        end
    end

end
endmodule
