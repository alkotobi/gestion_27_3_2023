try:
    with open('main.py', 'r', encoding='utf-8') as file:
        contents = file.read()
        if contents:
            print(contents)
        else:
            print("File is empty.")
except Exception as e:
    print(f"Error reading file: {e}")


