import math 

a = 0.1
b = 1
# for i in range(50): 
# 	t = 5*i*math.pi/50.0  
# 	x = (a-b)*math.cos(t) + b*math.cos((a/b-1)*t); 
# 	y = (a-b)*math.sin(t) - b*math.sin((a/b-1)*t); 
# 	print("[" + str(x) + " " + str(y) + "]")

for i in range(20): 
	t = 5*i*math.pi/20 
	x = a*(2*math.cos(t)-math.cos(2*t))
	y = a*(2*math.sin(t)-math.sin(2*t))
	print("[" + str(x) + " " + str(y) + "]")