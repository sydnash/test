--
--------------------------------------------------------------------------------
--  FILE:  encoder.lua
--  DESCRIPTION:  protoc-gen-lua
--      Google's Protocol Buffers project, ported to lua.
--      https://code.google.com/p/protoc-gen-lua/
--
--      Copyright (c) 2010 , 林卓毅 (Zhuoyi Lin) netsnail@gmail.com
--      All rights reserved.
--
--      Use, modification and distribution are subject to the "New BSD License"
--      as listed at <url: http://www.opensource.org/licenses/bsd-license.php >.
--
--  COMPANY:  NetEase
--  CREATED:  2010年07月29日 19时30分46秒 CST
--------------------------------------------------------------------------------
--
local string = string
local table = table
local ipairs = ipairs
local assert =assert
local print = print
local pairs = pairs
local _G = _G
local uint64 = uint64
local int64 = int64
local pb = require "pb"
local wire_format = require "wire_format"
local tostring = tostring
module "encoder"
for k, v in pairs(_G) do
    print(k, v)
end
local T7F = uint64.new("127")
local T3fff = uint64.new("16383")
local T1fffff = uint64.new("2097151")
local Tfffffff = uint64.new("268435455")
local T7ffffffff  = uint64.new("34359738367")
local T3FFFFFFFFFF  = uint64.new("4398046511103")
local T1FFFFFFFFFFFF = uint64.new("562949953421311")
local TFFFFFFFFFFFFFF = uint64.new("72057594037927935") 
local T7FFFFFFFFFFFFFFF = uint64.new("9223372036854775807")
local zero = int64.new("0")
function _VarintSize(value)
    value = uint64.new(value)
    if value <= T7F then return 1 end
    if value <= T3fff then return 2 end
    if value <= T1fffff then return 3 end
    if value <= Tfffffff then return 4 end
    if value <= T7ffffffff then return 5 end
    if value <= T3FFFFFFFFFF then return 6 end
    if value <= T1FFFFFFFFFFFF then return 7 end
    if value <= TFFFFFFFFFFFFFF then return 8 end
    if value <= T7FFFFFFFFFFFFFFF then return 9 end
    return 10
end

function _SignedVarintSize(value)
    value = int64.new(value)
    if value < zero then return 10 end
    value = uint64.new(tostring(value))
    if value <= T7F then return 1 end
    if value <= T3fff then return 2 end
    if value <= T1fffff then return 3 end
    if value <= Tfffffff then return 4 end
    if value <= T7ffffffff then return 5 end
    if value <= T3FFFFFFFFFF then return 6 end
    if value <= T1FFFFFFFFFFFF then return 7 end
    if value <= TFFFFFFFFFFFFFF then return 8 end
    if value <= T7FFFFFFFFFFFFFFF then return 9 end
    return 10
end

function _TagSize(field_number)
  return _VarintSize(wire_format.PackTag(field_number, 0))
end

function _SimpleSizer(compute_value_size)
    return function(field_number, is_repeated, is_packed)
        local tag_size = _TagSize(field_number)
        if is_packed then
            local VarintSize = _VarintSize
            return function(value)
                local result = 0
                for _, element in ipairs(value) do
                    result = result + compute_value_size(element)
                end
                return result + VarintSize(result) + tag_size
            end
        elseif is_repeated then
            return function(value)
                local result = tag_size * #value
                for _, element in ipairs(value) do
                    result = result + compute_value_size(element)
                end
                return result
            end
        else
            return function (value)
                return tag_size + compute_value_size(value)
            end
        end
    end
end

function _ModifiedSizer(compute_value_size, modify_value)
    return function (field_number, is_repeated, is_packed)
        local tag_size = _TagSize(field_number)
        if is_packed then
            local VarintSize = _VarintSize
            return function (value)
                local result = 0
                for _, element in ipairs(value) do
                    result = result + compute_value_size(modify_value(element))
                end
                return result + VarintSize(result) + tag_size
            end
        elseif is_repeated then
            return function (value)
                local result = tag_size * #value
                for _, element in ipairs(value) do
                    result = result + compute_value_size(modify_value(element))
                end
                return result
            end
        else
            return function (value)
                return tag_size + compute_value_size(modify_value(value))
            end
        end
    end
end

function _FixedSizer(value_size)
    return function (field_number, is_repeated, is_packed)
        local tag_size = _TagSize(field_number)
        if is_packed then
            local VarintSize = _VarintSize
            return function (value)
                local result = #value * value_size
                return result + VarintSize(result) + tag_size
            end
        elseif is_repeated then
            local element_size = value_size + tag_size
            return function(value)
                return #value * element_size
            end
        else
            local field_size = value_size + tag_size
            return function (value)
                return field_size
            end
        end
    end
end

Int32Sizer = _SimpleSizer(_SignedVarintSize)
Int64Sizer = Int32Sizer
EnumSizer = Int32Sizer

UInt32Sizer = _SimpleSizer(_VarintSize)
UInt64Sizer = UInt32Sizer 

SInt32Sizer = _ModifiedSizer(_VarintSize, wire_format.ZigZagEncode)
SInt64Sizer = _ModifiedSizer(_VarintSize, wire_format.ZigZagEncode64)

Fixed32Sizer = _FixedSizer(4) 
SFixed32Sizer = Fixed32Sizer
FloatSizer = Fixed32Sizer

Fixed64Sizer = _FixedSizer(8) 
SFixed64Sizer = Fixed64Sizer
DoubleSizer = Fixed64Sizer

BoolSizer = _FixedSizer(1)


function StringSizer(field_number, is_repeated, is_packed)
    local tag_size = _TagSize(field_number)
    local VarintSize = _VarintSize
    assert(not is_packed)
    if is_repeated then
        return function(value)
            local result = tag_size * #value
            for _, element in ipairs(value) do
                local l = #element
                result = result + VarintSize(l) + l
            end
            return result
        end
    else
        return function(value)
            local l = #value
            return tag_size + VarintSize(l) + l
        end
    end
end

function BytesSizer(field_number, is_repeated, is_packed)
    local tag_size = _TagSize(field_number)
    local VarintSize = _VarintSize
    assert(not is_packed)
    if is_repeated then
        return function (value)
            local result = tag_size * #value
            for _,element in ipairs(value) do
                local l = #element
                result = result + VarintSize(l) + l
            end
            return result
        end
    else
        return function (value)
            local l = #value
            return tag_size + VarintSize(l) + l
        end
    end
end

function MessageSizer(field_number, is_repeated, is_packed)
    local tag_size = _TagSize(field_number)
    local VarintSize = _VarintSize
    assert(not is_packed)
    if is_repeated then
        return function(value)
            local result = tag_size * #value
            for _,element in ipairs(value) do
                local l = element:ByteSize()
                result = result + VarintSize(l) + l
            end
            return result
        end
    else
        return function (value)
            local l = value:ByteSize()
            return tag_size + VarintSize(l) + l
        end
    end
end


-- ====================================================================
--  Encoders!

local _EncodeVarint = pb.varint_encoder
local _EncodeSignedVarint = pb.signed_varint_encoder


function _VarintBytes(value)
    local out = {}
    local write = function(value)
        out[#out + 1 ] = value
    end
    _EncodeSignedVarint(write, value)
    return table.concat(out)
end

function TagBytes(field_number, wire_type)
  return _VarintBytes(wire_format.PackTag(field_number, wire_type))
end

function _SimpleEncoder(wire_type, encode_value, compute_value_size)
    return function(field_number, is_repeated, is_packed)
        if is_packed then
            local tag_bytes = TagBytes(field_number, wire_format.WIRETYPE_LENGTH_DELIMITED)
            local EncodeVarint = _EncodeVarint
            return function(write, value)
                write(tag_bytes)
                local size = 0
                for _, element in ipairs(value) do
                    size = size + compute_value_size(element)
                end
                EncodeVarint(write, size)
                for element in value do
                    encode_value(write, element)
                end
            end
        elseif is_repeated then
            local tag_bytes = TagBytes(field_number, wire_type)
            return function(write, value)
                for _, element in ipairs(value) do
                    write(tag_bytes)
                    encode_value(write, element)
                end
            end
        else
            local tag_bytes = TagBytes(field_number, wire_type)
            return function(write, value)
                write(tag_bytes)
                encode_value(write, value)
            end
        end
    end
end

function _ModifiedEncoder(wire_type, encode_value, compute_value_size, modify_value)
    return function (field_number, is_repeated, is_packed)
        if is_packed then
            local tag_bytes = TagBytes(field_number, wire_format.WIRETYPE_LENGTH_DELIMITED)
            local EncodeVarint = _EncodeVarint
            return function (write, value)
                write(tag_bytes)
                local size = 0
                for _, element in ipairs(value) do
                    size = size + compute_value_size(modify_value(element))
                end
                EncodeVarint(write, size)
                for _, element in ipairs(value) do
                    encode_value(write, modify_value(element))
                end
            end
        elseif is_repeated then
            local tag_bytes = TagBytes(field_number, wire_type)
            return function (write, value)
                for _, element in ipairs(value) do
                    write(tag_bytes)
                    encode_value(write, modify_value(element))
                end
            end
        else
            local tag_bytes = TagBytes(field_number, wire_type)
            return function (write, value)
                write(tag_bytes)
                encode_value(write, modify_value(value))
            end
        end
    end
end

function _StructPackEncoder(wire_type, value_size, format)
    return function(field_number, is_repeated, is_packed)
        local struct_pack = pb.struct_pack
        if is_packed then
            local tag_bytes = TagBytes(field_number, wire_format.WIRETYPE_LENGTH_DELIMITED)
            local EncodeVarint = _EncodeVarint
            return function (write, value)
                write(tag_bytes)
                EncodeVarint(write, #value * value_size)
                for _, element in ipairs(value) do
                    struct_pack(write, format, element)
                end
            end
        elseif is_repeated then
            local tag_bytes = TagBytes(field_number, wire_type)
            return function (write, value)
                for _, element in ipairs(value) do
                    write(tag_bytes)
                    struct_pack(write, format, element)
                end
            end
        else
            local tag_bytes = TagBytes(field_number, wire_type)
            return function (write, value)
                write(tag_bytes)
                struct_pack(write, format, value)
            end
        end

    end
end

Int32Encoder = _SimpleEncoder(wire_format.WIRETYPE_VARINT, _EncodeSignedVarint, _SignedVarintSize)
Int64Encoder = Int32Encoder
EnumEncoder = Int32Encoder

UInt32Encoder = _SimpleEncoder(wire_format.WIRETYPE_VARINT, _EncodeVarint, _VarintSize)
UInt64Encoder = UInt32Encoder

SInt32Encoder = _ModifiedEncoder(
    wire_format.WIRETYPE_VARINT, _EncodeVarint, _VarintSize,
    wire_format.ZigZagEncode32)

SInt64Encoder = _ModifiedEncoder(
    wire_format.WIRETYPE_VARINT, _EncodeVarint, _VarintSize,
    wire_format.ZigZagEncode64)

Fixed32Encoder  = _StructPackEncoder(wire_format.WIRETYPE_FIXED32, 4, string.byte('I'))
Fixed64Encoder  = _StructPackEncoder(wire_format.WIRETYPE_FIXED64, 8, string.byte('Q'))
SFixed32Encoder = _StructPackEncoder(wire_format.WIRETYPE_FIXED32, 4, string.byte('i'))
SFixed64Encoder = _StructPackEncoder(wire_format.WIRETYPE_FIXED64, 8, string.byte('q'))
FloatEncoder    = _StructPackEncoder(wire_format.WIRETYPE_FIXED32, 4, string.byte('f'))
DoubleEncoder   = _StructPackEncoder(wire_format.WIRETYPE_FIXED64, 8, string.byte('d'))


function BoolEncoder(field_number, is_repeated, is_packed)
    local false_byte = '\0'
    local true_byte = '\1'
    if is_packed then
        local tag_bytes = TagBytes(field_number, wire_format.WIRETYPE_LENGTH_DELIMITED)
        local EncodeVarint = _EncodeVarint
        return function (write, value)
            write(tag_bytes)
            EncodeVarint(write, #value)
            for _, element in ipairs(value) do
                if element then
                    write(true_byte)
                else
                    write(false_byte)
                end
            end
        end
    elseif is_repeated then
        local tag_bytes = TagBytes(field_number, wire_format.WIRETYPE_VARINT)
        return function(write, value)
            for _, element in ipairs(value) do
                write(tag_bytes)
                if element then
                    write(true_byte)
                else
                    write(false_byte)
                end
            end
        end
    else
        local tag_bytes = TagBytes(field_number, wire_format.WIRETYPE_VARINT)
        return function (write, value)
            write(tag_bytes)
            if value then
                return write(true_byte)
            end
            return write(false_byte)
        end
    end
end

function StringEncoder(field_number, is_repeated, is_packed)
    local tag = TagBytes(field_number, wire_format.WIRETYPE_LENGTH_DELIMITED)
    local EncodeVarint = _EncodeVarint
    assert(not is_packed)
    if is_repeated then
        return function (write, value)
            for _, element in ipairs(value) do
--                encoded = element.encode('utf-8')
                write(tag)
                EncodeVarint(write, #element)
                write(element)
            end
        end
    else
        return function (write, value)
--            local encoded = value.encode('utf-8')
            write(tag)
            EncodeVarint(write, #value)
            return write(value)
        end
    end
end

function BytesEncoder(field_number, is_repeated, is_packed)
    local tag = TagBytes(field_number, wire_format.WIRETYPE_LENGTH_DELIMITED)
    local EncodeVarint = _EncodeVarint
    assert(not is_packed)
    if is_repeated then
        return function (write, value)
            for _, element in ipairs(value) do
                write(tag)
                EncodeVarint(write, #element)
                write(element)
            end
        end
    else
        return function(write, value)
            write(tag)
            EncodeVarint(write, #value)
            return write(value)
        end
    end
end


function MessageEncoder(field_number, is_repeated, is_packed)
    local tag = TagBytes(field_number, wire_format.WIRETYPE_LENGTH_DELIMITED)
    local EncodeVarint = _EncodeVarint
    assert(not is_packed)
    if is_repeated then
        return function(write, value)
            for _, element in ipairs(value) do
                write(tag)
                EncodeVarint(write, element:ByteSize())
                element:_InternalSerialize(write)
            end
        end
    else
        return function (write, value)
            write(tag)
            EncodeVarint(write, value:ByteSize())
            return value:_InternalSerialize(write)
        end
    end
end

