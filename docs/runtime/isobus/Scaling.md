# Scaling


## Grundlegendes

Ja, im **ISOBUS-Standard ISO 11783-6** (Teil 6: **Virtual Terminal**) ist das **Skalieren der Anbaugerätemasken** tatsächlich dem **Anbaugerät (Implement) zugeordnet** und nicht dem virtuellen Terminal (VT).  

### Hintergrund:
- **ISO 11783-6** definiert die Kommunikation zwischen dem **Virtuellen Terminal (VT)** und den angeschlossenen **Anbaugeräten (Implements)**.  
- Die **Darstellung der Benutzeroberfläche** (Masken, Symbole, Texte) wird vom Anbaugerät über **Object Pools** an das VT übertragen.  
- Das **Skalieren** der Masken ist notwendig, um die korrekte Darstellung auf unterschiedlichen VT-Bildschirmgrößen und Auflösungen zu gewährleisten.  

### Zuständigkeit für das Skalieren:
- **Das Anbaugerät ist verantwortlich** für die Skalierung seiner Masken, da es die **Object Pools** bereitstellt und die logische Struktur der Benutzeroberfläche definiert.  
- Das VT führt die Skalierung nicht eigenständig durch, sondern nutzt die vom Anbaugerät gelieferten Daten.  
- Falls das VT eine andere Auflösung hat als vom Anbaugerät erwartet, muss das Anbaugerät die **Skalierungsfaktoren anpassen** (z. B. durch dynamische Generierung der Object Pools oder Nutzung von **Scaled Objects**).  

### Praktische Umsetzung:
- Das Anbaugerät kann **skalierbare Objekte** (z. B. **Softkeys, Zahlenfelder, Grafiken**) bereitstellen.  
- Die **VT-Auflösung** wird im **Device-Descriptor** kommuniziert, sodass das Anbaugerät die Masken entsprechend anpassen kann.  
- Falls keine automatische Skalierung erfolgt, kann es zu Darstellungsproblemen kommen (z. B. abgeschnittene Elemente auf kleinen Displays).  

### Fazit:
Die ISOBUS-Norm weist die Verantwortung für das Skalieren der Masken klar dem **Anbaugerät** zu, während das VT primär für die korrekte Darstellung der übermittelten Daten zuständig ist. Dies ermöglicht eine flexible Anpassung an verschiedene Terminalgrößen, erfordert aber eine korrekte Implementierung seitens der Anbaugeräte-Hersteller.  

## **Skalierungsregeln für ISOBUS-Objekte (ISO 11783-6)**  

Diese Analyse beschreibt die Skalierungslogik für ISOBUS-Objekte basierend auf **Objekt-ID-Bereichen** gemäß der Referenztabelle. Die Regeln unterscheiden zwischen *DataMask* (skalierte Darstellung) und *SoftkeyMask/Auxiliary* (zentrierte oder kontextabhängige Behandlung).

---

### **Kernprinzipien**  
1. **DataMask-Objekte** (z. B. Inputs, Outputs, Grafiken):  
   - Immer skaliert (Beispiele: `InputNumber: 9000–9999`, `LinearBargraph: 18000–18599`)  
2. **SoftkeyMask/Auxiliary-Objekte**:  
   - Zentriert (keine Skalierung, z. B. `0: Working Set Object`) oder haben spezielle Regeln (z. B. `5000–5999: Softkey-Buttons`).
3. **Hybrid-Objekte** (getrennte ID-Bereiche):  
   - Die Skalierung hängt vom **Bereich der Objekt-ID** ab:  
     - **DataMask-Variante**: Skalierung aktiv (z. B. `11000–11499: OutputString`).  
     - **SoftkeyMask-Variante**: Skalierung deaktiviert oder anders behandelt (z. B. `11500–11999: OutputString`).

---

### **Kritische Punkte & Handlungsempfehlungen**  

#### **1. Überschneidungen und Kontextabhängigkeit**  
- **Problem**:  
  - Objekte wie `Container` oder `OutputString` existieren in beiden Masken, aber mit unterschiedlichen ID-Bereichen (z. B. `11000–11499` vs. `11500–11999`).  
  - **Frage**: Darf ein `OutputString` mit ID `11000` (eigentlich DataMask) auch in einer *SoftkeyMask* verwendet werden?  
    - *ISO 11783-6-Regel*: Die Maskenzugehörigkeit wird primär durch den **Parent-Object-Kontext** definiert (z. B. ein `OutputString` in einem `SoftKeyMask`-Container). Die ID-Bereiche sind **empfohlene Defaults**, aber nicht zwingend.  
  - **Empfehlung**:  
    - Im Zweifel den **Parent-Object-Typ** prüfen (z. B. `SoftKeyMask`-Container → Zentrierung).  
    - Bei abweichenden IDs ein **Warning-Log** ausgeben, aber Skalierung anhand des Kontexts durchführen.   

#### **2. Skalierungsausnahme:**  
- **Besonderheit**:  
  - Die **PictureGraphic**-Objekte im SoftkeyMask-Bereich (`20500–20999`) sind als *Working Set Bitmaps* deklariert – im Gegensatz zur DataMask-Variante (`20000–20499`).  
  - **Warum "Scaling" trotzdem?**  
    - Diese Bitmaps werden zwar als Teil des *Working Sets* behandelt, unterliegen aber dennoch einer **begrenzten Skalierung** (z. B. für Auflösungsanpassungen oder Symbolgrößen-Steuerung).  
    - *Unterschied zur DataMask*: Die Skalierung ist hier **nicht viewport-relativ**, sondern folgt internen Regeln (z. B. feste Skalierungsfaktoren für Menü-Icons).  

#### **3. Auxiliary Functions (`31000–31999`) – Zentrierungspflicht**  
- **Problem**:  
  - Auxiliary-Objekte müssen laut Norm **immer zentriert** werden (keine Skalierung).  
  - **Risiko**: Wenn ein Auxiliary-Object fälschlich im DataMask-Bereich platziert wird (z. B. ID `31500`), könnte die Skalierung die Darstellung brechen.  

#### **4. Fehlende Klarheit bei "Working Set Object" (ID 0)**  
- **Besonderheit**:  
  - Das "Working Set Object" (ID 0) ist **immer zentriert** und gilt nur für die *SoftkeyMask*.  
  - **Achtung**: Wenn ein DataMask-Container fälschlich ID 0 referenziert, sollte dies als Fehler behandelt werden.  

---

### **Hinweise zur Anwendung**  
- **Pfeile (→)**: Markieren korrespondierende ID-Bereiche für Hybrid-Objekte.  
- **"x"**: Keine Zuordnung in diesem Kontext.  
- **ISO-Konformität**: Die Tabelle folgt ISO 11783-6, wobei die Skalierungslast beim Anbaugerät liegt.  

Die strikte Einhaltung der ID-Bereiche durch das Anbaugerät ist entscheidend. 

## **Tabelle**  

| DATA MASK                                |         | SOFTKEY MASK & AUX                             |
|------------------------------------------|---------|------------------------------------------------|
| x                                        |         | 0 -    0 - Centering - Working set object      |
| 1000 - 1999 - Scaling - DataMask         |         | x                                              |
| 2000 - 2999 - Scaling - AlarmMask        |         |                                                |
| 3000 - 3499 - Scaling - Container        | →       | 3500 - 3999 - Scaling - Container              |
| 6000 - 6999 - Scaling - Button           | →       | 5000 - 5999 - Centering – Softkeys             |
| 7000 - 7999 - Scaling - InputBoolean     |         |                                                |
| 8000 - 8999 - Scaling - InputString      |         |                                                |
| 9000 - 9999 - Scaling - InputNumber      |         |                                                |
| 10000 - 10999 - Scaling - InputList      |         |                                                |
| 11000 - 11499 - Scaling - OutputString   | →       | 11500 - 11999 - Scaling – OutputString         |
| 12000 - 12499 - Scaling - OutputNumber   | →       | 12500 - 12999 - Scaling - OutputNumber         |
| 13000 - 13499 - Scaling - Line           | →       | 13500 - 13999 - Scaling - Line                 |
| 14000 - 14499 - Scaling - Rectangle      | →       | 14500 - 14999 - Scaling - Rectangle            |
| 15000 - 15499 - Scaling - Ellipse        | →       | 15500 - 15999 - Scaling - Ellipse              |
| 16000 - 16499 - Scaling - Polygon        | →       | 16500 - 16999 - Scaling – Polygon              |
| 17000 - 17599 - Scaling - Meter          |         |                                                |
| 18000 - 18599 - Scaling - LinearBargraph |         |                                                |
| 19000 - 19599 - Scaling - ArchedBargraph |         |                                                |
| 20000 - 20499 - Scaling - PictureGraphic | →       | 20500 - 20999 - Scaling - Working set bitmaps  |
| 23000 - 23499 - Scaling - FontAttributes | →       | 23500 - 23999 - Scaling - FontAttributes       |
| 24000 - 24499 - Scaling - LineAttributes | →       | 24500 - 24900 - Scaling - LineAttributes       |
| 25000 - 25499 - Scaling - FillAttributes | →       | 25500 - 25999 - Scaling – FillAttributes       |
| 30000 - 30999 - Scaling – OutputList     |         |                                                |
|                                          |         | 31000 - 31999 - Centering - Auxiliary function |  
---