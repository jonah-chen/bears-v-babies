from PIL import Image, ImageDraw, ImageFont

image = Image.new("RGB", (45,80))
draw = ImageDraw.Draw(image)
# use a truetype font
font = ImageFont.load_default()

draw.text((10, 25), "world", font=font)

image.save("test.png")
