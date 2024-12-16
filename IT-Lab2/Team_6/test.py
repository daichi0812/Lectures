from matplotlib import font_manager
for font in font_manager.findSystemFonts():
    if "IPAex" in font:
        print(font)