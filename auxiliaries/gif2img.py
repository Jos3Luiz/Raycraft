#!/usr/bin/python3
from PIL import Image
import sys

if len(sys.argv) < 3:
    print("./gif2img source.gif dst.gif")
    sys.exit()

sourceFname=sys.argv[1]
dstFname=sys.argv[2]

im = Image.open(sourceFname)


dst = Image.new('RGBA', (im.width*im.n_frames, im.height))

for i in range(im.n_frames):
    current = im.seek(i)
    dst.paste(im,(im.width*i,0))
dst.save(dstFname)
