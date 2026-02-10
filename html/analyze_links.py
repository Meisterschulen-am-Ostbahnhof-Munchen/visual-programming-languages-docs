import json

file_path = 'html/Abkuerzungen_und_Bedeutungen.json'

try:
    with open(file_path, 'r', encoding='utf-8') as f:
        data = json.load(f)

    print(f"{'Category':<20} | {'Term':<30} | {'Missing DE':<10} | {'Missing EN':<10}")
    print("-" * 80)
    
    count = 0
    for cat in data.get('categories', []):
        cat_title = cat.get('title', 'Unknown')
        for item in cat.get('data', []):
            term = item.get('term', '')
            ext_de = item.get('ext_de', '')
            ext_en = item.get('ext_en', '')
            
            if not ext_de or not ext_en:
                if count < 20: # Limit output
                    print(f"{cat_title[:20]:<20} | {term[:30]:<30} | {'Yes' if not ext_de else 'No':<10} | {'Yes' if not ext_en else 'No':<10}")
                count += 1
    
    print("-" * 80)
    print(f"Total entries with at least one missing external link: {count}")

except Exception as e:
    print(f"Error: {e}")
