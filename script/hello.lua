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
end

print("we will register callback.")
engine_register(hello)
print("we done register callback.")
