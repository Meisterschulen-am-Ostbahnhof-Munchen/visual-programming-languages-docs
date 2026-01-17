import json
import os

# Configuration
file_name = 'Abkürzungen und Bedeutungen.json'
script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, file_name)

def load_json(path):
    print(f"Loading {path}...")
    with open(path, 'r', encoding='utf-8') as f:
        return json.load(f)

def save_json(path, data):
    print(f"Saving to {path}...")
    with open(path, 'w', encoding='utf-8') as f:
        # Use indent=3 to match the existing file style
        json.dump(data, f, indent=3, ensure_ascii=False)

def modify_data(data):
    """
    Place your modification logic here.
    """
    # Example: Iterating through categories
    # for category in data.get('categories', []):
    #     print(f"Processing category: {category.get('title')}")
    #     for item in category.get('data', []):
    #         # Modify item here
    #         pass
    
    return data

def main():
    if not os.path.exists(file_path):
        print(f"Error: File not found at {file_path}")
        return

    try:
        data = load_json(file_path)
        data = modify_data(data)
        save_json(file_path, data)
        print("Done.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
