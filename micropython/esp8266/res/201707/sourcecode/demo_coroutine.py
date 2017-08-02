import uasyncio as asyncio
							
#create event loop
loop = asyncio.get_event_loop()
c = 0					
#create coroutine
async def foo1():	
	global c
	for i in range(5):
		c = c + 1
		print("foo1: {} ".format(c))
		await asyncio.sleep(1)
		
async def foo2():	
	global c
	for i in range(10):
		c = c + 1
		print("foo2: {} ".format(c))
		await asyncio.sleep(1)

async def foo3():	
	global c
	for i in range(20):
		c = c + 1
		print("foo3: {} ".format(c))
		await asyncio.sleep(1)
				
async def main():
	global c
	while c < 20:
		await asyncio.sleep(1)						
#call coroutine									
loop.create_task(foo1())
loop.create_task(foo2())
loop.create_task(foo3())
loop.run_until_complete(main())
loop.close()	

