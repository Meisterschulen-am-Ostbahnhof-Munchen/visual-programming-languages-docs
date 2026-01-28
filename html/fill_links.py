import json
import os

file_path = 'html/Abkürzungen und Bedeutungen.json'

# Mappings for term -> (ext_de, ext_en)
# Focusing on Wikipedia as the primary safe source
link_map = {
    # Data Types
    "BOOL": ("https://de.wikipedia.org/wiki/Boolean", "https://en.wikipedia.org/wiki/Boolean_data_type"),
    "BYTE": ("https://de.wikipedia.org/wiki/Datenwort", "https://en.wikipedia.org/wiki/Word_(computer_architecture)"),
    "WORD": ("https://de.wikipedia.org/wiki/Datenwort", "https://en.wikipedia.org/wiki/Word_(computer_architecture)"),
    "DWORD": ("https://de.wikipedia.org/wiki/Datenwort", "https://en.wikipedia.org/wiki/Word_(computer_architecture)"),
    "LWORD": ("https://de.wikipedia.org/wiki/Datenwort", "https://en.wikipedia.org/wiki/Word_(computer_architecture)"),
    
    "SINT": ("https://de.wikipedia.org/wiki/Ganzzahl", "https://en.wikipedia.org/wiki/Integer_(computer_science)"),
    "INT": ("https://de.wikipedia.org/wiki/Ganzzahl", "https://en.wikipedia.org/wiki/Integer_(computer_science)"),
    "DINT": ("https://de.wikipedia.org/wiki/Ganzzahl", "https://en.wikipedia.org/wiki/Integer_(computer_science)"),
    "LINT": ("https://de.wikipedia.org/wiki/Ganzzahl", "https://en.wikipedia.org/wiki/Integer_(computer_science)"),
    "USINT": ("https://de.wikipedia.org/wiki/Ganzzahl", "https://en.wikipedia.org/wiki/Integer_(computer_science)"),
    "UINT": ("https://de.wikipedia.org/wiki/Ganzzahl", "https://en.wikipedia.org/wiki/Integer_(computer_science)"),
    "UDINT": ("https://de.wikipedia.org/wiki/Ganzzahl", "https://en.wikipedia.org/wiki/Integer_(computer_science)"),
    "ULINT": ("https://de.wikipedia.org/wiki/Ganzzahl", "https://en.wikipedia.org/wiki/Integer_(computer_science)"),
    
    "REAL": ("https://de.wikipedia.org/wiki/Gleitkommazahl", "https://en.wikipedia.org/wiki/Floating-point_arithmetic"),
    "LREAL": ("https://de.wikipedia.org/wiki/Gleitkommazahl", "https://en.wikipedia.org/wiki/Floating-point_arithmetic"),
    
    "STRING": ("https://de.wikipedia.org/wiki/Zeichenkette", "https://en.wikipedia.org/wiki/String_(computer_science)"),
    "WSTRING": ("https://de.wikipedia.org/wiki/Zeichenkette", "https://en.wikipedia.org/wiki/String_(computer_science)"),
    "CHAR": ("https://de.wikipedia.org/wiki/Zeichen_(Computer)", "https://en.wikipedia.org/wiki/Character_(computing)"),
    "WCHAR": ("https://de.wikipedia.org/wiki/Breitzeichen", "https://en.wikipedia.org/wiki/Wide_character"),

    # Time/Date
    "TIME": ("https://de.wikipedia.org/wiki/Zeit", "https://en.wikipedia.org/wiki/Time"),
    "DATE": ("https://de.wikipedia.org/wiki/Datum_(Kalender)", "https://en.wikipedia.org/wiki/Calendar_date"),
    "TIME_OF_DAY": ("https://de.wikipedia.org/wiki/Uhrzeit", "https://en.wikipedia.org/wiki/Time_of_day"),
    "TOD": ("https://de.wikipedia.org/wiki/Uhrzeit", "https://en.wikipedia.org/wiki/Time_of_day"),
    "DATE_AND_TIME": ("https://de.wikipedia.org/wiki/ISO_8601", "https://en.wikipedia.org/wiki/ISO_8601"),
    "DT": ("https://de.wikipedia.org/wiki/ISO_8601", "https://en.wikipedia.org/wiki/ISO_8601"),
    
    # Logic
    "AND": ("https://de.wikipedia.org/wiki/Und-Gatter", "https://en.wikipedia.org/wiki/AND_gate"),
    "OR": ("https://de.wikipedia.org/wiki/Oder-Gatter", "https://en.wikipedia.org/wiki/OR_gate"),
    "NOT": ("https://de.wikipedia.org/wiki/Nicht-Gatter", "https://en.wikipedia.org/wiki/NOT_gate"),
    "XOR": ("https://de.wikipedia.org/wiki/XOR-Gatter", "https://en.wikipedia.org/wiki/XOR_gate"),
    
    # Arithmetic
    "ADD": ("https://de.wikipedia.org/wiki/Addition", "https://en.wikipedia.org/wiki/Addition"),
    "SUB": ("https://de.wikipedia.org/wiki/Subtraktion", "https://en.wikipedia.org/wiki/Subtraction"),
    "MUL": ("https://de.wikipedia.org/wiki/Multiplikation", "https://en.wikipedia.org/wiki/Multiplication"),
    "DIV": ("https://de.wikipedia.org/wiki/Division_(Mathematik)", "https://en.wikipedia.org/wiki/Division_(mathematics)"),
    "MOD": ("https://de.wikipedia.org/wiki/Division_mit_Rest", "https://en.wikipedia.org/wiki/Modulo_operation"),
    
    # Comparison
    "EQ": ("https://de.wikipedia.org/wiki/Vergleichsoperator", "https://en.wikipedia.org/wiki/Relational_operator"),
    "NE": ("https://de.wikipedia.org/wiki/Vergleichsoperator", "https://en.wikipedia.org/wiki/Relational_operator"),
    "GT": ("https://de.wikipedia.org/wiki/Vergleichsoperator", "https://en.wikipedia.org/wiki/Relational_operator"),
    "LT": ("https://de.wikipedia.org/wiki/Vergleichsoperator", "https://en.wikipedia.org/wiki/Relational_operator"),
    "GE": ("https://de.wikipedia.org/wiki/Vergleichsoperator", "https://en.wikipedia.org/wiki/Relational_operator"),
    "LE": ("https://de.wikipedia.org/wiki/Vergleichsoperator", "https://en.wikipedia.org/wiki/Relational_operator"),

    # Selection
    "SEL": ("https://de.wikipedia.org/wiki/Multiplexer", "https://en.wikipedia.org/wiki/Multiplexer"),
    "MUX": ("https://de.wikipedia.org/wiki/Multiplexer", "https://en.wikipedia.org/wiki/Multiplexer"),
    "LIMIT": ("https://de.wikipedia.org/wiki/Begrenzer", "https://en.wikipedia.org/wiki/Limiter"),
    "MAX": ("https://de.wikipedia.org/wiki/Extremwert", "https://en.wikipedia.org/wiki/Maxima_and_minima"),
    "MIN": ("https://de.wikipedia.org/wiki/Extremwert", "https://en.wikipedia.org/wiki/Maxima_and_minima"),
    
    # Flip-Flops
    "RS": ("https://de.wikipedia.org/wiki/Flipflop#RS-Flipflop", "https://en.wikipedia.org/wiki/Flip-flop_(electronics)#SR_latch"),
    "SR": ("https://de.wikipedia.org/wiki/Flipflop#RS-Flipflop", "https://en.wikipedia.org/wiki/Flip-flop_(electronics)#SR_latch"),
}

def clean_term(term):
    """Removes prefixes like F_ or E_ for mapping lookup."""
    if not term:
        return ""
    clean = term
    prefixes = ["F_", "E_", "FB_"]
    for p in prefixes:
        if clean.startswith(p):
            clean = clean[len(p):]
            break
    # Remove _2, _3 suffixes for logic gates (e.g. AND_2 -> AND)
    if "_" in clean:
        parts = clean.split('_')
        if parts[0] in ["AND", "OR", "XOR", "ADD", "MUL", "SUB", "DIV"]:
            clean = parts[0]
            
    return clean

def update_json(path):
    print(f"Loading {path}...")
    try:
        with open(path, 'r', encoding='utf-8') as f:
            content = json.load(f)
    except Exception as e:
        print(f"Error loading JSON: {e}")
        return

    updated_count = 0
    
    if "categories" in content:
        for category in content["categories"]:
            if "data" in category:
                for item in category["data"]:
                    term = item.get("term", "").strip()
                    ext_de = item.get("ext_de", "").strip()
                    ext_en = item.get("ext_en", "").strip()
                    
                    # Determine links if missing
                    new_de = ext_de
                    new_en = ext_en
                    
                    # 1. Exact match
                    if term in link_map:
                        mapped_de, mapped_en = link_map[term]
                        if not new_de: new_de = f'<a href="{mapped_de}" target="_blank">Wikipedia (DE)</a>'
                        if not new_en: new_en = f'<a href="{mapped_en}" target="_blank">Wikipedia (EN)</a>'
                    
                    # 2. Cleaned match
                    else:
                        clean = clean_term(term)
                        if clean in link_map:
                            mapped_de, mapped_en = link_map[clean]
                            if not new_de: new_de = f'<a href="{mapped_de}" target="_blank">Wikipedia (DE)</a>'
                            if not new_en: new_en = f'<a href="{mapped_en}" target="_blank">Wikipedia (EN)</a>'
                    
                    # Apply changes if any
                    if new_de != ext_de or new_en != ext_en:
                        item["ext_de"] = new_de
                        item["ext_en"] = new_en
                        updated_count += 1

    print(f"Updated links for {updated_count} entries.")
    
    try:
        with open(path, 'w', encoding='utf-8') as f:
            json.dump(content, f, indent=3, ensure_ascii=False)
        print("File saved successfully.")
    except Exception as e:
        print(f"Error saving JSON: {e}")

if __name__ == "__main__":
    update_json(file_path)
