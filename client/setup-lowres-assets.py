import os

from utils import CARD_TYPES
from PIL import Image, ImageDraw, ImageFont

folders = list(CARD_TYPES.values()) + ['lAND', 'sEA', 'sKY']
for name in folders:
    os.mkdir(os.path.join("assets", name))
    image = Image.new("RGB", (90,160))
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 22, encoding="unic")
    draw.text((10,25), name, font=font)
    for i in range(10):
        image.save(os.path.join("assets", name, str(i)+'.png'))

