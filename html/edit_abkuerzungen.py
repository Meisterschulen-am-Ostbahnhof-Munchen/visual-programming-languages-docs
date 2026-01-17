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
    
    # 4. Update Timers in cat_timer
    cat_timer = find_category('cat_timer')
    if cat_timer:
        timers_to_process = [
            # Cyclical (IEC 61131-3) - Adapters
            {"term": "AX_FB_TOF", "mean": "Standard Timer (Ausschaltverzögerung) mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/iec61131/timers/AX_FB_TOF.html", "title": "Off-Delay Timer (Cyclic) with Adapter", "type": "adapter", "ex": "Uebung_020e2_AX"},
            {"term": "AX_FB_TON", "mean": "Standard Timer (Einschaltverzögerung) mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/iec61131/timers/AX_FB_TON.html", "title": "On-Delay Timer (Cyclic) with Adapter", "type": "adapter", "ex": "Uebung_020c3_AX"},
            {"term": "AX_FB_TP", "mean": "Standard Timer (Impuls) mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/iec61131/timers/AX_FB_TP.html", "title": "Pulse Timer (Cyclic) with Adapter", "type": "adapter", "ex": "Uebung_020f2_AX"},
            
            # Cyclical (IEC 61131-3) - Standard
            {"term": "FB_TON", "mean": "Standard Timer (Einschaltverzögerung), zyklisch", "link": "Bibliotheken/StandardLibraries/iec61131-3/timers/FB_TON.html", "title": "On-Delay Timer (Cyclic)", "type": "", "ex": "Uebung_020c3"},
            {"term": "FB_TOF", "mean": "Standard Timer (Ausschaltverzögerung), zyklisch", "link": "Bibliotheken/StandardLibraries/iec61131-3/timers/FB_TOF.html", "title": "Off-Delay Timer (Cyclic)", "type": "", "ex": "Uebung_020e2"},
            {"term": "FB_TP", "mean": "Standard Timer (Impuls), zyklisch", "link": "Bibliotheken/StandardLibraries/iec61131-3/timers/FB_TP.html", "title": "Pulse Timer (Cyclic)", "type": "", "ex": "Uebung_020f2"},
            
            # Event-Based (IEC 61499) - Standard
            {"term": "E_PULSE", "mean": "Event-basierter Timer (Impulsformend)", "link": "Bibliotheken/StandardLibraries/events/timers/E_PULSE.html", "title": "Event-driven Pulse", "type": "event", "ex": "Uebung_020h, Uebung_020i"},
            {"term": "E_TP", "mean": "Event-basierter Timer (Puls)", "link": "Bibliotheken/StandardLibraries/events/timers/E_TP.html", "title": "Event-driven Pulse Timer", "type": "event", "ex": "Uebung_020f, Uebung_039b"},
            {"term": "E_TON", "mean": "Event-basierter Timer (Einschaltverzögerung)", "link": "Bibliotheken/StandardLibraries/events/timers/E_TON.html", "title": "Event-driven On-Delay Timer", "type": "event", "ex": "Uebung_020c, Uebung_020c2, Uebung_039b"},
            {"term": "E_TONOF", "mean": "Event-basierter Timer (Ein-/Ausschaltverzögerung)", "link": "Bibliotheken/StandardLibraries/events/timers/E_TONOF.html", "title": "Event-driven On/Off-Delay Timer", "type": "event", "ex": "Uebung_020g"},
            
            # Event-Based - Adapters
            {"term": "AX_TON", "mean": "Event-basierter Timer (Einschaltverzögerung) mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/events/unidirectional/timers/AX_TON.html", "title": "Event-driven On-Delay Timer with Adapter", "type": "adapter", "ex": "Uebung_020c_AX"},
            {"term": "AX_TONOF", "mean": "Event-basierter Timer (Ein-/Ausschaltverzögerung) mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/events/unidirectional/timers/AX_TONOF.html", "title": "Event-driven On/Off-Delay Timer with Adapter", "type": "adapter", "ex": "Uebung_020g_AX"},
            {"term": "AX_TOF", "mean": "Event-basierter Timer (Ausschaltverzögerung) mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/events/unidirectional/timers/AX_TOF.html", "title": "Event-driven Off-Delay Timer with Adapter", "type": "adapter", "ex": "Uebung_020e_AX"},
            {"term": "AX_PULSE", "mean": "Event-basierter Timer (Impuls) mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/events/unidirectional/timers/AX_PULSE.html", "title": "Event-driven Pulse Timer with Adapter", "type": "adapter", "ex": "Uebung_020h_AX, Uebung_020i_AX"}
        ]

        for timer_def in timers_to_process:
            term = timer_def["term"]
            item = find_item(cat_timer, term)
            full_link = f'{base_url}{timer_def["link"]}'
            
            if item:
                print(f"Updating Timer {term}...")
                # Update link and description if needed, preserving existing fields like 'ex' if they exist
                item['link_int'] = f'<a href="{full_link}" target="_blank">{term}</a>'
                # Only update 'mean' if it's generic or empty
                if not item.get('mean') or item.get('mean') == "Datentyp":
                     item['mean'] = timer_def["mean"]
                # Ensure type is set
                if not item.get('type'):
                    item['type'] = timer_def["type"]
                # Update ex
                item['ex'] = timer_def["ex"]

            else:
                print(f"Adding Timer {term}...")
                new_timer = {
                    "nr": "",
                    "term": term,
                    "mean": timer_def["mean"],
                    "ex": timer_def["ex"],
                    "exdoc": "",
                    "link_int": f'<a href="{full_link}" target="_blank">{term}</a>',
                    "vid": "",
                    "ext_de": "",
                    "ext_en": "",
                    "title": timer_def["title"],
                    "type": timer_def["type"]
                }
                cat_timer['data'].append(new_timer)

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
