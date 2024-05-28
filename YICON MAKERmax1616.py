from PIL import Image
import PIL

def image_to_binary(image_path,invert):
    # Open the image
    image = Image.open(image_path)

    # Resize the image to 16x16
    image = image.resize((16, 16))#(17, 24)

    if(invert):
        image = PIL.ImageChops.invert(image)

    # Convert to grayscale
    image = image.convert('L')

    # Threshold the image (convert to black and white)
    threshold = 128
    image = image.point(lambda p: p > threshold and 255)

    # Get the pixel values
    pixels = list(image.getdata())

    # Convert pixel values to binary string
    binary_data = ''.join('1' if pixel == 0 else '0' for pixel in pixels)

    # Chunk the binary data into 16-character lines
    binary_lines = [binary_data[i:i+16] for i in range(0, len(binary_data), 16)]

    # Join the lines with newline characters
    binary_string = '\n'.join(binary_lines)

    return binary_string

# Example usage
decodeHex = input('Decode Hex?: ')
if(decodeHex=='n'):
    image_path = input('image name: ')#'ICON1616.png'#MAX SIZE as hex limit
    invert = input("invert? y/n ")
    if(invert=="y"):
        invert=True
    else:
        invert=False
    binary_representation = image_to_binary(image_path,invert)
    print(binary_representation)

    binary_data=binary_representation

    '''
    binary_data = """
    0000111111110000
    0001000000001000
    0001000000001000
    0001000000001000
    0001000000001000
    0000111111110000
    0010000110000100
    0001110110111000
    0000001111000000
    0000000110000000
    0000000110000000
    0000001001000000
    0000010000100000
    0000100000010000
    0001000000001000
    0001000000001000
    """
    '''

    # Split the binary data into lines and remove empty lines
    lines = [line.strip() for line in binary_data.strip().split('\n')]

    # Convert binary lines to hex chunks and format as desired
    hex_values = []

    for line in lines:
        for i in range(0, len(line), 8):#8 is binary stuff, skip by 8
            chunk = line[i:i+8] #8 is binary stuff
            print(chunk)
            print(int(chunk, 2))        
            print(hex(int(chunk, 2)))
            #hex_values.append(hex(int(chunk, 2)))
            hex_values.append('0x'+str(format(int(chunk, 2), '02X')))


    # Print the resulting list
    print(str(hex_values).replace("'",'').replace(' ',''))

    hex_values = [int(x, 16) for x in hex_values]
else:
    hex_values = eval(input('Hex Values: '))


icon_data=hex_values

'''icon_data = [
    0x0F, 0xF0,
    0x10, 0x08,
    0x10, 0x08,
    0x10, 0x08,
    0x10, 0x08,
    0x0F, 0xF0,
    0x20, 0x34,
    0x0E, 0xB8,
    0x00, 0xF0,
    0x00, 0x60,
    0x00, 0x60,
    0x01, 0x20,
    0x02, 0x40,
    0x04, 0x10,
    0x10, 0x08
]
'''

# Convert the icon data to a binary string
binary_string = ""
for byte in icon_data:
    for bit in range(7, -1, -1):
        toAdd=str((byte >> bit) & 1)
        if(toAdd=='0'):
            toAdd=' '
        else:
            toAdd='#'
        binary_string += str(toAdd)

print(len(icon_data))
objSize = int(input('Object Size (usually 16): '))
# Print the binary string, line wrapping at 16 characters per line
for i in range(0, len(binary_string), objSize):
    print(binary_string[i:i+objSize])


while True:
    continue
