import json
import os
import re

# Configuration
file_name = 'Abkuerzungen_und_Bedeutungen.json'
script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, file_name)

base_url = "https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/de/latest/"
dt_base_url = base_url + "Allgemeines/Datentypen/"
ex_base_url = base_url + "training1/Ventilsteuerung/4diacIDE-workspace/"

def load_json(path):
    print(f"Loading {path}...")
    with open(path, 'r', encoding='utf-8') as f:
        return json.load(f)

def save_json(path, data):
    print(f"Saving to {path}...")
    with open(path, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=3, ensure_ascii=False)

def find_category(data, cat_id):
    for cat in data.get('categories', []):
        if cat.get('id') == cat_id:
            return cat
    return None

def find_item(category, term):
    for item in category.get('data', []):
        if item.get('term') == term:
            return item
    return None

def get_type_for_dt(dt_name):
    if dt_name == "BOOL": return "bool"
    if dt_name in ["BYTE", "WORD", "DWORD", "LWORD", "QUARTER"]: return "any_bit"
    if dt_name in ["SINT", "INT", "DINT", "LINT", "USINT", "UINT", "UDINT", "ULINT"]: return "any_int"
    if dt_name in ["REAL", "LREAL"]: return "any_real"
    if dt_name in ["STRING", "WSTRING", "CHAR", "WCHAR"]: return "any_string"
    if dt_name in ["TIME", "LTIME", "DATE", "LDATE", "TIME_OF_DAY", "LTOD", "DATE_AND_TIME", "LDT", "CAN_MSG"]: return "time"
    return ""

def update_or_add(category, item_def):
    term = item_def["term"]
    item = find_item(category, term)
    
    # Prefix-based type auto-detection
    detected_type = item_def.get("type", "")
    if not detected_type:
        if '_AX' in term or term.startswith(('AX_', 'AW_', 'AB_', 'AD_', 'AL_', 'AS_', 'AI_', 'AE_', 'ASR_', 'AUDI_', 'AUI_', 'ADI_', 'ALI_', 'AULI_', 'AR_', 'ALR_', 'A2X_')):
            detected_type = 'adapter'
        elif 'sequence_E_' in term or term.startswith('E_'):
            detected_type = 'event'

    if item:
        item['link_int'] = f'<a href="{item_def["link"]}" target="_blank">{term}</a>'
        if not item.get('mean') or item.get('mean') == "Datentyp":
            item['mean'] = item_def.get("mean", item.get('mean', ""))
        item['title'] = item_def.get("title", item.get('title', ""))
        item['type'] = detected_type
        if item_def.get("ex"):
            item['ex'] = item_def["ex"]
    else:
        new_item = {
            "nr": "",
            "term": term,
            "mean": item_def.get("mean", ""),
            "ex": item_def.get("ex", ""),
            "exdoc": "",
            "link_int": f'<a href="{item_def["link"]}" target="_blank">{term}</a>',
            "vid": "",
            "ext_de": "",
            "ext_en": "",
            "title": item_def.get("title", ""),
            "type": detected_type
        }
        category['data'].append(new_item)

def modify_data(data):
    # 1. Categories
    cat_types = find_category(data, 'cat_types')
    if cat_types: cat_types['title'] = "Standard-Datentypen"
    
    cat_adapter = find_category(data, 'cat_adapter')
    if not cat_adapter:
        cat_adapter = {"id": "cat_adapter", "title": "Adapter-Typen", "data": []}
        data['categories'].insert(1, cat_adapter)

    cat_sequence = find_category(data, 'cat_sequence')
    if not cat_sequence:
        cat_sequence = {"id": "cat_sequence", "title": "Sequenzsteuerung", "data": []}
        data['categories'].append(cat_sequence)

    # 2. Data Types
    dts = ["BOOL", "BYTE", "CHAR", "DATE", "DATE_AND_TIME", "DINT", "DWORD", "INT", 
           "LDATE", "LDT", "LINT", "LREAL", "LTIME", "LTOD", "LWORD", "QUARTER", "REAL", 
           "SINT", "STRING", "TIME", "TIME_OF_DAY", "UDINT", "UINT", "ULINT", 
           "USINT", "WCHAR", "WORD", "WSTRING", "CAN_MSG"]
    for dt in dts:
        link = f'{base_url}Bibliotheken/ExternalLibraries/isobus/pgn/CAN_MSG.html' if dt == "CAN_MSG" else f'{dt_base_url}{dt}/{dt}_Detail.html'
        mean = "Datentyp (2 Bit / 4 Zustände)" if dt == "QUARTER" else ("Strukturierte CAN-Nachricht" if dt == "CAN_MSG" else f"Standard-Datentyp {dt}")
        update_or_add(cat_types, {"term": dt, "link": link, "type": get_type_for_dt(dt), "mean": mean})

    # 3. Adapters
    adapters = [
        ("AX", "BOOL"), ("AW", "WORD"), ("AB", "BYTE"), ("AD", "DWORD"), ("AL", "LWORD"), 
        ("AS", "SINT"), ("AUS", "USINT"), ("AI", "INT"), ("AUI", "UINT"), ("ADI", "DINT"), 
        ("AUDI", "UDINT"), ("ALI", "LINT"), ("AULI", "ULINT"), ("AR", "REAL"), ("ALR", "LREAL"),
        ("AE", "EVENT"), ("ASR", "EVENT"), ("A2X", "BOOL")
    ]
    for term, dtype in adapters:
        link = f'{base_url}Bibliotheken/ExternalLibraries/adapter/types/unidirectional/{dtype}/{term}.html'
        update_or_add(cat_adapter, {"term": term, "link": link, "type": "adapter"})

    # 4. IO Blocks (cat_hw)
    cat_hw = find_category(data, 'cat_hw')
    io_defs = [
        ("IX", "Uebung_001, Uebung_002, Uebung_005, Uebung_010, Uebung_020c, Uebung_087"),
        ("QX", "Uebung_001, Uebung_002, Uebung_005, Uebung_010, Uebung_020c, Uebung_087"),
        ("IE", "Uebung_004a, Uebung_006, Uebung_013, Uebung_020f3"),
        ("IB", "Uebung_006c, Uebung_011a"), ("QB", ""), ("IW", ""), ("QW", ""),
        ("ID", "Uebung_011, Uebung_012, Uebung_034, Uebung_060, Uebung_103"), ("QD", "Uebung_060"), ("IL", ""), ("QL", "")
    ]
    for term, ex in io_defs:
        link = f'{base_url}Bibliotheken/StandardLibraries/io/{term}.html'
        update_or_add(cat_hw, {"term": term, "link": link, "type": "io", "ex": ex})

    # 5. Timers (cat_timer)
    cat_timer = find_category(data, 'cat_timer')
    timers = [
        ("AX_FB_TOF", "adapter", "Uebung_020e2_AX"), ("AX_FB_TON", "adapter", "Uebung_020c3_AX"), ("AX_FB_TP", "adapter", "Uebung_020f2_AX"),
        ("FB_TON", "", "Uebung_020c3"), ("FB_TOF", "", "Uebung_020e2"), ("FB_TP", "", "Uebung_020f2"),
        ("E_PULSE", "event", "Uebung_020h, Uebung_020i"), ("E_TP", "event", "Uebung_020f, Uebung_039b"),
        ("E_TON", "event", "Uebung_020c, Uebung_020c2, Uebung_039b"), ("E_TONOF", "event", "Uebung_020g"),
        ("AX_TON", "adapter", "Uebung_020c_AX"), ("AX_TONOF", "adapter", "Uebung_020g_AX"), ("AX_TOF", "adapter", "Uebung_020e_AX"), ("AX_PULSE", "adapter", "Uebung_020h_AX, Uebung_020i_AX")
    ]
    for term, t, ex in timers:
        link = f'{base_url}Bibliotheken/{"ExternalLibraries/adapter/iec61131" if term.startswith("AX_FB") else ("ExternalLibraries/adapter/events/unidirectional" if term.startswith("AX_") else ("StandardLibraries/iec61131-3" if term.startswith("FB_") else "StandardLibraries/events"))}/timers/{term}.html'
        update_or_add(cat_timer, {"term": term, "link": link, "type": t, "ex": ex})

    # 6. Flip-Flops (cat_flipflop)
    cat_ff = find_category(data, 'cat_flipflop')
    ffs = [
        ("FB_RS", "", ""), ("FB_SR", "", ""), 
        ("E_T_FF", "event", "Uebung_004a, Uebung_004a2, Uebung_005"), ("E_T_FF_SR", "event", "Uebung_004a7, Uebung_006a"),
        ("E_SR", "event", "Uebung_004b, Uebung_006"), ("E_RS", "event", "Uebung_006b, Uebung_020a"), ("E_D_FF", "event", "Uebung_071a, Uebung_085"),
        ("AX_RS", "adapter", "Uebung_006b_AX"), ("AX_SR", "adapter", "Uebung_006d_AX"), ("AX_T_FF_SR", "adapter", "Uebung_004a7_AX"),
        ("AX_D_FF", "adapter", ""), ("AX_T_FF", "adapter", "Uebung_004a2_AX")
    ]
    for term, t, ex in ffs:
        path = "StandardLibraries/iec61131-3/bistableElements" if term.startswith("FB_") else ("ExternalLibraries/adapter/events/unidirectional" if term.startswith("AX_") else "StandardLibraries/events")
        link = f'{base_url}Bibliotheken/{path}/{term}.html'
        if term == "AX_SR": link = f'{base_url}Bibliotheken/ExternalLibraries/adapter/events/unidirectional/ASR_AX_SR.html'
        update_or_add(cat_ff, {"term": term, "link": link, "type": t, "ex": ex})

    # 7. Sequences (cat_sequence)
    for steps in ["04", "05", "08"]:
        for t in ["E", "T", "ET"]:
            for suffix in ["", "_loop", "_AX", "_loop_AX"]:
                term = f"sequence_{t}_{steps}{suffix}"
                # Mapping exercises (simplified)
                ex = ""
                if term == "sequence_ET_04": ex = "Uebung_035, Uebung_036"
                elif term == "sequence_ET_05": ex = "Uebung_039"
                elif term == "sequence_E_08_loop": ex = "Uebung_040"
                
                group = "event" if t == "E" else ("timed" if t == "T" else "combi")
                lib = "ExternalLibraries/logiBUS" if "AX" in suffix else "StandardLibraries"
                link = f'{base_url}Bibliotheken/{lib}/utils/sequence-control/{group}/{term}.html'
                if "AX" in suffix: link = f'{base_url}Bibliotheken/{lib}/utils/sequence/{group}/{term}.html'
                update_or_add(cat_sequence, {"term": term, "link": link, "ex": ex})

    # Special Sequences
    update_or_add(cat_sequence, {"term": "sequence_ET_04_04", "link": f"{base_url}Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/combi/sequence_ET_04_04.html", "type": "sequence"})
    update_or_add(cat_sequence, {"term": "sequence_ET_04_04_AX", "link": f"{base_url}Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/combi/sequence_ET_04_04_AX.html", "type": "adapter"})

    # 8. MUX/DEMUX & Logic
    cat_logic = find_category(data, 'cat_logic')
    cat_events = find_category(data, 'cat_events')
    muxs = [
        (cat_events, "E_MUX_2", "StandardLibraries/events", "event", ""),
        (cat_events, "E_MUX_4", "StandardLibraries/events", "event", "Uebung_087a2"),
        (cat_events, "E_DEMUX", "StandardLibraries/events", "event", "Uebung_087"),
        (cat_logic, "AX_MUX_2", "ExternalLibraries/adapter/selection/unidirectional/BOOL", "adapter", "Uebung_090a1_AX"),
        (cat_logic, "AX_MUX_3", "ExternalLibraries/adapter/selection/unidirectional/BOOL", "adapter", "Uebung_103"),
        (cat_logic, "SPLIT_BYTE_INTO_QUARTERS", "StandardLibraries/utils/splitting", "", "Uebung_056"),
        (cat_logic, "GET_AT_INDEX", "StandardLibraries/convert", "", ""),
        (cat_logic, "ASSEMBLE_BYTE_FROM_BOOLS", "StandardLibraries/utils/assembling", "", "Uebung_053"),
        (cat_logic, "SPLIT_BYTE_INTO_BOOLS", "StandardLibraries/utils/splitting", "", "Uebung_053")
    ]
    for cat, term, path, t, ex in muxs:
        update_or_add(cat, {"term": term, "link": f'{base_url}Bibliotheken/{path}/{term}.html', "type": t, "ex": ex})

    # Update E_STOPWATCH link in cat_timer
    update_or_add(cat_timer, {"term": "E_STOPWATCH", "link": f'{base_url}Bibliotheken/StandardLibraries/utils/timing/E_STOPWATCH.html', "type": "event", "ex": "Uebung_020i"})

    # 9. Final type fix for all
    for category in data.get('categories', []):
        for item in category.get('data', []):
            term = item.get('term', '')
            if '_AX' in term or term.startswith(('AX_', 'AW_', 'AB_', 'AD_', 'AL_', 'AS_', 'AI_', 'AE_', 'ASR_', 'AUDI_', 'AUI_', 'ADI_', 'ALI_', 'AULI_', 'AR_', 'ALR_', 'A2X_')):
                item['type'] = 'adapter'
    # 12. Add ISOBUS UT Blocks (New Category)
    cat_isobus = find_category(data, 'cat_isobus')
    if not cat_isobus:
        cat_isobus = {"id": "cat_isobus", "title": "ISOBUS UT (Client)", "data": []}
        data['categories'].append(cat_isobus)

    isobus_blocks = [
        ("Q_ActiveMask", "Change Active Mask"),
        ("Q_Attribute", "Change Attribute"),
        ("Q_BackgroundColour", "Change Background Colour"),
        ("Q_BackgroundColourAux", "Change Background Colour (Aux)"),
        ("Q_ChangeObjectLabel", "Change Object Label"),
        ("Q_ChangePolygonPoint", "Change Polygon Point"),
        ("Q_ChangePolygonScale", "Change Polygon Scale"),
        ("Q_ChildLocation", "Change Child Location"),
        ("Q_ChildPosition", "Change Child Position"),
        ("Q_CtrlAudioSignal", "Control Audio Signal"),
        ("Q_EndPoint", "Change End Point"),
        ("Q_ESC", "ESC Command"),
        ("Q_ExecuteExtendedMacro", "Execute Extended Macro"),
        ("Q_ExecuteMacro", "Execute Macro"),
        ("Q_FillAttributes", "Change Fill Attributes"),
        ("Q_FontAttributes", "Change Font Attributes"),
        ("Q_GetAttribute", "Get Attribute Value"),
        ("Q_GraphicsContext", "Graphics Context"),
        ("Q_LineAttributes", "Change Line Attributes"),
        ("Q_ListItem", "Change List Item"),
        ("Q_LockUnlockMask", "Lock/Unlock Mask"),
        ("Q_NumericValue", "Change Numeric Value"),
        ("Q_NumericValue_AUDI", "Change Numeric Value (AUDI Adapter)"),
        ("Q_NumericValueAux", "Change Numeric Value (Aux)"),
        ("Q_ObjEnableDisable", "Enable/Disable Object"),
        ("Q_ObjHideShow", "Hide/Show Object"),
        ("Q_ObjSelectInput", "Select Input Object"),
        ("Q_Priority", "Change Priority"),
        ("Q_SelectActiveWorkingSet", "Select Active Working Set"),
        ("Q_SelectColourMap", "Select Colour Map"),
        ("Q_SetAudioVolume", "Set Audio Volume"),
        ("Q_Size", "Change Size"),
        ("Q_SoftKeyMask", "Change Soft Key Mask"),
        ("Q_StringValue", "Change String Value")
    ]

    for term, mean in isobus_blocks:
        # 1. Remove from other categories to avoid duplicates
        for cat in data['categories']:
            if cat['id'] == 'cat_isobus': continue
            existing = find_item(cat, term)
            if existing:
                cat['data'].remove(existing)
        
        # 2. Add/Update in cat_isobus
        link = f'{base_url}Bibliotheken/ExternalLibraries/isobus/UT/Q/{term}.html'
        # Check specific exercises (simplified map, or let scan find them next time)
        # Using a few known ones
        ex = ""
        if term == "Q_NumericValue": ex = "Uebung_009, Uebung_010..." 
        
        update_or_add(cat_isobus, {"term": term, "link": link, "mean": mean, "title": f"ISOBUS UT Command: {mean}", "type": "io", "ex": ex})

    return data

def make_exercises_clickable(data):
    for category in data.get('categories', []):
        for item in category.get('data', []):
            ex_str = item.get('ex', '')
            if ex_str and '<a href=' not in ex_str:
                exercises = [e.strip() for e in ex_str.split(',')]
                links = []
                for ex in exercises:
                    if not ex: continue
                    path = "test_AX/Uebungen_doc/" if '_AX' in ex else "test_B/Uebungen_doc/"
                    links.append(f'<a href="{ex_base_url}{path}{ex}.html" target="_blank">{ex}</a>')
                item['ex'] = ', '.join(links)
    return data

def main():
    if not os.path.exists(file_path): return
    try:
        data = load_json(file_path)
        data = modify_data(data)
        data = make_exercises_clickable(data)
        save_json(file_path, data)
        print("Done.")
    except Exception as e: print(f"Error: {e}")

if __name__ == "__main__":
    main()