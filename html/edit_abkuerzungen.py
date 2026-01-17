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

    # 8. Add/Update IO blocks in cat_hw
    cat_hw = find_category('cat_hw')
    if cat_hw:
        io_blocks = [
            {"term": "IX", "link": "Bibliotheken/StandardLibraries/io/IX.html", "mean": "Input Bool", "title": "Input Bool Interface", "type": "io", "ex": "Uebung_001, Uebung_001c, Uebung_002, Uebung_002a, Uebung_002a2, Uebung_002a3, Uebung_002a4, Uebung_002a5b, Uebung_002b2, Uebung_002b3, Uebung_003, Uebung_003a0, Uebung_003a_sub, Uebung_003b2_sub, Uebung_003b_sub, Uebung_003c_sub, Uebung_003d, Uebung_005, Uebung_010, Uebung_010a, Uebung_010a2, Uebung_010a3, Uebung_010a4, Uebung_010b1, Uebung_010b4_sub, Uebung_010b5_sub, Uebung_010c, Uebung_010c2, Uebung_010c3_sub, Uebung_010c4_sub, Uebung_019c, Uebung_020a, Uebung_020b, Uebung_020c, Uebung_020c2, Uebung_020c3, Uebung_020d, Uebung_020e, Uebung_020e2, Uebung_020f, Uebung_020f2, Uebung_020g, Uebung_020i, Uebung_028, Uebung_029, Uebung_030, Uebung_032, Uebung_033_sub, Uebung_039b, Uebung_039_sub_Outputs, Uebung_049, Uebung_051, Uebung_052, Uebung_053, Uebung_054, Uebung_055, Uebung_056, Uebung_085, Uebung_086, Uebung_087, Uebung_087a1, Uebung_087a2, Uebung_088, Uebung_089, Uebung_090a1, Uebung_090a2, Uebung_094, Uebung_094a, Uebung_095, Uebung_160, Uebung_090a1_AX, Uebung_090a2_AX"},
            {"term": "QX", "link": "Bibliotheken/StandardLibraries/io/QX.html", "mean": "Output Bool", "title": "Output Bool Interface", "type": "io", "ex": "Uebung_001, Uebung_001c, Uebung_002, Uebung_002a, Uebung_002a2, Uebung_002a3, Uebung_002a4, Uebung_002a5b, Uebung_002b2, Uebung_002b3, Uebung_003, Uebung_003a0, Uebung_003a_sub, Uebung_003b2_sub, Uebung_003b_sub, Uebung_003c_sub, Uebung_003d, Uebung_004a, Uebung_004a2, Uebung_004a3, Uebung_004a4, Uebung_004a5, Uebung_004a6, Uebung_004a7, Uebung_004a8, Uebung_004a9, Uebung_004b, Uebung_004b2, Uebung_004b3, Uebung_004c1, Uebung_004c2, Uebung_004c3, Uebung_004c4, Uebung_004c5, Uebung_004c6, Uebung_004c7, Uebung_005, Uebung_006, Uebung_006a, Uebung_006a2, Uebung_006a3, Uebung_006a4, Uebung_006b, Uebung_006c, Uebung_006d, Uebung_007, Uebung_007a1, Uebung_007a2, Uebung_007a3, Uebung_008, Uebung_009, Uebung_010, Uebung_010a, Uebung_010a2, Uebung_010a3, Uebung_010a4, Uebung_010b1, Uebung_010b2, Uebung_010b3, Uebung_010b4_sub, Uebung_010b5_sub, Uebung_010b6, Uebung_010b7, Uebung_010b8, Uebung_010b9, Uebung_010bA, Uebung_010bA2, Uebung_010bA3, Uebung_010bA4, Uebung_010c, Uebung_010c2, Uebung_010c3_sub, Uebung_010c4_sub, Uebung_013, Uebung_019b, Uebung_019c, Uebung_020a, Uebung_020b, Uebung_020c, Uebung_020c2, Uebung_020c3, Uebung_020d, Uebung_020e, Uebung_020e2, Uebung_020f, Uebung_020f2, Uebung_020f3, Uebung_020g, Uebung_020h, Uebung_020i, Uebung_021, Uebung_022, Uebung_023, Uebung_024, Uebung_025, Uebung_026_sub, Uebung_028, Uebung_029, Uebung_030, Uebung_032, Uebung_033_sub, Uebung_035, Uebung_035a, Uebung_035a2, Uebung_035a3, Uebung_036, Uebung_037, Uebung_038, Uebung_039a_sub_Outputs, Uebung_039b, Uebung_039_sub_Outputs, Uebung_040, Uebung_041, Uebung_049, Uebung_051, Uebung_052, Uebung_053, Uebung_054, Uebung_055, Uebung_056, Uebung_060_sub_Outputs, Uebung_071, Uebung_071a, Uebung_071b, Uebung_072b, Uebung_080, Uebung_080b, Uebung_080c, Uebung_081, Uebung_082, Uebung_083, Uebung_084, Uebung_085, Uebung_087, Uebung_087a1, Uebung_087a2, Uebung_088, Uebung_089, Uebung_090a1, Uebung_090a2, Uebung_091, Uebung_093, Uebung_093b, Uebung_094, Uebung_094a, Uebung_095, Uebung_110, Uebung_111, Uebung_160"},
            {"term": "IE", "link": "Bibliotheken/StandardLibraries/io/IE.html", "mean": "Input Event", "title": "Input Event Interface", "type": "io", "ex": "Uebung_004a, Uebung_004a2, Uebung_004a3, Uebung_004a4, Uebung_004a5, Uebung_004a6, Uebung_004a7, Uebung_004a8, Uebung_004a9, Uebung_004b, Uebung_004b2, Uebung_004b3, Uebung_004c1, Uebung_004c2, Uebung_004c3, Uebung_004c4, Uebung_004c5, Uebung_006, Uebung_006a, Uebung_006a2, Uebung_006a3, Uebung_006a4, Uebung_006b, Uebung_006d, Uebung_007a1, Uebung_007a2, Uebung_007a3, Uebung_009a, Uebung_010b2, Uebung_010b3, Uebung_010b6, Uebung_010b7, Uebung_010b8, Uebung_010b9, Uebung_010bA, Uebung_010bA2, Uebung_010bA3, Uebung_010bA4, Uebung_013, Uebung_014, Uebung_015, Uebung_015a, Uebung_016, Uebung_016a, Uebung_017, Uebung_018, Uebung_019, Uebung_019a, Uebung_019b, Uebung_019c, Uebung_020f3, Uebung_020h, Uebung_020i, Uebung_021, Uebung_022, Uebung_023, Uebung_024, Uebung_025, Uebung_026, Uebung_031, Uebung_034b, Uebung_035, Uebung_035a, Uebung_035a2, Uebung_035a3, Uebung_036, Uebung_037, Uebung_038, Uebung_039, Uebung_039a, Uebung_039a_sub_Outputs, Uebung_040, Uebung_041, Uebung_042, Uebung_043, Uebung_080, Uebung_080b, Uebung_080c, Uebung_081, Uebung_082, Uebung_083, Uebung_084, Uebung_085, Uebung_087, Uebung_087a1, Uebung_091, Uebung_093, Uebung_093b, Uebung_094, Uebung_094a, Uebung_095, Uebung_110, Uebung_111, Uebung_124, Uebung_127, Uebung_128, Uebung_132, Uebung_004a2_AX, Uebung_004a3_AX, Uebung_004a4_AX, Uebung_004a5_AX, Uebung_004a6_AX, Uebung_004a7_AX, Uebung_004a8_AX, Uebung_004a9_AX, Uebung_004a_AX, Uebung_004b_AX, Uebung_004c1_AX, Uebung_004c2_AX, Uebung_004c3_AX, Uebung_004c4_AX, Uebung_004c5_AX, Uebung_006a2_AX, Uebung_006a3_AX, Uebung_006a4_AX, Uebung_006a_AX, Uebung_006b_AX, Uebung_006d_AX, Uebung_006_AX, Uebung_007a1_AX, Uebung_007a2_AX, Uebung_007a3_AX, Uebung_010b2_AX, Uebung_010b3_AX, Uebung_010b6_AX, Uebung_010b7_AX, Uebung_010b8_AX, Uebung_010b9_AX, Uebung_010bA2_AX, Uebung_010bA3_AX, Uebung_010bA4_AX, Uebung_010bA_AX, Uebung_013_AX, Uebung_020f3_AX, Uebung_020h_AX, Uebung_020i_AX, Uebung_038_AX, Uebung_040_AX, Uebung_083_AX, Uebung_094a_AX, Uebung_095_AX, Uebung_150_AX, Uebung_151_AX, Uebung_152, Uebung_153"},
            
            {"term": "IB", "link": "Bibliotheken/StandardLibraries/io/IB.html", "mean": "Input Byte", "title": "Input Byte Interface", "type": "io", "ex": "Uebung_006c, Uebung_011a"},
            {"term": "QB", "link": "Bibliotheken/StandardLibraries/io/QB.html", "mean": "Output Byte", "title": "Output Byte Interface", "type": "io", "ex": ""},
            {"term": "IW", "link": "Bibliotheken/StandardLibraries/io/IW.html", "mean": "Input Word", "title": "Input Word Interface", "type": "io", "ex": ""},
            {"term": "QW", "link": "Bibliotheken/StandardLibraries/io/QW.html", "mean": "Output Word", "title": "Output Word Interface", "type": "io", "ex": ""},
            {"term": "ID", "link": "Bibliotheken/StandardLibraries/io/ID.html", "mean": "Input DWord", "title": "Input DWord Interface", "type": "io", "ex": "Uebung_011, Uebung_011a2, Uebung_012, Uebung_012a_sub, Uebung_012b, Uebung_012c, Uebung_020c2_sub, Uebung_028, Uebung_034, Uebung_034a1_Q1, Uebung_034a1_Q2, Uebung_034a1_Q4, Uebung_060, Uebung_103, Uebung_150_AX, Uebung_151_AX, Uebung_152, Uebung_153"},
            {"term": "QD", "link": "Bibliotheken/StandardLibraries/io/QD.html", "mean": "Output DWord", "title": "Output DWord Interface", "type": "io", "ex": "Uebung_060"},
            {"term": "IL", "link": "Bibliotheken/StandardLibraries/io/IL.html", "mean": "Input LWord", "title": "Input LWord Interface", "type": "io", "ex": ""},
            {"term": "QL", "link": "Bibliotheken/StandardLibraries/io/QL.html", "mean": "Output LWord", "title": "Output LWord Interface", "type": "io", "ex": ""}
        ]

        for io_def in io_blocks:
            term = io_def["term"]
            item = find_item(cat_hw, term)
            full_link = f'{base_url}{io_def["link"]}'
            
            if item:
                print(f"Updating IO Block {term}...")
                item['link_int'] = f'<a href="{full_link}" target="_blank">{term}</a>'
                if not item.get('mean') or item.get('mean') == "Datentyp": # Or generic
                     item['mean'] = io_def["mean"]
                item['title'] = io_def["title"]
                item['type'] = io_def["type"]
                if io_def["ex"]:
                    item['ex'] = io_def["ex"]
            else:
                print(f"Adding IO Block {term}...")
                new_io = {
                    "nr": "",
                    "term": term,
                    "mean": io_def["mean"],
                    "ex": io_def["ex"],
                    "exdoc": "",
                    "link_int": f'<a href="{full_link}" target="_blank">{term}</a>',
                    "vid": "",
                    "ext_de": "",
                    "ext_en": "",
                    "title": io_def["title"],
                    "type": io_def["type"]
                }
                cat_hw['data'].append(new_io)

    # 7. Add all unidirectional adapters to cat_adapter
    cat_adapter = find_category('cat_adapter')
    if cat_adapter:
        adapters_to_add = [
            {"term": "AB", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/BYTE/AB.html", "mean": "Adapter Interface (1 Event, 1 Byte)", "title": "Unidirectional Adapter Interface (Byte)"},
            {"term": "AD", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/DWORD/AD.html", "mean": "Adapter Interface (1 Event, 1 DWord)", "title": "Unidirectional Adapter Interface (DWord)"},
            {"term": "AL", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/LWORD/AL.html", "mean": "Adapter Interface (1 Event, 1 LWord)", "title": "Unidirectional Adapter Interface (LWord)"},
            {"term": "AS", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/SINT/AS.html", "mean": "Adapter Interface (1 Event, 1 SINT)", "title": "Unidirectional Adapter Interface (SINT)"},
            {"term": "AUS", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/USINT/AUS.html", "mean": "Adapter Interface (1 Event, 1 USINT)", "title": "Unidirectional Adapter Interface (USINT)"},
            {"term": "AI", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/INT/AI.html", "mean": "Adapter Interface (1 Event, 1 INT)", "title": "Unidirectional Adapter Interface (INT)"},
            {"term": "AUI", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/UINT/AUI.html", "mean": "Adapter Interface (1 Event, 1 UINT)", "title": "Unidirectional Adapter Interface (UINT)"},
            {"term": "ADI", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/DINT/ADI.html", "mean": "Adapter Interface (1 Event, 1 DINT)", "title": "Unidirectional Adapter Interface (DINT)"},
            {"term": "AUDI", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/UDINT/AUDI.html", "mean": "Adapter Interface (1 Event, 1 UDINT)", "title": "Unidirectional Adapter Interface (UDINT)"},
            {"term": "ALI", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/LINT/ALI.html", "mean": "Adapter Interface (1 Event, 1 LINT)", "title": "Unidirectional Adapter Interface (LINT)"},
            {"term": "AULI", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/ULINT/AULI.html", "mean": "Adapter Interface (1 Event, 1 ULINT)", "title": "Unidirectional Adapter Interface (ULINT)"},
            {"term": "AR", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/REAL/AR.html", "mean": "Adapter Interface (1 Event, 1 REAL)", "title": "Unidirectional Adapter Interface (REAL)"},
            {"term": "ALR", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/LREAL/ALR.html", "mean": "Adapter Interface (1 Event, 1 LREAL)", "title": "Unidirectional Adapter Interface (LREAL)"},
            {"term": "AE", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/EVENT/AE.html", "mean": "Adapter Interface (1 Event)", "title": "Unidirectional Adapter Interface (Event)"},
            {"term": "ASR", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/EVENT/ASR.html", "mean": "Adapter Interface (Set/Reset)", "title": "Unidirectional Adapter Interface (Set/Reset)"},
            {"term": "A2X", "link": "Bibliotheken/ExternalLibraries/adapter/types/unidirectional/BOOL/A2X.html", "mean": "Adapter Interface (BOOL)", "title": "Unidirectional Adapter Interface (A2X)"}
        ]

        for adapter_def in adapters_to_add:
            term = adapter_def["term"]
            item = find_item(cat_adapter, term)
            full_link = f'{base_url}{adapter_def["link"]}'
            
            if not item:
                print(f"Adding Adapter {term}...")
                new_adapter = {
                    "nr": "",
                    "term": term,
                    "mean": adapter_def["mean"],
                    "ex": "",
                    "exdoc": "",
                    "link_int": f'<a href="{full_link}" target="_blank">{term}</a>',
                    "vid": "",
                    "ext_de": "",
                    "ext_en": "",
                    "title": adapter_def["title"],
                    "type": "adapter"
                }
                cat_adapter['data'].append(new_adapter)
            else:
                print(f"Updating Adapter {term}...")
                item['link_int'] = f'<a href="{full_link}" target="_blank">{term}</a>'
                item['mean'] = adapter_def["mean"]
    # 9. Add Sequence Control Blocks to cat_sequence
    cat_sequence = find_category('cat_sequence')
    if not cat_sequence:
        cat_sequence = {
            "id": "cat_sequence",
            "title": "Sequenzsteuerung",
            "data": []
        }
        data['categories'].append(cat_sequence)

    if cat_sequence:
        sequence_blocks = [
            # Standard - Event
            {"term": "sequence_E_04", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/event/sequence_E_04.html", "mean": "Sequenz (Event, 4 Schritte)", "title": "Sequence Control (Event, 4 Steps)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_05", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/event/sequence_E_05.html", "mean": "Sequenz (Event, 5 Schritte)", "title": "Sequence Control (Event, 5 Steps)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_08", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/event/sequence_E_08.html", "mean": "Sequenz (Event, 8 Schritte)", "title": "Sequence Control (Event, 8 Steps)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_04_loop", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/event/sequence_E_04_loop.html", "mean": "Sequenz (Event, 4 Schritte, Loop)", "title": "Sequence Control (Event, 4 Steps, Loop)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_05_loop", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/event/sequence_E_05_loop.html", "mean": "Sequenz (Event, 5 Schritte, Loop)", "title": "Sequence Control (Event, 5 Steps, Loop)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_08_loop", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/event/sequence_E_08_loop.html", "mean": "Sequenz (Event, 8 Schritte, Loop)", "title": "Sequence Control (Event, 8 Steps, Loop)", "type": "sequence", "ex": "Uebung_040, Uebung_041"},

            # Standard - Time
            {"term": "sequence_T_04", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/time/sequence_T_04.html", "mean": "Sequenz (Time, 4 Schritte)", "title": "Sequence Control (Time, 4 Steps)", "type": "sequence", "ex": ""},
            {"term": "sequence_T_05", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/time/sequence_T_05.html", "mean": "Sequenz (Time, 5 Schritte)", "title": "Sequence Control (Time, 5 Steps)", "type": "sequence", "ex": ""},
            {"term": "sequence_T_08", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/time/sequence_T_08.html", "mean": "Sequenz (Time, 8 Schritte)", "title": "Sequence Control (Time, 8 Steps)", "type": "sequence", "ex": ""},
            {"term": "sequence_T_04_loop", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/time/sequence_T_04_loop.html", "mean": "Sequenz (Time, 4 Schritte, Loop)", "title": "Sequence Control (Time, 4 Steps, Loop)", "type": "sequence", "ex": "Uebung_035a"},
            {"term": "sequence_T_05_loop", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/time/sequence_T_05_loop.html", "mean": "Sequenz (Time, 5 Schritte, Loop)", "title": "Sequence Control (Time, 5 Steps, Loop)", "type": "sequence", "ex": "Uebung_035a2, Uebung_035a3"},
            {"term": "sequence_T_08_loop", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/time/sequence_T_08_loop.html", "mean": "Sequenz (Time, 8 Schritte, Loop)", "title": "Sequence Control (Time, 8 Steps, Loop)", "type": "sequence", "ex": "Uebung_038"},

            # Standard - Combi
            {"term": "sequence_ET_04", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/combi/sequence_ET_04.html", "mean": "Sequenz (Event/Time, 4 Schritte)", "title": "Sequence Control (Event/Time, 4 Steps)", "type": "sequence", "ex": "Uebung_035, Uebung_036"},
            {"term": "sequence_ET_05", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/combi/sequence_ET_05.html", "mean": "Sequenz (Event/Time, 5 Schritte)", "title": "Sequence Control (Event/Time, 5 Steps)", "type": "sequence", "ex": "Uebung_039, Uebung_039a"},
            {"term": "sequence_ET_08", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/combi/sequence_ET_08.html", "mean": "Sequenz (Event/Time, 8 Schritte)", "title": "Sequence Control (Event/Time, 8 Steps)", "type": "sequence", "ex": ""},
            {"term": "sequence_ET_04_loop", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/combi/sequence_ET_04_loop.html", "mean": "Sequenz (Event/Time, 4 Schritte, Loop)", "title": "Sequence Control (Event/Time, 4 Steps, Loop)", "type": "sequence", "ex": "Uebung_037"},
            {"term": "sequence_ET_05_loop", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/combi/sequence_ET_05_loop.html", "mean": "Sequenz (Event/Time, 5 Schritte, Loop)", "title": "Sequence Control (Event/Time, 5 Steps, Loop)", "type": "sequence", "ex": ""},
            {"term": "sequence_ET_08_loop", "link": "Bibliotheken/StandardLibraries/utils/sequence-control/combi/sequence_ET_08_loop.html", "mean": "Sequenz (Event/Time, 8 Schritte, Loop)", "title": "Sequence Control (Event/Time, 8 Steps, Loop)", "type": "sequence", "ex": ""},

            # Adapter (AX) - Event
            {"term": "sequence_E_04_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/event/sequence_E_04_AX.html", "mean": "Sequenz (Event, 4 Schritte, AX)", "title": "Sequence Control (Event, 4 Steps, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_05_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/event/sequence_E_05_AX.html", "mean": "Sequenz (Event, 5 Schritte, AX)", "title": "Sequence Control (Event, 5 Steps, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_08_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/event/sequence_E_08_AX.html", "mean": "Sequenz (Event, 8 Schritte, AX)", "title": "Sequence Control (Event, 8 Steps, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_04_loop_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/event/sequence_E_04_loop_AX.html", "mean": "Sequenz (Event, 4 Schritte, Loop, AX)", "title": "Sequence Control (Event, 4 Steps, Loop, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_05_loop_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/event/sequence_E_05_loop_AX.html", "mean": "Sequenz (Event, 5 Schritte, Loop, AX)", "title": "Sequence Control (Event, 5 Steps, Loop, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_E_08_loop_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/event/sequence_E_08_loop_AX.html", "mean": "Sequenz (Event, 8 Schritte, Loop, AX)", "title": "Sequence Control (Event, 8 Steps, Loop, AX)", "type": "sequence", "ex": "Uebung_040_AX"},

            # Adapter (AX) - Time (Note path: timed)
            {"term": "sequence_T_04_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/timed/sequence_T_04_AX.html", "mean": "Sequenz (Time, 4 Schritte, AX)", "title": "Sequence Control (Time, 4 Steps, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_T_05_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/timed/sequence_T_05_AX.html", "mean": "Sequenz (Time, 5 Schritte, AX)", "title": "Sequence Control (Time, 5 Steps, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_T_08_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/timed/sequence_T_08_AX.html", "mean": "Sequenz (Time, 8 Schritte, AX)", "title": "Sequence Control (Time, 8 Steps, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_T_04_loop_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/timed/sequence_T_04_loop_AX.html", "mean": "Sequenz (Time, 4 Schritte, Loop, AX)", "title": "Sequence Control (Time, 4 Steps, Loop, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_T_05_loop_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/timed/sequence_T_05_loop_AX.html", "mean": "Sequenz (Time, 5 Schritte, Loop, AX)", "title": "Sequence Control (Time, 5 Steps, Loop, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_T_08_loop_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/timed/sequence_T_08_loop_AX.html", "mean": "Sequenz (Time, 8 Schritte, Loop, AX)", "title": "Sequence Control (Time, 8 Steps, Loop, AX)", "type": "sequence", "ex": "Uebung_038_AX"},

            # Adapter (AX) - Combi
            {"term": "sequence_ET_04_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/combi/sequence_ET_04_AX.html", "mean": "Sequenz (Event/Time, 4 Schritte, AX)", "title": "Sequence Control (Event/Time, 4 Steps, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_ET_05_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/combi/sequence_ET_05_AX.html", "mean": "Sequenz (Event/Time, 5 Schritte, AX)", "title": "Sequence Control (Event/Time, 5 Steps, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_ET_08_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/combi/sequence_ET_08_AX.html", "mean": "Sequenz (Event/Time, 8 Schritte, AX)", "title": "Sequence Control (Event/Time, 8 Steps, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_ET_04_loop_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/combi/sequence_ET_04_loop_AX.html", "mean": "Sequenz (Event/Time, 4 Schritte, Loop, AX)", "title": "Sequence Control (Event/Time, 4 Steps, Loop, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_ET_05_loop_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/combi/sequence_ET_05_loop_AX.html", "mean": "Sequenz (Event/Time, 5 Schritte, Loop, AX)", "title": "Sequence Control (Event/Time, 5 Steps, Loop, AX)", "type": "sequence", "ex": ""},
            {"term": "sequence_ET_08_loop_AX", "link": "Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/combi/sequence_ET_08_loop_AX.html", "mean": "Sequenz (Event/Time, 8 Schritte, Loop, AX)", "title": "Sequence Control (Event/Time, 8 Steps, Loop, AX)", "type": "sequence", "ex": ""}
        ]

        for seq_def in sequence_blocks:
            term = seq_def["term"]
            item = find_item(cat_sequence, term)
            full_link = f'{base_url}{seq_def["link"]}'
            
            if not item:
                print(f"Adding Sequence Block {term}...")
                new_seq = {
                    "nr": "",
                    "term": term,
                    "mean": seq_def["mean"],
                    "ex": seq_def["ex"],
                    "exdoc": "",
                    "link_int": f'<a href="{full_link}" target="_blank">{term}</a>',
                    "vid": "",
                    "ext_de": "",
                    "ext_en": "",
                    "title": seq_def["title"],
                    "type": seq_def["type"]
                }
                cat_sequence['data'].append(new_seq)
            else:
                print(f"Updating Sequence Block {term}...")
                item['link_int'] = f'<a href="{full_link}" target="_blank">{term}</a>'
                item['mean'] = seq_def["mean"]
                item['title'] = seq_def["title"]
    # 10. Add missing Counter and Adapter Conversion blocks
    cat_counters = find_category('cat_counters')
    if cat_counters:
        term = "AUDI_CTUD_UDINT"
        item = find_item(cat_counters, term)
        full_link = f'{base_url}Bibliotheken/ExternalLibraries/adapter/events/unidirectional/AUDI_CTUD_UDINT.html'
        ex = "Uebung_009_AX, Uebung_083_AX"
        
        if not item:
            print(f"Adding Counter {term}...")
            new_counter = {
                "nr": "",
                "term": term,
                "mean": "Adapter-basierter Auf-/Abwärtszähler (UDINT)",
                "ex": ex,
                "exdoc": "",
                "link_int": f'<a href="{full_link}" target="_blank">{term}</a>',
                "vid": "",
                "ext_de": "",
                "ext_en": "",
                "title": "Adapter-based Up/Down Counter (UDINT)",
                "type": "event"
            }
            cat_counters['data'].append(new_counter)
        else:
            print(f"Updating Counter {term}...")
            item['link_int'] = f'<a href="{full_link}" target="_blank">{term}</a>'
            item['ex'] = ex

    cat_adapter = find_category('cat_adapter')
    if cat_adapter:
        conversions = [
            {"term": "AUDI_TO_AD", "link": "Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/AD_AUDI/AUDI_TO_AD.html", "mean": "Adapter-Konvertierung (UDINT -> DWORD)", "title": "Adapter Conversion (UDINT to DWORD)", "ex": ""},
            {"term": "ADI_DI_TO_DINT", "link": "Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/DINT/ADI_DI_TO_DINT.html", "mean": "Adapter-Konvertierung (ADI -> DINT)", "title": "Adapter Conversion (ADI to DINT)", "ex": ""}
        ]
        
        for conv in conversions:
            term = conv["term"]
            item = find_item(cat_adapter, term)
            full_link = f'{base_url}{conv["link"]}'
            
            if not item:
                print(f"Adding Conversion {term}...")
                new_conv = {
                    "nr": "",
                    "term": term,
                    "mean": conv["mean"],
                    "ex": conv["ex"],
                    "exdoc": "",
                    "link_int": f'<a href="{full_link}" target="_blank">{term}</a>',
                    "vid": "",
                    "ext_de": "",
                    "ext_en": "",
                    "title": conv["title"],
                    "type": "adapter"
                }
                cat_adapter['data'].append(new_conv)
            else:
                print(f"Updating Conversion {term}...")
                item['link_int'] = f'<a href="{full_link}" target="_blank">{term}</a>'

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
