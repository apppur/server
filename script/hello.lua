function hello()
  print("welcome callback, applepurle...")
  function fabi(max)
      a, b = 0, 1
      for i = 0, max do
          print(a)
          a, b = b, a+b
      end
  end
  fabi(20)
  t = {2, 3, 8, 9, 4, 5}
  table.sort(t)
  print(table.unpack(t))
end

function ping()
  print("ping ping ping...")
end

function pong()
  print("pong pong pong...")
end

engine_timer(ping)
engine_timer(pong)
engine_timer_callback();
engine_timer_callback();

print("we will register callback.")

--[[
package.cpath = "luaclib/?.so"
package.path = "lualib/?.lua"

local protobuf = require "protobuf"

--addr = io.open("../../build/addressbook.pb","rb")
addr = io.open("script/addressbook.pb","rb")
buffer = addr:read "*a"
addr:close()

protobuf.register(buffer)

t = protobuf.decode("google.protobuf.FileDescriptorSet", buffer)

proto = t.file[1]

print(proto.name)
print(proto.package)

message = proto.message_type

for _,v in ipairs(message) do
	print(v.name)
	for _,v in ipairs(v.field) do
		print("\t".. v.name .. " ["..v.number.."] " .. v.label)
	end
end

addressbook = {
	name = "Alice",
	id = 12345,
	phone = {
		{ number = "1301234567" },
		{ number = "87654321", type = "WORK" },
	}
}

code = protobuf.encode("tutorial.Person", addressbook)

decode = protobuf.decode("tutorial.Person" , code)

print(decode.name)
print(decode.id)
for _,v in ipairs(decode.phone) do
	print("\t"..v.number, v.type)
end

phonebuf = protobuf.pack("tutorial.Person.PhoneNumber number","87654321")
buffer = protobuf.pack("tutorial.Person name id phone", "Alice", 123, { phonebuf })
print(protobuf.unpack("tutorial.Person name id phone", buffer))
--]]

engine_register(hello)
print("we done register callback.")
