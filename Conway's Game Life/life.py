#Name:Shangde Han
#Conway's Game Life
import sys
import time

#return a plane
def empty_plane(x, y):
    l =[]
    for i in range(0, y+1):
        l.append((int(x)+1)*[False])
    return l
print(empty_plane(3,2))

#put a point(x,y) change to True
def seed_plane_position(plane, x, y):
    if int(x)+1 > len(plane[0][0:]) or int(y)+1 > len(plane[0:]):
        return plane
    else:
        plane[int(y)][int(x)] = True
    return plane

#change many points to True
def seed_plane(plane):
    line=sys.stdin.readline()
    while line !="" and line !="\n":
        y = int(line.split()[0])
        x = int(line.split()[1])
        seed_plane_position(plane,x,y)
        line=sys.stdin.readline()
    return plane

#change "False" to " " and changing"True"to "o"
def print_plane(plane):
    for i in range(len(plane[0:])):
        for j in range(len(plane[0][0:])):
            if plane[i][j]:
                print("o", end="")
            else:
                print(" ", end="")
        print()

#count how many neithbors near point(x,y)
def count_neighbors(plane, x, y):
    count = 0
    if x -1 >= 0 and y - 1 >= 0 and plane[y - 1][x - 1]==True:
        count+=1
    if x>=0 and y-1 >= 0 and plane[y-1][x]==True:
        count+=1
    if x+1<len(plane[0][0:]) and y-1>=0 and plane[y-1][x+1]== True:
        count+=1
    if x-1>=0 and y>=0 and plane[y][x-1]==True:
        count+=1
    if x+1<len(plane[0][0:]) and plane[y][x+1]==True:
        count+=1
    if x-1<len(plane[0][0:]) and y+1<len(plane[0:]) and plane[y+1][x-1]==True:
        count+=1
    if x>=0 and y+1<len(plane[0:]) and plane[y+1][x]==True:
        count+=1
    if x+1<len(plane[0][0:]) and y+1<len(plane[0:]) and plane[y+1][x+1]==True:
        count+=1
    return count

#decide the point(x,y) next time wehther alive or die
def run_timestep(plane):
    new = empty_plane(len(plane[0][0:]), len(plane[0:]))
    for i in range(0, len(plane[0:])):
        for j in range(0, int(len(plane[0][0:]))):
            counts = count_neighbors(plane, j, i)
            if plane[i][j]:
                if counts == 2 or counts == 3:
                    new[i][j] = True 
            else:
                if counts == 3:
                    new[i][j] = True
    return new

#run this game
def play_life():
    x = int(sys.stdin.readline())
    y = int(sys.stdin.readline())
    iteration = int(sys.stdin.readline())
    plane = empty_plane(int(x), int(y))
    seed_plane(plane)
    
    if iteration == 0:
        return ""
    elif iteration > 0:
        while iteration > 0:
            print_plane(plane)
            plane = run_timestep(plane)
            iteration -= 1
            time.sleep(0.1)
    else:
        while True:
            print_plane(plane)
            plane = run_timestep(plane)
            time.sleep(0.1)
play_life()

