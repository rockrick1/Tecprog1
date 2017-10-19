from __future__ import print_function
import math

class axial:
	def __init__(self):
		self.q = 0
		self.r = 0

class cube:
	def __init__(self):
		self.x = 0
		self.y = 0
		self.z = 0

def cube2axial(c):
	a = axial()
	a.q = c.x
	a.r = c.z
	return a

def axial2cube(a):
	c = cube()
	c.x = a.q
	c.z = a.r
	c.y = -c.x-c.z
	return c

def move(mapa, a, dir):
	mapa[a.r][a.q] = 0
	c = axial2cube(a)
	if (dir == 0):
		c.y+=1
		c.z-=1
	if (dir == 1):
		c.x+=1
		c.z-=1
	if (dir == 2):
		c.x+=1
		c.y-=1
	if (dir == 3):
		c.y-=1
		c.z+=1
	if (dir == 4):
		c.x-=1
		c.z+=1
	if (dir == 5):
		c.x-=1
		c.y+=1
	a = cube2axial(c)
	mapa[a.r][a.q] = 1
	return

def printMapa(m):
	for i in range(10):
		for j in range(10):
			print(str(m[i][j]) + " ", end ='')
		print() #\n
		for k in range(i + 1):
			print(" ", end = '')

a = axial()
a.r = 1
a.q = 1
mapa = []
for i in range(10):
	mapa.append([])
	for j in range(10):
		mapa[i].append(0)
mapa[1][1] = 1
move(mapa, a, 3)
printMapa(mapa)