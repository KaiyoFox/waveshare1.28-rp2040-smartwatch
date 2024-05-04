import pygame
import sys
import subprocess
import os
import easygui
import cv2
import math
from PIL import Image, ImageDraw
import numpy as np

# Initialize Pygame
pygame.init()

# Constants
WIDTH, HEIGHT = 240, 240
FPS = 60
MAX_THICKNESS = 8

# Create the screen
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Icon Creator")

# Variables
rectangles = []
selected_rectangle = None
offset_x = 0
offset_y = 0
ox=0
oy=0
exported = False
color_index = 0

text_input = ""
input_rect = pygame.Rect(10, 10, 220, 30)
input_active = False

# Function to handle text input
def handle_input_events(event):
    global text_input, input_active
    if event.type == pygame.MOUSEBUTTONDOWN:
        if input_rect.collidepoint(event.pos):
            input_active = not input_active
        else:
            input_active = False
    if event.type == pygame.KEYDOWN:
        if input_active:
            if event.key == pygame.K_RETURN:
                input_active = False
                return text_input
            elif event.key == pygame.K_BACKSPACE:
                text_input = text_input[:-1]
            else:
                text_input += event.unicode
    return None

# Function to draw text input box
def draw_text_input():
    global text_input
    pygame.draw.rect(screen, (0,0,0), input_rect)
    font = pygame.font.Font(None, 24)
    try:
        text_surface = font.render(text_input, True, (255,255,255))
    except:
        text_input=""
        return
    screen.blit(text_surface, (input_rect.x + 5, input_rect.y + 5))
    pygame.draw.rect(screen, (255,255,255), input_rect, 2)



#8.22580645161
COLORS = {
    (255, 255, 255): "WHITE",
    (0, 0, 0): "BLACK",
    (0, 0, 255): "BLUE",
    (255, 0, 255): "BRED",
    (255, 255, 0): "GRED",
    (0, 255, 255): "GBLUE",
    (255, 0, 0): "RED",
    (254, 0, 254): "MAGENTA",
    (255, 190, 255): "PINK",
    (0, 255, 0): "GREEN",
    (123, 255, 255): "CYAN",
    (254, 254, 0): "YELLOW",
    (255, 239, 82): "GOOD_YELLOW",
    (189, 138, 0): "BROWN",
    (255, 130, 58): "BRRED",
    (132, 134, 132): "GRAY",
    (58, 57, 58): "DARKGRAY",
    (189, 186, 189): "LIGHT_GRAY",
    (255, 142, 0): "ORANGE",
    (181, 182, 239): "LIGHTPURPLE",
    (181, 210, 239): "LIGHTBLUE",
    (165, 0, 214): "PURPLE",
    (0, 117, 214): "SKYBLUE",
    (173, 255, 0): "LIMEY",
}
'''
    (0, 255, 140): "AQUAGREEN",
    (0, 85, 49): "DARKGREEN",
    (0, 162, 90): "MIDGREEN",
    (58, 158, 115): "IJUSTWWANTGRASS",
    (74, 134, 74): "IGIVEUP",
    (66, 28, 41): "MAROON",
    (148, 77, 165): "BRIGHTPURPLE",
    (247, 198, 189): "PEACH",
    (189, 125, 107):  "LIGHTBROWN",
    (74, 45, 25): "DARKBROWN",
    (197, 134, 123): "REDTAN",
    (247, 215, 214): "TAN",
    (255, 243, 181): "FRIEDYELLOW",
    (247, 215, 148): "YELLOWORANGE",
    (181, 178, 181): "PAPERGRAY",
    (230, 53, 140): "HOTPINK",
}
'''

fontSizes=[8,12,16,20,24]

# Function to draw rectangles
def draw_rectangles():
    for text in rectangles:
        if(text['type']=='text'):
            rectangles.remove(text)
            rectangles.append(text)
    for rect in rectangles:
        if(rect['type']=='rect'):
            if rect['thickness']==1:
                pygame.draw.rect(screen, rect['color'], rect['rect'])
            else:
                pygame.draw.rect(screen, rect['color'], rect['rect'], rect['thickness'])
        else:
            fontSiz=fontSizes[rect['fontSize']]
            font = pygame.font.Font(None, int(fontSiz*1.5))
            text_surface = font.render(rect['text'], False, rect['color'])  # Temporary text color
            temp_surface = pygame.Surface((text_surface.get_size()[0]+11,text_surface.get_size()[1]))
            for rect_ in rectangles:
                if rect_['type'] == 'rect' and rect_['rect'].collidepoint(rect['rect'].topleft):
                    temp_surface.fill(rect_['color'])
            temp_surface.blit(text_surface, (11, 0))
            screen.blit(temp_surface, (rect['rect'].x,rect['rect'].y))

# Function to export the icon
def export_iconOld():
    global exported
    with open("Icon.code", "w") as file:
        for rect in rectangles:
            x1, y1, width, height = rect['rect']
            if(x1>240):
                x1=240
            if(x1<0):
                x1=0
            width=min(240,x1+width)-x1
            if(y1>240):
                y1=240
            if(y1<0):
                y1=0
            height=min(240,y1+height)-y1

            if(width>0 and height>0):
                if(rect['type']=='rect'):
                    color_name = "BLACK"
                    for key, value in COLORS.items():
                        if rect['color'] == key:
                            color_name = value
                            break
                    if rect['thickness'] == 1:
                        draw_style = "DRAW_FILL_FULL"
                    else:
                        draw_style = "DRAW_FILL_EMPTY"
                    file.write(f"Paint_DrawRectangle({x1}, {y1}, {x1 + width}, {y1 + height}, {color_name}, DOT_PIXEL_{rect['thickness']}X{rect['thickness']}, {draw_style});\n")
                else:
                    text=rect['text']
                    backgroundColor='BLACK'
                    for rect_ in rectangles:
                        if rect_['type'] == 'rect' and rect_['rect'].collidepoint(rect['rect'].topleft):
                            for key, value in COLORS.items():
                                if rect_['color'] == key:
                                    backgroundColor=value
                    foregroundColor = "BLACK"
                    for key, value in COLORS.items():
                        if rect['color'] == key:
                            foregroundColor = value
                            break
                    fontSize=fontSizes[rect['fontSize']]
                    file.write(f'Paint_DrawString_EN({x1}, {y1}, "{text}", &Font{fontSize}, {backgroundColor}, {foregroundColor});\n')
        if not exported:
            subprocess.Popen(['notepad.exe', 'Icon.code'])
            exported = True


def distance(x, y):
    return math.sqrt((x - 120) ** 2 + (y - 120) ** 2)

def intersects_circle(x1, y1, width, height):
    x2 = x1 + width
    y2 = y1 + height
    return (x1 < 120 + 120 and x2 > 120 - 120 and y1 < 120 + 120 and y2 > 120 - 120)

# Function to export the icon
def export_icon():
    global exported
    with open("Icon.code", "w") as file:
        for rect in rectangles:
            x1, y1, width, height = rect['rect']
            x1 = max(0, min(240, x1))
            y1 = max(0, min(240, y1))
            width = max(0, min(240 - x1, width))
            height = max(0, min(240 - y1, height))

            if width > 0 and height > 0:
                if rect['type'] == 'rect':
                    color_name = COLORS.get(rect['color'], "BLACK")
                    draw_style = "DRAW_FILL_FULL" if rect['thickness'] == 1 else "DRAW_FILL_EMPTY"
                    file.write(f"Paint_DrawRectangle({x1}, {y1}, {x1 + width}, {y1 + height}, {color_name}, DOT_PIXEL_{rect['thickness']}X{rect['thickness']}, {draw_style});\n")# // {rect}
                else:
                    text = rect['text']
                    background_color = 'BLACK'
                    for rect_ in rectangles:
                        if rect_['type'] == 'rect' and rect_['rect'].collidepoint(rect['rect'].topleft):
                            background_color = COLORS.get(rect_['color'], 'BLACK')
                            break
                    foreground_color = COLORS.get(rect['color'], 'BLACK')
                    font_size = fontSizes[rect['fontSize']]
                    file.write(f'Paint_DrawString_EN({x1}, {y1}, "{text}", &Font{font_size}, {background_color}, {foreground_color});\n')# // {rect}
    if not exported:
        subprocess.Popen(['notepad.exe', 'Icon.code'])
        exported = True

def export_icon_image():
    global exported
    image=[]
    with open("Icon.code", "w") as file:
        tRectang=rectangles.copy()
        for rect in tRectang:
            x1, y1, width, height = rect['rect']
            x1 = max(0, min(240, x1))
            y1 = max(0, min(240, y1))
            width = max(0, min(240 - x1, width))
            height = max(0, min(240 - y1, height))

            #if width > 0 and height > 0 and intersects_circle(x1, y1, width, height):
            if width > 0 and height > 0:
                if rect['type'] == 'rect':
                    color_name = COLORS.get(rect['color'], "BLACK")
                    if('0x' not in color_name):
                        color_name = convRgb(rect['color'])
                    image.extend([str(x1), str(y1), str(x1 + width), str(y1 + height), color_name])
                    draw_style = "DRAW_FILL_FULL" if rect['thickness'] == 1 else "DRAW_FILL_EMPTY"
                    #file.write(f"Paint_DrawRectangle({x1}, {y1}, {x1 + width}, {y1 + height}, {color_name}, DOT_PIXEL_{rect['thickness']}X{rect['thickness']}, {draw_style});\n")
            else:
                rectangles.remove(rect)
        print(len(image))
        file.write('std::list<uint16_t> image = {\n')
        file.write(', '.join(image))
        file.write('\n};\n')
    if not exported:
        subprocess.Popen(['notepad.exe', 'Icon.code'])
        exported = True

def closest_colorBEST(rgb_value):
    rgb_value=(int(int(rgb_value[0]/5)*5),int(int(rgb_value[1]/5)*5),int(int(rgb_value[2]/5)*5))
    #print(rgb_value)
    min_dist = float('inf')
    closest_color_rgb = None

    for color, _ in COLORS.items():
        dist = math.sqrt(sum((c1 - c2) ** 2 for c1, c2 in zip(rgb_value, color)))
        if dist < min_dist:
            min_dist = dist
            closest_color_rgb = color
    return closest_color_rgb

def closest_colorA(rgb_value):
    rgb_value=(int(int(rgb_value[0]/5)*5),int(int(rgb_value[1]/5)*5),int(int(rgb_value[2]/5)*5))
    color=rgb_value
    lowest={'d':99999999,'val':None}
    for fro in COLORS.items():
        fro=fro[0]
        d=math.sqrt(((color[0]-fro[0])**2)+((color[1]-fro[1])**2)+((color[2]-fro[2])**2))
        if(d<lowest['d']):
            lowest={'d':d,'val':fro}
    return lowest['val']


def convRgb(rgb):
    red, green, blue = rgb
    r = (red >> 3) & 0x1F
    g = (green >> 2) & 0x3F
    b = (blue >> 3) & 0x1F
    rgb565 = (r << 11) | (g << 5) | b
    rgb565_hex = hex(rgb565)
    return rgb565_hex

def closest_color(rgb_value,colorChunk=5):
    global COLORS
    rgb_value=(int(rgb_value[0] / colorChunk) * colorChunk,
               int(rgb_value[1] / colorChunk) * colorChunk,
               int(rgb_value[2] / colorChunk) * colorChunk)
    if(rgb_value not in list(COLORS)):
        con=convRgb(rgb_value)
        COLORS[rgb_value]=str(con)
    return rgb_value


def create_rectangles_from_image_color(img_path,size=14,colorChunk=5):
    global rectangles
    imageE = Image.open(img_path)
    
    # Calculate the scale factor to fit within 240x240 while maintaining aspect ratio
    width, height = imageE.size
    max_size = 240
    scale = min(max_size / width, max_size / height)
    
    # Resize the image
    new_width = int(width * scale)
    new_height = int(height * scale)
    #imageE.thumbnail((new_width, new_height))
    imageE = imageE.resize((new_width, new_height), resample=Image.LANCZOS)
    
    groupId=len(rectangles)
    
    #size=10
    if(size<1):
        size=1
    
    width, height = imageE.size
    pixels = imageE.load()
    
    num=0
    x=0
    y=0
    lenX=0
    startX=-1
    lastColor=closest_color(pixels[x,y])
    for y in range(0,height,size):
        lenX = 0
        for x in range(0,width,size):
            theColor = closest_color(pixels[x, y],colorChunk=colorChunk)
            if theColor == lastColor:
                try:
                    if pixels[x, y][3] == 255:
                        lenX += size
                        if startX == -1:
                            startX = x
                except IndexError:
                    lenX += size
                    if startX == -1:
                        startX = x
                        #print('x',startX)
            else:
                lastColor=theColor
                #if(lenX>0):
                if(startX==-1):
                    startX=x
                try:
                    rectangles.append({'rect': pygame.Rect(startX, y, lenX+size, size), 'color': closest_color(pixels[startX,y],colorChunk), 'thickness': 1, 'fill': True,'group': groupId, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect', 'img':img_path,'InColor':True,'colorMode':colorChunk,'qualMode':size})
                except:
                    rectangles.append({'rect': pygame.Rect(startX, y, lenX+size, size), 'color': closest_color(pixels[startX-size,y],colorChunk), 'thickness': 1, 'fill': True,'group': groupId, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect','img':img_path,'InColor':True,'colorMode':colorChunk,'qualMode':size})
                num+=1
                x+=lenX
                lenX=0
                startX=-1
            #lastColor=theColor
            ##x+=size
        if(lenX>0):
            if(startX==-1):
                startX=x
            try:
                rectangles.append({'rect': pygame.Rect(startX, y, lenX+size, size), 'color': closest_color(pixels[startX,y],colorChunk), 'thickness': 1, 'fill': True,'group': groupId, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect','img':img_path,'InColor':True,'colorMode':colorChunk,'qualMode':size})
            except:
                rectangles.append({'rect': pygame.Rect(startX, y, lenX+size, size), 'color': closest_color(pixels[startX-size,y],colorChunk), 'thickness': 1, 'fill': True,'group': groupId, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect','img':img_path,'InColor':True,'colorMode':colorChunk,'qualMode':size})
            num+=1
            lenX=0
            startX=-1
        else:
            lenX=0
            startX=-1
        #y+=size
        #x=0
        #startX=-1
    print('Number of Rectangles:',num)
    

def create_rectangles_from_image(img_path,size=14):
    global rectangles
    imageE = Image.open(img_path)
    
    # Calculate the scale factor to fit within 240x240 while maintaining aspect ratio
    width, height = imageE.size
    max_size = 240
    scale = min(max_size / width, max_size / height)
    
    # Resize the image
    new_width = int(width * scale)
    new_height = int(height * scale)
    #imageE.thumbnail((new_width, new_height))
    imageE = imageE.resize((new_width, new_height), resample=Image.LANCZOS)
    
    groupId=len(rectangles)
    
    #size=1
    if(size<1):
        size=1
    
    width, height = imageE.size
    pixels = imageE.load()
    
    num=0
    x=0
    y=0
    lenX=0
    startX=-1
    while(y<height):
        while(x<width):
            #print(pixels[x, y],lenX)
            if (pixels[x, y][0]+pixels[x, y][1]+pixels[x, y][2])/3 < 100:
                try:
                    if(pixels[x, y][3]==255):
                        lenX+=size
                        if(startX==-1):
                            startX=x
                except:
                    lenX+=size
                    if(startX==-1):
                        startX=x
            else:
                if(lenX>2):
                    
                    rectangles.append({'rect': pygame.Rect(startX, y, lenX, size), 'color': (0,0,0), 'thickness': 1, 'fill': True,'group': groupId, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect','img':img_path,'InColor':False,'qualMode':size})
                    num+=1
                    lenX=0
                    startX=-1
                else:
                    lenX=0
                    startX=-1
            x+=size
        if(lenX>2):
            rectangles.append({'rect': pygame.Rect(startX, y, lenX, size), 'color': (0,0,0), 'thickness': 1, 'fill': True, 'group': groupId, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect','img':img_path,'InColor':False,'qualMode':size})
            num+=1
            lenX=0
            startX=-1
        else:
            lenX=0
            startX=-1
        y+=size
        x=0
        startX=-1


    
    #second pass
    x=0
    y=0
    lenX=0
    startX=-1
    while(y<height):
        while(x<width):
            #print(pixels[x, y],lenX)
            if (pixels[x, y][0]+pixels[x, y][1]+pixels[x, y][2])/3 < 135 and (pixels[x, y][0]+pixels[x, y][1]+pixels[x, y][2])/3 >= 100:
                try:
                    if(pixels[x, y][3]==255):
                        lenX+=size
                        if(startX==-1):
                            startX=x
                except:
                    lenX+=size
                    if(startX==-1):
                        startX=x
            else:
                if(lenX>2):
                    rectangles.append({'rect': pygame.Rect(startX, y, lenX, size), 'color': (58, 57, 58), 'thickness': 1, 'fill': True,'group': groupId, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect','img':img_path,'InColor':False,'qualMode':size})
                    num+=1
                    lenX=0
                    startX=-1
                else:
                    lenX=0
                    startX=-1
            x+=size
        if(lenX>2):
            rectangles.append({'rect': pygame.Rect(startX, y, lenX, size), 'color': (58, 57, 58), 'thickness': 1, 'fill': True, 'group': groupId, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect','img':img_path,'InColor':False,'qualMode':size})
            num+=1
            lenX=0
            startX=-1
        else:
            lenX=0
            startX=-1
        y+=size
        x=0
        startX=-1
    
    print('Number of Rectangles:',num)
    

# Main loop
clock = pygame.time.Clock()
running = True

radius = min(WIDTH, HEIGHT) // 2
center = (WIDTH // 2, HEIGHT // 2)

typing=False
rectangleToResize=None
AEtriggered=False
resizeToValue=0
while running:
    screen.fill((20,20,20))
    draw_rectangles()

    for event in pygame.event.get():
        if(typing):
            input_text = handle_input_events(event)
            if(input_text!=None):
                typing=False
                tt=input_text
                fontSiz=fontSizes[4]
                font = pygame.font.Font(None, int(fontSiz*1.5))
                text_surface = font.render(tt, True, (0,0,0))
                text = {'rect': pygame.Rect(120, 120, text_surface.get_size()[0]+11, text_surface.get_size()[1]), 'color': (255,255,255), 'thickness': 1, 'fill': True, 'group': None, 'ogCords': pygame.Rect(0,0,0,0),'text':tt,'fontSize':4,'type':'text'}
                rectangles.append(text)
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:  # Left mouse button
                exported = False
                for rect in reversed(rectangles):
                    if rect['rect'].collidepoint(event.pos):
                        selected_rectangle = rect
                        offset_x = event.pos[0] - rect['rect'].x
                        offset_y = event.pos[1] - rect['rect'].y
                        if(selected_rectangle['group']!=None):
                            ox=event.pos[0]
                            oy=event.pos[1]
                            for rectE in rectangles:
                                if(rectE['group']==selected_rectangle['group']):
                                    rectE['ogCords'].x = rectE['rect'].x
                                    rectE['ogCords'].y = rectE['rect'].y
                        #rectangles.remove(rect)
                        #rectangles.append(rect)
                        break
                #else:
                #    rect = {'rect': pygame.Rect(event.pos[0], event.pos[1], 50, 50), 'color': (0,0,0), 'thickness': 1, 'fill': True, 'group': None, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect'}
                #    rectangles.append(rect)
            elif event.button == 4:  # Mouse wheel up
                exported = False
                if selected_rectangle:
                    if pygame.key.get_mods() & pygame.KMOD_SHIFT:
                        color_index = (color_index + 1) % len(COLORS)



                        if(selected_rectangle['group']!=None):
                            if(selected_rectangle['InColor']==True):
                                #tRectang=rectangles.copy()
                                #for rect in tRectang:
                                #    if(rect['group']==selected_rectangle['group']):
                                #        rectangles.remove(rect)
                                selected_rectangle['colorMode']=min(255,selected_rectangle['colorMode']+1)
                                rectangleToResize=selected_rectangle
                                AEtriggered=True
                                resizeToValue=-1
                                #create_rectangles_from_image_color(rect['img'],size=selected_rectangle['qualMode'],colorChunk=selected_rectangle['colorMode'])
                            else:
                                for rect in rectangles:
                                    if(rect['group']==selected_rectangle['group']):
                                        rect['color'] = list(COLORS)[color_index]





                                        
                        else:
                            selected_rectangle['color'] = list(COLORS)[color_index]
                    else:
                        if(selected_rectangle['type']=='rect'):
                            if(selected_rectangle['group']==None):
                                if selected_rectangle['thickness'] < MAX_THICKNESS:
                                    selected_rectangle['thickness'] += 1
                        else:
                            if(selected_rectangle['fontSize']<len(fontSizes)-1):
                                selected_rectangle['fontSize']+=1

                                fontSiz=fontSizes[selected_rectangle['fontSize']]
                                font = pygame.font.Font(None, int(fontSiz*1.5))
                                text_surface = font.render(selected_rectangle['text'], True, (0,0,0))
                                selected_rectangle['rect'].w=text_surface.get_size()[0]
                                selected_rectangle['rect'].h=text_surface.get_size()[1]
                                
            elif event.button == 5:  # Mouse wheel down
                exported = False
                if selected_rectangle:
                    if pygame.key.get_mods() & pygame.KMOD_SHIFT:
                        color_index = (color_index - 1) % len(COLORS)
                        if(selected_rectangle['group']!=None):
                            if(selected_rectangle['InColor']==True):
                                #tRectang=rectangles.copy()
                                #for rect in tRectang:
                                #    if(rect['group']==selected_rectangle['group']):
                                #        rectangles.remove(rect)
                                selected_rectangle['colorMode']=max(1,selected_rectangle['colorMode']-1)
                                rectangleToResize=selected_rectangle
                                AEtriggered=True
                                resizeToValue=-1


                                #create_rectangles_from_image_color(rect['img'],selected_rectangle['qualMode'],selected_rectangle['colorMode'])
                            else:
                                for rect in rectangles:
                                    if(rect['group']==selected_rectangle['group']):
                                        rect['color'] = list(COLORS)[color_index]
                        else:
                            selected_rectangle['color'] = list(COLORS)[color_index]
                    else:
                        if(selected_rectangle['type']=='rect'):
                            if(selected_rectangle['group']==None):
                                selected_rectangle['thickness'] = max(1, selected_rectangle['thickness'] - 1)
                        else:
                            if(selected_rectangle['fontSize']>0):
                                selected_rectangle['fontSize']-=1

                                fontSiz=fontSizes[selected_rectangle['fontSize']]
                                font = pygame.font.Font(None, int(fontSiz*1.5))
                                text_surface = font.render(selected_rectangle['text'], True, (0,0,0))
                                selected_rectangle['rect'].w=text_surface.get_size()[0]+11
                                selected_rectangle['rect'].h=text_surface.get_size()[1]
                                
        elif event.type == pygame.MOUSEBUTTONUP:
            if event.button == 1:  # Left mouse button
                selected_rectangle = None
        elif event.type == pygame.MOUSEMOTION:
            exported = False
            if selected_rectangle:
                if pygame.key.get_mods() & pygame.KMOD_CTRL and pygame.key.get_mods() & pygame.KMOD_SHIFT:
                    # Scale the rectangle proportionally
                    if(selected_rectangle['group']==None and selected_rectangle['type']!='text'):
                        selected_rectangle['rect'].width = max(0, min(event.pos[0], 240) - selected_rectangle['rect'].x)
                        selected_rectangle['rect'].height = max(0, min(event.pos[1], 240) - selected_rectangle['rect'].y) #max(0, min(
                    elif(selected_rectangle['group']!=None):
                        rectangleToResize=selected_rectangle
                        AEtriggered=True
                        resizeToValue=int(event.pos[0]/(240/14))+1


                        '''
                        tRectang=rectangles.copy()
                        for rect in tRectang:
                            if(rect['group']==selected_rectangle['group']):
                                rectangles.remove(rect)
                        if(rect['InColor']):
                            create_rectangles_from_image_color(rect['img'],int(event.pos[0]/(240/9))+1)
                        else:
                            create_rectangles_from_image(rect['img'],int(event.pos[0]/(240/9))+1)
                        '''
                            
                elif(not pygame.key.get_mods() & pygame.KMOD_SHIFT):
                    # Update the position of the rectangle, ensuring it stays within bounds
                    if(selected_rectangle['group']!=None):
                            for rect in rectangles:
                                if(rect['group']==selected_rectangle['group']):
                                    rect['rect'].x = event.pos[0] - (ox - rect['ogCords'].x)#, 240 - selected_rectangle['rect'].width))
                                    rect['rect'].y = event.pos[1] - (oy - rect['ogCords'].y)#, 240 - selected_rectangle['rect'].height))
                    else:
                        selected_rectangle['rect'].x = event.pos[0] - offset_x#, 240 - selected_rectangle['rect'].width))
                        selected_rectangle['rect'].y = event.pos[1] - offset_y#, 240 - selected_rectangle['rect'].height))#at start max(0, min(
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                exported = False
                rectangles.clear()
            elif event.key == pygame.K_t and pygame.key.get_mods() & pygame.KMOD_CTRL:
                rect = {'rect': pygame.Rect(120, 120, 50, 50), 'color': (0,0,0), 'thickness': 1, 'fill': True, 'group': None, 'ogCords': pygame.Rect(0,0,0,0),'type':'rect'}
                rectangles.append(rect)
            elif event.key == pygame.K_e and pygame.key.get_mods() & pygame.KMOD_CTRL:
                export_icon()
                exported = True
            elif event.key == pygame.K_i and pygame.key.get_mods() & pygame.KMOD_CTRL:
                export_icon_image()
                exported = True
            
            elif event.key == pygame.K_y and pygame.key.get_mods() & pygame.KMOD_CTRL:
                typing=True
                input_active=True
                text_input=True
                #tt=input('text: ')
                #fontSiz=fontSizes[4]
                #font = pygame.font.Font(None, int(fontSiz*1.5))
                #text_surface = font.render(tt, True, (0,0,0))
                #text = {'rect': pygame.Rect(120, 120, text_surface.get_size()[0]+11, text_surface.get_size()[1]), 'color': (255,255,255), 'thickness': 1, 'fill': True, 'group': None, 'ogCords': pygame.Rect(0,0,0,0),'text':tt,'fontSize':4,'type':'text'}
                #rectangles.append(text)
            elif event.key == pygame.K_c and pygame.key.get_mods() & pygame.KMOD_CTRL:
                # Open file selector
                try:
                    create_rectangles_from_image_color(easygui.fileopenbox('Open file','Select File to convert to Rectangles in Color'))
                except:
                    print('Image Err')
            elif event.key == pygame.K_o and pygame.key.get_mods() & pygame.KMOD_CTRL:
                # Open file selector
                try:
                    create_rectangles_from_image(easygui.fileopenbox('Open file','Select File to convert to Rectangles'))
                except:
                    print('Image Err')
            elif event.key == pygame.K_BACKSPACE:
                if selected_rectangle:
                    if(selected_rectangle['group']!=None):
                        tRectang=rectangles.copy()
                        for rect in tRectang:
                            if(rect['group']==selected_rectangle['group']):
                                rectangles.remove(rect)
                    else:
                        rectangles.remove(selected_rectangle)
                    selected_rectangle = None
            if selected_rectangle:
                if event.key == pygame.K_KP_PLUS:  # Plus key
                    # Move the rectangle to a higher layer (lower index in the list)
                    index = rectangles.index(selected_rectangle)
                    if(selected_rectangle['group']!=None):
                        tRectang=rectangles.copy()
                        for rect in tRectang[::-1]:
                            if(rect['group']==selected_rectangle['group']):
                                if index > 0:
                                    rectangles.remove(rect)#index - 1
                                    rectangles.insert(0, rect)
                    else:
                        if index > 0:
                            rectangles.remove(selected_rectangle)#index - 1
                            rectangles.insert(0, selected_rectangle)
                elif event.key == pygame.K_KP_MINUS:  # Minus key
                    # Move the rectangle to a lower layer (higher index in the list)
                    index = rectangles.index(selected_rectangle)
                    if(selected_rectangle['group']!=None):
                        tRectang=rectangles.copy()
                        for rect in tRectang:
                            if(rect['group']==selected_rectangle['group']):
                                if index < len(rectangles) - 1:
                                    rectangles.remove(rect)
                                    rectangles.insert(len(rectangles), rect)
                    else:
                        if index < len(rectangles) - 1:
                            rectangles.remove(selected_rectangle)#index + 1
                            rectangles.insert(len(rectangles), selected_rectangle)
        else:
            if(selected_rectangle==None):
                AEtriggered=False
    pygame.draw.circle(screen, (120,0,120), center, radius, 5)  # 1 indicates the circle is not filled
    pygame.draw.rect(screen, (120,255,120), pygame.Rect(119,0,2,240))
    pygame.draw.rect(screen, (255,120,120), pygame.Rect(0,119,240,2))

    if(resizeToValue==0):
        resizeToValue=1
    if(AEtriggered==False):
        if(rectangleToResize!=None):
            if(resizeToValue!=-1):
                tRectang=rectangles.copy()
                for rect in tRectang:
                    if(rect['group']==rectangleToResize['group']):
                        rectangles.remove(rect)
                if(rectangleToResize['InColor']):
                    create_rectangles_from_image_color(rectangleToResize['img'],resizeToValue,colorChunk=rectangleToResize['colorMode'])
                else:
                    create_rectangles_from_image(rectangleToResize['img'],resizeToValue)
            else:
                if(rectangleToResize['InColor']):
                    tRectang=rectangles.copy()
                    for rect in tRectang:
                        if(rect['group']==rectangleToResize['group']):
                            rectangles.remove(rect)
                    create_rectangles_from_image_color(rectangleToResize['img'],rectangleToResize['qualMode'],rectangleToResize['colorMode'])
            rectangleToResize=None
    elif(AEtriggered and resizeToValue!=-1):
        pygame.draw.rect(screen, (120,255,120), pygame.Rect(0, 50, resizeToValue*(240/14), 50))
        pygame.draw.rect(screen, (120,50,120), pygame.Rect(0, 50, 240, 50), 5)
    elif(AEtriggered and resizeToValue==-1):
        fontSiz=48
        font = pygame.font.Font(None, int(fontSiz*1.5))
        text_surface = font.render(str(rectangleToResize['colorMode']), False, (255,255,120))  # Temporary text color
        screen.blit(text_surface, (rectangleToResize['rect'].x,rectangleToResize['rect'].y))

    if(typing):
        draw_text_input()
    pygame.display.flip()
    clock.tick(FPS)

pygame.quit()
sys.exit()
