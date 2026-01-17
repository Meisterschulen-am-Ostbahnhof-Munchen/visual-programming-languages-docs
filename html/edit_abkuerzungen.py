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
    base_url = "https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/de/latest/"
    
    # Helper to find category
    def find_category(cat_id):
        for cat in data.get('categories', []):
            if cat.get('id') == cat_id:
                return cat
        return None

    # Helper to find item in category
    def find_item(category, term):
        for item in category.get('data', []):
            if item.get('term') == term:
                return item
        return None

    # 1. Update BOOL in cat_types
    cat_types = find_category('cat_types')
    if cat_types:
        item_bool = find_item(cat_types, 'BOOL')
        if item_bool:
            print("Updating BOOL...")
            item_bool['mean'] = "Datentyp (1 Bit), FALSE/TRUE"
            item_bool['title'] = "Boolesche Variable"
            item_bool['link_int'] = f'<a href="{base_url}Allgemeines/Datentypen/BOOL/BOOL_Detail.html" target="_blank">BOOL Detail</a>'
    
    # 2. Add or Update AX in cat_types (or where appropriate)
    # Using cat_types for generic Adapter type AX
    if cat_types:
        item_ax = find_item(cat_types, 'AX')
        if not item_ax:
            print("Adding AX...")
            new_ax = {
                "nr": "",
                "term": "AX",
                "mean": "Adapter Interface (1 Event, 1 Bool)",
                "ex": "Uebung_001_AX",
                "exdoc": "",
                "link_int": f'<a href="{base_url}Bibliotheken/ExternalLibraries/adapter/types/unidirectional/BOOL/AX.html" target="_blank">AX</a>',
                "vid": "",
                "ext_de": "",
                "ext_en": "",
                "title": "Unidirectional Adapter Interface",
                "type": "adapter"
            }
            cat_types['data'].append(new_ax)
        else:
            print("Updating AX...")
            item_ax['mean'] = "Adapter Interface (1 Event, 1 Bool)"
            item_ax['ex'] = "Uebung_001_AX"
            item_ax['link_int'] = f'<a href="{base_url}Bibliotheken/ExternalLibraries/adapter/types/unidirectional/BOOL/AX.html" target="_blank">AX</a>'

    # 3. Add GET_AT_INDEX in cat_logic
    cat_logic = find_category('cat_logic')
    if cat_logic:
        item_get = find_item(cat_logic, 'GET_AT_INDEX')
        if not item_get:
            print("Adding GET_AT_INDEX...")
            new_get = {
                "nr": "",
                "term": "GET_AT_INDEX",
                "mean": "Wert aus Array an Index abrufen",
                "ex": "",
                "exdoc": "",
                "link_int": f'<a href="{base_url}Bibliotheken/StandardLibraries/convert/GET_AT_INDEX.html" target="_blank">GET_AT_INDEX</a>',
                "vid": "",
                "ext_de": "",
                "ext_en": "",
                "title": "Get value at index",
                "type": ""
            }
            cat_logic['data'].append(new_get)
        else:
            print("Updating GET_AT_INDEX...")
            item_get['link_int'] = f'<a href="{base_url}Bibliotheken/StandardLibraries/convert/GET_AT_INDEX.html" target="_blank">GET_AT_INDEX</a>'
    
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
