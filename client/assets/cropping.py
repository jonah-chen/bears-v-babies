from PIL import Image

WIDTH = 222
HEIGHT = 318
H2 = 320

def img(x,y):
    return (x*WIDTH, y*HEIGHT, (x+1)*WIDTH, (y+1)*HEIGHT)

base_img = Image.open("all-cards.jpeg")
base_img.putalpha(192)

i2 = Image.open("cards2.png")
i2.putalpha(192)

for i in range(5):
    bear = base_img.crop(img(i,0))
    bear.save(f"BEAR/{i}.png")

for i in range(3):
    dism = base_img.crop(img(i+5,0))
    dism.save(f"DISMEMBER/{i}.png")

for i in range(2):
    wild = base_img.crop(img(i+2,1))
    wild.save(f"WILD_PROVOKE/{i}.png")

for i in range(2):
    swap = base_img.crop(img(i+4,1))
    swap.save(f"SWAP/{i}.png")

for i in range(3):
    mask = base_img.crop(img(i+6,1))
    mask.save(f"MASK/{i}.png")

for i in range(7):
    sea = base_img.crop(img(i+2,2))
    sea.save(f"SEA/{i}.png")

for i in range(8):
    lAND = base_img.crop(img(i,3))
    lAND.save(f"lAND/{i}.png")

lAND = base_img.crop(img(9,2))
lAND.save("lAND/8.png")

for i in range(7):
    sea = base_img.crop(img(i,4))
    sea.save(f"sEA/{i}.png")
for i in range(2):
    sea = base_img.crop(img(i+8,3))
    sea.save(f"sEA/{i+7}.png")

for i in range(3):
    sky = base_img.crop(img(i+7,4))
    sky.save(f"sKY/{i}.png")
for i in range(6):
    sky = base_img.crop(img(i,5))
    sky.save(f"sKY/{i+3}.png")

for i in range(4):
    land = base_img.crop(img(i+6,5))
    land.save(f"LAND/{i}.png")

for i in range(3):
    land = base_img.crop(img(i,6))
    land.save(f"LAND/{i+4}.png")

for i in range(7):
    land = base_img.crop(img(i+3,6))
    land.save(f"SKY/{i}.png")

l1, l2 = base_img.crop(img(1,9)), base_img.crop(img(2,0))
l1.save(f"LULLABY/0.png")
l2.save(f"LULLABY/1.png")

count = 0
for i in [(8,0),(8,1),(1,1),(1,0),(2,1)]:
    tool = base_img.crop(img(i[0],i[1]))
    tool.save(f"TOOL/{count}.png")
    count += 1

for i in range(2):
    hat = i2.crop(img(i,0))
    hat.save(f"HAT/{i}.png")
hat = base_img.crop(img(9,6))
hat.save("HAT/2.png")

def extract(name, coords):
    counter = 0
    for i in coords:
        im = i2.crop((i[0]*WIDTH, i[1]*H2, i[0]*WIDTH+WIDTH, i[1]*H2+HEIGHT))
        im.save(f"{name}/{counter}.png")
        counter += 1

extract("C_TORSO", [(2,0),(3,0),(4,0),(7,0),(9,0),(1,1),(3,1),(4,1),(5,1)])
extract("TORSO", [(6,0),(8,0),(0,1)])
extract("AL_BODY", [(5,0),(5,2)])
extract("M_BODY", [(8,1),(7,2),(8,2)])
extract("LEGS", [(2,1),(6,1),(7,1),(9,1),(0,2),(6,2),(9,2)])
extract("ARM", [(1,2),(2,2),(3,2),(4,2),(0,3),(1,3),(2,3),(3,3),(4,3),(5,3)])
        

bear1 = base_img.crop(img(0,0))
bear1.show()


