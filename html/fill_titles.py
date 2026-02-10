import json
import os

file_path = 'html/Abkuerzungen_und_Bedeutungen.json'

# Mappings for specific terms to provide high-quality titles
term_title_map = {
    # Data Types
    "BOOL": "Boolesche Variable",
    "QUARTER": "2-Bit-Variable",
    "BYTE": "Byte (8 Bit)",
    "WORD": "Wort (16 Bit)",
    "DWORD": "Doppelwort (32 Bit)",
    "LWORD": "Langwort (64 Bit)",
    "SINT": "Kurze Ganzzahl (8 Bit)",
    "INT": "Ganzzahl (16 Bit)",
    "DINT": "Doppelganzzahl (32 Bit)",
    "LINT": "Lange Ganzzahl (64 Bit)",
    "USINT": "Vorzeichenlose kurze Ganzzahl (8 Bit)",
    "UINT": "Vorzeichenlose Ganzzahl (16 Bit)",
    "UDINT": "Vorzeichenlose Doppelganzzahl (32 Bit)",
    "ULINT": "Vorzeichenlose lange Ganzzahl (64 Bit)",
    "REAL": "Gleitkommazahl (32 Bit)",
    "LREAL": "Gleitkommazahl (64 Bit)",
    "DATE": "Datum",
    "TIME": "Zeitdauer",
    "TIME_OF_DAY": "Uhrzeit",
    "TOD": "Uhrzeit",
    "DATE_AND_TIME": "Datum und Uhrzeit",
    "DT": "Datum und Uhrzeit",
    "CHAR": "Zeichen",
    "WCHAR": "Breites Zeichen",
    "STRING": "Zeichenkette",
    "WSTRING": "Breite Zeichenkette",
    
    # Logic
    "NOT": "Bitweises NICHT",
    "AND": "Bitweises UND",
    "OR": "Bitweises ODER",
    "XOR": "Bitweises Exklusiv-ODER",
    
    # Arithmetic
    "ADD": "Addition",
    "SUB": "Subtraktion",
    "MUL": "Multiplikation",
    "DIV": "Division",
    "MOD": "Modulo",
    "MOVE": "Zuweisung",
    
    # Comparison
    "GT": "Größer als",
    "GE": "Größer oder gleich",
    "EQ": "Gleich",
    "LE": "Kleiner oder gleich",
    "LT": "Kleiner als",
    "NE": "Ungleich",
    
    # Selection
    "SEL": "Binäre Auswahl",
    "MAX": "Maximum",
    "MIN": "Minimum",
    "LIMIT": "Begrenzer",
    "MUX": "Multiplexer",
    
    # Counters
    "CTU": "Vorwärtszähler",
    "CTD": "Rückwärtszähler",
    "CTUD": "Vor-/Rückwärtszähler",
    
    # Timers
    "TON": "Einschaltverzögerung",
    "TOF": "Ausschaltverzögerung",
    "TP": "Impulsgeber",
    
    # Flip-Flops
    "RS": "Bistabiles Element (Rücksetzvorrang)",
    "SR": "Bistabiles Element (Setzvorrang)",
    "R_TRIG": "Flankenerkennung (steigend)",
    "F_TRIG": "Flankenerkennung (fallend)",
}

def clean_term(term):
    """Removes prefixes like F_ or E_ for mapping lookup."""
    if not term:
        return ""
    
    clean = term
    # Remove common prefixes for lookup
    prefixes = ["F_", "E_", "FB_"]
    for p in prefixes:
        if clean.startswith(p):
            clean = clean[len(p):]
            break # Remove only one prefix
            
    # Handle suffixes or variants if needed, but simple prefix removal is usually enough
    # for mapping F_ADD to ADD
    
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
                    current_title = item.get("title", "").strip()
                    term = item.get("term", "").strip()
                    mean = item.get("mean", "").strip()
                    
                    if not current_title:
                        new_title = ""
                        
                        # 1. Try exact map
                        if term in term_title_map:
                            new_title = term_title_map[term]
                        
                        # 2. Try cleaned map (e.g. F_ADD -> ADD -> Addition)
                        if not new_title:
                            clean = clean_term(term)
                            if clean in term_title_map:
                                new_title = term_title_map[clean]
                        
                        # 3. Handle Adapter specific patterns (AX_...)
                        if not new_title and term.startswith("AX_"):
                            # If it's an adapter, often "Adapter Interface for [Base]"
                            base_term = term[3:] # remove AX_
                            base_clean = clean_term(base_term)
                            if base_clean in term_title_map:
                                new_title = f"{term_title_map[base_clean]} (Adapter)"
                            elif base_term in term_title_map:
                                new_title = f"{term_title_map[base_term]} (Adapter)"
                            else:
                                # Generic Adapter fallback
                                new_title = f"{base_term} Adapter"

                        # 4. Fallback to 'mean' if it looks like a title (not too long description)
                        if not new_title:
                            if mean and len(mean) < 50: # Arbitrary length check
                                new_title = mean
                            elif term:
                                new_title = term # Last resort: just use the term

                        if new_title:
                            item["title"] = new_title
                            updated_count += 1
                            # print(f"Updated '{term}': '{new_title}'")

    print(f"Updated {updated_count} entries.")
    
    try:
        with open(path, 'w', encoding='utf-8') as f:
            json.dump(content, f, indent=3, ensure_ascii=False)
        print("File saved successfully.")
    except Exception as e:
        print(f"Error saving JSON: {e}")

if __name__ == "__main__":
    update_json(file_path)
