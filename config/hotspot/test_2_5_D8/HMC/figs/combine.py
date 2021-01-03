import sys
from PIL import Image

background = Image.open("test1.png")
foreground = Image.open("test2.png")

#Image.alpha_composite(background, foreground).save("test3.png")
background.paste(foreground, (10, 10), foreground)
background.show()