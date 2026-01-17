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
        "LDATE", "LDT", "LINT", "LREAL", "LTIME", "LTOD", "LWORD", "QUARTER", "REAL", 
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
                if dt == "QUARTER":
                    item['mean'] = "Datentyp (2 Bit / 4 Zustände)"
                elif item.get('mean') == "Datentyp":
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

    # 5. Update Flip-Flops in cat_flipflop
    cat_flipflop = find_category('cat_flipflop')
    if cat_flipflop:
        flipflops_to_process = [
            # Standard (IEC 61131-3)
            {"term": "FB_RS", "mean": "Bistabiles Element (Rücksetz-Priorität)", "link": "Bibliotheken/StandardLibraries/iec61131-3/bistableElements/FB_RS.html", "title": "Bistable Element (Reset Priority)", "type": "", "ex": ""},
            {"term": "FB_SR", "mean": "Bistabiles Element (Setz-Priorität)", "link": "Bibliotheken/StandardLibraries/iec61131-3/bistableElements/FB_SR.html", "title": "Bistable Element (Set Priority)", "type": "", "ex": ""},
            
            # Event-Based (IEC 61499)
            {"term": "E_T_FF", "mean": "Event-driven Toggle Flip-Flop", "link": "Bibliotheken/StandardLibraries/events/E_T_FF.html", "title": "Toggle Flip-Flop", "type": "event", "ex": "Uebung_004a, Uebung_004a2, Uebung_004a3, Uebung_005, Uebung_007"},
            {"term": "E_T_FF_SR", "mean": "Event-driven Toggle Flip-Flop mit Set/Reset", "link": "Bibliotheken/StandardLibraries/events/E_T_FF_SR.html", "title": "Toggle Flip-Flop with Set/Reset", "type": "event", "ex": "Uebung_004a7, Uebung_006a, Uebung_006a2"},
            {"term": "E_SR", "mean": "Event-driven SR Flip-Flop", "link": "Bibliotheken/StandardLibraries/events/E_SR.html", "title": "SR Flip-Flop", "type": "event", "ex": "Uebung_004b, Uebung_006, Uebung_009, Uebung_015"},
            {"term": "E_RS", "mean": "Event-driven RS Flip-Flop", "link": "Bibliotheken/StandardLibraries/events/E_RS.html", "title": "RS Flip-Flop", "type": "event", "ex": "Uebung_006b, Uebung_020a, Uebung_020b"},
            {"term": "E_D_FF", "mean": "Event-driven Data Flip-Flop", "link": "Bibliotheken/StandardLibraries/events/E_D_FF.html", "title": "D Flip-Flop", "type": "event", "ex": "Uebung_071a, Uebung_085"},

            # Adapter Event-Based
            {"term": "AX_RS", "mean": "RS Flip-Flop mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/events/unidirectional/AX_RS.html", "title": "RS Flip-Flop with Adapter", "type": "adapter", "ex": "Uebung_006b_AX, Uebung_020a_AX"},
            {"term": "AX_SR", "mean": "SR Flip-Flop mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/events/unidirectional/ASR_AX_SR.html", "title": "SR Flip-Flop with Adapter", "type": "adapter", "ex": "Uebung_006d_AX, Uebung_006_AX, Uebung_008_AX"},
            {"term": "AX_T_FF_SR", "mean": "Toggle Flip-Flop (SR) mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/events/unidirectional/AX_T_FF_SR.html", "title": "Toggle Flip-Flop (SR) with Adapter", "type": "adapter", "ex": "Uebung_004a7_AX, Uebung_006a2_AX"},
            {"term": "AX_D_FF", "mean": "Data Flip-Flop mit Adapter", "link": "Bibliotheken/ExternalLibraries/adapter/events/unidirectional/AX_D_FF.html", "title": "D Flip-Flop with Adapter", "type": "adapter", "ex": ""},
            {"term": "AX_T_FF", "mean": "Toggle Flip-Flop mit Adapter", "link": "", "title": "", "type": "adapter", "ex": "Uebung_004a2_AX, Uebung_005_AX, Uebung_007_AX"} # Link missing in prompt but found exercises
        ]

        for ff_def in flipflops_to_process:
            term = ff_def["term"]
            item = find_item(cat_flipflop, term)
            full_link = f'{base_url}{ff_def["link"]}' if ff_def["link"] else ""
            
            if item:
                print(f"Updating Flip-Flop {term}...")
                if full_link:
                    item['link_int'] = f'<a href="{full_link}" target="_blank">{term}</a>'
                if not item.get('mean') or item.get('mean') == "Datentyp":
                     item['mean'] = ff_def["mean"]
                if not item.get('type'):
                    item['type'] = ff_def["type"]
                item['ex'] = ff_def["ex"]
            else:
                print(f"Adding Flip-Flop {term}...")
                new_ff = {
                    "nr": "",
                    "term": term,
                    "mean": ff_def["mean"],
                    "ex": ff_def["ex"],
                    "exdoc": "",
                    "link_int": f'<a href="{full_link}" target="_blank">{term}</a>' if full_link else "",
                    "vid": "",
                    "ext_de": "",
                    "ext_en": "",
                    "title": ff_def["title"],
                    "type": ff_def["type"]
                }
                cat_flipflop['data'].append(new_ff)
    
    # 6. Restructuring and adding IO/Adapter types
    
    # Rename cat_types
    cat_types = find_category('cat_types')
    if cat_types:
        cat_types['title'] = "Standard-Datentypen"
        
        # Move AX to cat_adapter
        item_ax = find_item(cat_types, 'AX')
        if item_ax:
            cat_types['data'].remove(item_ax)
            
            # Find or create cat_adapter
            cat_adapter = find_category('cat_adapter')
            if not cat_adapter:
                cat_adapter = {
                    "id": "cat_adapter",
                    "title": "Adapter-Typen",
                    "data": []
                }
                # Insert after cat_types (index 1)
                data['categories'].insert(1, cat_adapter)
            
            # Add AX to cat_adapter
            if not find_item(cat_adapter, 'AX'):
                cat_adapter['data'].append(item_ax)

    # Add AW to cat_adapter
    cat_adapter = find_category('cat_adapter')
    if cat_adapter:
        if not find_item(cat_adapter, 'AW'):
            print("Adding AW...")
            new_aw = {
                "nr": "",
                "term": "AW",
                "mean": "Adapter Interface (1 Event, 1 Word)",
                "ex": "",
                "exdoc": "",
                "link_int": f'<a href="{base_url}Bibliotheken/ExternalLibraries/adapter/types/unidirectional/WORD/AW.html" target="_blank">AW</a>',
                "vid": "",
                "ext_de": "",
                "ext_en": "",
                "title": "Unidirectional Adapter Interface (Word)",
                "type": "adapter"
            }
            cat_adapter['data'].append(new_aw)

    # Add IW and QW to cat_hw
    cat_hw = find_category('cat_hw')
    if cat_hw:
        if not find_item(cat_hw, 'IW'):
            print("Adding IW...")
            new_iw = {
                "nr": "",
                "term": "IW",
                "mean": "Input Word",
                "ex": "",
                "exdoc": "",
                "link_int": f'<a href="{base_url}Bibliotheken/StandardLibraries/io/IW.html" target="_blank">IW</a>',
                "vid": "",
                "ext_de": "",
                "ext_en": "",
                "title": "Input Word Interface",
                "type": "io"
            }
            cat_hw['data'].append(new_iw)
            
        if not find_item(cat_hw, 'QW'):
            print("Adding QW...")
            new_qw = {
                "nr": "",
                "term": "QW",
                "mean": "Output Word",
                "ex": "",
                "exdoc": "",
                "link_int": f'<a href="{base_url}Bibliotheken/StandardLibraries/io/QW.html" target="_blank">QW</a>',
                "vid": "",
                "ext_de": "",
                "ext_en": "",
                "title": "Output Word Interface",
                "type": "io"
            }
            cat_hw['data'].append(new_qw)

    return data

def make_exercises_clickable(data):
    base_url = "https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/de/latest/training1/Ventilsteuerung/4diacIDE-workspace/"
    
    for category in data.get('categories', []):
        for item in category.get('data', []):
            ex_str = item.get('ex', '')
            if ex_str and '<a href=' not in ex_str:
                exercises = [e.strip() for e in ex_str.split(',')]
                links = []
                for ex in exercises:
                    if not ex: continue
                    # Determine path based on _AX suffix
                    if '_AX' in ex:
                        path = "test_AX/Uebungen_doc/"
                    else:
                        path = "test_B/Uebungen_doc/"
                    
                    link = f'<a href="{base_url}{path}{ex}.html" target="_blank">{ex}</a>'
                    links.append(link)
                
                item['ex'] = ', '.join(links)
    return data

def main():
    if not os.path.exists(file_path):
        print(f"Error: File not found at {file_path}")
        return

    try:
        data = load_json(file_path)
        data = modify_data(data)
        data = make_exercises_clickable(data) # Apply clickability
        save_json(file_path, data)
        print("Done.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
