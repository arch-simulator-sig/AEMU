/**
 * @def IO_DECLARE(module, declare, name, type, width)
 * @param module 模块名称，与模块类名称一致
 * @param declare 信号声明类型
 * @param name 型号名称
 * @param tpye 信号类型 reg/wire
 * @param width 信号位宽
*/
#ifndef IO_DECLARE
#define IO_DECLARE(module, declare, name, type, width)
#endif

IO_DECLARE(IFU      , uint32_t      , pc            , reg   , 32)
IO_DECLARE(IFU      , bool          , pc_valid      , reg   , 1)
IO_DECLARE(IFU      , uint8_t       , test1         , reg   , 8)
IO_DECLARE(IFU      , uint16_t      , test2         , reg   , 16)
IO_DECLARE(IFU      , uint32_t      , test3         , reg   , 32)
IO_DECLARE(IFU      , uint64_t      , test4         , reg   , 64)

IO_DECLARE(RAM      , uint32_t      , inst          , reg   , 32)
IO_DECLARE(RAM      , bool          , ready         , wire  , 1)
