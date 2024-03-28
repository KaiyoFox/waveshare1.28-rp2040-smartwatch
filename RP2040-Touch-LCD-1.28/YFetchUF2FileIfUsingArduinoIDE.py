import os
import time
import shutil
import time

def read_new_uf2(file_path):
    try:
        # Check if the file exists and its size is greater than 100 bytes
        if os.path.exists(file_path) and os.path.getsize(file_path) > 100:
            # Read the contents of the file
            with open(file_path, 'rb') as file:
                file_contents = file.read()
                print(file_contents)
                print(f"Contents of {file_path}:\n{file_contents.hex()}")
            time.sleep(5)
        else:
            print(f"{file_path} either doesn't exist or its size is less than or equal to 100 bytes.")
            time.sleep(0.1)
    except Exception as e:
        print(f"An error occurred: {e}")
        time.sleep(0.1)

def copy_new_uf2(file_path, destination_path):
    try:
        # Check if the file exists and its size is greater than 100 bytes
        if os.path.exists(file_path) and os.path.getsize(file_path) > 100:
            # Construct the destination path
            destination_file_path = os.path.join(destination_path, os.path.basename(file_path))

            # Copy the file to the specified destination
            shutil.copy2(file_path, destination_file_path)

            print(int(time.time()/10),f"File successfully copied to: {destination_file_path}")
            time.sleep(5)
        else:
            #print(f"{file_path} either doesn't exist or its size is less than or equal to 100 bytes.")
            time.sleep(0.1)
    except Exception as e:
        print(f"An error occurred: {e}")
        time.sleep(0.1)



# Specify the path to the file on the F:\ drive
file_path = r"G:\NEW.UF2"
destination_path = r".\UF2"

# Call the function to read and print the file contents
while True:
    copy_new_uf2(file_path, destination_path)
    #read_new_uf2(file_path)
    time.sleep(0.1)
