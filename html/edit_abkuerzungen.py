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
    dt_base_url = base_url + "Allgemeines/Datentypen/"
    
    # List of data types from the directory structure
    data_types = [
        "BOOL", "BYTE", "CHAR", "DATE", "DATE_AND_TIME", "DINT", "DWORD", "INT", 
        "LDATE", "LDT", "LINT", "LREAL", "LTIME", "LTOD", "LWORD", "REAL", 
        "SINT", "STRING", "TIME", "TIME_OF_DAY", "UDINT", "UINT", "ULINT", 
        "USINT", "WCHAR", "WORD", "WSTRING"
    ]
    
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

    cat_types = find_category('cat_types')
    if cat_types:
        for dt in data_types:
            item = find_item(cat_types, dt)
            if item:
                print(f"Updating {dt}...")
                item['link_int'] = f'<a href="{dt_base_url}{dt}/{dt}_Detail.html" target="_blank">{dt} Detail</a>'
                # Optionally update mean/title if they are generic "Datentyp"
                if item.get('mean') == "Datentyp":
                    item['mean'] = f"Standard-Datentyp {dt}"
            else:
                print(f"Adding {dt} to cat_types...")
                new_dt = {
                    "nr": "",
                    "term": dt,
                    "mean": f"Standard-Datentyp {dt}",
                    "ex": "",
                    "exdoc": "",
                    "link_int": f'<a href="{dt_base_url}{dt}/{dt}_Detail.html" target="_blank">{dt} Detail</a>',
                    "vid": "",
                    "ext_de": "",
                    "ext_en": "",
                    "title": "",
                    "type": ""
                }
                cat_types['data'].append(new_dt)

    # 2. Update AX in cat_types
    if cat_types:
        item_ax = find_item(cat_types, 'AX')
        if item_ax:
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
