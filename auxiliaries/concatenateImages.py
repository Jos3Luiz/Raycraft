#!/usr/bin/python3
from PIL import Image
import sys

if len(sys.argv) < 3:
    print("./concatenateImages dst.png img0.png img1.png ....")
    sys.exit()

dstFname=sys.argv[1]
im=Image.open(sys.argv[2])
dst = Image.new('RGBA', (im.width*(len(sys.argv)-2), im.height))
im.close()

for i in range(2,len(sys.argv)):
    im = Image.open(sys.argv[i])
    dst.paste(im,(im.width*(i-2),0))

dst.save(dstFname)
